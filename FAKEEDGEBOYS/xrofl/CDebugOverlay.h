class CDebugOverlay {
public:
	virtual void AddEntityTextOverlay(int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;
	virtual void AddBoxOverlay(const Vector& origin, const Vector& mins, const Vector& max, Vector const& orientation, int r, int g, int b, int a, float duration = 0) = 0;
	virtual void AddSphereOverlay(const Vector& vOrigin, float flRadius, int nTheta, int nPhi, int r, int g, int b, int a, float flDuration = 0) = 0;
	virtual void AddTriangleOverlay(const Vector& p1, const Vector& p2, const Vector& p3, int r, int g, int b, int a, bool noDepthTest, float duration = 0) = 0;
	virtual void AddBoxOverlayNew(const Vector& v1, const Vector& v2, const Vector& v3, const Vector& v4, int r, int g, int b, int a) = 0;
	virtual void AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration = 0) = 0;
	virtual void AddTextOverlay(const Vector& origin, float duration, const char *format, ...) = 0;
	virtual void AddTextOverlay(const Vector& origin, int line_offset, float duration, const char *format, ...) = 0;
	virtual void AddScreenTextOverlay(float flXPos, float flYPos, float flDuration, int r, int g, int b, int a, const char *text) = 0;
	virtual void AddSweptBoxOverlay(const Vector& start, const Vector& end, const Vector& mins, const Vector& max, const Vector & angles, int r, int g, int b, int a, float flDuration = 0) = 0;
	virtual void AddGridOverlay(const Vector& origin) = 0;
	virtual void AddCoordFrameOverlay(const int& frame, float flScale, int vColorTable[3][3] = NULL) = 0;
	virtual int ScreenPosition(const Vector& point, Vector& screen) = 0;
	virtual int ScreenPosition(float flXPos, float flYPos, Vector& screen) = 0;
	virtual void *GetFirst(void) = 0;
	virtual void *GetNext(int *current) = 0;
	virtual void ClearDeadOverlays(void) = 0;
	virtual void ClearAllOverlays() = 0;
	virtual void AddTextOverlayRGB(const Vector& origin, int line_offset, float duration, float r, float g, float b, float alpha, const char *format, ...) = 0;
	virtual void AddTextOverlayRGB(const Vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;
	virtual void AddLineOverlayAlpha(const Vector& origin, const Vector& dest, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
	virtual void AddBoxOverlay2(const Vector& origin, const Vector& mins, const Vector& max, Vector const& orientation, const Color& faceColor, const Color& edgeColor, float duration) = 0;
	virtual void PurgeTextOverlays() = 0;
	virtual void NewOverlay(const Vector& origin1, const Vector& origin2, int a3, int r, int g, int b, int a, int unusedParam) = 0;
private:
	inline void AddTextOverlay(const Vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) {} /* catch improper use of bad interface. Needed because '0' duration can be resolved by compiler to NULL format string (i.e., compiles but calls wrong function) */
};