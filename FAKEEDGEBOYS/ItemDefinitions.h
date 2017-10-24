#pragma once
#include <map>
#include <vector>

enum ItemDefinitionIndex : int
{
	WEAPON_DEAGLE = 1,
    WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 5,
	WEAPON_AUG = 6,
	WEAPON_AWP = 7,
	WEAPON_FAMAS = 8,
	WEAPON_G3SG1 = 9,
	WEAPON_GALILAR = 10,
	WEAPON_M249 = 11,
	WEAPON_M4A1 = 12,
	WEAPON_MAC10 = 13,
	WEAPON_P90 = 14,
	WEAPON_UMP45 = 15,
	WEAPON_XM1014 = 16,
	WEAPON_BIZON = 17,
	WEAPON_MAG7 = 18,
	WEAPON_NEGEV = 19,
	WEAPON_SAWEDOFF = 20,
	WEAPON_TEC9 = 21,
	WEAPON_TASER = 22,
	WEAPON_HKP2000 = 23,
	WEAPON_MP7 = 24,
	WEAPON_MP9 = 25,
	WEAPON_NOVA = 26,
	WEAPON_P250 = 27,
	WEAPON_SCAR20 = 28,
	WEAPON_SG556 = 29,
	WEAPON_SSG08 = 30,
	WEAPON_KNIFE = 31,
	WEAPON_FLASHBANG = 32,
	WEAPON_HEGRENADE = 33,
	WEAPON_SMOKEGRENADE = 34, 
	WEAPON_MOLOTOV = 35,
	WEAPON_DECOY = 36,
	WEAPON_INCGRENADE = 37,
	WEAPON_C4 = 38,
	WEAPON_KNIFE_T = 39,
	WEAPON_M4A1_SILENCER = 40, 
	WEAPON_USP_SILENCER = 41,
	WEAPON_CZ75A = 42,
	WEAPON_REVOLVER = 43,
	WEAPON_KNIFE_BAYONET = 44,
	WEAPON_KNIFE_FLIP = 45,
	WEAPON_KNIFE_GUT = 46,
	WEAPON_KNIFE_KARAMBIT = 47,
	WEAPON_KNIFE_M9_BAYONET = 48,
	WEAPON_KNIFE_TACTICAL = 49,
	WEAPON_KNIFE_FALCHION = 50,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 51,
	WEAPON_KNIFE_BUTTERFLY = 52,
	WEAPON_KNIFE_PUSH = 53,
	GLOVE_STUDDED_BLOODHOUND = 54,
	GLOVE_T_SIDE = 55,
	GLOVE_CT_SIDE = 56, 
	GLOVE_SPORTY = 57,
	GLOVE_SLICK = 58,
    GLOVE_LEATHER_WRAP = 59,
	GLOVE_MOTORCYCLE = 60,
	GLOVE_SPECIALIST = 61
};

inline bool Isknife(int i) { return (i >= WEAPON_KNIFE_BAYONET && i < GLOVE_STUDDED_BLOODHOUND) || i == WEAPON_KNIFE_T || i == WEAPON_KNIFE; }


struct Item_t
{
	constexpr Item_t(const char* model, const char* icon = nullptr) :
		model(model),
		icon(icon)

	{}

	const char* model;
	const char* icon;
};

struct WeaponName_t
{
	constexpr WeaponName_t(int definition_index, const char* name) :
		definition_index(definition_index),
		name(name)

	{}

	int definition_index = 0;
	const char* name = nullptr;

};

struct QualityName_t
{
	constexpr QualityName_t(int index, const char* name) :
		index(index),
		name(name)

	{}

	int index = 0;
	const char* name = nullptr;

};


extern const std::map<size_t, Item_t> k_weapon_info;
extern const std::vector<WeaponName_t> k_knife_names;
extern const std::vector<WeaponName_t> k_glove_names;
extern const std::vector<WeaponName_t> k_weapon_names;
extern const std::vector<QualityName_t> k_quality_names;
