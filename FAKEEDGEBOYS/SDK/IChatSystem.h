class ChatMode {
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
	virtual void Func15();
	virtual void Func16();
	virtual void Func17();
	virtual void Func18();
	virtual void Func19();
	virtual void Func20();
	virtual void Func21();
	virtual void Func22();
	virtual void Func23();
	virtual void Func24();
	virtual void Func25();
	virtual void ChatPrintf(int iPlayerIndex, int iFilter, const char* fmt, ...);
	virtual void Func27();
	virtual void Func28();
	virtual void Func29();
	virtual void Func30();
};

class ClientModeShared {
public:
	char pad[28];
	ChatMode* m_pChat;
};