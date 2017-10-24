ULONG PatternSearch(std::string sModuleName, PBYTE pbPattern, std::string sMask, ULONG uCodeBase, ULONG uSizeOfCode)
{
	BOOL bPatternDidMatch = FALSE;
	HMODULE hModule = GetModuleHandle((LPCSTR)sModuleName.c_str());

	if (!hModule)
		return 0x0;

	PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(hModule);
	PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS(LONG(hModule) + pDsHeader->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;

	if (uCodeBase == 0x0)
		uCodeBase = (ULONG)hModule + pOptionalHeader->BaseOfCode;

	if (uSizeOfCode == 0x0)
		uSizeOfCode = pOptionalHeader->SizeOfCode;

	ULONG uArraySize = sMask.length();

	if (!uCodeBase || !uSizeOfCode || !uArraySize)
		return 0x0;

	for (size_t i = uCodeBase; i <= uCodeBase + uSizeOfCode; i++)
	{
		for (size_t t = 0; t < uArraySize; t++)
		{
			if (*((PBYTE)i + t) == pbPattern[t] || sMask.c_str()[t] == '?')
				bPatternDidMatch = TRUE;

			else
			{
				bPatternDidMatch = FALSE;
				break;
			}
		}

		if (bPatternDidMatch)
			return i;
	}

	return 0x0;
}

void SetClanTag(const char* tag, const char* name)
{
	static DWORD dwClantag = PatternSearch("engine", (PBYTE)"\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15\x00\x00\x00\x00\x6A\x24\x8B\xC8\x8B\x30", "xxxxxxxxx????xxxxxx", NULL, NULL);
	static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)> (uintptr_t(dwClantag));

	pSetClanTag(tag, name);
}