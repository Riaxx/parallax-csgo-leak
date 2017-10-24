class Source {
public:

	void Initialize();

	ISurface* pSurface;
	IPanel* pPanel;
	IVEngineClient* pEngine;
	IBaseClientDLL* pClient;
	IClientEntityList* pEntList;
	IVDebugOverlay* pOverlay;
	ICvar* pCvar;
	CGlobalVarsBase* pGlobals;
	IBaseClientDLL** xClient;
	IEngineTrace* pEngineTrace;
	IPhysicsSurfaceProps* pProps;
	IVModelInfo* pModelInfo;
	IVMaterialSystem* pMatSystem;
	IVRenderView* pRenderView;
	IVModelRender* pModelRender;
	CPrediction* pPrediction;
	ImoveHelper* pMoveHelper;
	CGameMovement* pGameMovement;

	CInput* pInput;
	tPaintTraverse oPaintTraverse;
	ClientModeInternally oCreateMove;
	tFrameStage oFrameStage;
	hkdDrawModelExecute oDrawModelExecute;

	CVMTHookManager* panelhook;
	CVMTHookManager* clienthook;
	CVMTHookManager* framerhook;
	CVMTHookManager* modelhook;
	CVMTHookManager* predhook;
};

extern Source* vlv;