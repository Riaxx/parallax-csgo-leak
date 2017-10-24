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
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int contentsMask )
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



class IEngineTrace {
public:
	virtual int GetPointContents(const Vector &vecAbsPosition, unsigned int fMask, IHandleEntity** ppEntity = NULL);
	virtual void Func1();
	virtual void Func2();
	virtual void Func3();
	virtual void Func4();
	virtual void TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter* filter, trace_t *trace);
};

class IEngineTracers
{
public:
	enum TraceType_t
	{
		TRACE_EVERYTHING = 0,
		TRACE_WORLD_ONLY,
		TRACE_ENTITIES_ONLY,
		TRACE_EVERYTHING_FILTER_PROPS,
	};

	struct cplane_t
	{
		Vector normal;
		float dist;
		BYTE type;
		BYTE signBits;
		BYTE pad[2];
	};

	struct csurface_t
	{
		const char*		name;
		short			surfaceProps;
		unsigned short	flags;
	};

	struct Ray_t
	{
		Ray_t() { }

		VectorAligned	 m_start;
		VectorAligned	 m_delta;
		VectorAligned	 m_startOffset;
		VectorAligned	 m_extents;
		const matrix3x4* m_worldAxisTransform;
		bool			 m_isRay;
		bool			 m_isSwept;

		void Init(Vector start, Vector end)
		{
			m_delta = VectorAligned(end - start);
			m_isSwept = (m_delta.LengthSqr() != 0);
			m_extents.Zero();
			m_worldAxisTransform = NULL;
			m_isRay = true;
			m_startOffset.Zero();
			m_start = start;
		}
	};

	struct trace_t
	{
		Vector		 start;
		Vector		 endpos;
		cplane_t	 plane;
		float		 fraction;
		int			 contents;
		WORD		 dispFlags;
		bool		 allSolid;
		bool		 startSolid;
		float		 fractionLeftSolid;
		csurface_t	 surface;
		int			 hitgroup;
		short		 physicsBone;
		WORD		 worldSurfaceIndex;
		C_BaseEntity* entity;
		int			 hitbox;
	};

	class ITraceFilterz
	{
	public:
		virtual bool shouldHitEntity(C_BaseEntity* entity, int contentsMask) = 0;
		virtual TraceType_t getTraceType() const = 0;
	};
	class CTraceFilterz : public ITraceFilterz
	{
	public:
		bool shouldHitEntity(C_BaseEntity* entityHandle, int contentsMask)
		{
			return !(entityHandle == skip);
		}
		virtual TraceType_t getTraceType() const
		{
			return TRACE_EVERYTHING;
		}

		void* skip;
	};

public:
	void traceRayz(const Ray_t& ray, unsigned int mask, CTraceFilter* filter, trace_t* trace)
	{
		//typedef void(__thiscall* original)(void*, const Ray_t&, unsigned int, CTraceFilter*, trace_t*);
		//getVirtualFunction<original>(this, 5)(this, ray, mask, filter, trace);
	}
};
#define CONTENTS_MOVEABLE		0x4000
#define	CONTENTS_MONSTER		0x2000000
#define	CONTENTS_EMPTY			0		// No contents
#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	0x80
#define	CONTENTS_DEBRIS			0x4000000
#define CONTENTS_HITBOX			0x40000000
#define	MASK_SOLID		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define	CONTENTS_MONSTERCLIP	0x20000
#define MASK_NPCWORLDSTATIC (CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE)
