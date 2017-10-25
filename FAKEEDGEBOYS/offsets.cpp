/*MIT License

Copyright (c) namazso 2017

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
#include "main.h"
#include "scanner.h"
#include "other.h"
NetWorkedOffsets offsets;


void NetWorkedOffsets::getEm() {
	this->m_iHealth = pOffsets.getOffset("DT_BasePlayer", "m_iHealth");
	this->m_iClip1 = pOffsets.getOffset("DT_BaseCombatWeapon", "m_iClip1");
	this->m_iClip2 = pOffsets.getOffset("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount");
	this->m_bIsDefusing = pOffsets.getOffset("DT_CSPlayer", "m_bIsDefusing");
	this->m_lifeState = pOffsets.getOffset("DT_BasePlayer", "m_lifeState");
	this->m_iTeamNum = pOffsets.getOffset("DT_BaseEntity", "m_iTeamNum");
	this->m_fFlags = pOffsets.getOffset("DT_BasePlayer", "m_fFlags");
	this->m_hOwnerEntity = pOffsets.getOffset("DT_BaseEntity", "m_hOwnerEntity");
	this->m_flFlashDuration = pOffsets.getOffset("DT_CSPlayer", "m_flFlashDuration");
	this->m_flFlashMaxAlpha = pOffsets.getOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
	this->m_CurrentStage = pOffsets.getOffset("DT_ParticleSmokeGrenade", "m_CurrentStage");
	this->m_ArmorValue = pOffsets.getOffset("DT_CSPlayer", "m_ArmorValue");
	this->m_bGunGameImmunity = pOffsets.getOffset("DT_CSPlayer", "m_bGunGameImmunity");
	this->m_punch = pOffsets.getOffset("DT_BasePlayer", "m_aimPunchAngle");
	this->m_visualpunch = pOffsets.getOffset("DT_BasePlayer", "m_viewPunchAngle");
	this->m_Local = pOffsets.getOffset("DT_BasePlayer", "m_Local");
	this->m_fAccuracyPenalty = pOffsets.getOffset("DT_WeaponCSBase", "m_fAccuracyPenalty");
	this->ForceBone = pOffsets.getOffset("DT_BaseAnimating", "m_nForceBone");
	this->MoveMent = pOffsets.getOffset("DT_CSPlayer", "m_bIsWalking");
	this->isScoped = pOffsets.getOffset("DT_CSPlayer", "m_bIsScoped");
	this->m_kit1 = pOffsets.getOffset("DT_EconEntity", "m_nFallbackPaintKit");
	this->m_CollisionGroup = pOffsets.getOffset("DT_BaseEntity", "m_CollisionGroup");
	this->m_Collision = pOffsets.getOffset("DT_BaseEntity", "m_Collision");
	this->m_iKills = pOffsets.getOffset("DT_CSPlayerResource", "m_iKills");
	this->m_movetype = pOffsets.getOffset("DT_BaseToggle", "m_movementType");
	this->m_nTickBase = pOffsets.getOffset("DT_BasePlayer", "m_nTickBase");
	this->m_flNextPrimaryAttack = pOffsets.getOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	this->m_bHasHelmet = pOffsets.getOffset("DT_CSPlayer", "m_bHasHelmet");
	this->m_hActiveWeapon = pOffsets.getOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
	this->dwiItemIDHigh = pOffsets.getOffset("DT_BaseCombatWeapon", "m_iItemIDHigh");
	this->dwiItemIDLow = pOffsets.getOffset("DT_BaseCombatWeapon", "m_iItemIDLow");
	this->dwOrigOwnerHigh = pOffsets.getOffset("DT_BaseCombatWeapon", "m_OriginalOwnerXuidHigh");
	this->dwOrigOwnerLow = pOffsets.getOffset("DT_BaseCombatWeapon", "m_OriginalOwnerXuidLow");
	this->dwiFallbackPaintKit = pOffsets.getOffset("DT_BaseCombatWeapon", "m_nFallbackPaintKit");
	this->dwiFallbackSeed = pOffsets.getOffset("DT_BaseCombatWeapon", "m_nFallbackSeed");
	this->dwflFallbackWear = pOffsets.getOffset("DT_BaseCombatWeapon", "m_flFallbackWear");
	this->dwiFallbackStatTrak = pOffsets.getOffset("DT_BaseCombatWeapon", "m_nFallbackStatTrak");
	this->dwiModelIndex = pOffsets.getOffset("DT_BaseCombatWeapon", "m_nModelIndex");
	this->dwszCustomName = pOffsets.getOffset("DT_BaseCombatWeapon", "m_szCustomName");
	this->m_iObserveTarget = pOffsets.getOffset("DT_BasePlayer", "m_hObserverTarget");
	this->m_iObserverMode = pOffsets.getOffset("DT_CSPlayer", "m_iObserverMode");
	this->m_iEyeAngles = pOffsets.getOffset("DT_CSPlayer", "m_angEyeAngles[0]");
	this->m_iEyeAngles1[1] = pOffsets.getOffset("DT_CSPlayer", "m_angEyeAngles[1]");
	this->dwDeadFlag = pOffsets.getOffset("DT_CSPlayer", "deadflag");
	this->m_flLowerBodyYawTarget = pOffsets.getOffset("DT_CSPlayer", "m_flLowerBodyYawTarget");
	this->m_bBombTicking = pOffsets.getOffset("DT_PlantedC4", "m_bBombTicking");
	this->m_flC4Blow = pOffsets.getOffset("DT_PlantedC4", "m_flC4Blow");
	this->m_bBombDefused = pOffsets.getOffset("DT_PlantedC4", "m_bBombDefused");
	this->m_hBombDefuser = pOffsets.getOffset("DT_PlantedC4", "m_hBombDefuser");
	this->m_bBombDropped = pOffsets.getOffset("DT_CSGameRulesProxy", "m_bBombDropped");
	this->m_bBombPlanted = pOffsets.getOffset("DT_CSGameRulesProxy", "m_bBombPlanted");
	this->m_bFreezePeriod = pOffsets.getOffset("DT_CSGameRulesProxy", "m_bFreezePeriod");
	this->LoadFromBufferEx = xyzFindPattern(strenc("client.dll"), strenc("55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04")); //this one is  p100
	this->InitKeyValuesEx = xyzFindPattern(strenc("client.dll"), strenc("55 8B EC 51 33 C0 C7 45"));
	this->IsRdy = xyzFindPattern(strenc("client.dll"), strenc("81 66 70 00 00 F0 FF C7 46 6C 00 00 00 00 C7 46 74 00 00 00 00 5E E9 ?? ?? ?? ?? CC CC CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ?? ?? ?? ?? 57")) + 0x28;

	//this->LoadClanTagEx = zFindPattern("engine.dll", (PBYTE)"\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15\x00\x00\x00\x00\x6A\x24\x8B\xC8\x8B\x30", "xxxxxxxxx????xxxxxx");
}

													