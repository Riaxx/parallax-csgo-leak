class model_t;
class Vector;
class SurfInfo;
class player_info_s;
class CAudioSource;
//class QAngle;
class ButtonCode_t;
class con_nprint_s;
class IMaterialSystem;
class Frustum_t;
class AudioState_t;
class CPhysCollide;
class IMaterial;
class matrix3x4_t;
struct color32_s;
class OcclusionParams_t;
class IAchievementMgr;
class string_t;
class CGamestatsData;
class C_BaseEntity;
class IClientEntity;
class ICollideable;
class EngineInputContextId_t;
class GenericMemoryStat_t;
class Color;
class IntRect;
class IHTML;
class IHTMLEvents;
class HCursor;
class HTexture;
class Vertex_t;
struct CharRenderInfo;
class IVguiMatInfo;
class IImage;
class ImageFormat;
class IHTMLChromeController;
class IConCommandBaseAccessor;
struct CVarDLLIdentifier_t;
struct characterset_t;
struct FnCommandCallbackVoid_t;
class FnCommandCompletionCallback;
struct FnCommandCallback_t;
class ICommandCallback;
class ICommandCompletionCallback;
class IConVar;
class ConVar;
class ICvarQuery;
class ConCommand;
class IConsoleDisplayFunc;
class PRINTF_FORMAT_STRING;
class m_fnCommandCallbackV1;
class m_fnCommandCallback;
struct FnChangeCallback_t;
class IAppSystem;
class FontVertex_t;
class FontCharRenderInfo;
class DrawTexturedRectParms_t;
class ConCommandBase;
class VMatrix;
class FontFeature_t;
class InputContextHandle_t__;
class InputEvent_t;
class SurfaceFeature_t;
class CUserCmd;
typedef unsigned long HFont;
typedef unsigned int VPANEL;
typedef float matrix3x4[3][4];
typedef float matrix4x4[4][4];

enum ClientFrameStage_t {
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

enum MoveType_t
{
	MOVETYPE_NONE = 0,	// never moves
	MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
	MOVETYPE_WALK,				// Player only - moving on the ground
	MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
	MOVETYPE_FLY,				// No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
	MOVETYPE_PUSH,				// no clip to world, push and crush
	MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER,			// Used by players only when going onto a ladder
	MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics

								// should always be defined as the last item in the list
								MOVETYPE_LAST = MOVETYPE_CUSTOM,

								MOVETYPE_MAX_BITS = 4
};

#define RandomInt(min, max) (rand() % (max - min + 1) + min)
#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

typedef __int16					int16;
typedef unsigned __int16		uint16;
typedef __int32					int32;
typedef unsigned __int32		uint32;
typedef __int64					int64;
typedef unsigned __int64		uint64;

struct ModelRender_t;
typedef void*(*CreateInterface)(const char*, int*);
typedef void(__thiscall* tPaintTraverse)(void* ecx, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
//typedef void(__fastcall *RenderViewFn) (void*, CViewSetup&, CViewSetup&, unsigned int, int);
typedef void(__stdcall* tFrameStage)(ClientFrameStage_t);
//typedef void(__fastcall* hkdDrawModelExecute)(void*, int, void*, void*, const ModelRender_t&, matrix3x4*);
typedef void(__fastcall* hkdDrawModelExecute)(void*, int, void*, void*, const ModelRender_t&, matrix3x4*);
typedef void(__stdcall* CreateMoveFn)(int, float, bool);
typedef bool(__stdcall* ClientModeInternally)(float, CUserCmd*);
typedef struct
{
	char szTableName[256];
	char szPropName[256];
	RecvVarProxyFn SavedProxy;
} Oldproxy_t;

class CNetworkedVariableManager
{
public:

	// stores all tables, and all props inside those
	~CNetworkedVariableManager(void);

	// Initialize shit.
	void Init(void);

	// calls GetProp wrapper to get the absolute offset of the prop
	int getOffset(const char *tableName, const char *propName);


	// calls GetProp wrapper to get prop and sets the proxy of the prop
	bool HookProp(const char *tableName, const char *propName, RecvVarProxyFn function);


private:

	// wrapper so we can use recursion without too much performance loss
	int GetProp(const char *tableName, const char *propName, RecvProp **prop = 0);


	// uses recursion to return a the relative offset to the given prop and sets the prop param
	int GetProp(RecvTable *recvTable, const char *propName, RecvProp **prop = 0);


	RecvTable *GetTable(const char *tableName);


	std::vector<RecvTable*>    m_tables;

	std::vector<Oldproxy_t> m_savedproxy;
};


extern CNetworkedVariableManager pOffsets;

class NetWorkedOffsets {
public:
	void getEm();
	int m_iHealth, m_iClip1, m_iClip2, m_vecAngles, m_iEyeAngles, m_hActiveWeapon, m_fAccuracyPenalty, m_iBoneMatrix, m_iObserveTarget, m_bHasHelmet, m_bIsMoving, m_vecVelocity, m_bIsDefusing, m_lifeState, m_iTeamNum, m_fFlags, m_hOwnerEntity, m_flFlashDuration, m_flFlashMaxAlpha, m_CurrentStage, m_ArmorValue, m_bGunGameImmunity, m_punch, m_visualpunch, m_Local, ForceBone, MoveMent, isScoped, m_kit1, m_kit2, m_CollisionGroup, m_Collision, m_iKills, m_movetype, m_nTickBase, m_flNextPrimaryAttack;
	int dwDeadFlag;
	int m_iObserverMode;
	int InitKeyValuesEx, LoadFromBufferEx, LoadClanTagEx, IsRdy;

	/* skins shit*/
	int dwiItemIDHigh;
	int dwiItemIDLow;
	int dwOrigOwnerHigh;
	int dwOrigOwnerLow;
	int dwiFallbackPaintKit;
	int dwiFallbackSeed;
	int dwflFallbackWear;
	int dwiFallbackStatTrak;
	int dwszCustomName;
	int dwiModelIndex;
	int m_flLowerBodyYawTarget;

	int m_bBombTicking;
	int m_flC4Blow;
	int m_bBombDefused;
	int m_hBombDefuser;
	int m_bBombDropped;
	int m_bBombPlanted;
	int m_bFreezePeriod;

	struct {
		
		std::ptrdiff_t m_iEyeAngles1[2];

	};

};

extern NetWorkedOffsets offsets;

