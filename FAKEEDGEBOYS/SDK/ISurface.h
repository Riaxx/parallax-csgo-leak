enum FontDrawType_t {
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,		// custom generated font - never fall back to asian compatibility mode
	FONTFLAG_BITMAP = 0x800,		// compiled bitmap font - no fallbacks
};

struct CharRenderInfo {
	// Text pos
	int				x, y;
	// Top left and bottom right
	// This is now a pointer to an array maintained by the surface, to avoid copying the data on the 360
	int				textureId;
	int				abcA;
	int				abcB;
	int				abcC;
	int				fontTall;
	// In:
	FontDrawType_t	drawType;
	wchar_t			ch;

	// Out
	bool			valid;
	// In/Out (true by default)
	bool			shouldclip;
};

class ISurface {
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
	virtual void DrawSetColor(Color color);
	virtual void Func15();
	virtual void DrawFilledRect(int x0, int y0, int x1, int y1);
	virtual void Func17();
	virtual void DrawOutlinedRect(int x0, int y0, int x1, int y1);
	virtual void DrawLine(int x0, int y0, int x1, int y1);
	virtual void Func20();
	virtual void Func21();
	virtual void Func22();
	virtual void DrawSetTextFont(DWORD Font);
	virtual void DrawSetTextColor(Color color);
	virtual void Func25();
	virtual void DrawSetTextPos(int x, int y);
	virtual void Func27();
	virtual void DrawPrintText(const wchar_t* text, int textLen, FontDrawType_t drawType = FONT_DRAW_DEFAULT);
	virtual void Func29();
	virtual void Func30();
	virtual void Func31();
	virtual void Func32();
	virtual void Func33();
	virtual int DrawGetTextureId(char const *filename);
	virtual bool DrawGetTextureFile(int id, char *filename, int maxlen);
	virtual void DrawSetTextureFile(int id, const char *filename, int hardwareFilter, bool forceReload);
	virtual void DrawSetTextureRGBA(int id, const unsigned char *rgba, int wide, int tall);
	virtual void DrawSetTexture(int id);
	virtual void DeleteTextureByID(int id);
	virtual void DrawGetTextureSize(int id, int &wide, int &tall);
	virtual void DrawTexturedRect(int x0, int y0, int x1, int y1);
	virtual bool IsTextureIDValid(int id);
	virtual int CreateNewTextureID(bool procedural = false);
	virtual void Func44();
	virtual void Func45();
	virtual void Func46();
	virtual void Func47();
	virtual void Func48();
	virtual void Func49();
	virtual void Func50();
	virtual void Func51();
	virtual void Func52();
	virtual void Func53();
	virtual void Func54();
	virtual void Func55();
	virtual void Func56();
	virtual void Func57();
	virtual void Func58();
	virtual void Func59();
	virtual void Func60();
	virtual void Func61();
	virtual void Func62();
	virtual void Func63();
	virtual void Func64();
	virtual bool UnlockCursor();
	virtual bool LockCursor();
	virtual void Func67();
	virtual void Func68();
	virtual void Func69();
	virtual void Func70();
	virtual DWORD CreateFont();
	virtual bool SetFontGlyphSet(DWORD Font, const char* FontName, int tall, int weight, int blur, int scanlines, EFontFlags flags, int x1 = 0, int x2 = 0);
	virtual void Func73();
	virtual void Func74();
	virtual void Func76();
	virtual void Func77();
	virtual void Func78();
	virtual void Func79();
	virtual void GetTextSize(unsigned long, wchar_t  const*, int &, int &);
	virtual void Func81();
	virtual void Func82();
	virtual void Func83();
	virtual void Func84();
	virtual void Func85();
	virtual void Func86();
	virtual void Func87();
	virtual void Func88();
	virtual void Func89();
	virtual void Func90();
	virtual void Func91();
	virtual void Func92();
	virtual void Func93();
	virtual void Func94();
	virtual void Func95();
	virtual void Func96();
	virtual void Func97();
	virtual void Func98();
	virtual void Func99();
	virtual void Func100();
	virtual void Func101();
	virtual void Func102();
	virtual void DrawOutlinedCircle(int x, int y, int radius, int segments);
	virtual void Func104();
	virtual void Func105();
	virtual void Func106();
	virtual void Func107();
	virtual void Func108();
	virtual void Func109();
	virtual void Func110();
	virtual void Func111();
	virtual void Func112();
	virtual void Func113();
};