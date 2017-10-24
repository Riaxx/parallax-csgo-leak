#define PRINTF_FORMAT_STRING _Printf_format_string_

class ConVar
{
public:
	void InternalSetString(const char *str)
	{
		typedef void(__thiscall* SetStringFn)(void*, const char *);
		ReadFunc< SetStringFn >(this, 17)(this, str);
	}
	char* GetName()
	{
		typedef char*(__thiscall* SetStringFn)(void*);
		return ReadFunc< SetStringFn >(this, 5)(this);
	}
	void SetValue(const char* value)
	{
		typedef void(__thiscall* SetStringFn)(void*, const char*);
		return  ReadFunc<SetStringFn>(this, 14)(this, value);
	}
	void SetValue(int value)
	{
		typedef void(__thiscall* SetStringFn)(void*, int);
		return ReadFunc<SetStringFn>(this, 16)(this, value);
	}
	char pad_0x0000[0x4]; //0x0000
	ConVar* pNext; //0x0004 
	__int32 bRegistered; //0x0008 
	char* pszName; //0x000C 
	char* pszHelpString; //0x0010 
	__int32 nFlags; //0x0014 
	char pad_0x0018[0x4]; //0x0018
	ConVar* pParent; //0x001C 
	char* pszDefaultValue; //0x0020 
	char* strString; //0x0024 
	__int32 StringLength; //0x0028 
	float fValue; //0x002C 
	__int32 nValue; //0x0030 
	__int32 bHasMin; //0x0034 
	float fMinVal; //0x0038 
	__int32 bHasMax; //0x003C 
	float fMaxVal; //0x0040 
	void* fnChangeCallback; //0x0044 

};//Size=0x0048

class ICvar {
public:
	virtual void Func0();
	virtual void Func1();
	virtual void Func2();
	virtual void Func3();
	virtual void Func4();
	virtual void Func5();
	virtual void Func6();
	virtual void Func7();
	virtual void Func8();
	virtual void Func9();
	virtual void Func10();
	virtual void Func11();
	virtual void Func12();
	virtual void Func13();
	virtual void Func14();
	virtual ConVar* FindVar(const char* getVar);
	virtual void Func16();
	virtual void Func17();
	virtual void Func18();
	virtual void Func19();
	virtual void Func20();
	virtual void Func21();
	virtual void Func22();
	virtual void Func23();
	virtual void Func24();
	virtual void ConsoleColorPrintf(const Color& clr, PRINTF_FORMAT_STRING const char *pFormat, ...);
	virtual void ConsolePrintf(PRINTF_FORMAT_STRING const char *pFormat, ...);
	virtual void ConsoleDPrintf(PRINTF_FORMAT_STRING const char *pFormat, ...);
	virtual void Func28();
	virtual void Func29();
	virtual void Func30();
	virtual void Func31();
	virtual void Func32();
	virtual void Func33();
	virtual void Func34();
	virtual void Func35();
	virtual void Func36();
	virtual void Func37();
};