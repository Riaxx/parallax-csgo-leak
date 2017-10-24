class Valve {
public:

	void InitializeAll(); // nigers stand back pls.

	IBaseClientDLL* pClient; // <- FrameStage.
	IBaseClientDLL** xClient; // <- ClientMode.
	IVEngineClient* pEngine;
	IVDebugOverlay* pOverlay;
	IClientEntityList* pEntList;
	ISurface* pSurface;
	IPanel* pPanel;
	IEngineTrace* pEngineTrace;
	ICvar* pCvar;
	IPhysicsSurfaceProps* pProps;
	CInput* pInput;
	CGlobalVarsBase* pGlobals;
	IVModelInfo* pModelInfo;
	IVModelRender* pModelRender;
	IVRenderView* pRenderView;
	IVMaterialSystem* pMatSystem;
	void* ViewRender;
	void* oPlaySound;

	/* Stages */
	tPaintTraverse oPaintTraverse;
	tFrameStage oFrameStage;
	ClientModeInternally oCreateMove;
	//CreateMoveFn oCreateMove;

	/* VMT's */
	CVMTHookManager* clienthook = NULL;
	CVMTHookManager* panelhook = NULL;
	CVMTHookManager* otherhook = NULL;
	CVMTHookManager* eventhook = NULL;
	CVMTHookManager* modelhook = NULL;
	CVMTHookManager* renderhook = NULL;
	CVMTHookManager* playsoundhook = NULL;
};
extern Valve* pValve;

// MBE LOGIC
// "Kan du bli untrustad av visuals..."

// KAZOR LOGIC
// "Kommer inte hacket bli detectat om du releasar SDK'n?"

// SHINEZ LOGIC
// "Jag är underbar"