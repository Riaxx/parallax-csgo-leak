class IVDebugOverlay {
public:
	virtual void Func0();
	virtual void Func1();
	virtual void Func2();
	virtual void Func3();
	virtual void Func4();
	virtual void Func5();
	virtual void Func6();
	virtual void AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b,bool noDepthTest, float duration);
	virtual void Func8();
	virtual void Func9();
	virtual void Func10();
	virtual void Func11();
	virtual void Func12();
	virtual int ScreenPosition(const Vector& Pos1, const Vector& Pos2);
};