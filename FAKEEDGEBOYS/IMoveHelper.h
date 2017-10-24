class IMoveHelper {
public:
	void SetHost(C_BaseEntity *pPlayer) {
		typedef void(__thiscall* oSetHost)(PVOID, C_BaseEntity*);
		return ReadFunc< oSetHost >(this, 1)(this, pPlayer);
	}
};

class IGameMovement {
public:

	void ProcessMovement(C_BaseEntity *pPlayer, void *pMove) {
		typedef void(__thiscall* oProcessMovement)(PVOID, C_BaseEntity*, void*);
		return ReadFunc< oProcessMovement >(this, 1)(this, pPlayer, pMove);
	}

	void StartTrackPredictionErrors(C_BaseEntity* player) {
		typedef void(__thiscall* oPredictionError)(PVOID, C_BaseEntity*);
		return ReadFunc< oPredictionError >(this, 3)(this, player);
	}

	void FinishTrackPredictionErrors(C_BaseEntity* player) {
		typedef void(__thiscall* oPredictionError)(PVOID, C_BaseEntity*);
		return ReadFunc< oPredictionError >(this, 4)(this, player);
	}
};

class IPrediction {
public:

	bool InPrediction() {
		typedef bool(__thiscall* oInPrediction)(PVOID);
		return ReadFunc< oInPrediction >(this, 14)(this);
	}

	void RunCommand(C_BaseEntity *player, CUserCmd *ucmd, IMoveHelper *moveHelper) {
		typedef void(__thiscall* oRunCommand)(PVOID, C_BaseEntity*, CUserCmd*, IMoveHelper*);
		return ReadFunc< oRunCommand >(this, 19)(this, player, ucmd, moveHelper);
	}

	void SetupMove(C_BaseEntity *player, CUserCmd *ucmd, IMoveHelper *moveHelper, void*pMoveData) {
		typedef void(__thiscall* oSetupMove)(PVOID, C_BaseEntity*, CUserCmd*, IMoveHelper*, void*);
		return ReadFunc< oSetupMove >(this, 20)(this, player, ucmd, moveHelper, pMoveData);
	}

	void FinishMove(C_BaseEntity *player, CUserCmd *ucmd, void*pMoveData) {
		typedef void(__thiscall* oFinishMove)(PVOID, C_BaseEntity*, CUserCmd*, void*);
		return ReadFunc< oFinishMove >(this, 21)(this, player, ucmd, pMoveData);
	}
};