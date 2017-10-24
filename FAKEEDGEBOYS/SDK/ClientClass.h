class ClientClass
{
public:

	const char* GetName(void)
	{
		return *(char**)(this + 0x8);
	}
	RecvTable* GetTable()
	{
		return *(RecvTable**)(this + 0xC);
	}
	ClientClass* NextClass()
	{
		return *(ClientClass**)(this + 0x10);
	}
	int GetClassID(void)
	{
		return *(int*)(this + 0x14);
	}
};
/*
class ClientClass
{
public:
	void*			m_pCreateFn;
	void*			m_pCreateEventFn;
	char			*m_pNetworkName;
	RecvTable		*m_pRecvTable;
	ClientClass		*m_pNext;
	int				m_ClassID;
};*/