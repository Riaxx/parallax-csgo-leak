
typedef float matrix3x4[3][4];
// Credits to Casual_Hacker 

class ICollideable {
public:
	virtual void Func0();
	virtual const Vector& OBBMins() const;
	virtual const Vector& OBBMaxs() const;
};

class C_BaseEntity {
public:
	int PrecacheModel(const char *name);
	
	Vector GetAbsOrigin() {
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x134); // Has not been changed for a while.
	}
	ClientClass* GetClientClass() {
		PVOID pNetworkable = (PVOID)(this + 0x8);
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID);
		return ReadFunc<OriginalFn>(pNetworkable, 2)(pNetworkable);
	}
	Vector GetAbsAngles() {
		typedef Vector(__thiscall* getxAngle)(PVOID);
		return ReadFunc<getxAngle>(this, 11)(this);
	}

	Vector GetEyePos() {
		return this->GetAbsOrigin() + *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x104);
	}
	Vector GetEyeAngles() {
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)offsets.m_iEyeAngles);
	}
	Vector GetVelocity() {
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x110);
	}
	Vector GetAngles() {
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)0x4D0C);
	}

	bool& bSpotted() {
		return *reinterpret_cast<bool*>((DWORD)this + (DWORD)0x939);
	}

	float& FlashAlpha() {
		return *reinterpret_cast<float*>((DWORD)this + (DWORD)0xA304);
	}
	
	int GetChokedTicks() {
		if (this->m_flSimulationTime() > this->m_flOldSimulationTime())
			return fabs(m_flSimulationTime() - this->m_flOldSimulationTime());
		return 0;
	}

	int Health() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)offsets.m_iHealth); // Same here.
	}

	int Team() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)offsets.m_iTeamNum); // and here...
	}

	bool Dormant() {
		return *reinterpret_cast<bool*>((DWORD)this + (DWORD)0xE9); // sigh.... and here.
	}

	model_t* GetModel()
	{
	return *( model_t** )( ( DWORD )this + 0x6C );
	}
	bool GetAlive()
	{
		return (bool)(*(int*)((DWORD)this + offsets.m_lifeState) == 0);
	}
	int GetIndex()
	{
		PVOID pNetworkable = (PVOID)(this + 0x8);
		typedef int(__thiscall* OriginalFn)(PVOID);
		return ReadFunc<OriginalFn>(pNetworkable, 10)(pNetworkable);
	}


	ICollideable* GetCollideable()
	{
		int m_Collision = pOffsets.getOffset("DT_BaseEntity", "m_Collision");
		return (ICollideable*)((DWORD)this + m_Collision);
	}

	int	entindex(void) {
		typedef int(__thiscall* OriginalFn)(PVOID);
		return ReadFunc<OriginalFn>(this, 16)(this);
	}

	bool SetupBones( matrix3x4 *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime )
{
	__asm
	{
		mov edi, this
		lea ecx, dword ptr ds : [edi + 0x4]
		mov edx, dword ptr ds : [ecx]
		push currentTime
		push boneMask
		push nMaxBones
		push pBoneToWorldOut
		call dword ptr ds : [edx + 0x34]
	}
}

	void setPos(Vector& vPos1, Vector& vPos2) {
		typedef void(__thiscall* OriginalFn)(PVOID, Vector&, Vector&);
		return ReadFunc<OriginalFn>(this, 109)(this, vPos1, vPos2);
	}

	int Flags() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)offsets.m_fFlags); // And this one.
	}

	int GlowIndex() {
		int getIndex = pOffsets.getOffset("DT_CSPlayer", "m_flFlashMaxAlpha") + 0x18;
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0xA310);
	}


	bool HasDefuser() {
		return *reinterpret_cast<bool*>((DWORD)this + (DWORD)0x17B8);
	}

	bool IsDefusing() {
		return *reinterpret_cast<bool*>((DWORD)this + (DWORD)0x3894);
	}

	bool IsImmune() {
		int getImmunity = pOffsets.getOffset("DT_CSPlayer", "m_bGunGameImmunity");
		return *reinterpret_cast<bool*>((DWORD)this + (DWORD)getImmunity);
	}

	bool IsWalking() {
		return *reinterpret_cast<bool*>((DWORD)this + (DWORD)offsets.MoveMent);
	}

	bool IsScoped() {
		return *reinterpret_cast<bool*>((DWORD)this + (DWORD)offsets.isScoped);
	}

	bool HasHelmet() {
		return *reinterpret_cast<bool*>((DWORD)this + (DWORD)offsets.m_bHasHelmet);
	}
	Vector GetPunch2()
	{
		return *(Vector*)((DWORD)this + (DWORD)0x3018);
	}
	Vector vecOrigin() {
		return *(Vector*)((DWORD)this + (DWORD)0x134);
	}


	DWORD BoneMatrix() {
		int pBoner = offsets.ForceBone + 0x1C;
		return *reinterpret_cast<DWORD*>((DWORD)this + (DWORD)pBoner);
	}

	Vector GetPunch() {
		int getPunch = offsets.m_Local + 0x70;
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)getPunch);
	}

	Vector GetVisualPunch() {
		int getPuncher = offsets.m_Local + 0x64;
		return *reinterpret_cast<Vector*>((DWORD)this + (DWORD)getPuncher);
	}

	int ArmorValue() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)offsets.m_ArmorValue);
	}

	int hittime() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0xA2C8);
	}

	int shotsfired() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0xA2C0);
	}

	ULONG GetWeapon() {
		static int offset = pOffsets.getOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
		return *reinterpret_cast<ULONG*>((DWORD)this + (DWORD)offset);
	}

	float& TickBase() {
		static int offset = pOffsets.getOffset("DT_BasePlayer", "m_nTickBase");
		return *(float*)((DWORD)this + offset);
	}
	float& m_flOldSimulationTime() {
		static int offset = pOffsets.getOffset("DT_BaseEntity", "m_flSimulationTime") + 0x4;
		return *(float*)((DWORD)this + offset);
	}
	float& m_flSimulationTime() {
		static int offset = pOffsets.getOffset("DT_BaseEntity", "m_flSimulationTime");
		return *(float*)((DWORD)this + offset);
	}
	int iObserverMode() {
		return *(int*)((DWORD)this + 0x3360);
	}
	float NextAttack() {
		static int GetNextAtc = pOffsets.getOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
		return *(float*)((DWORD)this + GetNextAtc);
	}
	
	float GetAccuracyPenalty()
	{
		return *(float*)((DWORD)this + offsets.m_fAccuracyPenalty);
	}

	char GetLifeState() {
		return *reinterpret_cast<char*>((DWORD)this + (DWORD)offsets.m_lifeState);
	}

	bool IsValid() {
		return (GetLifeState() == 0 && !this->Dormant() && this->Health() > 0);
	}

	int ObserverTarget() {
		int offsetx = pOffsets.getOffset("DT_BasePlayer", "m_hObserverTarget");
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)offsetx);
	}

	CUserCmd* m_pCurrentCommand() {
		int offsersetter = pOffsets.getOffset("DT_BasePlayer", "m_nButtons") + 0x4;
		return *reinterpret_cast<CUserCmd**>((DWORD)this + (DWORD)0x3328);
	}

	int MoveType() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0x258);
	}

	Vector* Eyeangles()
	{
		return (Vector*)((DWORD)this + offsets.m_iEyeAngles1[0]);
	}
	float GetLowerBodyYawTarget()
	{
		return *reinterpret_cast<float*>((DWORD)this + (DWORD)offsets.m_flLowerBodyYawTarget);

	}
	C_BaseCombatWeapon* Active();
	
};

