typedef void*(*CreateInterface)(const char*, int*);
void* GetInterface(const char* interfaceName, const char* ptrName, CreateInterface pInterface) {
		// den här funktionen ska tydligen få tag i alla interfaces automatiskt.
		char szDebugString[1024];

		std::string sinterface = "";
		std::string interfaceVersion = "0";

		for (int i = 0; i <= 99; i++) {
			sinterface = interfaceName;
			sinterface += interfaceVersion;
			sinterface += std::to_string(i);

			void* funcPtr = pInterface(sinterface.c_str(), NULL);

			if ((DWORD)funcPtr != 0x0) {

				sprintf_s(szDebugString, "%s: 0x%x (%s%s%i)", ptrName, (DWORD)funcPtr, interfaceName, interfaceVersion.c_str(), i);
				return funcPtr;
			}
			if (i >= 99 && interfaceVersion == "0") {
				interfaceVersion = "00";
				i = 0;
			}
			else if (i >= 99 && interfaceVersion == "00") {
				sprintf_s(szDebugString, "%s: 0x%x (error)", ptrName, (DWORD)funcPtr);
			}
		}
		// jupp.. det gjorde den. ;)
		return 0;
	}