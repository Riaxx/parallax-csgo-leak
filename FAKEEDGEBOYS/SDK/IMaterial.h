enum EFlags {
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),
	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_MULTIPASS = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	MATERIAL_VAR_NOALPHAMOD = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
};



class IMaterial {
public:
	virtual const char* GetName();
	virtual const char* GetTextureGroupName();
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
	virtual void IncrementReferenceCount();
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
	virtual void Func26();
	virtual void AlphaModulate(float alpha);
	virtual void ColorModulate(float r, float g, float b);
	virtual void SetVarFlag(EFlags flag, bool on);
	virtual void GetVarFlag(EFlags flag);
	virtual void Func31();
	virtual void Func32();
	virtual void Func33();
	virtual void Func34();
	virtual void Func35();
	virtual void Func36();
	virtual void Func37();
	virtual void Func38();
	virtual void Func39();
	virtual void Func40();
	virtual bool IsErrorMaterial() const = 0;
};