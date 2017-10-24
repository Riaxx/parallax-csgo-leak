enum getWeaponsNames {
	/* Weapons */
	WEAPON_NONE = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_DUALBERETTAS = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK18 = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A4 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_ZEUS = 31,
	WEAPON_HPK2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG553 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_S = 61,
	WEAPON_CZ75A = 63,
	WEAPON_R8REVOLVER = 64,
	/* Nades */
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	/* World */
	WEAPON_C4 = 49,
	/* Knifes, WHY VALVE? WHYY!!!!! Why so many knives? i mean like, you don't win or have any higher chances of winning depending on what knife you got. */
	WEAPON_KNIFE = 42,
	WEAPON_KNIFE_T = 59,
	WEAPON_BAYONET = 500,
	WEAPON_FLIP = 505,
	WEAPON_GUT = 506,
	WEAPON_KARAMBIT = 507,
	WEAPON_M9 = 508,
	WEAPON_HUNTSMAN = 509,
	WEAPON_FALCHION = 512,
	WEAPON_BOWIE = 514,
	WEAPON_BUTTERFLY = 515,
	WEAPON_DAGGER = 516
};
class CHudTexture
{
	char pad[0x82];
public:
	char cCharacterInFont;
};

class CSWeaponInfo {
public:
	char pad_0x0000[0x4]; // 0x00
	char _0x0800[0x7FC]; // 0x7FC
	float m_flArmorRatio; // 0x800.
	char _0x0814[0x10]; // 0x810
	float m_flPenetration; // 0x814
	__int32 m_iDamage; // 0x818
	float m_flRange; // 0x81C
	float m_flRangeModifier; // 0x820
};//Slut size = 0x828.
class C_BaseCombatWeapon {
public:

	int Item() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0x2F88);
	}

	bool isKnife() {
		int id = this->Item();
		return (id == 42 || id == 59 || id == 500 || id == 505 || id == 506 || id == 507 || id == 508 || id == 509 || id == 512 || id == 514 || id == 515 || id == 516);
	}

	bool isPistol() {
		int id = this->Item();
		return (id == WEAPON_DEAGLE || id == WEAPON_DUALBERETTAS || id == WEAPON_FIVESEVEN || id == WEAPON_GLOCK18 || id == WEAPON_TEC9 || id == WEAPON_ZEUS || id == WEAPON_HPK2000 || id == WEAPON_P250 || id == WEAPON_USP_S);
	}

	bool isSniper() {
		int id = this->Item();
		return (id == WEAPON_AWP || id == WEAPON_SSG08 || id == WEAPON_G3SG1 || id == WEAPON_SCAR20);
	}

	bool isRifle() {
		int id = this->Item();
		return (id == WEAPON_AK47 || id == WEAPON_M4A1_SILENCER || id == WEAPON_M4A4 || id == WEAPON_GALILAR || id == WEAPON_FAMAS || id == WEAPON_AUG || id == WEAPON_SG553 || id == WEAPON_CZ75A);
	}

	bool isSMG() {
		int id = this->Item();
		return (id == WEAPON_P90 || id == WEAPON_BIZON || id == WEAPON_UMP45 || id == WEAPON_MAC10 || id == WEAPON_MP7 || id == WEAPON_MP9);
	}
	bool isHeavy() {
		int id = this->Item();
		return (id == WEAPON_NEGEV || id == WEAPON_M249 || id == WEAPON_XM1014 || id == WEAPON_NOVA || id == WEAPON_SAWEDOFF || id == WEAPON_MAG7);
	}
	bool isGrenades() {
		int id = this->Item();
		return (id == WEAPON_FLASHBANG || id == WEAPON_HEGRENADE || id == WEAPON_MOLOTOV || id == WEAPON_INCGRENADE || id == WEAPON_SMOKEGRENADE || id == WEAPON_DECOY || id == WEAPON_C4 || id == WEAPON_ZEUS);
	}
	bool isBomb() {
		int id = this->Item();
		return (id == WEAPON_C4);
	}
	bool isAwp() {
		int id = this->Item();
		return (id == WEAPON_AWP);
	}

	int iClip() {
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)vars->iclip);
	}
	
	CSWeaponInfo* GetData() {
		typedef CSWeaponInfo*(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 456)(this);
	}

	const char* GetName() {
		typedef const char* (__thiscall* tGetName)(PVOID);
		return getvfunc<tGetName>(this, 378)(this);
	}

	const char* GetPrintName() {
		typedef const char* (__thiscall* tGetName)(PVOID);
		return getvfunc<tGetName>(this, 379)(this);
	}

	float GetNextPrimaryAttack() {
		return *(float*)((DWORD)this + vars->primaryattack);
	}
};

