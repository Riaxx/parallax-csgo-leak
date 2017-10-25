/*MIT License

Copyright (c) namazso 2017

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
#include "main.h"
CNetworkedVariableManager pOffsets;

void CNetworkedVariableManager::Init(void)
{
	m_tables.clear();
	m_savedproxy.clear();

	ClientClass *clientClass = pValve->pClient->GetAllClasses(); //g_InterfaceManager->Client()->GetOriginalMethod<GetAllClasses_t>( INDEX_GETALLCLASSES )( g_InterfaceManager->Client()->thisptr() );

	if (!clientClass)
	{
		return;
	}

	while (clientClass)
	{
		RecvTable *recvTable = clientClass->GetTable();

		m_tables.push_back(recvTable);

		clientClass = clientClass->NextClass();
	}
}

CNetworkedVariableManager::~CNetworkedVariableManager(void)
{
	for (unsigned int i = 0; i < m_savedproxy.size(); i++)
	{
		RecvProp *recvProp = 0;
		GetProp(m_savedproxy[i].szTableName, m_savedproxy[i].szPropName, &recvProp);

		if (!recvProp)
			return;

		recvProp->m_ProxyFn = m_savedproxy[i].SavedProxy;
	}
}

// calls GetProp wrapper to get the absolute offset of the prop
int CNetworkedVariableManager::getOffset(const char *tableName, const char *propName) {
	int offset = GetProp(tableName, propName);

	if (!offset) {
		//	pValve->pCvar->ConsoleColorPrintf(Color(255, 255, 0, 255), "[-] Couldn't find %s from %s.\n", propName, tableName);
		return 0;
	}

	// pValve->pCvar->ConsoleColorPrintf(Color(0, 255, 0, 255), "[+] %s: 0x%X\n", propName, offset);
	return offset;
}


// calls GetProp wrapper to get prop and sets the proxy of the prop
bool CNetworkedVariableManager::HookProp(const char *tableName, const char *propName, RecvVarProxyFn function)
{
	RecvProp *recvProp = 0;
	GetProp(tableName, propName, &recvProp);


	if (!recvProp)
	{
		//add_log("Failed to hook prop: %s from table: %s", propName, tableName);
		return false;
	}

	recvProp->m_ProxyFn = function;

	return true;
}


// wrapper so we can use recursion without too much performance loss
int CNetworkedVariableManager::GetProp(const char *tableName, const char *propName, RecvProp **prop)
{
	RecvTable *recvTable = GetTable(tableName);

	if (!recvTable)
	{
		printf("Failed to find table: %s", tableName);
		return 0;
	}


	int offset = GetProp(recvTable, propName, prop);

	if (!offset)
	{
		printf("Failed to find prop: %s from table: %s", propName, tableName);
		return 0;
	}


	return offset;
}



// uses recursion to return a the relative offset to the given prop and sets the prop param
int CNetworkedVariableManager::GetProp(RecvTable *recvTable, const char *propName, RecvProp **prop)
{
	int extraOffset = 0;

	for (int i = 0; i < recvTable->m_nProps; ++i)
	{
		RecvProp *recvProp = &recvTable->m_pProps[i];


		RecvTable *child = recvProp->m_pDataTable;

		if (child
			&& (child->m_nProps > 0))
		{
			int tmp = GetProp(child, propName, prop);

			if (tmp)
			{
				extraOffset += (recvProp->m_Offset + tmp);
			}
		}


		if (_stricmp(recvProp->m_pVarName, propName))
		{
			continue;
		}


		if (prop)
		{
			*prop = recvProp;
		}

		return (recvProp->m_Offset + extraOffset);
	}

	return extraOffset;
}


RecvTable *CNetworkedVariableManager::GetTable(const char *tableName)
{
	if (m_tables.empty())
	{
		printf("Failed to find table: %s (m_tables is empty)", tableName);

		return 0;
	}


	for each (RecvTable *table in m_tables)
	{
		if (!table)
		{
			continue;
		}


		if (_stricmp(table->m_pNetTableName, tableName) == 0)
		{
			return table;
		}
	}

	return 0;
}

extern void __cdecl SequenceProxyFn(const CRecvProxyData* proxy_data_const, void* entity, void* output);

