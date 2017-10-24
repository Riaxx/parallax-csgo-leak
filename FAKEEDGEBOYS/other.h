bool DataCompare(const BYTE* pData, const BYTE* bMask, const char* pszMask)
{
	for (; *pszMask; ++pszMask, ++pData, ++bMask)
		if (*pszMask == 'x' && *pData != *bMask)
			return false;
	return (*pszMask == 0);
}

DWORD dwFindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char *pszMask)
{
	for (DWORD i = 0; i<dwLen; i++)
		if (DataCompare((BYTE*)(dwAddress + i), bMask, pszMask))
			return dwAddress + i;

	return 0;
}

MODULEENTRY32* GetModuleInfo(char *szModule) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	static MODULEENTRY32 me32;
	ZeroMemory(&me32, sizeof(MODULEENTRY32));
	me32.dwSize = sizeof(MODULEENTRY32);

	Module32First(hSnapshot, &me32);
	while (Module32Next(hSnapshot, &me32))
	{
		if (!strcmp(szModule, me32.szModule))
		{
			CloseHandle(hSnapshot);
			return &me32;
		}
	}

	CloseHandle(hSnapshot);
	return 0;
}

DWORD zFindPattern(char *szModule, BYTE *bMask, char *pszMask) {
	MODULEENTRY32 *me32 = GetModuleInfo(szModule);
	if (!me32)
		return 0;

	DWORD dwAddress = (DWORD)me32->modBaseAddr;
	DWORD dwLen = (DWORD)me32->modBaseSize;

	return dwFindPattern(dwAddress, dwLen, bMask, pszMask);
}