class C_PlantedC4 : public C_BaseEntity
{
public:
	bool IsBombTicking()
	{
		return (bool)((uintptr_t)this + offsets.m_bBombTicking);
	}

	float GetBombTime()
	{
		return *(float*)((uintptr_t)this + offsets.m_flC4Blow);
	}

	bool IsBombDefused()
	{
		return *(bool*)((uintptr_t)this + offsets.m_bBombDefused);
	}

	int GetBombDefuser()
	{
		return *(int*)((uintptr_t)this + offsets.m_hBombDefuser);
	}
};


class C_CSGameRules
{
public:
	/*bool IsValveDS()
	{
		return *(bool*)((uintptr_t)this + offsets.DT_CSGameRulesProxy.m_bIsValveDS);
	}*/

	bool IsBombDropped()
	{
		return *(bool*)((uintptr_t)this + offsets.m_bBombDropped);
	}

	bool IsBombPlanted()
	{
		return *(bool*)((uintptr_t)this + offsets.m_bBombPlanted);
	}

	bool IsFreezeTime()
	{
		return *(bool*)((uintptr_t)this + offsets.m_bFreezePeriod);
	}
};

class xKeyValues;
struct WeaponInfo_t
{
	char pad00[0xC8];
	int m_WeaponType;		// 0xC8
	char padCC[0x20];
	int m_Damage;			// 0xEC
	float m_ArmorRatio;		// 0xF0
	char padF4[0x4];
	float m_Penetration;	// 0xF8
	char padFC[0x8];
	float m_Range;			// 0x104
	float m_RangeModifier;	// 0x108
	char pad10C[0x10];
	bool m_HasSilencer;		// 0x11C
};

class CSWeaponInfo : public WeaponInfo_t {
public:
	int Damage() {
		return this->m_Damage;
	}

	float Range() {
		return this->m_Range;
	}

	float RangeModifier() {
		return m_RangeModifier;
	}

	float ArmorRatio() {
		return this->m_ArmorRatio;
	}

	float Penetration() {
		return this->m_Penetration;
	}

	
};

class CUserCmd;
class CPrediction {
public:
	bool InPrediction() {
		typedef bool(__thiscall* oInPrediction)(void*);
		return ReadFunc< oInPrediction >(this, 14)(this);
	}
	void SetupMove(C_BaseEntity *player, CUserCmd *ucmd, PVOID empty, PVOID moveData) {
		typedef void(__thiscall* OriginalFn)(PVOID, C_BaseEntity *player, CUserCmd *ucmd, PVOID empty, PVOID moveData);
		ReadFunc<OriginalFn>(this, 20)(this, player, ucmd, NULL, moveData);
	}
	void FinishMove(C_BaseEntity *player, CUserCmd *ucmd, PVOID moveData) {
		typedef void(__thiscall* OriginalFn)(PVOID, C_BaseEntity *player, CUserCmd *ucmd, PVOID moveData);
		ReadFunc<OriginalFn>(this, 21)(this, player, ucmd, moveData);
	}
};

class ImoveHelper {
public:
	void SetHost(C_BaseEntity *pPlayer) {
		typedef void(__thiscall* OriginalFn)(PVOID, C_BaseEntity *pPlayer);
		ReadFunc<OriginalFn>(this, 1)(this, pPlayer);
	}
};

class CGameMovement {
public:
	void ProcessMovement(C_BaseEntity *pPlayer, PVOID moveData)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, C_BaseEntity *pPlayer, PVOID moveData);
		ReadFunc<OriginalFn>(this, 1)(this, pPlayer, moveData);
	}
};


