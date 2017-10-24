#define  Assert( _exp ) ((void)0)
#include <math.h>
enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};



struct cplane_t
{
	Vector  normal;
	float   dist;
	BYTE    type;
	BYTE    signbits;
	BYTE    pad[2];
};
struct csurface_t
{
	const char*             name;
	short                   surfaceProps;
	unsigned short  flags;
};

class IHandleEntity
{
public:
	virtual ~IHandleEntity() {}
	virtual void Func01() = 0;
	virtual void Func02() = 0;
};
class IClientUnknown : public IHandleEntity
{
public:
	virtual PVOID GetCollideable() = 0;
	virtual PVOID GetClientNetworkable() = 0;
	virtual PVOID GetClientRenderable() = 0;
	virtual PVOID GetIClientEntity() = 0;
	virtual C_BaseEntity* GetBaseEntity() = 0;
	virtual PVOID GetClientThinkable() = 0;
	virtual void *class1(void) = 0;
	virtual void *class2(void) = 0;
};

class CBaseTrace
{
public:

	Vector                  startpos;
	Vector                 endpos;
	cplane_t                plane;
	float                   fraction;
	int                             contents;
	unsigned short  dispFlags;
	bool                    allsolid;
	bool                    startsolid;
};



class CGameTrace : public CBaseTrace
{
public:
	bool                    DidHitWorld() const;
	bool                    DidHitNonWorldEntity() const;
	int                     GetEntityIndex() const;
	bool                    DidHit() const;
	bool					IsVisible() const;

public:

	float                   fractionleftsolid;
	csurface_t              surface;
	int                     hitgroup;
	short                   physicsbone;
	unsigned short          worldSurfaceIndex;
	C_BaseEntity*            m_pEnt;
	int                     hitbox;

	CGameTrace() { }

private:
	CGameTrace(const CGameTrace& vOther);
};



typedef CGameTrace trace_t;
typedef float vec_t;
class  VectorAligned : public Vector
{
public:
	inline VectorAligned(void) {};
	inline VectorAligned(vec_t X, vec_t Y, vec_t Z)
	{
		//		Init(X,Y,Z);
		//		X = 0.0f; Y=0.0f ;Z =0.0f;
	}

#ifdef VECTOR_NO_SLOW_OPERATIONS

private:
	// No copy constructors allowed if we're in optimal mode
	VectorAligned(const VectorAligned& vOther);
	VectorAligned(const Vector &vOther);

#else
public:
	explicit VectorAligned(const Vector &vOther)
	{
		//		Init(vOther.X, vOther.Y, vOther.Z);
		//		vOther.X=0.0f;vOther.Y=0.0f;vOther.Z =0.0;
	}

	VectorAligned& operator=(const Vector &vOther)
	{
		//		Init(vOther.X, vOther.Y, vOther.Z);
		x = vOther.x; y = vOther.y; z = vOther.z;
		return *this;
	}

#endif
	float w;	// this space is used anyway
};
struct Ray_t
{
	VectorAligned        m_Start;
	VectorAligned        m_Delta;
	VectorAligned        m_StartOffset;
	VectorAligned        m_Extents;

	const   matrix3x4* m_pWorldAxisTransform;

	bool    m_IsRay;
	bool    m_IsSwept;

	Ray_t() : m_pWorldAxisTransform(NULL) { }

	void Init(Vector& vecStart, Vector& vecEnd)
	{
		m_Delta = vecEnd - vecStart;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.x = m_Extents.y = m_Extents.z = 0.0f;

		m_pWorldAxisTransform = NULL;

		m_IsRay = true;

		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;

		m_Start = vecStart;
	}
};
class ITraceFilter {
public:
	virtual bool ShouldHitEntity(C_BaseEntity *pEntity, int contentsMask) = 0;
	virtual TraceType_t    GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter {
public:
	bool ShouldHitEntity(C_BaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};



class CTraceFilterWorldOnly : public CTraceFilter {
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int contentsMask)
	{
		return false;
	}
	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_WORLD_ONLY;
	}
};

