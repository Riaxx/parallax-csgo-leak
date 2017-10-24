class C_BaseEntity {
public:

	Vector GetAbsOrigin() {
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x134);
	}

	Vector GetEyePos() {
		return this->GetAbsOrigin() + *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x104);
	}

	Vector GetEyeAngles() {
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)vars->eyeang);
	}

	int Health() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)vars->health);
	}

	int Team() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)vars->team);
	}

	bool IsDormant() {
		return *reinterpret_cast<bool*>((DWORD)this + (DWORD)0xE9);
	}

	ICollideable* CollisionGroup() {
		return (ICollideable*)((DWORD)this + 0x318);
	}

	int Flags() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)vars->flags);
	}

	bool SetupBones(matrix3x4 *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) {
		PVOID pRenderable = (PVOID)(this + 0x4);
		typedef bool(__thiscall* oSetup)(PVOID, matrix3x4*, int, int, int);
		return getvfunc<oSetup>(pRenderable, 13)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}

	Vector GetPunch() {
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)vars->vecpunch);
	}

	Vector ViewAngle() {
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x4D0C);
	}

	int GetArmour() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)vars->getarmor);
	}

	int GetHelmet() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)vars->gethelmet);
	}

	char GetLifeState() {
		return *reinterpret_cast<char*>((DWORD)this + (DWORD)vars->lifestate);
	}

	bool IsValid() {
		return (GetLifeState() == 0 && !this->IsDormant() && this->Health() > 0);
	}

	int MoveType() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0x258);
	}

	Vector GetBonePosition(int bone) {
		matrix3x4 boneMatrix[128];
		if (this->SetupBones(boneMatrix, 128, 0x100, GetTickCount64())) {
			return Vector(boneMatrix[bone][0][3], boneMatrix[bone][1][3], boneMatrix[bone][2][3]);
		}
		return Vector(0, 0, 0);
	}

	Vector GetHeadBone() {
		return this->GetBonePosition(8);
	}

	int GetIndex() {
		PVOID pNetworkable = (PVOID)(this + 0x8);
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 10)(pNetworkable);
	}

	model_t* GetModel() {
		return *(model_t**)((DWORD)this + 0x6C);
	}

	int GetTickBase() {
		return *(int*)((DWORD)this + vars->servertime);
	}

	int PrecacheModel(const char *name);

	ClientClass* GetClientClass() {
		PVOID pNetworkable = (PVOID)(this + 0x8);
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pNetworkable, 2)(pNetworkable);
	}

	int OwnerEntity() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0x148);
	}

	bool bScoped() {
		return *reinterpret_cast<bool*>((DWORD)this + (DWORD)0x389C);
	}

	Vector GetVelocity() {
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x110);
	}

	C_BaseCombatWeapon* Active();

};