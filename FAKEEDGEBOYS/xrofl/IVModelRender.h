enum EType {
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS = 1,
	OVERRIDE_DEPTH_WRITE = 2,
	OVERRIDE_WHATEVER = 3
};

typedef float matrix3x4[3][4];

struct ModelRender_t {
	Vector origin;
	Vector angles;
	C_BaseEntity *pRenderable;
	const model_t *pModel;
	const matrix3x4 *pModelToWorld;
	const matrix3x4 *pLightingOffset;
	const Vector *pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	unsigned short instance;
	ModelRender_t() {
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};

class IVModelRender {
public:

	virtual void Func0();
	virtual void ForcedMaterialOverride(IMaterial *newMaterial, EType nOverrideType = OVERRIDE_NORMAL, int unknown = NULL);
	virtual bool IsForcedMaterialOverride();
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
};