class CTraceFilterNoPlayer : public CTraceFilter
{
public:
	CTraceFilterNoPlayer() {}
	virtual bool ShouldHitEntity(IHandleEntity *pServerEntity, int contentsMask)
	{
		IClientUnknown *pUnk = (IClientUnknown*)pServerEntity;
		C_BaseEntity *pEnt = pUnk->GetBaseEntity();
		return !pEnt->IsValid();
	}
};

class CSimpleTraceFilter : public CTraceFilter
{
public:
	CSimpleTraceFilter(PVOID pEnt)
	{
		m_pPassEnt = pEnt;
	}

	virtual bool ShouldHitEntity(IHandleEntity *pHandleEntity, int contentsMask)
	{
		return pHandleEntity != m_pPassEnt;
	}

	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	PVOID m_pPassEnt;
};

inline bool CGameTrace::DidHit() const
{
	return fraction < 1 || allsolid || startsolid;
}

inline bool CGameTrace::DidHitWorld() const
{
	return m_pEnt->GetIndex() == 0;
}

inline bool CGameTrace::DidHitNonWorldEntity() const
{
	return m_pEnt != NULL && !DidHitWorld();
}


class CTraceEngine {
public:
	virtual void	GetPointContents(Vector const&, trace_t **) = 0;
	virtual void	GetPointContents_Collideable(trace_t *, Vector const&) = 0;
	virtual void	ClipRayToEntity(Ray_t const&, unsigned int, int *, int *) = 0;
	virtual void	ClipRayToCollideable(Ray_t const&, unsigned int, int *, int *) = 0;
	virtual void	paaad() = 0;
	virtual void	TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter* filter, trace_t *trace) = 0;
	virtual void	SetupLeafAndEntityListRay(Ray_t const&, int &) = 0;
	virtual void	SetupLeafAndEntityListBox(Vector const&, Vector const&, int &) = 0;
	virtual void	TraceRayAgainstLeafAndEntityList(Ray_t const&, int &, unsigned int, ITraceFilter *, trace_t *) = 0;
	virtual void	SweepCollideable(int *, Vector const&, Vector const&, Vector const&, unsigned int, ITraceFilter *, trace_t *) = 0;
	virtual void	EnumerateEntities(Ray_t const&, bool, int *) = 0;
	virtual void	EnumerateEntities(Vector const&, Vector const&, int *) = 0;
};

struct surfacephysicsparams_t
{
	float			friction;
	float			elasticity;
	float			density;
	float			thickness;
	float			dampening;
};

struct surfaceaudioparams_t
{
	float			reflectivity;
	float			hardnessFactor;
	float			roughnessFactor;
	float			roughThreshold;
	float			hardThreshold;
	float			hardVelocityThreshold;
};

struct surfacesoundnames_t
{
	unsigned short	walkStepLeft;
	unsigned short	walkStepRight;
	unsigned short	runStepLeft;
	unsigned short	runStepRight;
	unsigned short	impactSoft;
	unsigned short	impactHard;
	unsigned short	scrapeSmooth;
	unsigned short	scrapeRough;
	unsigned short	bulletImpact;
	unsigned short	rolling;
	unsigned short	breakSound;
	unsigned short	strainSound;
};

struct surfacesoundhandles_t
{
	short	walkStepLeft;
	short	walkStepRight;
	short	runStepLeft;
	short	runStepRight;
	short	impactSoft;
	short	impactHard;
	short	scrapeSmooth;
	short	scrapeRough;
	short	bulletImpact;
	short	rolling;
	short	breakSound;
	short	strainSound;
};

struct surfacegameprops_t
{
public:
	float				maxSpeedFactor;
	float				jumpFactor;
	char				pad00[0x4];
	float				flPenetrationModifier;
	float				flDamageModifier;
	unsigned short		material;
	char				pad01[0x3];
};

struct surfacedata_t
{
	surfacephysicsparams_t	physics;
	surfaceaudioparams_t	audio;
	surfacesoundnames_t		sounds;
	surfacegameprops_t		game;
	surfacesoundhandles_t	soundhandles;
};