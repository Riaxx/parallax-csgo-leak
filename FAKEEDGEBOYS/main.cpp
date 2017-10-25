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
#include "Drawings.h"
#include "Engine.h"
#include "SDK\\GetInterface.h"
#include "ESP.h"
#include "EventManager.h"
#include "checksum_md5.h"
#include <io.h>
#include <fcntl.h>
#include "scanner.h"
#include "other.h"
#include "clantag.h"
#include "CMoveData.h"
#include "IMoveHelper.h"
#include "Misc.h"
#include "XorStr.h"

using InitKeyValuesFn = void(__thiscall*)(void* thisptr, const char* name);
using LoadFromBufferFn = void(__thiscall*)(void* thisptr, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc);


InitKeyValuesFn InitKeyValuesEx;
LoadFromBufferFn LoadFromBufferEx;

Valve* pValve = new Valve();
/* Aimstebb */

// JAG ÄR BÖG :DDDDDDDDDDDDDD


Vector RoflAngle;
Vector LastRoflAngle;
Vector nulledTarget;
int pWep;
C_CSGameRules** csGameRules = nullptr;
/* Classes */
TraceEngines* traceEngines = new TraceEngines();
CCRC gCRC;
ICvar* pCvar;
Vector tpangle;
int shots_fired = 0;

IPrediction* pPrediction;
IGameMovement* pGameMovement;
IMoveHelper* pMoveHelper;
C_BaseCombatWeapon* C_BaseEntity::Active() {
	ULONG pWeepEhandle = *(PULONG)((DWORD)this + offsets.m_hActiveWeapon);
	return (C_BaseCombatWeapon*)(pValve->pEntList->GetClientEntityFromHandle(pWeepEhandle));
}
bool cock = false;
IGameEventManager* g_pGameEventManager;
#define CenterX GetSystemMetrics(SM_CXSCREEN) / 2
#define CenterY GetSystemMetrics(SM_CYSCREEN) / 2
#define ScreenH GetSystemMetrics(SM_CYSCREEN)
#define ScreenW GetSystemMetrics(SM_CXSCREEN)

/* Credits: Kiro */
bool bCanFire;
extern void InitKeyValues(KeyValues* pKeyValues, const char* name);
void InitKeyValues(KeyValues* pKeyValues, const char* name) {
	InitKeyValuesEx = (InitKeyValuesFn)(offsets.InitKeyValuesEx);
	InitKeyValuesEx(pKeyValues, name);
}

extern void LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem = nullptr, const char* pPathID = NULL, void* pfnEvaluateSymbolProc = nullptr);
void LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc) {
	LoadFromBufferEx = (LoadFromBufferFn)(offsets.LoadFromBufferEx);
	LoadFromBufferEx(pKeyValues, resourceName, pBuffer, pFileSystem, pPathID, pfnEvaluateSymbolProc);
}
int C_BaseEntity::PrecacheModel(const char *name) {
	return pValve->pModelInfo->GetModelIndex(name);
}


IMaterial* CreateMaterial(bool shouldIgnoreZ, bool wireFramed = false) /* Creds: Kiro */
{
	static int created = 0;

	//this is a pointer to the cvar I use for controlling lighting on the materials,
	//I registered it in the source engines linked list of ConVars,
	//and it's changable through the games console
	std::string type = "VertexLitGeneric";

	//materialBuffer holds the vmt "script" or what to call it
	std::string tmp = {
		"\"" + type + "\"\n{\
		\n\t\"$basetexture\" \"VGUI/white_additive\"\
		\n\t\"$ignorez\" \"" + std::to_string(shouldIgnoreZ) + "\"\
		\n\t\"$nofog\" \"1\"\
		\n\t\"$wireframe\" \"" + std::to_string(wireFramed) + "\"\
		\n\t\"$halflambert\" \"1\"\
		\n}"
	};

	//make a unique name for our material
	char materialName[512];
	sprintf(materialName, "slayer_tron_%i.vmt", created);
	++created;

	//construct keyvalues based on the material type
	KeyValues* keyValues = new KeyValues(materialName);

	//load vmt "script" into our instance of keyvalues
	InitKeyValues(keyValues, type.c_str());
	LoadFromBuffer(keyValues, materialName, tmp.c_str());

	//create the actual material
	IMaterial* createdMaterial = pValve->pMatSystem->CreateMaterial(materialName, keyValues);
	createdMaterial->IncrementReferenceCount();

	return createdMaterial;
}


#define MAT( _TYPE_ ) "\"" + _TYPE_ + "\"\n{\n\t\"$basetexture\" \"VGUI/white_additive\"\n\t\"$ignorez\" \"1\"\n\t\"$nofog\" \"1\"\n\t\"$halflambert\" \"1\"\n}"
#define MAT_IGNOREZ( _TYPE_ ) "\"" + _TYPE_ + "\"\n{\n\t\"$basetexture\" \"VGUI/white_additive\"\n\t\"$ignorez\" \"0\"\n\t\"$nofog\" \"1\"\n\t\"$halflambert\" \"1\"\n}"
//IMaterial* CreateMaterial(bool shouldIgnoreZ, bool isWireframe) {
//	static int created = 0;
//
//
//
//	std::string type = "VertexLitGeneric";
//
//	char material[512];
//	if (shouldIgnoreZ)
//	{
//		std::string tmp(MAT(type));
//		sprintf(material, tmp.c_str());
//	}
//	else
//	{
//		std::string tmp(MAT_IGNOREZ(type));
//		sprintf(material, tmp.c_str());
//	}
//	if (isWireframe) {
//
//	}
//	char name[512];
//	sprintf(name, "shinez_%i.vmt", created);
//	++created;
//
//	//construct keyvalues based on the material type
//	KeyValues* pKeyValues = new KeyValues(type.c_str());
//
//	//load vmt "script" into our instance of keyvalues
//	//InitKeyValues(pKeyValues, type.c_str());
//	LoadFromBuffer(pKeyValues, name, material);
//
//	//create the actual material
//	IMaterial* createdMaterial = pValve->pMatSystem->CreateMaterial(name, pKeyValues);
//	createdMaterial->IncrementReferenceCount();
//
//	return createdMaterial;
//}



hkdDrawModelExecute oDrawModelExecute;


#define FCVAR_CHEAT (1<<14)
void PerformNightmode()
{
	static bool bPerformed = false, bLastSetting;

	C_BaseEntity* pLocal = pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());

	static ConVar* sv_skyname = pCvar->FindVar("sv_skyname");
	sv_skyname->nFlags &= ~FCVAR_CHEAT; // something something dont force convars

	if (!pLocal || !pValve->pEngine->IsConnected() || !pValve->pEngine->IsInGame())
		return;

	if (!bPerformed)
	{
		for (auto i = pValve->pMatSystem->FirstMaterial(); i != pValve->pMatSystem->InvalidMaterial(); i = pValve->pMatSystem->NextMaterial(i))
		{
			static IMaterial* pMaterial = pValve->pMatSystem->GetMaterial(i);

			if (!pMaterial || pMaterial->IsErrorMaterial())
				continue;

			if (strstr(pMaterial->GetTextureGroupName(), "World") || strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
			{
				//if (bLastSetting)
				//{
					sv_skyname->SetValue("sky_csgo_night02");
					pMaterial->SetVarFlag(MATERIAL_VAR_TRANSLUCENT, false); // walls were translucent for me for some odd reason, probably p100 codenz :/
					pMaterial->ColorModulate(0.15, 0.15, 0.15);
				//}
				//else
				//{
				//	sv_skyname->SetValue("vertigoblue_hdr"); // fixme: i was too lazy to backup old value
				//	pMaterial->ColorModulate(1.00, 1.00, 1.00);
				//}
			}
		}
	}

	//if (bLastSetting != Settings::bVisualNightmode)
	//{
	//	bLastSetting = Settings::bVisualNightmode;
	//
	//}
}


void __fastcall hkDrawModelExecute(void* thisptr, int edx, void* context, void* state, const ModelRender_t &pInfo, matrix3x4 *pCustomBoneToWorld) {
	C_BaseEntity* pLocalEntity = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
	C_BaseEntity* pBaseEntity = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pInfo.entity_index);
	C_BaseCombatWeapon* pWeapon = pLocalEntity->Active();

	if (pValve->pEngine->IsConnected() && pValve->pEngine->IsInGame()) {
	




		MaterialHandle_t(__stdcall *FirstMaterial)();
		MaterialHandle_t(__stdcall *NextMaterial)(MaterialHandle_t h);
		MaterialHandle_t(__stdcall *InvalidMaterial)();
		IMaterial* (__stdcall *GetMaterial)(MaterialHandle_t h);

		
		if (pInfo.pModel) {
			const char* szName = pValve->pModelInfo->GetModelName(pInfo.pModel);
			string pszModel = pValve->pModelInfo->GetModelName(pInfo.pModel);

			

			if (vars::esp_nosky) //No Sky
			{
				IMaterial* pMaterial = pValve->pMatSystem->FindMaterial(szName, TEXTURE_GROUP_SKYBOX, 1, 0);
				if (strstr(pMaterial->GetName(), "skybox"))
				{
					pMaterial->ColorModulate(0.f, 0.f, 0.f);
				}

			}
			else
			{
				IMaterial* pMaterial = pValve->pMatSystem->FindMaterial(szName, TEXTURE_GROUP_SKYBOX, 1, 0);
				if (strstr(pMaterial->GetName(), "skybox"))
				{
					pMaterial->ColorModulate(1.0f, 1.0f, 1.0f);
				}


			}

			if (strstr(szName, "models/weapons") && vars::wpn_chams > 1) {
				static IMaterial* wepMat1 = CreateMaterial(true, false);
				static IMaterial* wepMat2 = CreateMaterial(false, false);
				static IMaterial* wepMat3 = CreateMaterial(false, true);

				float gayColors[2];
				float wireColors[2];
				
				IMaterial* pWeapon = pValve->pMatSystem->FindMaterial(szName, TEXTURE_GROUP_MODEL, 1, 0);
				


				if (vars::wpn_chams == 2) {

					pWeapon->SetVarFlag(MATERIAL_VAR_NO_DRAW, true);
					pValve->pModelRender->ForcedMaterialOverride(pWeapon, OVERRIDE_NORMAL, 0);
					oDrawModelExecute(thisptr, edx, context, state, pInfo, pCustomBoneToWorld);
				}
				if (vars::wpn_chams == 3) {
					pWeapon->SetVarFlag(MATERIAL_VAR_NO_DRAW, false);
					pWeapon->SetVarFlag(MATERIAL_VAR_WIREFRAME, true);
					pValve->pModelRender->ForcedMaterialOverride(pWeapon, OVERRIDE_NORMAL, 0);
					oDrawModelExecute(thisptr, edx, context, state, pInfo, pCustomBoneToWorld);
				}
				if (vars::wpn_chams == 4) {
					gayColors[0] = vars::weaponR / 255.f;
					gayColors[1] = vars::weaponG / 255.f;
					gayColors[2] = vars::weaponB / 255.f;
					
					pValve->pRenderView->SetBlend(vars::weapons_transparency / 100.f);
					pValve->pRenderView->SetColorModulation(gayColors);
					pValve->pModelRender->ForcedMaterialOverride(wepMat2, OVERRIDE_NORMAL, 0);
					oDrawModelExecute(thisptr, edx, context, state, pInfo, pCustomBoneToWorld);
					
				}
			}

			if (strstr(szName, "arms") && vars::esp_hands > 1 && pLocalEntity) {
				static IMaterial* handMat1 = CreateMaterial(true, false);
				static IMaterial* handMat2 = CreateMaterial(false, false);

				float gayColors[2];

				IMaterial* pHands = pValve->pMatSystem->FindMaterial(szName, TEXTURE_GROUP_MODEL, 1, 0);

				if (vars::esp_hands < 2 && vars::wpn_chams > 1) {
					pHands->SetVarFlag(MATERIAL_VAR_NO_DRAW, false);
					pHands->SetVarFlag(MATERIAL_VAR_WIREFRAME, false);
					pValve->pModelRender->ForcedMaterialOverride(pHands, OVERRIDE_NORMAL, 0);
					oDrawModelExecute(thisptr, edx, context, state, pInfo, pCustomBoneToWorld);
				}
				if (vars::esp_hands == 2) {
					pHands->SetVarFlag(MATERIAL_VAR_NO_DRAW, true);
					pValve->pModelRender->ForcedMaterialOverride(pHands, OVERRIDE_NORMAL, 0);
					oDrawModelExecute(thisptr, edx, context, state, pInfo, pCustomBoneToWorld);
				
				}
				if (vars::esp_hands == 3) {

					pHands->SetVarFlag(MATERIAL_VAR_NO_DRAW, false);
					pHands->SetVarFlag(MATERIAL_VAR_WIREFRAME, true);
					pValve->pModelRender->ForcedMaterialOverride(pHands, OVERRIDE_NORMAL, 0);
					oDrawModelExecute(thisptr, edx, context, state, pInfo, pCustomBoneToWorld);
				

				}
				if (vars::esp_hands >= 4) {



					gayColors[0] = vars::handsr / 255.f;
					gayColors[1] = vars::handsg / 255.f;
					gayColors[2] = vars::handsb / 255.f;


					
					pValve->pRenderView->SetBlend(vars::hands_transparency / 100.f);
					pValve->pRenderView->SetColorModulation(gayColors);
					pValve->pModelRender->ForcedMaterialOverride(handMat2, OVERRIDE_NORMAL, 0);
					oDrawModelExecute(thisptr, edx, context, state, pInfo, pCustomBoneToWorld);
			
				}

			}



			if (pszModel.find("models/player") != std::string::npos && vars::chamselect > 1) {
				static IMaterial* outline = CreateMaterial(true, true);
				static IMaterial* outline2 = CreateMaterial(true, true);
				static IMaterial* playerMat1 = CreateMaterial(true, false);
				static IMaterial* playerMat2 = CreateMaterial(false, false);

				static IMaterial* z1 = CreateMaterial(true, false);
				static IMaterial* z2 = CreateMaterial(false, false);

				C_BaseEntity* pBaseEntity = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pInfo.entity_index);
				C_BaseEntity* pLocalEntity = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());

				if (pBaseEntity) {
					if (pBaseEntity->IsValid()) {
						if (pBaseEntity->Team() == 2 || pBaseEntity->Team() == 3) {

							Color Render;
							Color VisRend;
							float flAlpha = { 1.f };
							if ((pLocalEntity->Team() == pBaseEntity->Team()) && vars::chams_enemies) {
								oDrawModelExecute(thisptr, edx, context, state, pInfo, pCustomBoneToWorld);
								return;
							}
							if (vars::chamselect == 3) {
								//Color outlineclr = Color(255.f, 255.f, 255.f);
								//pValve->pRenderView->SetColorModulation(outlineclr);
								//
								//
								//pValve->pModelRender->ForcedMaterialOverride(outline);

								oDrawModelExecute(thisptr, edx, context, state, pInfo, pCustomBoneToWorld);

								if (pBaseEntity->Team() == 3) {
									if (vars::chams_ct_transparency == 100)
										Render = Color(vars::chams_ct_r, vars::chams_ct_g, vars::chams_ct_b);
									else
										Render = Color(vars::chams_ct_r, vars::chams_ct_g, vars::chams_ct_b, vars::chams_ct_transparency * 2.55f);
									pValve->pRenderView->SetBlend(vars::chams_ct_transparency / 100.f);



								}

								if (pBaseEntity->Team() == 2) {
									if (vars::chams_ct_transparency == 100)
										Render = Color(vars::chams_t_r, vars::chams_t_g, vars::chams_t_b);
									else
										Render = Color(vars::chams_t_r, vars::chams_t_g, vars::chams_t_b, vars::chams_t_transparency * 2.55f);
									pValve->pRenderView->SetBlend(vars::chams_t_transparency / 100.f);
								}

								pValve->pRenderView->SetColorModulation(Render.Base());


								pValve->pModelRender->ForcedMaterialOverride(playerMat1);

								oDrawModelExecute(thisptr, edx, context, state, pInfo, pCustomBoneToWorld);
							}
							

							if (pBaseEntity->Team() == 3) {
								VisRend = Color(vars::chams_ct_visible_r, vars::chams_ct_visible_g, vars::chams_ct_visible_b);


							}

							if (pBaseEntity->Team() == 2) {
								VisRend = Color(vars::chams_t_visible_r, vars::chams_t_visible_g, vars::chams_t_visible_b);

							}


							pValve->pRenderView->SetBlend(1.f);
							pValve->pRenderView->SetColorModulation(VisRend.Base());
							
							pValve->pModelRender->ForcedMaterialOverride(playerMat2);
							

							oDrawModelExecute(thisptr, edx, context, state, pInfo, pCustomBoneToWorld);
							
						}
					}


				}

			}

		}
		oDrawModelExecute(thisptr, edx, context, state, pInfo, pCustomBoneToWorld);
		pValve->pModelRender->ForcedMaterialOverride(0, OVERRIDE_NORMAL, 0);
	}
}









struct FireBulletData {

	Vector           src;
	trace_t          enter_trace;
	Vector           direction;
	CTraceFilter    filter;
	float           trace_length;
	float           trace_length_remaining;
	float           current_damage;
	int             penetrate_count;
};


bool DidHitNonWorldEntity(C_BaseEntity* m_pEnt) {
	return m_pEnt != NULL && m_pEnt == pValve->pEntList->GetClientEntity(0);
}

bool TraceToExit(Vector &end, trace_t *enter_trace, Vector start, Vector dir, trace_t *exit_trace)
{
	//epic cooel trace3exit
	float distance = 0.0f;

	while (distance <= 90.0f)
	{
		distance += 4.0f;
		end = start + dir * distance;

		auto point_contents = pValve->pEngineTrace->GetPointContents(end, MASK_SHOT_HULL || CONTENTS_HITBOX, NULL);

		if (point_contents & MASK_SHOT_HULL && (!(point_contents & CONTENTS_HITBOX)))
			continue;

		auto new_end = end - (dir * 4.0f);

		Ray_t ray;
		ray.Init(end, new_end);
		pValve->pEngineTrace->TraceRay(ray, MASK_SHOT, 0, exit_trace);

		if (exit_trace->startsolid && exit_trace->surface.flags & SURF_HITBOX)
		{
			ray.Init(end, start);
			CTraceFilter filter;
			filter.pSkip = exit_trace->m_pEnt;
			pValve->pEngineTrace->TraceRay(ray, 0x600400B, &filter, exit_trace);

			if ((exit_trace->fraction < 1.0f || exit_trace->allsolid) && !exit_trace->startsolid)
			{
				end = exit_trace->endpos;
				return true;
			}
			continue;
		}

		if (!(exit_trace->fraction < 1.0 || exit_trace->allsolid || exit_trace->startsolid) || exit_trace->startsolid)
		{
			if (exit_trace->m_pEnt)
			{
				if (DidHitNonWorldEntity(enter_trace->m_pEnt))
					return true;
			}
			continue;
		}

		if (((exit_trace->surface.flags >> 7) & 1) && !((enter_trace->surface.flags >> 7) & 1))
			continue;

		if (exit_trace->plane.normal.Dot(dir) <= 1.0f)
		{
			auto fraction = exit_trace->fraction * 4.0f;
			end = end - (dir * fraction);
			return true;
		}
	}
	return false;
}

void TraceLine(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, C_BaseEntity* ignore, trace_t* ptr) {
	Ray_t ray;
	ray.Init(vecAbsStart, vecAbsEnd);
	CTraceFilter filter;
	filter.pSkip = ignore;

	pValve->pEngineTrace->TraceRay(ray, mask, &filter, ptr);
}



DWORD xFindPattern(std::string moduleName, std::string pattern) {
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;    //one ?
		}
		else
		{
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}
	return NULL;
}

#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4	
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR	10	

struct FireKrulleData {
	Vector          src;
	trace_t         enter_trace;
	Vector          direction;
	CTraceFilter    filter;
	float           trace_length;
	float           trace_length_remaining;
	float           current_damage;
	int             penetrate_count;
};

float GetHitgroupDamageMultiplier2(int iHitGroup) {
	switch (iHitGroup) {
	case HITGROUP_GENERIC: {
		return 1.0f;
	}
	case HITGROUP_HEAD: {
		return 4.0f;
	}
	case HITGROUP_CHEST: {
		return 1.0f;
	}
	case HITGROUP_LEFTARM: {
		return 1.0f;
	}
	case HITGROUP_RIGHTARM: {
		return 1.0f;
	}
	case HITGROUP_STOMACH: {
		return 1.25f;
	}
	case HITGROUP_LEFTLEG: {
		return 0.75f;
	}
	case HITGROUP_RIGHTLEG: {
		return 0.75f;
	}
	}
	return 1.0f;
}

void ScaleDamage2(int hitgroup, C_BaseEntity *enemy, float weapon_armor_ratio, float &current_damage) {
	current_damage *= GetHitgroupDamageMultiplier2(hitgroup);

	int armor = enemy->ArmorValue();
	int helmet = enemy->HasHelmet();

	if (armor > 0) {
		if (hitgroup == HITGROUP_HEAD) {
			if (helmet)
				current_damage *= (weapon_armor_ratio * .6f);
		}
		else {
			current_damage *= (weapon_armor_ratio * .5f);
		}
	}
}


bool TraceToExit(Vector& end, trace_t& tr, float x, float y, float z, float x2, float y2, float z2, trace_t* trace) {
	typedef bool(__fastcall* TraceToExitFn)(Vector&, trace_t&, float, float, float, float, float, float, trace_t*);
	static TraceToExitFn TraceToExit = (TraceToExitFn)xFindPattern("client.dll", "55 8B EC 83 EC 30 F3 0F 10 75");
	//55 8B EC 83 EC 2C F3 0F 10 75 ? 33 C0
	//55 8B EC 83 EC 30 F3 0F 10 75
	
																				  
	if (!TraceToExit)
		return false;

	_asm {
		push trace
		push z2
		push y2
		push x2
		push z
		push y
		push x
		mov edx, tr
		mov ecx, end
		call TraceToExit
		add esp, 0x1C
	}
}

bool HandleBulletPenetration2(CSWeaponInfo *wpn_data, FireKrulleData &data) {
	surfacedata_t *enter_surface_data = pValve->pProps->GetSurfaceData(data.enter_trace.surface.surfaceProps);
	int enter_material = enter_surface_data->game.material;
	float enter_surf_penetration_mod = *(float*)((DWORD)enter_surface_data + 76);

	data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
	data.current_damage *= pow((wpn_data->RangeModifier()), (data.trace_length * 0.002));

	if ((data.trace_length > 3000.f) || (enter_surf_penetration_mod < 0.1f))
		data.penetrate_count = 0;

	if (data.penetrate_count <= 0)
		return false;

	Vector dummy;
	trace_t trace_exit;
	if (!TraceToExit(dummy, data.enter_trace, data.enter_trace.endpos.x, data.enter_trace.endpos.y, data.enter_trace.endpos.z, data.direction.x, data.direction.y, data.direction.z, &trace_exit))
		return false;

	surfacedata_t *exit_surface_data = pValve->pProps->GetSurfaceData(trace_exit.surface.surfaceProps);
	int exit_material = exit_surface_data->game.material;

	float exit_surf_penetration_mod = *(float*)((DWORD)exit_surface_data + 76);
	float final_damage_modifier = 0.16f;
	float combined_penetration_modifier = 0.0f;

	if (((data.enter_trace.contents & CONTENTS_GRATE) != 0) || (enter_material == 89) || (enter_material == 71)) {
		combined_penetration_modifier = 3.0f;
		final_damage_modifier = 0.05f;
	}
	else {
		combined_penetration_modifier = (enter_surf_penetration_mod + exit_surf_penetration_mod) * 0.5f;
	}

	if (enter_material == exit_material) {
		if (exit_material == 87 || exit_material == 85)
			combined_penetration_modifier = 3.0f;
		else if (exit_material == 76)
			combined_penetration_modifier = 2.0f;
	}

	float v34 = fmaxf(0.f, 1.0f / combined_penetration_modifier);
	float v35 = (data.current_damage * final_damage_modifier) + v34 * 3.0f * fmaxf(0.0f, (3.0f / wpn_data->Penetration()) * 1.25f);
	float thickness = (trace_exit.endpos - data.enter_trace.endpos).Length();

	thickness *= thickness;
	thickness *= v34;
	thickness /= 24.0f;

	float lost_damage = fmaxf(0.0f, v35 + thickness);

	if (lost_damage > data.current_damage)
		return false;

	if (lost_damage >= 0.0f)
		data.current_damage -= lost_damage;

	if (data.current_damage < 1.0f)
		return false;

	data.src = trace_exit.endpos;
	data.penetrate_count--;

	return true;
}





bool SimulateFireBullet2(C_BaseCombatWeapon* pWeapon, FireKrulleData &data, C_BaseEntity* pLocal) {

	data.penetrate_count = 4;
	data.trace_length = 0.0f;
	CSWeaponInfo* weaponData = pLocal->Active()->GetCSWpnData();

	if (weaponData == NULL)
		return false;

	data.current_damage = (float)weaponData->Damage();

	while ((data.penetrate_count > 0) && (data.current_damage >= 1.0f)) {
		data.trace_length_remaining = weaponData->Range() - data.trace_length;

		Vector end = data.src + data.direction * data.trace_length_remaining;

		TraceLine(data.src, end, MASK_SHOT, pLocal, &data.enter_trace);

		Ray_t ray;
		ray.Init(data.src, end + data.direction*40.f);

		pValve->pEngineTrace->TraceRay(ray, MASK_SHOT, &data.filter, &data.enter_trace);

		TraceLine(data.src, end + data.direction*40.f, MASK_SHOT, pLocal, &data.enter_trace);

		if (data.enter_trace.fraction == 1.0f)
			break;

		if ((data.enter_trace.hitgroup <= 7) && (data.enter_trace.hitgroup > 0) && pLocal->Team() != data.enter_trace.m_pEnt->Team()) {
			data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
			data.current_damage *= pow(weaponData->RangeModifier(), data.trace_length * 0.002);
			ScaleDamage2(data.enter_trace.hitgroup, data.enter_trace.m_pEnt, weaponData->ArmorRatio(), data.current_damage);

			return true;
		}

		if (!HandleBulletPenetration2(weaponData, data))
			break;
	}

	return false;
}





bool GetDamage2(Vector &point, float *damage_given) {
	auto *local = pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
	FireKrulleData data;
	data.src = local->GetEyePos();
	data.filter = CTraceFilter();
	data.filter.pSkip = local;

	Vector angles;
	C::CalcAngle(data.src, point, angles, local);
	C::AngleVectors(angles, &data.direction);
	VectorNormalize(data.direction);

	if (SimulateFireBullet2(local->Active(), data, local)) {
		*damage_given = data.current_damage;
		return true;
	}

	return false;
}

namespace backtrack {
	float lowerbodyyaw = 0.f;
	int tick_count = 0;
	float curtime = 0.f;
	float frametime = 0.f;
	Vector velocity(0, 0, 0);
	Vector absangles(0, 0, 0);
	Vector eyeangles(0, 0, 0);
	int flags = 0;
	int ticks = 0;
	int simTicks = 0;
	float simTime = 0;
}

void StoreVars(C_BaseEntity * ent) {
	backtrack::lowerbodyyaw = ent->GetLowerBodyYawTarget();
	backtrack::tick_count = pValve->pGlobals->tickcount;
	backtrack::curtime = pValve->pGlobals->curtime;
	backtrack::velocity = ent->GetVelocity();
	backtrack::absangles = ent->GetAbsAngles();
	backtrack::eyeangles = ent->GetAngles();
	backtrack::curtime = pValve->pGlobals->curtime;
	backtrack::frametime = pValve->pGlobals->frametime;
	backtrack::simTicks = pValve->pGlobals->simTicksThisFrame;

	backtrack::simTime = ent->m_flSimulationTime();
}
void ReleaseVars(C_BaseEntity * ent) {
	pValve->pGlobals->tickcount = backtrack::tick_count;
	pValve->pGlobals->simTicksThisFrame = backtrack::simTicks;
	ent->GetVelocity() = backtrack::velocity;
	pValve->pGlobals->curtime = backtrack::curtime;
	pValve->pGlobals->frametime = backtrack::frametime;	
	ent->m_flSimulationTime() = backtrack::simTime;
	
}

/* END */

bool Aimstep(Vector src, Vector dst, Vector& out, int steps)
{
	Vector delta_angle = (dst - src).Normalized();;
	bool x_finished = false;
	bool y_finished = false;

	if (delta_angle.x > steps)
		src.x += steps;

	else if (delta_angle.x < -steps)
		src.x -= steps;

	else
	{
		x_finished = true;
		src.x = dst.x;
	}

	if (delta_angle.y > steps)
		src.y += steps;

	else if (delta_angle.y < -steps)
		src.y -= steps;

	else
	{
		y_finished = true;
		src.y = dst.y;
	}

	src.Normalized();

	out = src;

	return x_finished && y_finished;
}
int iSpeed = 0;

int scoped = 1;

void SetNormalAngles(float& angles) {
	while (angles < -180.f)
		angles += 360.f;
	while (angles > 180.f)
		angles -= 360.f;
}

void SendSpeed(Vector& Angles, CUserCmd* pCmd, float flSpeed) {
	if(flSpeed > 2.f) {
		Vector getDelta = pCmd->viewangles - Angles;
		float GetSpeedLimit = flSpeed / 10;
		getDelta.Clamp();
		Angles = pCmd->viewangles - getDelta * GetSpeedLimit;
	}
}

void MakeAutostrafe(CUserCmd* pCmd) {
	if (vars::misc_autostrafe) {
		static float move = 650.f;
		float s_move = move * 0.5065f;
		if (pCmd->buttons & IN_JUMP) {
			pCmd->forwardmove = move * 0.015f;
			pCmd->sidemove += (float)(((pCmd->tick_count % 2) * 2) - 1) * s_move;

			if (pCmd->mousedx)
				pCmd->sidemove = (float)(pCmd->mousedx, -1, 1) * s_move;

			static float strafe = pCmd->viewangles.y;

			float rt = pCmd->viewangles.y, rotation;
			rotation = strafe - rt;

			if (rotation < FloatNegate(pValve->pGlobals->interval_per_tick))
				pCmd->sidemove = -s_move;

			if (rotation > pValve->pGlobals->interval_per_tick)
				pCmd->sidemove = s_move;

			strafe = rt;
		}
	}
}

#define TICK_INTERVAL			( pValve->pGlobals->interval_per_tick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )

void ProcessSimulation(float flTime)
{
	if (flTime <= 0.0f)
		return;

	int target_Tick_men = TIME_TO_TICKS(flTime);
	if ((pValve->pGlobals->tickcount - target_Tick_men) > 8 || (pValve->pGlobals->tickcount - target_Tick_men) < -10)
		return;

	pValve->pGlobals->tickcount = target_Tick_men + TIME_TO_TICKS(0.031f);
}

void SetSmoothAngles(CUserCmd* pCmd, Vector& dst, int smoothX, int smoothY) {
		Vector delta = pCmd->viewangles - dst;
		delta.Clamp();
		float smoothx = smoothX + 0.2f;
		float smoothy = smoothY + 0.2f;
		dst.y = pCmd->viewangles.y - delta.y / smoothx;
		dst.x = pCmd->viewangles.x - delta.x / smoothy;
		dst.z = 0, delta.z = 0;
}


bool BulletTime = false;
bool bShouldAutoshoot = false;
Vector LastAngle;
bool aimbotting, antiaiming;

int bestTarget = -1;


int trkey, trd, trc;
bool tra, trh, xwall;

Vector viewTriggerAngles(0.0f, 0.0f, 0.0f);
void Triggerbot(CUserCmd* pCmd, C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon, bool& SendP) {

	trace_t trace;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = pLocal;


	if (vars::legit_wpns) {
		if (pWeapon->isRifle()) {
			tra = riflea;
			trh = rifleh;
			trc = riflec;
			trd = rifled;
			trkey = riflekey;
		}

		if (pWeapon->isSniper()) {
			tra = snipera;
			trh = sniperh;
			trc = sniperc;
			trd = sniperd;
			trkey = sniperkey;

		}
		else if (pWeapon->isSMG()) {
			tra = smga;
			trh = smgh;
			trc = smgc;
			trd = smgd;
			trkey = smgkey;
		}
		else if (pWeapon->isHeavy()) {
			tra = heavya;
			trh = heavyh;
			trc = heavyc;
			trd = heavyd;
			trkey = heavykey;
		}
		else if (pWeapon->isPistol()) {
			tra = pistola;
			trh = pistolh;
			trc = pistolc;
			trd = pistold;
			trkey = pistolkey;
		}
	}
	else if (!vars::legit_wpns) {
		tra = vars::legit_trigg;
		trh = vars::legit_head;
		trc = vars::trigg_cooldown;
		trd = vars::trigg_delay;
		trkey = vars::triggerkey;

	}

	if (!tra)
		return;

	if (pWeapon->IsKnife())
		return;

	if (pWeapon->iClip1() < 1)
		return;


	

	pValve->pEngine->GetViewAngles(viewTriggerAngles);
	viewTriggerAngles += pLocal->GetPunch() * 2.0f;

	Vector traceStart, traceEnd;
	C::NiggerVectors(viewTriggerAngles, traceEnd);

	traceStart = pLocal->GetEyePos();
	traceEnd = traceStart + (traceEnd * 8192.0f);



	ray.Init(traceStart, traceEnd); //0x46004003
	float dmg = 0.f;
	
	pValve->pEngineTrace->TraceRay(ray, 0x46004003, (CTraceFilter*)&filter, &trace);

	if (!trh) {
		if (!(trace.hitgroup < 10 && trace.hitgroup > 0))
			return;
	}
	else {
		if (!(trace.hitgroup == 1))
			return;
	}
	
	if (!vars::legit_team) {
		if (trace.m_pEnt->Team() == pLocal->Team())
			return;
	}
	if (trace.m_pEnt->Team() != 2 && trace.m_pEnt->Team() != 3)
		return;

	if (vars::Friend[trace.m_pEnt->GetIndex()])
		return;

	if (trace.m_pEnt->IsImmune())
		return;

	if (GetAsyncKeyState(trkey) & 0x8000) {
		
		static bool bAttack = false;
		static size_t lastTime = 0;
		if (GetTickCount() > lastTime) {
			lastTime = GetTickCount() + trd;
			if (bAttack) {
				pCmd->buttons &= ~IN_ATTACK;
			}
			else {
				pCmd->buttons |= IN_ATTACK;
			}
			bAttack = !bAttack;
			lastTime = GetTickCount() + trc;
		}
	}
	

}




bool xactive = false;
bool xpsilent = false;
int aimtime;
int holdtime = 0;
int xbone, xkey, xsmoothx, xsmoothy;
float xfov, xcurvevalue;
bool  xcurve, xteam;
int finalbone;
void LEGITBOT(CUserCmd* pCmd, C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon, bool& SendP) {
	if (!(GetForegroundWindow() == FindWindow(charenc("Valve001"), 0)))
		return;

	for (int i = 1; i < pValve->pEntList->GetHighestEntityIndex(); i++) {
		C_BaseEntity* pBaseEntity = (C_BaseEntity*)pValve->pEntList->GetClientEntity(i);


		if (!pBaseEntity)
			continue;

		if (!pBaseEntity->IsValid())
			continue;
		if (pBaseEntity->Team() != 2 && pBaseEntity->Team() != 3)
			continue;
		if (vars::Friend[pBaseEntity->GetIndex()])
			continue;


		if (vars::legit_wpns) {

			if (pWeapon->isRifle()) {
				xactive = rifle_active;
				xfov = rifle_fov;
				xbone = rifle_bone;
				xcurvevalue = rifle_curvevalue;
				xpsilent = rifle_psilent;
				xcurve = rifle_curve;
				xkey = rifle_aimkey;
				xsmoothx = rifle_smoothx;
				xsmoothy = rifle_smoothy;
				aimtime = rifle_aimtime;
				if (rifle_bone == 0 || rifle_bone == 1) {
					finalbone = 8;
				}
				else if (rifle_bone == 2) {
					finalbone = 7;
				}
				else if (rifle_bone == 3) {
					finalbone = 6;
				}
				else if (rifle_bone == 4) {
					finalbone = 5;
				}
				else if (rifle_bone == 5) {
					finalbone = 0;
				}
			}
			else if (pWeapon->isSniper()) {
				xactive = sniper_active;
				xfov = sniper_fov;
				xbone = sniper_bone;
				xcurvevalue = sniper_curvevalue;
				xpsilent = sniper_psilent;
				xcurve = sniper_curve;
				xkey = sniper_aimkey;
				xsmoothx = sniper_smoothx;
				xsmoothy = sniper_smoothy;
				aimtime = sniper_aimtime;
				if (sniper_bone == 0 || sniper_bone == 1) {
					finalbone = 8;
				}
				else if (sniper_bone == 2) {
					finalbone = 7;
				}
				else if (sniper_bone == 3) {
					finalbone = 6;
				}
				else if (sniper_bone == 4) {
					finalbone = 5;
				}
				else if (sniper_bone == 5) {
					finalbone = 0;
				}
			}
			else if (pWeapon->isPistol()) {
				xactive = pistol_active;
				xfov = pistol_fov;
				xbone = pistol_bone;
				xcurvevalue = pistol_curvevalue;
				xpsilent = pistol_psilent;
				xcurve = pistol_curve;
				xkey = pistol_aimkey;
				xsmoothx = pistol_smoothx;
				xsmoothy = pistol_smoothy;
				aimtime = pistol_aimtime;
				if (pistol_bone == 0 || pistol_bone == 1) {
					finalbone = 8;
				}
				else if (pistol_bone == 2) {
					finalbone = 7;
				}
				else if (pistol_bone == 3) {
					finalbone = 6;
				}
				else if (pistol_bone == 4) {
					finalbone = 5;
				}
				else if (pistol_bone == 5) {
					finalbone = 0;
				}

			}
			else if (pWeapon->isSMG()) {
				xactive = smg_active;
				xfov = smg_fov;
				xbone = smg_bone;
				xcurvevalue = smg_curvevalue;
				xpsilent = smg_psilent;
				xcurve = smg_curve;
				xkey = smg_aimkey;
				xsmoothx = smg_smoothx;
				xsmoothy = smg_smoothy;
				aimtime = smg_aimtime;
				if (smg_bone == 0 || smg_bone == 1) {
					finalbone = 8;
				}
				else if (smg_bone == 2) {
					finalbone = 7;
				}
				else if (smg_bone == 3) {
					finalbone = 6;
				}
				else if (smg_bone == 4) {
					finalbone = 5;
				}
				else if (smg_bone == 5) {
					finalbone = 0;
				}
			}
			else if (pWeapon->isHeavy()) {
				xactive = heavy_active;
				xfov = heavy_fov;
				xbone = heavy_bone;
				xcurvevalue = heavy_curvevalue;
				xpsilent = heavy_psilent;
				xcurve = heavy_curve;
				xkey = heavy_aimkey;
				xsmoothx = heavy_smoothx;
				xsmoothy = heavy_smoothy;
				aimtime = heavy_aimtime;
				if (heavy_bone == 0 || heavy_bone == 1) {
					finalbone = 8;
				}
				else if (heavy_bone == 2) {
					finalbone = 7;
				}
				else if (heavy_bone == 3) {
					finalbone = 6;
				}
				else if (heavy_bone == 4) {
					finalbone = 5;
				}
				else if (heavy_bone == 5) {
					finalbone = 0;
				}
			}
		}
		else if (!vars::legit_wpns) {
			xactive = vars::legit_active;
			xfov = vars::legit_fov;
			xcurvevalue = vars::aim_curvevalue;
			xpsilent = vars::legit_psilent;
			xcurve = vars::aim_curve;
			xkey = vars::aimkey;
			xsmoothx = iSmoothFactor;
			xsmoothy = iSmoothFactory;
			aimtime = vars::aim_time;
			if (vars::aim_boner1 == 0 || vars::aim_boner1 == 1) {
				finalbone = 8;
			}
			else if (vars::aim_boner1 == 2) {
				finalbone = 7;
			}
			else if (vars::aim_boner1 == 3) {
				finalbone = 6;
			}
			else if (vars::aim_boner1 == 4) {
				finalbone = 5;
			}
			else if (vars::aim_boner1 == 5) {
				finalbone = 0;
			}
		}

		if (!vars::legit_team && pBaseEntity->Team() == pLocal->Team())
			continue;

		if (pBaseEntity->Dormant())
			continue;

		if (pBaseEntity->IsImmune())
			continue;

		if (pWeapon->IsKnife())
			continue;

		if (pWeapon->iClip1() < 1)
			continue;

		if (PlayerFriend[pBaseEntity->GetIndex()])
			continue;
		if (!xactive)
			continue;
		bestTarget = i;
		if (bestTarget == -1)
			continue;

		if (aimtime > 0 && GetAsyncKeyState(xkey) & 0x8000) {
			holdtime++;
			if (holdtime > aimtime)
				continue;
		}
		else {
			holdtime = 0;
		}

		

		Vector vFrom, vAngles, myAngles;
		pValve->pEngine->GetViewAngles(vAngles);
		//vAngles = Vector(0.f, 0.f, 0.f);

		
		pValve->pEntList->GetClientEntity(bestTarget);
		GetBonePosition(pBaseEntity->BoneMatrix(), finalbone, vFrom);
		C::CalcAngle2(pLocal->GetEyePos(), vFrom, vAngles, pLocal, pWeapon);
		if (A::GetFOV2(pCmd->viewangles, pLocal->GetEyePos(), vFrom, pLocal) < xfov) {
			if (traceEngines->IsVisible(pBaseEntity, pLocal)) {
				if (GetAsyncKeyState(xkey) & 0x8000) {
					if (xpsilent) {
						if (pCmd->buttons & IN_ATTACK)
							pCmd->viewangles = vAngles;
					}
					else {
					
						if (xsmoothy > 0 && xsmoothx > 0)
							SetSmoothAngles(pCmd, vAngles, xsmoothx, xsmoothy);
						pValve->pEngine->SetViewAngles(vAngles);
				

					}

				}
			}
			else if (traceEngines->IsVisibleHDD(pBaseEntity, pLocal, vFrom, 8)) {
				if (GetAsyncKeyState(xkey) & 0x8000) {
					if (xpsilent) {
						if (pCmd->buttons & IN_ATTACK)
							pCmd->viewangles = vAngles;
					}
					else {

						if (xsmoothy > 0 && xsmoothx > 0)
							SetSmoothAngles(pCmd, vAngles, xsmoothx, xsmoothy);
						pValve->pEngine->SetViewAngles(vAngles);
		

					}

				}
			}
		}
	}
}














bool aActive = false;
int Mode = 0;
bool ShouldAcB = false;
void AccuracyBoost(CUserCmd* pCmd, C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon, bool& SendP) {
	if (!(GetForegroundWindow() == FindWindow(charenc("Valve001"), 0)))
		return;
	for (int i = 1; i < pValve->pEntList->GetHighestEntityIndex(); i++) {
		C_BaseEntity* pBaseEntity = (C_BaseEntity*)pValve->pEntList->GetClientEntity(i);
		bool aActive = false;
		int Mode = 0;

		if (!pBaseEntity)
			continue;

		if (!pBaseEntity->IsValid())
			continue;
		if (pBaseEntity->Team() != 2 && pBaseEntity->Team() != 3)
			continue;
		if (vars::Friend[pBaseEntity->GetIndex()])
			continue;
		

		if (vars::legit_wpns) {

			if (pWeapon->isRifle()) {
				aActive = rifle_aactive;
				Mode = rifle_aactive;
				
			}
			else if (pWeapon->isSniper()) {
				aActive = sniper_aactive;
				Mode = sniper_aactive;
			}
			else if (pWeapon->isPistol()) {
				aActive = pistol_aactive;
				Mode = pistol_aactive;

			}
			else if (pWeapon->isSMG()) {
				aActive = smg_aactive;
				Mode = smg_aactive;
			}
			else if (pWeapon->isHeavy()) {
				aActive = heavy_aactive;
				Mode = heavy_aactive;
			}
		}
		else if (!vars::legit_wpns) {
			aActive = vars::accuracyboost;
			Mode = vars::aaMode;
		}

		if (!vars::legit_team && pBaseEntity->Team() == pLocal->Team())
			continue;

		if (pBaseEntity->Dormant())
			continue;

		if (pBaseEntity->IsImmune())
			continue;

		if (pWeapon->IsKnife())
			continue;

		if (pWeapon->iClip1() < 1)
			continue;

		if (PlayerFriend[pBaseEntity->GetIndex()])
			continue;

		if (!aActive)
			continue;

		if (pLocal->shotsfired() > 1)
			continue;

		bestTarget = i;
		if (bestTarget == -1)
			continue;

		if (aimtime > 0 && (pCmd->buttons & IN_ATTACK)) {
			holdtime++;
			if (holdtime > aimtime)
				continue;
		}
		else {
			holdtime = 0;
		}



		Vector vFrom, vAngles, myAngles;
		pValve->pEngine->GetViewAngles(vAngles);
		static float fieldOfView = 0.4f;
		if (Mode == 0 || Mode == 1) { //static
			fieldOfView = 0.9432f;
		}
		else if (Mode == 2) {
			fieldOfView = 0.32234f; //smart
		}



		
		float m_flTime = pLocal->m_flSimulationTime();


		pValve->pEntList->GetClientEntity(bestTarget);
		GetBonePosition(pBaseEntity->BoneMatrix(), finalbone, vFrom);
		C::CalcAngle(pLocal->GetEyePos(), vFrom, vAngles, pLocal);
		
		if (A::GetFOV2(pCmd->viewangles, pLocal->GetEyePos(), vFrom, pLocal) < fieldOfView) {
			ProcessSimulation(m_flTime);
			if (traceEngines->IsVisible(pBaseEntity, pLocal)) {
				if (pCmd->buttons & IN_ATTACK) {
					ShouldAcB = true;
					//btrc->BacktrackEntity(pBaseEntity, tarTick);
					pCmd->viewangles = vAngles;
					//ReleaseVars(pBaseEntity);


			
				}
			}
			else if (traceEngines->IsVisibleHDD(pBaseEntity, pLocal, vFrom, 8)) {
				if (pCmd->buttons & IN_ATTACK) {
					ShouldAcB = true;
	
					//btrc->BacktrackEntity(pBaseEntity, tarTick);
					pCmd->viewangles = vAngles;
					//ReleaseVars(pBaseEntity);
	
				}
			}
			
		}
		else {
			ShouldAcB = false;
		}

		//else
			//StoreVars(pBaseEntity);
		
	}
}

void angleVectors(const Vector &angles, Vector &forward)
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward.x = cp*cy;
	forward.y = cp*sy;
	forward.z = -sp;
}
bool IsVisibleBone(C_BaseEntity* local, C_BaseEntity* entity, int iBone) {
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = local;

	ray.Init(local->GetEyePos(), GetBonePos(iBone, entity));
	pValve->pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &tr);

	return (tr.m_pEnt == entity || tr.fraction > 0.99f);
}
class Hitbox {
private:
	Vector points[22];
public:
	void FixHitbox(C_BaseEntity* entity)
	{
		for (int index = 0; index <= 8; ++index)
		{
			trace_t tr;
			Ray_t ray;
			CTraceFilter filter;
			filter.pSkip = entity;
			ray.Init(points[index], points[0]);
			pValve->pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

			points[index] = tr.endpos;
		}
	}
	Vector point(Vector &aimspot, int amount) {
		C_BaseEntity* ply = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
		if (amount < 1) amount = 1;
		float bestdamage = 0;
		for (int index = 0; index < amount; ++index)
		{
			Vector Aimangles;
			C::CalcAngle(ply->GetEyePos(), this->points[index], Aimangles, ply);
			float damage = GetDamage2(this->points[index], &bestdamage);
			aimspot = points[index];
				
			
		}
		return aimspot;
	}
	bool GetBestPoint(Vector &aimspot, int amount) {
		C_BaseEntity* ply = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
		if (amount < 1) amount = 1;
		float bestdamage = 0;
		for (int index = 0; index < amount; ++index)
		{
			Vector Aimangles;
			C::CalcAngle(ply->GetEyePos(), this->points[index], Aimangles, ply);
			float damage = GetDamage2(this->points[index], &bestdamage);
			if (damage > bestdamage)
			{
				aimspot = points[index];
				bestdamage = damage;
			}
		}
		return bestdamage > vars::aim_awall_factor;
	}
	void FindActualHitbox(C_BaseEntity* pEntity, Vector &best, C_BaseCombatWeapon* wep) {
		C_BaseEntity* ply = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
		FireKrulleData data;
		data.src = ply->GetEyePos();
		data.filter = CTraceFilter();
		data.filter.pSkip = ply;
		int bestdamage = 0;
		for (int i = -180; i < 180; i += 30)
		{
			Vector Angle = Vector(0, i, 0);
			angleVectors(Angle, data.direction);
			if (SimulateFireBullet2(wep, data, ply))
				if (data.current_damage > bestdamage)
				{
					bestdamage = data.current_damage;
					best = data.enter_trace.endpos;
				}
		}
	}
};



void VectorTransform(const Vector in1, float in2[3][4], Vector &out) {
	out[0] = DotProduct(in1, Vector(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3];
	out[1] = DotProduct(in1, Vector(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3];
	out[2] = DotProduct(in1, Vector(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3];
}


namespace hitscan {
	/*int isBone = 2;
	int looperdooper = 2;
	int primarybone = vars::aim_bone;
	int Hitscaner(C_BaseEntity* entity, C_BaseEntity* local) {
		//studiohdr_t* pmodel = pValve->pModelInfo->GetStudiomodel(entity->GetModel());
		
	//	if (!pmodel)
	//		return 0;
		isBone++;
		if (isBone > 10 && isBone < 36)
			isBone = 36;

		if (isBone > 42 && isBone < 62)
			isBone = 62;

		if (isBone > 67 && isBone < 70)
			isBone = 70;

		if (isBone > 74 && isBone < 77)
			isBone = 77;

		if (isBone > 77 && isBone < 87)
			isBone = 87;
		if (isBone > 88)
			isBone = 2;

		if (IsVisibleBone(local, entity, isBone)) {
			return isBone;
		}
		
	}
	int HitscanAutowall(C_BaseEntity* entity, Vector& vDst, float* damage) {
		studiohdr_t* pModel = pValve->pModelInfo->GetStudiomodel(entity->GetModel());
		if (!pModel)
			return 0;

		for (int i = 0; i < pModel->numbones; i++) {
			mstudiobone_t* pBone = pModel->GetBone(i);
			vDst = GetBonePos(i, entity);


			if (pBone && (pBone->flags & 0x100) && (pBone->parent != -1)) {
				if (GetDamage2(vDst, damage)) {
					return i;
				}
			}
		}
	}
	*/

	//p1000000000 hitscan.

	enum class Hitboxes {
		Head,
		Neck,
		NeckLower,
		Pelvis,
		Stomach,
		LowerChest,
		Chest,
		UpperChest,
		RightThigh,
		LeftThigh,
		RightShin,
		LeftShin,
		RightFoot,
		LeftFoot,
		RightHand,
		LeftHand,
		RightUpperArm,
		RightLowerArm,
		LeftUpperArm,
		LeftLowerArm
	};

	Vector GetHitboxPosition(C_BaseEntity* pEntity, int Hitbox) {
		matrix3x4 matrix[128];

		if (!pEntity->SetupBones(matrix, 128, 0x00000100, GetTickCount64()))
			return Vector(0, 0, 0);

		studiohdr_t* hdr = pValve->pModelInfo->GetStudiomodel(pEntity->GetModel());
		mstudiohitboxset_t* set = hdr->GetHitboxSet(0);

		mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

		if (!hitbox)
			return Vector(0, 0, 0);

		Vector vMin, vMax, vCenter, sCenter;
		VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
		VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
		vCenter = (vMin + vMax) *0.5f;
		return vCenter;
	}
	struct Target_t {
		Vector aimspot;
		C_BaseEntity* ent;
	};

	int iHitScan(C_BaseEntity* pEntity, C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon, Vector angles) { // Creds to Sfab and Syn!
		std::vector<int> box;
		Hitbox hbox;
		if (vars::hsMode == 2) {
			//simple
		
			box.push_back((int)Hitboxes::Head);
			box.push_back((int)Hitboxes::Neck);
			box.push_back((int)Hitboxes::UpperChest);
			box.push_back((int)Hitboxes::Chest);
			box.push_back((int)Hitboxes::Stomach);
			box.push_back((int)Hitboxes::Pelvis);
		}
		else if (vars::hsMode == 3) {
			//smart
			if (pWeapon->isPistol()) {

				box.push_back((int)Hitboxes::Neck);
				box.push_back((int)Hitboxes::Stomach);

			}
			else {
				box.push_back((int)Hitboxes::Head);
				box.push_back((int)Hitboxes::Neck);
				box.push_back((int)Hitboxes::UpperChest);
				box.push_back((int)Hitboxes::Chest);
				box.push_back((int)Hitboxes::Stomach);
				box.push_back((int)Hitboxes::Pelvis);
			}
		}
		else if (vars::hsMode == 4) {
			//advanced
			if (!pWeapon->isPistol()) {
				if (pWeapon->WeaponID() == WEAPON_AWP) {
					box.push_back((int)Hitboxes::UpperChest);
					box.push_back((int)Hitboxes::Chest);
					box.push_back((int)Hitboxes::Stomach);
					box.push_back((int)Hitboxes::Pelvis);
				}
				else if (pWeapon->WeaponID() == WEAPON_SSG08) {
					box.push_back((int)Hitboxes::Head);
					box.push_back((int)Hitboxes::Neck);
				}
				else {
					box.push_back((int)Hitboxes::Head);
					box.push_back((int)Hitboxes::Neck);
					box.push_back((int)Hitboxes::UpperChest);
					box.push_back((int)Hitboxes::Chest);
					box.push_back((int)Hitboxes::Stomach);
					box.push_back((int)Hitboxes::Pelvis);
					box.push_back((int)Hitboxes::LeftUpperArm);
					box.push_back((int)Hitboxes::RightUpperArm);
					box.push_back((int)Hitboxes::LeftThigh);
					box.push_back((int)Hitboxes::RightThigh);
					box.push_back((int)Hitboxes::Head);
					box.push_back((int)Hitboxes::LeftHand);
					box.push_back((int)Hitboxes::RightHand);
					box.push_back((int)Hitboxes::Neck);
					box.push_back((int)Hitboxes::LeftFoot);
					box.push_back((int)Hitboxes::RightFoot);
					box.push_back((int)Hitboxes::UpperChest);
					box.push_back((int)Hitboxes::LeftShin);
					box.push_back((int)Hitboxes::RightShin);
					box.push_back((int)Hitboxes::Neck);
					box.push_back((int)Hitboxes::LeftLowerArm);
					box.push_back((int)Hitboxes::RightLowerArm);
				}
			}
			else {
				box.push_back((int)Hitboxes::Head);
				box.push_back((int)Hitboxes::Neck);
				box.push_back((int)Hitboxes::UpperChest);
				box.push_back((int)Hitboxes::Chest);
				box.push_back((int)Hitboxes::Stomach);
				box.push_back((int)Hitboxes::Pelvis);
			}
		}
		else if (vars::hsMode == 5) {

		}

		







		for (auto HitBoxID : box)
		{
			if (vars::hsMode > 1)
			{
				
				Vector Point = GetHitboxPosition(pEntity, HitBoxID);				
				float Damage = 0;
				if (GetDamage2(Point, &Damage)) {
					return HitBoxID;
				}
			}
			else {
				return (int)Hitboxes::Head;
			}
		}
		return (int)Hitboxes::Head;
	}

}

bool hitscanning = false;
bool hHead = false;
bool hRest = false;
int cBone = 8;

bool bHitchance(float hitchance, C_BaseEntity* ply, CUserCmd* pCmd) {
	if (pCmd->buttons & IN_JUMP)
		return false;


	if (hitchance > 0 && hitchance <= 10) {
		if (ply->GetVelocity().Length2D() > 250)
			return false;
	}
	else if (hitchance > 10 && hitchance <= 25) {
		if (ply->GetVelocity().Length2D() > 200)
			return false;
	}
	else if (hitchance > 25 && hitchance <= 40) {
		if (ply->GetVelocity().Length2D() > 180)
			return false;
	}
	else if (hitchance > 40 && hitchance <= 65) {
		if (ply->GetVelocity().Length2D() > 130)
			return false;
	}
	else if (hitchance > 65 && hitchance <= 99) {
		if (ply->GetVelocity().Length2D() > 30)
			return false;
	}
	else if (hitchance >= 100) {
		if (ply->GetVelocity().Length2D() > 0)
			return false;
	}
	return true;	
}

#define TIME2TICKS( time ) ( (int)( .5f + ( (float)time / pValve->pGlobals->interval_per_tick ) ) )
int counter = 1;
void AdjustTickBase2(C_BaseEntity *localplayer, int simulation_ticks)
{
	// client pred fix
	if (counter == 15)
	{
		counter = 1;
	}

	if (counter == 1)
	{
		INetChannelInfo *netinfo = pValve->pEngine->GetNetChannelInfo();

		int correctionTicks = TIME2TICKS(netinfo->GetLatency(1))/*, 1 )*/;
		int idealTick = (localplayer->TickBase() + correctionTicks);

		localplayer->TickBase() = ((idealTick - simulation_ticks) + counter /*- 1*/);
	}
}

void AdjustTickBase(C_BaseEntity *localplayer, int simulation_ticks)
{
	INetChannelInfo *netinfo = pValve->pEngine->GetNetChannelInfo();

	int correctionTicks = TIME2TICKS(netinfo->GetLatency(1))/*, 1 )*/;
	int idealTick = (localplayer->TickBase() + correctionTicks);

	localplayer->TickBase() = ((idealTick - simulation_ticks) + counter /*- 1*/);

	if (counter == 15)
	{
		counter = 1;
	}
	else
	{
		counter++;
	}
}





int lastsentangle = 0;
void RAGEBOT(CUserCmd* pCmd, C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon, bool& SendP) {
	for (int i = 1; i < pValve->pEntList->GetHighestEntityIndex(); i++) {
		C_BaseEntity* pBaseEntity = (C_BaseEntity*)pValve->pEntList->GetClientEntity(i);

		if (!pBaseEntity)
			continue;

		if (!pBaseEntity->IsValid())
			continue;

		if (!vars::rage_active)
			continue;

		if (!vars::rage_team && pBaseEntity->Team() == pLocal->Team())
			continue;

		if (pBaseEntity->Dormant())
			continue;

		if (pBaseEntity->IsImmune())
			continue;

		if (pWeapon->IsKnife())
			continue;

		if (pWeapon->iClip1() < 1)
			continue;

		if (PlayerFriend[pBaseEntity->GetIndex()])
			continue;

		if (!pLocal->IsValid())
			continue;

		if (!pBaseEntity->IsValid())
			continue;

		if (pBaseEntity->Team() != 2 && pBaseEntity->Team() != 3)
			continue;
		if (vars::Friend[pBaseEntity->GetIndex()])
			continue;
		Vector vIfra, vAngles;
		pValve->pEngine->GetViewAngles(vAngles);
		float m_flTime = pBaseEntity->m_flSimulationTime();
		float dmgDamage = (vars::aim_awall_factor);
		if (vars::hsMode > 1) {
			
			vIfra = hitscan::GetHitboxPosition(pBaseEntity, hitscan::iHitScan(pBaseEntity, pLocal, pWeapon, vIfra));

		}
		else {
			if (vars::rage_awpbody) {
				if (pWeapon->WeaponID() == WEAPON_AWP) {
					GetBonePosition(pBaseEntity->BoneMatrix(), 4, vIfra);
				}
				else {
					GetBonePosition(pBaseEntity->BoneMatrix(), vars::aim_bone, vIfra);
				}
			}
			else
				GetBonePosition(pBaseEntity->BoneMatrix(), vars::aim_bone, vIfra);
		}

		
		C::CalcAngle(pLocal->GetEyePos(), vIfra, vAngles, pLocal);


		bool bAttack = true;
		if (pLocal->NextAttack() - pValve->pGlobals->interval_per_tick > pLocal->TickBase() * pValve->pGlobals->interval_per_tick)
			bAttack = false;


		float hurenkorn = vars::aim_hitchanceF / 4.f;
		float hitchance = 70.f + hurenkorn;

		if (A::GetFOV2(pCmd->viewangles, pLocal->GetEyePos(), vIfra, pLocal) < (vars::aim_fov)) {
			if (vars::rage_awall ? GetDamage2(vIfra, &dmgDamage) : IsVisible(pLocal, pBaseEntity)) {
				if (vars::rage_autocrouch) {
					pCmd->buttons |= IN_DUCK;
				}
				
				ProcessSimulation(m_flTime);
				if (vars::rage_autoscope) {
					if (pWeapon->isSniper()) {
						if (pLocal->IsScoped()) {

						}
						else {
							pCmd->buttons |= IN_ATTACK2;
						}
					}
				}
				static int maxSleep = 0;
				static int mySleep = 0;
				if (vars::rage_autoshoot && !(pCmd->buttons & IN_ATTACK) && bAttack) {
					if (pWeapon->isSniper()) {
						if (vars::autorest && (pWeapon->WeaponID() == WEAPON_AWP || pWeapon->WeaponID() == WEAPON_SSG08)) {
							mySleep++;
							maxSleep = 1200;
							if (mySleep >= maxSleep + 200)
								mySleep = 0;
						}
						else {
							mySleep = 0;
							maxSleep = 0;
						}
						if (pLocal->IsScoped() && vars::rage_autoscope)
						{
							if (vars::rage_autoshoot && (mySleep >= maxSleep)) {
								if (bHitchance(vars::aim_hitchanceF, pLocal, pCmd) && (vars::aim_hitchanceF > 0 && (pWeapon && (1.0f - pWeapon->GetAccuracyPenalty()) * 100.f >= hitchance)))
									pCmd->buttons |= IN_ATTACK;
								else if (vars::aim_hitchanceF == 0)
									pCmd->buttons |= IN_ATTACK;

								shots_fired++;
							}
						}
					}
					else {
						if (vars::rage_autoshoot) {
							if (bHitchance(vars::aim_hitchanceF, pLocal, pCmd) && (vars::aim_hitchanceF > 0 && (pWeapon && (1.0f - pWeapon->GetAccuracyPenalty()) * 100.f >= hitchance)))
								pCmd->buttons |= IN_ATTACK;
							else if (vars::aim_hitchanceF == 0)
								pCmd->buttons |= IN_ATTACK;


							shots_fired++;
						}
					}
				}
				if (vars::rage_autostop) {
					pCmd->forwardmove = 0.0f;
					pCmd->sidemove = 0.0f;
				}

				if (pCmd->buttons & IN_ATTACK) {
					if (vars::rage_psilent) {
						pCmd->viewangles = vAngles;
					}
					else {
						pValve->pEngine->SetViewAngles(vAngles);



					}
				}
			}
		}
	}
}
void MakeRecoil(CUserCmd* pCmd, C_BaseEntity* pLocal) {
	if (vars::aim_recoil && (pCmd->buttons & IN_ATTACK)) {
		Vector SurNeger = pLocal->GetPunch() * 2.f;
		pCmd->viewangles.x -= SurNeger.x;
		pCmd->viewangles.y -= SurNeger.y;
		
	}
}
bool fixLook = false;

void doorspammer(CUserCmd* pCmd) {
	if (vars::doorspam && (GetAsyncKeyState(vars::spamKey) & 0x8000)) {
		static bool bAttack = false;
		if (vars::spamKey == 1)
			return;
		if (bAttack) {
			pCmd->buttons &= ~IN_USE;
		}
		else {
			pCmd->buttons |= IN_USE;
		}
		bAttack = !bAttack;
	}
}

void MakeAutoPistol(CUserCmd* pCmd, C_BaseCombatWeapon* pWeapon) {
	if (vars::rage_active && vars::rage_autopistol && (pCmd->buttons & IN_ATTACK) && (pWeapon->isPistol() || pWeapon->isSniper())) {
		static bool bAttack = false;
		static int Sreep = 0;

		if (bAttack) {
			pCmd->buttons &= ~IN_ATTACK;
		}
		else {
			pCmd->buttons |= IN_ATTACK;
		}
		bAttack = !bAttack;
	}
}
void RotateMovement(CUserCmd* pCmd, float rotation)
{
	rotation = DEG2RAD(rotation);

	float cos_rot = cos(rotation);
	float sin_rot = sin(rotation);

	float new_forwardmove = (cos_rot * pCmd->forwardmove) - (sin_rot * pCmd->sidemove);
	float new_sidemove = (sin_rot * pCmd->forwardmove) + (cos_rot * pCmd->sidemove);

	pCmd->forwardmove = new_forwardmove;
	pCmd->sidemove = new_sidemove;
}



void teleStrafer(CUserCmd * cmd, C_BaseEntity * Local, bool &bSendPacket)
{
	if (!Local)
		return;

	static bool bDirection = true;

	static float move = 450.f;
	float s_move = move * 0.6395f;

	if ((cmd->buttons & IN_JUMP) || !(Local->Flags() & FL_ONGROUND)) 
	{
		if (Local->GetVelocity().Length() < 20.f) {
			cmd->forwardmove = 450.f;
		}
		else {
			cmd->forwardmove = move * 0.015f;
		}
		
		cmd->sidemove += (float)(((cmd->tick_count % 2) * 2) - 1) * s_move;

		if (cmd->mousedx)
			cmd->sidemove = (float)(cmd->mousedx, -1, 1) * s_move;
		static float strafe = cmd->viewangles.y;

		float rt = cmd->viewangles.y, rotation;
		rotation = strafe - rt;

		if (rotation < FloatNegate(pValve->pGlobals->interval_per_tick))
			cmd->sidemove = -s_move;

		if (rotation > pValve->pGlobals->interval_per_tick)
			cmd->sidemove = s_move;

		strafe = rt;
	}

	auto Delta = 0.f;

	if ((cmd->buttons & IN_JUMP) && (Local->Flags() & FL_ONGROUND) && Local->GetVelocity().Length() <= 50.f) // should we check for velocity? idk it could be useless
	{
		cmd->forwardmove = 450.f;
	}

	if (Local->GetVelocity().Length() > 50.f) // again could it be useless?
	{
		auto x = 30.f;
		auto z = x / Local->GetVelocity().Length();
		z = fabsf(z);
		auto a = x * z;
		Delta = a;
	}

	if ((cmd->buttons & IN_JUMP) && !(Local->Flags() & FL_ONGROUND))
	{
		if (cmd->mousedx < 0)
		{
			cmd->sidemove = -450;
		}

		if (cmd->mousedx > 0)
		{
			cmd->sidemove = 450;
		}

		if (cmd->tick_count % 2)
		{
			cmd->sidemove = -450;
		}
		else
		{
			cmd->viewangles.y += Delta;
			cmd->sidemove = 450;
		}
	}
}

void MakeAutoPistol2(CUserCmd* pCmd, C_BaseCombatWeapon* pWeapon) {
	if (vars::legit_active && vars::legit_autopistol && (pCmd->buttons & IN_ATTACK) && pWeapon->isPistol()) {
		static bool bAttack = false;
		if (bAttack) {
			pCmd->buttons &= ~IN_ATTACK;
		}
		else {
			pCmd->buttons |= IN_ATTACK;
		}
		bAttack = !bAttack;
	}
}

CTraceFilterWorldOnly tfNoPlayers;


int intervaltick = 0;
int chapamtick = 1;
void Chatspam() {

	if (!vars::misc_chatspam)
		return;
	chapamtick++;
	if (pValve->pEngine->IsConnected() && pValve->pEngine->IsInGame() && chapamtick >= 200) {
		pValve->pEngine->ExecuteClientCmd("say parallax ist mein gang brudda");
		chapamtick = 1;
	}
}


void shit(C_BaseCombatWeapon* pWeapon) {
	static bool pSwitch = false;
	if (vars::misc_knife == 2) {
		if (pWeapon->IsKnife()) {
			pValve->pEngine->ExecuteClientCmd("cl_righthand 0");
		}
		else {
			pValve->pEngine->ExecuteClientCmd("cl_righthand 1");
		}
	}
	else if (vars::misc_knife == 3) {
		if (pWeapon->IsKnife()) {
			pValve->pEngine->ExecuteClientCmd("cl_righthand 1");
		}
		else {
			pValve->pEngine->ExecuteClientCmd("cl_righthand 0");
		}
	}

}

void AtTargets(CUserCmd* cmd, C_BaseEntity* localPly) {
	float lowest = 99999999.f;
	

	for (int i = 1; i < 65; i++) {
		if (i == pValve->pEngine->GetLocalPlayer()) continue;
		C_BaseEntity* pEnt = pValve->pEntList->GetClientEntity(i);
		if (!pEnt) continue;
		if (pEnt->Dormant()) continue;
		if (pEnt->Health() < 1) continue;
		if (pEnt->Team() == localPly->Team()) continue;
		if (vars::Friend[pEnt->GetIndex()]) continue;

		Vector CurPos = pEnt->GetAngles() + pEnt->GetAbsOrigin();

		if (CurPos.DistToSqr(localPly->GetEyePos()) < lowest) {
			lowest = CurPos.DistTo(localPly->GetEyePos());
			C::CalcAngle(localPly->GetEyePos(), CurPos, cmd->viewangles, localPly);
		}
	}
}



float flWall = 0, flCornor = 0;
bool jitterticky = false;
static auto jitterangs = 0;
static auto jitterangs2 = 0;
static auto jittertick1 = -1;
static auto jittertick2 = -1;
static auto faketimer = 1;
auto Random = 0;

float sseSqrt(float x)
{
	float root = 0.0f;

	__asm
	{
		sqrtss xmm0, x
		movss root, xmm0
	}

	return root;
}
#define square(x) (x * x)
void vectorAnglesVec(Vector forward, Vector &angles)
{
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f;
		angles[1] = 0.0f;
	}
	else
	{
		float len2d = sseSqrt(square(forward[0]) + square(forward[1]));

		angles[0] = RAD2DEG(atan2f(-forward[2], len2d));
		angles[1] = RAD2DEG(atan2f(forward[1], forward[0]));

		if (angles[0] < 0.0f) angles[0] += 360.0f;
		if (angles[1] < 0.0f) angles[1] += 360.0f;
	}
}

int lastEdgeY = 0;
static bool EdgeAntiAim(Vector in, Vector& out, int faketimer, int jittertimer, C_BaseEntity* local, bool &sendp)
{
	if (vars::misc_edge < 2)
		return false;

	Ray_t ray;
	trace_t tr;
	CTraceFilterWorldOnly traceFilter;

	if (faketimer > 0)
		faketimer = -1;
	faketimer++;

	auto vecCurPos = local->GetEyePos();

	for (float i = 0; i < 360; i++)
	{
		Vector vecDummy(10.f, in.y, 0.f);
		vecDummy.y += i;
		vecDummy.Normalized();

		Vector vecForward;
		angleVectors(vecDummy, vecForward);

		auto flLength = ((16.f + 3.f) + ((16.f + 3.f) * sin(DEG2RAD(10.f)))) + 7.f;
		vecForward *= flLength;

		ray.Init(vecCurPos, (vecCurPos + vecForward));
		pValve->pEngineTrace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);

		if (tr.DidHit())
		{
			float flWall = 0, flCornor = 0;
			if (vars::misc_edge == 2) {
		
					flCornor = -90.0f;
				

			}
			else if (vars::misc_edge == 3) {
				if (!vars::aa_fake)
				{
					flCornor = -45.0f;
				}

				else {
					if (!sendp) { flCornor = -45.0f; }
					else { flCornor = 90.f; }
				}
			}
			else if (vars::misc_edge == 4) {
					if (!sendp) { flCornor = -90.f; }
					else { flCornor = 90.f; }
			}

			if (vars::aa_fake) {
				if (sendp) {
					flWall = 0.f;
				}
				else {
					static bool e = false;
					static int o = 0;
					o++;
					if (o > 6) {
						e = !e;
						o = 0;
					}
					if (e) flWall = 20.3f;
					else flWall = -20.3f;

				}
			}
			else {
				if (vars::misc_edge == 3) {
					static bool r = false;
					r = !r;
					if (r) flWall = 20.3f;
					else flWall = -20.3f;
				}
				else
					flWall = 0.000f;
			}

			Vector qAngles;
			auto vecNegate = tr.plane.normal;

			vecNegate *= -1.f;
			vectorAnglesVec(vecNegate, qAngles);

			qAngles.Normalized();

			vecDummy.y = qAngles.y;

			trace_t leftTrace, rightTrace;

			Vector vecLeft;
			angleVectors(vecDummy + Vector(0.f, 30.f, 0.f), vecLeft);

			Vector vecRight;
			angleVectors(vecDummy - Vector(0.f, 30.f, 0.f), vecRight);

			vecLeft *= (flLength + (flLength * sin(DEG2RAD(30.f))));
			vecRight *= (flLength + (flLength * sin(DEG2RAD(30.f))));

			ray.Init(vecCurPos, (vecCurPos + vecLeft));
			pValve->pEngineTrace->TraceRay(ray, MASK_SHOT, &traceFilter, &leftTrace);

			ray.Init(vecCurPos, (vecCurPos + vecRight));
			pValve->pEngineTrace->TraceRay(ray, MASK_SHOT, &traceFilter, &rightTrace);

			if ((!leftTrace.DidHit()) && (rightTrace.DidHit()))
				vecDummy.y += flCornor; // left
			else if ((leftTrace.DidHit()) && (!rightTrace.DidHit()))
				vecDummy.y -= flCornor; // right

			out.y = vecDummy.y;
			vecDummy.y = lastEdgeY;
			out.y -= flWall;
			return true;
		}
	}

	return false;
}
int reex = 0;
int spin = 90;
bool switchAngles = false;
int pJit = 0;
bool switchFake = false;
Vector edgeangle;
float swapAng = 0.0f;
float body = 0.0f;
bool fuckingOnce = false;
void pHuvud(CUserCmd* cmd, C_BaseEntity* ply, bool& bSP, C_BaseCombatWeapon *vapen) {
	
	/* epic checks for lulze to not crash !!! */

	if ((vars::misc_pitch > 1 || vars::misc_yaw > 1))
		return;
	if (!vars::headfix)
		return;
	if (cmd->buttons & IN_ATTACK)
		return;
	if (cmd->buttons & IN_GRENADE1)
		return;
	if (cmd->buttons & IN_GRENADE2)
		return;
	if (cmd->buttons & IN_ATTACK3)
		return;
	if (vapen->IsGrenades())
		return;
	if (ply->Health() < 1)
		return;
	if (ply->MoveType() == MOVETYPE_LADDER)
		return;
	if (ply->MoveType() == MOVETYPE_NOCLIP)
		return;

	/* actual feeture! haha plopp u feel??? */
	if (vars::misc_fakelag < 1) {
		switchFake = !switchFake;
		if (switchFake)
			bSP = false;
		else bSP = true;
	}
	float angle = vars::randmizeXd + 000.f;
	if (!bSP) {
		cmd->viewangles.y += angle;	
	}
}


bool DynamicAA(CUserCmd* cmd, C_BaseEntity* localPly) {
	for (int i = 1; i < 65; i++) {
		if (i == pValve->pEngine->GetLocalPlayer()) continue;
		C_BaseEntity* pEnt = pValve->pEntList->GetClientEntity(i);
		if (!pEnt) continue;
		if (pEnt->Dormant()) continue;
		if (pEnt->Health() < 1) continue;
		if (pEnt->Team() == localPly->Team()) continue;
		if (vars::Friend[pEnt->GetIndex()]) continue;
		return true;
	}
	return false;
}

bool ShouldFake()
{
	bool will_update = false;
	static float lby_time = 0;

	float server_time = pValve->pGlobals->curtime;

	INetChannelInfo* nci = pValve->pEngine->GetNetChannelInfo();

	float latency = nci->GetAvgLatency(0);

	if (server_time >= (lby_time - latency))
	{
		lby_time = server_time + 1.1f;
		will_update = true;
	}

	return will_update;
}

void MakeAntiAim(CUserCmd* pCmd, C_BaseEntity* pLocalEntity, C_BaseCombatWeapon* pWeapon, bool& SendP, bool fl) {
	if ((!vars::misc_pitch > 1 || !vars::misc_yaw > 1))
		return;
	
	if (!vars::rage_active)
		return;

	if (pLocalEntity->Health() < 1)
		return;

	if (!DynamicAA(pCmd, pLocalEntity) && vars::dynamicaa)
		return;

	if (pCmd->buttons & IN_USE)
		return;
	if (pWeapon->IsKnife()) {
		if ((pCmd->buttons & IN_ATTACK) || (pCmd->buttons & IN_ATTACK2))
			return;
	}
	static bool hasAttacked = false;
	if (pWeapon->IsGrenades()) {
		if ((pCmd->buttons & IN_ATTACK) || (pCmd->buttons & IN_ATTACK2)) {
			hasAttacked = true;
			return;
		}
		else {
			static int fluga = 0;
			if (hasAttacked) {
				fluga++;
				if (fluga < 60) {
					return;
				}
				else {
					hasAttacked = false;
				}
			}
			else {
				fluga = 0;
			}
		}
	}
	else {
		hasAttacked = false;
	}
	if (pLocalEntity->MoveType() == MOVETYPE_LADDER)
		return;
	if (pLocalEntity->MoveType() == MOVETYPE_NOCLIP)
		return;

	static auto shouldChoke = 0;
	shouldChoke++;
	static int lastAng = 0;
	bool bAttack = true;
	if (pLocalEntity->NextAttack() - pValve->pGlobals->interval_per_tick > pLocalEntity->TickBase() * pValve->pGlobals->interval_per_tick)
		bAttack = false;


	if (pLocalEntity->IsValid()) {
		if ((pCmd->buttons & IN_ATTACK) && (bAttack) && shouldChoke < 12) {
			lastAng = pCmd->viewangles.y;
			if (fuckingOnce) {
				SendP = false;
				fuckingOnce = false;
			}
		}
		else {
			if (!fuckingOnce) {
				SendP = true;
				fuckingOnce = true;
			}
			//SendP = true;
			shouldChoke = 0;

		


		

			/*PITCH ANTI AIMS XDDDDDDDDDDDDDDDD*/
			if (vars::aa_at_target) {
				AtTargets(pCmd, pLocalEntity);
			}

			if (vars::misc_pitch == 2) {
				pCmd->viewangles.x = 88.8887f; ///becoz schaufel
			}
			else if (vars::misc_pitch == 3) {
		
				static bool snood = false;
				snood = !snood;
				if (!snood)
					pCmd->viewangles.x = -89;		//jitter
				else
					pCmd->viewangles.x = 89;
				
				
			}
			else if (vars::misc_pitch == 4) {
				static bool snood = false;
				snood = !snood;
				if (!snood)
					pCmd->viewangles.x = 80;		//jitter
				else
					pCmd->viewangles.x = 89;


			}

			/*YAW ANTI AIMS XDDDDDDDDDDDDDDDD*/
			static auto jittertick1 = -1;
			static auto faketimer = 1;
			if (faketimer > 0)
				faketimer = -1;
			faketimer++;

			static bool direction = false;

			if (pCmd->sidemove > 0)
			{
				direction = true;
			}
			else if (pCmd->sidemove < 0)
			{
				direction = false;
			}


			if ((!EdgeAntiAim(pCmd->viewangles, pCmd->viewangles, faketimer, jittertick1, pLocalEntity, SendP))) 
			{
				/*if (pLocalEntity->GetVelocity().Length() > 0.5)
				{
					pCmd->viewangles.y += 180;
				}*/
				//else
				{
					/*
						"Off",
						"Backward",
						"Forward",
						"Sideways",
						"Jitter",
						"Spin"
					*/
					
					switch (vars::misc_yaw)
					{
					case 2:
					{
						if (ShouldFake())
						{
							if (!SendP)
							{
								pCmd->viewangles.y += 180;
							}
							else
							{
								pCmd->viewangles.y += 0;
							}
						}
						else
						{
							if (!SendP)
							{
								pCmd->viewangles.y += 0;
							}
							else
							{
								pCmd->viewangles.y += 180;
							}
						}
					}break;

					case 3:
					{
						if (ShouldFake())
						{
							if (!SendP)
							{
								pCmd->viewangles.y += 0;
							}
							else
							{
								pCmd->viewangles.y += 180;
							}
						}
						else
						{
							if (!SendP)
							{
								pCmd->viewangles.y += 180;
							}
							else
							{
								pCmd->viewangles.y += 0;
							}
						}
					}break;

					case 4:
					{
						if (ShouldFake())
						{
							if (!SendP)
							{
								pCmd->viewangles.y += direction ? 90 : 270;
							}
							else
							{
								pCmd->viewangles.y += direction ? 270 : 90;
							}
						}
						else
						{
							if (!SendP)
							{
								pCmd->viewangles.y += direction ? 270 : 90;
							}
							else
							{
								pCmd->viewangles.y += direction ? 90 : 270;
							}
						}
					}break;

					case 5:
					{
						if (ShouldFake())
						{
							if (!SendP)
							{
								pCmd->viewangles.y += 90 + direction ? 35 : -35;
							}
							else
							{
								pCmd->viewangles.y -= 90 + direction ? 35 : -35;
							}
						}
						else
						{
							if (!SendP)
							{
								pCmd->viewangles.y -= 90 + direction ? 35 : -35;
							}
							else
							{
								pCmd->viewangles.y += 90 + direction ? 35 : -35;
							}
						}
					}break;

					case 6:
					{
						if (!SendP)
						{
							if (direction)
								pCmd->viewangles.y += (float)(fmod(pValve->pGlobals->curtime / 0.9f * 720.0f, 360.0f));
							else
								pCmd->viewangles.y -= (float)(fmod(pValve->pGlobals->curtime / 1.8f * 720.0f, 360.0f));
						}
						else
						{
							pCmd->viewangles.y += direction ? 90 : 270;
						}
					}break;
					}
				}
			}
			
		}
	}
}


void RagePsilentAim(CUserCmd* pCmd, C_BaseEntity* pLocalEntity, C_BaseCombatWeapon* pWeapon, Vector OldView, float OldForward, float OldSidemove, bool& SendP) {
	
	if (vars::misc_pitch > 1 || vars::misc_yaw > 1)
		return;

	bool bAttack = true;
	if (pLocalEntity->NextAttack() - pValve->pGlobals->interval_per_tick > pLocalEntity->TickBase() * pValve->pGlobals->interval_per_tick)
		bAttack = false;


	if (pWeapon->iClip1() < 1)
		return;

	if (pLocalEntity->IsValid() && !(pWeapon->IsKnife())) {
		if ((pCmd->buttons & IN_ATTACK) && (bAttack)) {
			SendP = false;
			
		}
		else {
			SendP = true;
			pCmd->viewangles = OldView;
			pCmd->forwardmove = OldForward;
			pCmd->sidemove = OldSidemove;
		}
	}
}




void EnginePrediction(C_BaseEntity* self, CUserCmd* cmd) {
	int tickBase = self->TickBase();

	float oldCurTime = pValve->pGlobals->curtime;
	float oldFrameTime = pValve->pGlobals->frametime;

	pValve->pGlobals->curtime = self->TickBase() * pValve->pGlobals->interval_per_tick;
	pValve->pGlobals->frametime = pValve->pGlobals->interval_per_tick;

	CUserCmd oldCmd;

	memcpy(&oldCmd, cmd, sizeof(CUserCmd));

	CMoveData move_data;
	memset(&move_data, 0, sizeof(move_data));

	pMoveHelper->SetHost(self);

	pPrediction->SetupMove(self, cmd, NULL, &move_data);
	pGameMovement->ProcessMovement(self, &move_data);
	pPrediction->FinishMove(self, cmd, &move_data);

	if (oldCmd.hasbeenpredicted) {
		tickBase = self->TickBase();
	}
	else {
		++tickBase;
	}

	pMoveHelper->SetHost(NULL);
	pValve->pGlobals->curtime = oldCurTime;
	pValve->pGlobals->frametime = oldFrameTime;
}

enum class EClassIds : int
{
	CAI_BaseNPC = 0,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBreakableProp,
	CBreakableSurface,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMaterialModifyControl,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPlantedC4,
	CPlasma,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWorld,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail
};

typedef void(__thiscall* tRunCommand)(void*, C_BaseEntity *, CUserCmd *, IMoveHelper *);
tRunCommand oRunCommand;

void __fastcall hkRunCommand(void* ecx, void* edx, C_BaseEntity* player, CUserCmd* pCmd, IMoveHelper* moveHelper) {
	oRunCommand(ecx, player, pCmd, moveHelper);
}
void NormaliseViewAngle(Vector &angle)
{
	while (angle.y <= -180) angle.y += 360;
	while (angle.y > 180) angle.y -= 360;
	while (angle.x <= -180) angle.x += 360;
	while (angle.x > 180) angle.x -= 360;


	if (angle.x > 89.0) angle.x = 89;
	if (angle.x < -89.0) angle.x = -89;
	if (angle.y < -180) angle.y = -179.999;
	if (angle.y > 180) angle.y = 179.999;

	angle.z = 0;
}


int ixx = -1;
int itrapbot = 0;
const wchar_t* WeaponIcons(int WeaponID) {
	switch (WeaponID) {
		/*pistols*/
	case 4:
		return L"U+E004";
	case 2:
		return L"U+E002";
	case 36:
		return L"U+E036";
	case 30:
		return L"U+E030";
	case 1:
		return L"U+E001";
	case 32:
		return L"U+E032";
	case 3:
		return L"U+E003";
	case 64:
		return L"U+E064";
	case 63:
		return L"U+E063";
	case 61:
		return L"U+E061";
		/*heavy*/
	case 35:
		return L"U+E035";
	case 25:
		return L"U+E025";
	case 29:
		return L"U+E029";
	case 14:
		return L"U+E014";
	case 28:
		return L"U+E028";
	case 27:
		return L"U+E027";
		/*smgs*/
	case 17:
		return L"U+E017";
	case 33:
		return L"U+E033";
	case 24:
		return L"U+E024";
	case 19:
		return L"U+E019";
	case 26:
		return L"U+E026";
	case 34:
		return L"U+E034";
		/*rifles*/
	case 10:
		return L"U+E010";
	case 16:
		return L"U+E016";
	case 40:
		return L"U+E040";
	case 8:
		return L"U+E008";
	case 9:
		return L"U+E009";
	case 38:
		return L"U+E038";
	case 13:
		return L"U+E013";
	case 7:
		return L"U+E007";
	case 39:
		return L"U+E039";
	case 11:
		return L"U+E011";
	case 60:
		return L"U+E060";
		/*grenades*/
	case 46:
		return L"U+E046";
	case 48:
		return L"U+E048";
	case 44:
		return L"U+E044";
	case 43:
		return L"U+E043";
	case 45:
		return L"U+E045";
	case 47:
		return L"U+E047";
		/*other*/
	case 31:
		return L"U+E031";
	case 49:
		return L"U+E049";
	case 42:
		return L"U+E042";
	case 59:
		return L"U+E059";
	case 500:
		return L"U+E504";
	case 505:
		return L"U+E505";
	case 506:
		return L"U+E506";
	case 507:
		return L"U+E507";

	case 508:
		return L"U+E508";
	case 509:
		return L"U+E509";
	case 512:
		return L"U+E512";
	case 514:
		return L"U+E514";
	case 515:
		return L"U+E515";
	case 516:
		return L"U+E516";
	default:
		return L"U+E049";
	}

	/*return (id == 42 || id == 59 || id == 500 || id == 505 || id == 506 || id == 507 || id == 508 || id == 509 || id == 512 || id == 514 || id == 515 || id == 516);*/
}
std::string IconWeapon(int id, C_BaseCombatWeapon* weapon)
{

	if (!weapon)
		return "";

	switch (id)
	{
		/*pistols*/
	case WEAPON_GLOCK18:
		return "s";
	case WEAPON_DUALBERETTAS:
		return "m";
	case WEAPON_P250:
		return "v";
	case WEAPON_TEC9:
		return "2";
	case WEAPON_DEAGLE:
		return "k";
	case WEAPON_HPK2000:
		return "S";
	case WEAPON_FIVESEVEN:
		return "o";
	case WEAPON_R8REVOLVER:
		return "T";
	case WEAPON_CZ75A:
		return "k";
	case WEAPON_USP_S:
		return "4";
		/*heavy*/
	case WEAPON_NOVA:
		return "Q";
	case WEAPON_XM1014:
		return "5";
	case WEAPON_SAWEDOFF:
		return "V";
	case WEAPON_M249:
		return "J";
	case WEAPON_NEGEV:
		return "P";
	case WEAPON_MAG7:
		return "K";
		/*smgs*/
	case WEAPON_MAC10:
		return "K";
	case WEAPON_MP7:
		return "N";
	case WEAPON_UMP45:
		return "3";
	case WEAPON_P90:
		return "R";
	case WEAPON_BIZON:
		return "h";
	case WEAPON_MP9:
		return "O";
		/*rifles*/
	case WEAPON_FAMAS:
		return "n";
	case WEAPON_M4A4:
		return "H";
	case WEAPON_SSG08:
		return "Z";
	case WEAPON_AUG:
		return "e";
	case WEAPON_AWP:
		return "f";
	case WEAPON_SCAR20:
		return "W";
	case WEAPON_GALILAR:
		return "r";
	case WEAPON_AK47:
		return "d";
	case WEAPON_SG553:
		return "X";
	case WEAPON_G3SG1:
		return "q";
	case WEAPON_M4A1_SILENCER:
		return "I";
		/*grenades*/
	case WEAPON_MOLOTOV:
		return "M";
	case WEAPON_INCGRENADE:
		return "w";
	case WEAPON_HEGRENADE:
		return "t";
	case WEAPON_FLASHBANG:
		return "p";
	case WEAPON_SMOKEGRENADE:
		return "Y";
	case WEAPON_DECOY:
		return "l";
		/*others*/
	case WEAPON_ZEUS:
		return "1";
	case WEAPON_KARAMBIT:
		return "C";
	case WEAPON_HUNTSMAN:
		return "G";
	case WEAPON_M9:
		return "D";
	case WEAPON_FLIP:
		return "A";
	case WEAPON_BAYONET:
		return "e";
	case WEAPON_FALCHION:
		return "z";
	case WEAPON_DAGGER:
		return "E";
	case WEAPON_BOWIE:
		return "u";
	case WEAPON_GUT:
		return "B";
	case WEAPON_BUTTERFLY:
		return "y";
	case WEAPON_C4:
		return "i";
	case WEAPON_KNIFE:
		return "x";
	case WEAPON_KNIFE_T:
		return "F";
	}

	return "";
}


const char* GetWeaponName(int WeaponID) {
	switch (WeaponID) {
		/*pistols*/
	case 4:
		return "Glock-18";
	case 2:
		return "Dual Berettas";
	case 36:
		return "P250";
	case 30:
		return "Tec-9";
	case 1:
		return "Desert Eagle";
	case 32:
		return "P2000";
	case 3:
		return "Five-SeveN";
	case 64:
		return "R8 Revolver";
	case 63:
		return "CZ-75";
	case 61:
		return "USP-S";
		/*heavy*/
	case 35:
		return "Nova";
	case 25:
		return "XM1014";
	case 29:
		return "Sawed-Off";
	case 14:
		return "M249";
	case 28:
		return "Negev";
	case 27:
		return "Mag-7";
		/*smgs*/
	case 17:
		return "MAC-10";
	case 33:
		return "MP7";
	case 24:
		return "UMP45";
	case 19:
		return "P90";
	case 26:
		return "PP-Bizon";
	case 34:
		return "MP9";
		/*rifles*/
	case 10:
		return "Famas";
	case 16:
		return "M4A4";
	case 40:
		return "SSG 08";
	case 8:
		return "AUG";
	case 9:
		return "AWP";
	case 38:
		return "SCAR-20";
	case 13:
		return "Galil AR";
	case 7:
		return "AK-47";
	case 39:
		return "SG 553";
	case 11:
		return "G3SG1";
	case 60:
		return "M4A1-S";
		/*grenades*/
	case 46:
		return "Molotov";
	case 48:
		return "Incendiary Grenade";
	case 44:
		return "HE Grenade";
	case 43:
		return "Flashbang";
	case 45:
		return "Smoke Grenade";
	case 47:
		return "Decoy";
		/*other*/
	case 31:
		return "Zeus";
	case 49:
		return "C4 Explosive";
	default:
		return "Knife";
	}
}




void debugwindow(C_BaseEntity* entity, CUserCmd* cmd) {
	float yawang = cmd->viewangles.y;
	float pitchang = cmd->viewangles.x;
	PKAZOR->FillRGBA(CenterX - 300, CenterY - 150, 250, 100, Color(0, 0, 0, 100));
	std::stringstream yawangChar, pitchangChar;
	yawangChar << "Yaw: " << yawang;
	pitchangChar << "Pitch: " << pitchang;
	PKAZOR->DrawString(CenterX - 280, CenterY - 135, Color(255, 255, 255, 170), labelFont, pitchangChar.str().c_str());
	PKAZOR->DrawString(CenterX - 280, CenterY - 127, Color(255, 255, 255, 170), labelFont, yawangChar.str().c_str());

}



void BulletTrace(C_BaseEntity* entity, Color color) {
	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	C::AngleVectors(entity->GetEyeAngles(), &forward);
	filter.pSkip = entity;
	src3D = GetBonePos(8, entity) - Vector(0, 0, 0);
	dst3D = src3D + (forward * 1000.f);

	ray.Init(src3D, dst3D);

	pValve->pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

	if (!WorldToScreen(src3D, src) || !WorldToScreen(tr.endpos, dst))
		return;

	PKAZOR->DrawLine(src.x, src.y, dst.x, dst.y, color);
	PKAZOR->DrawBox(dst.x - 4, dst.y - 4, 8, 8, color);
}
int pDis = 2;
bool turnoff = true;
 void WriteVisuals() {
	ShinezBox shinezSizeOfPenis;
	C_BaseEntity* pLocalEntity = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
	for (int i = 1; i < pValve->pEntList->GetHighestEntityIndex(); i++) {
		C_BaseEntity* pBaseEntity = (C_BaseEntity*)pValve->pEntList->GetClientEntity(i);
	
		
		if (vars::onkey) {
			if (!(GetAsyncKeyState(vars::espKey) & 0x8000))
				return;
		}

		if (!pBaseEntity)
			continue;

		if (!pBaseEntity->IsValid())
			continue;

		if (vars::esp_ignore) {
			if (pBaseEntity->Team() == pLocalEntity->Team())
				continue;
			
		}
		if (pBaseEntity == pLocalEntity)
			continue;
	
		if (pBaseEntity->Health() < 1)
			continue;

		if (pBaseEntity->Dormant())
			continue;
		

		player_info_t pInfo;
		pValve->pEngine->GetPlayerInfo(i, &pInfo);
		C_BaseCombatWeapon* pWeapon = pBaseEntity->Active();

		bool bVis = IsVisibleBone(pLocalEntity, pBaseEntity, 8);
		if (vars::SkipESP[pBaseEntity->GetIndex()])
			continue;
		if (vars::visonly) {
			if (bVis)
				continue; // pfix
		}

		if (vars::bullettrace) {

			if (pBaseEntity->Team() == 2) {
				if (bVis)
					BulletTrace(pBaseEntity, Color(vars::esp_t_visible_r, vars::esp_t_visible_g, vars::esp_t_visible_b, 255));
				else
					BulletTrace(pBaseEntity, Color(vars::esp_t_r, vars::esp_t_g, vars::esp_t_b, vars::t_transparency * 2.55f));
			}
			if (pBaseEntity->Team() == 3) {
				if (bVis)
					BulletTrace(pBaseEntity, Color(vars::esp_ct_visible_r, vars::esp_ct_visible_g, vars::esp_ct_visible_b, 255));
				else
					BulletTrace(pBaseEntity, Color(vars::esp_ct_r, vars::esp_ct_g, vars::esp_ct_b, vars::ct_transparency * 2.55f));
			}

		}
		if (GetBoxStatic(pBaseEntity, shinezSizeOfPenis)) {
			if (pBaseEntity->Team() == 2 || pBaseEntity->Team() == 3) {
				if (vars::esp_box) {

					if (vars::esp_boxstyle == 0 || vars::esp_boxstyle == 1) {
						if (pBaseEntity->Team() == 3) { // CT
							PKAZOR->DrawOutlinedBox(shinezSizeOfPenis.x, shinezSizeOfPenis.y, shinezSizeOfPenis.w, shinezSizeOfPenis.h, bVis ? Color(vars::esp_ct_visible_r, vars::esp_ct_visible_g, vars::esp_ct_visible_b, 255) : Color(vars::esp_ct_r, vars::esp_ct_g, vars::esp_ct_b, vars::ct_transparency * 2.55f), bVis ? Color(0, 0, 0, 255) : Color(10, 10, 10, vars::ct_transparency * 2.55f));

						}
						else if (pBaseEntity->Team() == 2) { // T
							PKAZOR->DrawOutlinedBox(shinezSizeOfPenis.x, shinezSizeOfPenis.y, shinezSizeOfPenis.w, shinezSizeOfPenis.h, bVis ? Color(vars::esp_t_visible_r, vars::esp_t_visible_g, vars::esp_t_visible_b, 255) : Color(vars::esp_t_r, vars::esp_t_g, vars::esp_t_b, vars::t_transparency * 2.55f), bVis ? Color(0, 0, 0, 255) : Color(10, 10, 10, vars::t_transparency * 2.55f));
						}
					}


					if (vars::esp_boxstyle == 2) {
						if (pBaseEntity->Team() == 3) { // CT

							PKAZOR->DrawOutlinedBox(shinezSizeOfPenis.x - 1, shinezSizeOfPenis.y - 1, shinezSizeOfPenis.w + 2, shinezSizeOfPenis.h + 2, bVis ? Color(0, 0, 0, 255) : Color(0, 0, 0, vars::ct_transparency * 2.55f), bVis ? Color(0, 0, 0, 255) : Color(10, 10, 10, vars::ct_transparency * 2.55f));
							PKAZOR->DrawOutlinedBox(shinezSizeOfPenis.x + 1, shinezSizeOfPenis.y + 1, shinezSizeOfPenis.w - 2, shinezSizeOfPenis.h - 2, bVis ? Color(0, 0, 0, 255) : Color(0, 0, 0, vars::ct_transparency * 2.55f), bVis ? Color(0, 0, 0, 255) : Color(10, 10, 10, vars::ct_transparency * 2.55f));
							PKAZOR->DrawOutlinedBox(shinezSizeOfPenis.x, shinezSizeOfPenis.y, shinezSizeOfPenis.w, shinezSizeOfPenis.h, bVis ? Color(vars::esp_ct_visible_r, vars::esp_ct_visible_g, vars::esp_ct_visible_b, 255) : Color(vars::esp_ct_r, vars::esp_ct_g, vars::esp_ct_b, vars::ct_transparency * 2.55f), bVis ? Color(0, 0, 0, 255) : Color(10, 10, 10, vars::ct_transparency * 2.55f));

						}
						else if (pBaseEntity->Team() == 2) { // T

							PKAZOR->DrawOutlinedBox(shinezSizeOfPenis.x - 1, shinezSizeOfPenis.y - 1, shinezSizeOfPenis.w + 2, shinezSizeOfPenis.h + 2, bVis ? Color(0, 0, 0, 255) : Color(0, 0, 0, vars::t_transparency * 2.55f), bVis ? Color(0, 0, 0, 255) : Color(10, 10, 10, vars::t_transparency * 2.55f));
							PKAZOR->DrawOutlinedBox(shinezSizeOfPenis.x + 1, shinezSizeOfPenis.y + 1, shinezSizeOfPenis.w - 2, shinezSizeOfPenis.h - 2, bVis ? Color(0, 0, 0, 255) : Color(0, 0, 0, vars::t_transparency * 2.55f), bVis ? Color(0, 0, 0, 255) : Color(10, 10, 10, vars::t_transparency * 2.55f));
							PKAZOR->DrawOutlinedBox(shinezSizeOfPenis.x, shinezSizeOfPenis.y, shinezSizeOfPenis.w, shinezSizeOfPenis.h, bVis ? Color(vars::esp_t_visible_r, vars::esp_t_visible_g, vars::esp_t_visible_b, 255) : Color(vars::esp_t_r, vars::esp_t_g, vars::esp_t_b, vars::t_transparency * 2.55f), bVis ? Color(0, 0, 0, 255) : Color(10, 10, 10, vars::t_transparency * 2.55f));

						}
					}
					if (vars::esp_boxstyle == 3) {
						if (pBaseEntity->Team() == 3) {

							if (bVis)
								ESPBoxes(shinezSizeOfPenis.x, shinezSizeOfPenis.y, shinezSizeOfPenis.w, shinezSizeOfPenis.h, Color(vars::esp_ct_visible_r, vars::esp_ct_visible_g, vars::esp_ct_visible_b, 255));
							else
								ESPBoxes(shinezSizeOfPenis.x, shinezSizeOfPenis.y, shinezSizeOfPenis.w, shinezSizeOfPenis.h, Color(vars::esp_ct_r, vars::esp_ct_g, vars::esp_ct_b, vars::ct_transparency * 2.55f));

						}
						else if (pBaseEntity->Team() == 2) {
							if (bVis)
								ESPBoxes(shinezSizeOfPenis.x, shinezSizeOfPenis.y, shinezSizeOfPenis.w, shinezSizeOfPenis.h, Color(vars::esp_t_visible_r, vars::esp_t_visible_g, vars::esp_t_visible_b, 255));
							else
								ESPBoxes(shinezSizeOfPenis.x, shinezSizeOfPenis.y, shinezSizeOfPenis.w, shinezSizeOfPenis.h, Color(vars::esp_t_r, vars::esp_t_g, vars::esp_t_b, vars::t_transparency * 2.55f));

						}
					}
				}
				if (vars::esp_boxstyle == 2)
					pDis = 4;
				else
					pDis = 2;



				if (vars::esp_name) {


					if (bVis)
						PKAZOR->DrawString(shinezSizeOfPenis.x + shinezSizeOfPenis.w + pDis, shinezSizeOfPenis.y, Color(255, 255, 255, 255), espFont, pInfo.name);
					else {

						if (pBaseEntity->Team() == 2)
							PKAZOR->DrawString(shinezSizeOfPenis.x + shinezSizeOfPenis.w + pDis, shinezSizeOfPenis.y, Color(255, 255, 255, vars::t_transparency * 2.55f), espFont, pInfo.name);
						else if (pBaseEntity->Team() == 3)
							PKAZOR->DrawString(shinezSizeOfPenis.x + shinezSizeOfPenis.w + pDis, shinezSizeOfPenis.y, Color(255, 255, 255, vars::ct_transparency * 2.55f), espFont, pInfo.name);


					}

				}

				if (vars::esp_weapons == 2) {
					if (!pWeapon) continue;
					if (bVis)
						PKAZOR->DrawString(shinezSizeOfPenis.x + shinezSizeOfPenis.w + pDis, shinezSizeOfPenis.y + 10, Color(255, 255, 255, 255), espFont, GetWeaponName(pWeapon->WeaponID()));
					else {
						if (pBaseEntity->Team() == 2)
							PKAZOR->DrawString(shinezSizeOfPenis.x + shinezSizeOfPenis.w + pDis, shinezSizeOfPenis.y + 10, Color(255, 255, 255, vars::t_transparency* 2.55f), espFont, GetWeaponName(pWeapon->WeaponID()));
						else if (pBaseEntity->Team() == 3)
							PKAZOR->DrawString(shinezSizeOfPenis.x + shinezSizeOfPenis.w + pDis, shinezSizeOfPenis.y + 10, Color(255, 255, 255, vars::ct_transparency* 2.55f), espFont, GetWeaponName(pWeapon->WeaponID()));
					}
				}

				if (vars::esp_weapons == 3) {

					if (!pWeapon) continue;
					if (bVis)
						PKAZOR->DrawString(shinezSizeOfPenis.x + shinezSizeOfPenis.w + pDis, shinezSizeOfPenis.y + 10, Color(255, 255, 255, 255), weaponFont, IconWeapon(pWeapon->WeaponID(), pWeapon).c_str());
					else {
						if (pBaseEntity->Team() == 2)
							PKAZOR->DrawString(shinezSizeOfPenis.x + shinezSizeOfPenis.w + pDis, shinezSizeOfPenis.y + 10, Color(255, 255, 255, vars::t_transparency* 2.55f), weaponFont, IconWeapon(pWeapon->WeaponID(), pWeapon).c_str());
						else if (pBaseEntity->Team() == 3)
							PKAZOR->DrawString(shinezSizeOfPenis.x + shinezSizeOfPenis.w + pDis, shinezSizeOfPenis.y + 10, Color(255, 255, 255, vars::ct_transparency* 2.55f), weaponFont, IconWeapon(pWeapon->WeaponID(), pWeapon).c_str());

					}
				}


				if (vars::esp_healthbar) {
					if (vars::esp_boxstyle == 3) {


						if (bVis)
							PKAZOR->DrawHealthbarVertical(shinezSizeOfPenis.x - 5, shinezSizeOfPenis.y, 4, shinezSizeOfPenis.h, Color(0, 255, 0, 255), pBaseEntity->Health(), 255);

						else {
							if (pBaseEntity->Team() == 2)
								PKAZOR->DrawHealthbarVertical(shinezSizeOfPenis.x - 5, shinezSizeOfPenis.y, 4, shinezSizeOfPenis.h, Color(0, 255, 0, vars::t_transparency* 2.55f), pBaseEntity->Health(), vars::t_transparency* 2.55f);
							else if (pBaseEntity->Team() == 3)
								PKAZOR->DrawHealthbarVertical(shinezSizeOfPenis.x - 5, shinezSizeOfPenis.y, 4, shinezSizeOfPenis.h, Color(0, 255, 0, vars::ct_transparency* 2.55f), pBaseEntity->Health(), vars::ct_transparency* 2.55f);

						}
					}
					else if (vars::esp_boxstyle == 2) {
						if (pBaseEntity->Team() == 2)
							PKAZOR->DrawOutlinedBox(shinezSizeOfPenis.x - 5, shinezSizeOfPenis.y - 1, 3, shinezSizeOfPenis.h + 2, bVis ? Color(0, 0, 0, 255) : Color(0, 0, 0, vars::t_transparency* 2.55f), bVis ? Color(0, 0, 0, 255) : Color(0, 0, 0, vars::t_transparency* 2.55f));
						else if (pBaseEntity->Team() == 3)
							PKAZOR->DrawOutlinedBox(shinezSizeOfPenis.x - 5, shinezSizeOfPenis.y - 1, 3, shinezSizeOfPenis.h + 2, bVis ? Color(0, 0, 0, 255) : Color(0, 0, 0, vars::ct_transparency* 2.55f), bVis ? Color(0, 0, 0, 255) : Color(0, 0, 0, vars::ct_transparency* 2.55f));


						if (bVis)
							DrawPlayerHealthBox(shinezSizeOfPenis.x - 5, shinezSizeOfPenis.y, 4, shinezSizeOfPenis.h, Color(0, 255, 0, 255), pBaseEntity->Health(), 100, 255);

						else {

							if (pBaseEntity->Team() == 2)
								DrawPlayerHealthBox(shinezSizeOfPenis.x - 5, shinezSizeOfPenis.y, 4, shinezSizeOfPenis.h, Color(0, 255, 0, vars::t_transparency* 2.55f), pBaseEntity->Health(), 100, vars::t_transparency* 2.55f);
							else if (pBaseEntity->Team() == 3)
								DrawPlayerHealthBox(shinezSizeOfPenis.x - 5, shinezSizeOfPenis.y, 4, shinezSizeOfPenis.h, Color(0, 255, 0, vars::ct_transparency* 2.55f), pBaseEntity->Health(), 100, vars::ct_transparency* 2.55f);
						}
					}
					else {
						if (bVis)
							DrawPlayerHealthBox(shinezSizeOfPenis.x - 5, shinezSizeOfPenis.y, 4, shinezSizeOfPenis.h, Color(0, 255, 0, 255), pBaseEntity->Health(), 100, 255);
						else {

							if (pBaseEntity->Team() == 2)
								DrawPlayerHealthBox(shinezSizeOfPenis.x - 5, shinezSizeOfPenis.y, 4, shinezSizeOfPenis.h, Color(0, 255, 0, vars::t_transparency* 2.55f), pBaseEntity->Health(), 100, vars::t_transparency* 2.55f);
							else if (pBaseEntity->Team() == 3)
								DrawPlayerHealthBox(shinezSizeOfPenis.x - 5, shinezSizeOfPenis.y, 4, shinezSizeOfPenis.h, Color(0, 255, 0, vars::ct_transparency* 2.55f), pBaseEntity->Health(), 100, vars::ct_transparency* 2.55f);

						}
					}
				}
		

				if (vars::esp_skeleton) {
					if (pBaseEntity == pLocalEntity)
						continue;

					GetSkeletal(pBaseEntity, pLocalEntity);
				}
			}
		}
	}
}
 int ctTick = 0;
 void CTag() {
	 static bool fixerer = false;
	 if ((fixerer) && (vars::misc_clantag == 1 || vars::misc_clantag == 0)) {

		 SetClanTag("", "");
		 fixerer = false;
	 }
	 if (vars::misc_clantag == 2) {
		 SetClanTag("\n", "");
		 fixerer = true;
	 }
	 if (vars::misc_clantag == 4) {
		 SetClanTag("[Admin]", "Valve");
		 fixerer = true;
	 }
	 if (vars::misc_clantag == 3) {
		 SetClanTag("[VALV\xE1\xB4\xB1]", "Valve");
		 fixerer = true;
	 }
	 if (vars::misc_clantag == 5) {
		 static int iLastTime = NULL;
		 if (int(pValve->pGlobals->curtime) != iLastTime)
		 {
			 switch (int(pValve->pGlobals->curtime) % 15)
			 {
			 case 0:  SetClanTag("  parallax", ""); break;
			 case 1:  SetClanTag(" parallax ", ""); break;
			 case 2:  SetClanTag("parallax  ", ""); break;
			 case 3:  SetClanTag("arallax    ", ""); break;
			 case 4:  SetClanTag("rallax      ", ""); break;
			 case 5:  SetClanTag("allax        ", ""); break;
			 case 6:  SetClanTag("llax          ", ""); break;
			 case 7:  SetClanTag("lax            ", ""); break;
			 case 8:  SetClanTag("ax              ", ""); break;
			 case 9:  SetClanTag("x               ", ""); break;
			 case 11: SetClanTag("              p", ""); break;
			 case 12: SetClanTag("            pa", ""); break;
			 case 13: SetClanTag("          par", ""); break;
			 case 14: SetClanTag("        paral", ""); break;
			 case 15: SetClanTag("      parall", ""); break;
			 case 16: SetClanTag("    paralla", ""); break;
				 //case 16: this->Clantag("  anxiety", ""); break;
			 }
		 }
		 iLastTime = int(pValve->pGlobals->curtime);

		 fixerer = true;
	 }

 }

 using PlaySoundFn = void(__stdcall*)(const char*);
 PlaySoundFn oPlaySound;

 using IsReadyFn = void(__cdecl*)();
 IsReadyFn IsReady;


 inline void hkPlaySound_CSGO(const char* filename)
 {
	
     
	 if (pValve->pEngine->IsConnected() || !vars::autoaccept)
		 return;

	 if (!strcmp(filename, ("!UI/competitive_accept_beep.wav")))
	 {
		 IsReady = (IsReadyFn)(offsets.IsRdy);
		 IsReady();
	 }
 }





 bool named = false;
 void Namespam() {
	 if (!vars::misc_namechange)
		 return;
	 static ConVar* pVar = pValve->pCvar->FindVar(charenc("name"));
	 if (pVar) {
		 *(int*)((DWORD)&pVar->fnChangeCallback + 0xC) = NULL;
		 named = !named;
		 if (named)
			 pVar->SetValue("\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7");
		 else
			 pVar->SetValue("\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\parallax.cc\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7\xC7");
	 }
 }

 std::stringstream displayText;
void PlantedBomb(C_PlantedC4* bomb){
	 if (!(*csGameRules) || !(*csGameRules)->IsBombPlanted())
		 return;

	

	 float bombTimer = bomb->GetBombTime() - pValve->pGlobals->curtime;
	 
	 if (bomb->IsBombDefused() || !bomb->IsBombTicking() || bombTimer <= 0.f)
	 {
		 displayText << "C4 Explosive";
	 }
	 else
	 {
		 C_BaseEntity* localplayer = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
		 Vector vecOrigin = bomb->vecOrigin();

		 float flDistance = localplayer->GetEyePos().DistTo(vecOrigin);

		 float a = 450.7f;
		 float b = 75.68f;
		 float c = 789.2f;
		 float d = ((flDistance - b) / c);
		 float flDamage = a * expf(-d * d);

		 //float damage = std::max((int)ceilf(GetArmourHealth(flDamage, localplayer->GetArmor())), 0);

		 displayText << "C4 Explosive [" << std::fixed << std::showpoint << std::setprecision(1) << bombTimer << "]"; //<< ", damage: " << (int)damage;
	 }

	 
	 //DrawEntity(bomb, displayText.str().c_str(), Color::FromImColor(color));
 }

CUserCmd*		m_cmd;
Vector			m_position;
Vector			m_size;
C_BaseEntity*	m_player;
void Update(CUserCmd* pCmd)
{
	m_cmd = pCmd;

	if (!m_cmd) {
		return;
	}

	int index = pValve->pEngine->GetLocalPlayer();

	if (!index) {
		return;
	}

	m_player = (C_BaseEntity*)pValve->pEntList->GetClientEntity(index);
}

void Radar()
{
	if (!vars::radar)
		return;

	if (!m_cmd)
		return;



	m_position.x = Settings::RadarX;
	m_position.y = Settings::RadarY;
	m_size.x = m_size.y = Settings::radarsize;

	Vector lposition = m_player->GetAbsOrigin();

	int playerCount = pValve->pEntList->GetHighestEntityIndex();
	
	PKAZOR->FillRGBA(m_position.x, m_position.y, m_size.x, m_size.y, Color(50,50,50, 255));
	
	PKAZOR->DrawBox(m_position.x + m_size.x / 2, m_position.y, 1, m_size.y, Color::Black());
	PKAZOR->DrawBox(m_position.x, m_position.y + m_size.y / 2, m_size.x, 1, Color::Black());

	for (int i = 1; i <= playerCount; i++)
	{
		C_BaseEntity* entity = (C_BaseEntity*)pValve->pEntList->GetClientEntity(i);

		if (!entity)
			continue;

		if (entity == m_player)
			continue;

		if (entity->Health() < 1)
			continue;

		if (!entity->IsValid())
			continue;

		if (entity->Dormant())
			continue;


		Vector eposition = entity->GetAbsOrigin();

		if (eposition.IsZero())
			continue;

		float radar_x = lposition.x - eposition.x;
		float radar_y = lposition.y - eposition.y;

		float angle = DEG2RAD(m_cmd->viewangles.y);

		float rotate_x = radar_y * cos(angle) - radar_x * sin(angle);
		float rotate_y = radar_x * cos(angle) + radar_y * sin(angle);

		float final_x = (m_position.x + (m_size.x / 2)) + rotate_x / 27;
		float final_y = (m_position.y + (m_size.y / 2)) + rotate_y / 27;

		if (final_x < m_position.x)
			final_x = m_position.x;
		if (final_x > m_position.x + m_size.x)
			final_x = m_position.x + m_size.x - 1;
		if (final_y < m_position.y)
			final_y = m_position.y;
		if (final_y > m_position.y + m_size.y)
			final_y = m_position.y + m_size.y - 1;

		Color dot_color = Color::White();
		if (entity->Team() == 2)
			dot_color = Color::Red();
		else if (entity->Team() == 3)
			dot_color = Color::Cyan();
		PKAZOR->FillRGBA(final_x, final_y, 1, 1, dot_color);

	}
	PKAZOR->DrawBox(m_position.x, m_position.y, m_size.x, m_size.y, Color::Black());
	if (isOpend) {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			Settings::RadarX--;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			Settings::RadarX++;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			Settings::RadarY--;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			Settings::RadarY++;
		}
	}
		
}


void MakeWorldModels() {
	for (int i = 1; i < pValve->pEntList->GetHighestEntityIndex(); i++) {
		C_BaseEntity* pEntity = pValve->pEntList->GetClientEntity(i);

		if (!pEntity)
			continue;
		if (pEntity->Dormant())
			continue;
		if (pEntity->Team() == 2 && pEntity->Team() == 3)
			continue;
		ULONG pOwnerHandle = *(PULONG)((DWORD)pEntity + 0x148);
		if (!(pValve->pEntList->GetClientEntityFromHandle(pOwnerHandle))) {
			std::string szWeapons = pEntity->GetClientClass()->GetName();
			if (pEntity) {
				ShinezBox pboxer;
				if (GetBoxStatic(pEntity, pboxer)) {
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponAug")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "AUG");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponAWP")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "AWP");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponBizon")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "PP-Bizon");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponElite")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Dual Berettas");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponFamas")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Famas");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponFiveSeven")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Five-SeveN");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponG3SG1")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "G3SG1");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponGalil")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Galil-AR");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponGalilAR")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Galil-AR");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponGlock")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Glock-18");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponHKP2000")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "P2000");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponM249")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "M249");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponM4A1")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "M4A4");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponMAC10")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "MAC10");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponMag7")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Mag-7");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponMP7")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "MP7");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponMP9")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "MP9");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponNegev")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Negev");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponNOVA")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Nova");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponP250")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "P250");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponP90")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "P90");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponSawedoff")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Sawed-Off");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponSCAR20")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "SCAR-20");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponScout")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "SSG 08");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponSSG08")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "SSG 08");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponSG550")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "SG 553");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponSG552")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "SG 553");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponSG556")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "SG 553");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponTaser")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Zeus");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponTec9")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Tec-9");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponUMP45")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "UMP-45");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponUSP")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "USP-S");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CWeaponXM1014")) {
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "XM1014");
					}

					if (strstr(pEntity->GetClientClass()->GetName(), "CAK47")) {
						
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "AK-47");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CKnife")) {
						
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Knife");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CDEagle")) {
						
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Desert Eagle");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CHEGrenade")) {
						
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "HE Grenade");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CMolotovGrenade")) {
						
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Molotov");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CIncendiaryGrenade")) {
						
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Incendiary");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CFlashbang")) {
						
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Flashbang");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CDecoyGrenade")) {
						
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Decoy");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CSmokeGrenade")) {
						
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "Smoke Grenade");
					}
					if (strstr(pEntity->GetClientClass()->GetName(), "CChicken")) {
						
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), pFont, "Chicken");
					}
					
					if (strstr(pEntity->GetClientClass()->GetName(), "CFish")) {
						//
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), pFont, "Fish");
					}
					if (pEntity->GetClientClass()->GetClassID() == (int)EClassIds::CC4) {

						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, "C4 Explosive");
					}
					if (pEntity->GetClientClass()->GetClassID() == (int)EClassIds::CPlantedC4) {
						C_PlantedC4* pC4 = (C_PlantedC4*)pEntity;
						PlantedBomb(pC4);
						PKAZOR->DrawString(pboxer.x + pboxer.w - 3, pboxer.y - 3, Color(255, 255, 255, 255), espFont, displayText.str().c_str());
					}

				}

			}
		}
	}
}
int slide = 0;
int Selectionen = 0;
int dummy = 0;
void sideslide(bool& doSlide) {
	static int delayenz = 0;
	static bool change_dir = false;
	static int textenz = 0;
	if (doSlide) {
		if (textenz < 16)
			textenz+=3;
		if (slide < 200) {
			slide+=4;
			change_dir = true;
		}
		if (change_dir) {
			delayenz++;
		}

		
		if (delayenz > 700) {
			change_dir = false;
			doSlide = false;
		}
	}
	else {
		if (textenz > 0)
			textenz-=3;
		if (slide > 0)
			slide-=4;
		if (delayenz != 0)
			delayenz = 0;
		change_dir = false;
	}
	PKAZOR->FillRGBA(slide - 203, CenterY - 200, 160, 19, Color(41, 41, 41, 255));
	PKAZOR->DrawBox(slide - 203, CenterY - 200, 160, 19, Color(4, 4, 4, 255));
	if (LoadCFG) {
		if (vars::config_select == 0 || vars::config_select == 1) {
			if (doEins) {
				Selectionen = 1;
				doEins = false;
			}
			
		}
		else if (vars::config_select == 2) {
			if (doEins) {
				Selectionen = 2;
				doEins = false;
			}
		}
		else if (vars::config_select == 3) {
			if (doEins) {
				Selectionen = 3;
				doEins = false;
			}
		}
		else if (vars::config_select == 4) {
			if (doEins) {
				Selectionen = 4;
				doEins = false;
			}
		}
		else if (vars::config_select == 5) {
			if (doEins) {
				Selectionen = 5;
				doEins = false;
			}
		}
		else if (vars::config_select == 6) {
			if (doEins) {
				Selectionen = 6;
				doEins = false;
			}
		}
		if (Selectionen == 1) {
			PKAZOR->DrawString((slide - 203) + textenz, CenterY - 197, Color(255, 255, 255, 255), labelFont, "Loaded config: Default");
		}
		else if (Selectionen == 2) {
			PKAZOR->DrawString((slide - 203) + textenz, CenterY - 197, Color(255, 255, 255, 255), labelFont, "Loaded config: Legit");
		}
		else if (Selectionen == 3) {
			PKAZOR->DrawString((slide - 203) + textenz, CenterY - 197, Color(255, 255, 255, 255), labelFont, "Loaded config: Rage");
		}
		else if (Selectionen == 4) {
			PKAZOR->DrawString((slide - 203) + textenz, CenterY - 197, Color(255, 255, 255, 255), labelFont, "Loaded config: HvH #1");
		}
		else if (Selectionen == 5) {
			PKAZOR->DrawString((slide - 203) + textenz, CenterY - 197, Color(255, 255, 255, 255), labelFont, "Loaded config: HvH #2");
		}
		else if (Selectionen == 6) {
			PKAZOR->DrawString((slide - 203) + textenz, CenterY - 197, Color(255, 255, 255, 255), labelFont, "Loaded config: Secret");
		}
	}
	else {
		if (vars::config_select == 0 || vars::config_select == 1) {
			if (doEins) {
				Selectionen = 1;
				doEins = false;
			}

		}
		else if (vars::config_select == 2) {
			if (doEins) {
				Selectionen = 2;
				doEins = false;
			}
		}
		else if (vars::config_select == 3) {
			if (doEins) {
				Selectionen = 3;
				doEins = false;
			}
		}
		else if (vars::config_select == 4) {
			if (doEins) {
				Selectionen = 4;
				doEins = false;
			}
		}
		else if (vars::config_select == 5) {
			if (doEins) {
				Selectionen = 5;
				doEins = false;
			}
		}
		else if (vars::config_select == 6) {
			if (doEins) {
				Selectionen = 6;
				doEins = false;
			}
		}
		if (Selectionen == 1) {
			
			PKAZOR->DrawString((slide - 203) + textenz, CenterY - 197, Color(255, 255, 255, 255), labelFont, "Saved config: Default");
		}
		else if (Selectionen == 2) {
			PKAZOR->DrawString((slide - 203) + textenz, CenterY - 197, Color(255, 255, 255, 255), labelFont, "Saved config: Legit");
		}
		else if (Selectionen == 3) {
			PKAZOR->DrawString((slide - 203) + textenz, CenterY - 197, Color(255, 255, 255, 255), labelFont, "Saved config: Rage");
		}
		else if (Selectionen == 4) {
			PKAZOR->DrawString((slide - 203) + textenz, CenterY - 197, Color(255, 255, 255, 255), labelFont, "Saved config: HvH #1");
		}
		else if (Selectionen == 5) {
			PKAZOR->DrawString((slide - 203) + textenz, CenterY - 197, Color(255, 255, 255, 255), labelFont, "Saved config: HvH #2");
		}
		else if (Selectionen == 6) {
			PKAZOR->DrawString((slide - 203) + textenz, CenterY - 197, Color(255, 255, 255, 255), labelFont, "Saved config: Secret");
		}
		
	}
}

void FakeWalk(C_BaseEntity *localplayer, CUserCmd* pCmd, bool &bSendPacket, C_BaseEntity* ply)
{
	static int iChoked = -1;

	if (GetAsyncKeyState(vars::misc_fakewalkkey))
	{
		if (!(localplayer->Flags() & FL_ONGROUND) ||
			(pCmd->command_number % 7) == 0 ||
			localplayer->GetVelocity().Length() > 75)
			return;

		pCmd->buttons &= ~IN_SPEED;

		iChoked++;

		if (iChoked < 1)
			bSendPacket = false;

		pCmd->tick_count += 10;
		pCmd->command_number += 7 + pCmd->tick_count % 2 ? 0 : 1;

		pCmd->buttons |= ply->MoveType() == IN_BACK;
		pCmd->forwardmove = pCmd->sidemove = 0.f;
	}
	else
	{
		bSendPacket = true;
		iChoked = -1;

		//pVape->GetInterface->Globals->frametime *= (localplayer->GetVelocity().Length2D()) / 1.f;
		pCmd->buttons |= ply->MoveType() == IN_FORWARD;
	}
}

int velocity = 0;
int width = 300;
int split = 3;
void speedBar() {
	if (pValve->pEngine->IsConnected() && pValve->pEngine->IsInGame()) {
		C_BaseEntity* pLocal = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());

		/*if (!pLocal)
			return;
		if (!pLocal->IsValid())
			return;*/
		
		if (!vars::velocitybar)
			return;

		
		if ((pLocal->GetVelocity().Length2D() / split) < width - 2)
			velocity = pLocal->GetVelocity().Length2D() / split;
	
		else if ((pLocal->GetVelocity().Length2D() / split) >= width - 2) {
			velocity = width - 2;
		}

		PKAZOR->DrawBox(CenterX, CenterY * 1.8f - 1, width + 1, 27, Color(0, 0, 0, 255));
		PKAZOR->DrawBox(CenterX - (width + 1), CenterY * 1.8f - 1, width + 1, 27, Color(0, 0, 0, 255));
		PKAZOR->FillRGBA(CenterX, CenterY * 1.8f , width, 25, Color(24, 24, 24, 255));
		PKAZOR->FillRGBA(CenterX - width, CenterY * 1.8f ,width, 25, Color(24, 24, 24, 255));
		if (!pLocal->GetVelocity().Length2D())
			return;
		PKAZOR->FillRGBA(CenterX, CenterY * 1.8f + 2, velocity, 21, Color(vars::menur, vars::menug, vars::menub, 255));
		PKAZOR->FillRGBA(CenterX - velocity, CenterY * 1.8f + 2, velocity, 21, Color(vars::menur, vars::menug, vars::menub, 255));
		
		
	}

}



const char* YawAngleChar;
static bool nigger = false;
bool cocksz = true;
bool animate = false;
bool slidenz = false;
void __fastcall hkPaintTraverse(void* ecx, void* edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce) {
	pValve->oPaintTraverse(ecx, vguiPanel, forceRepaint, allowForce);
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	static UINT paneeel;
	if (!paneeel) {
		const char* name = pValve->pPanel->GetName(vguiPanel);
		if (strstr(name, "MatSystemTopPanel")) {
			pFont = pValve->pSurface->CreateFontA();
			xFont = pValve->pSurface->CreateFontA();
			oBlock = pValve->pSurface->CreateFontA();
			espFont = pValve->pSurface->CreateFontA();
			labelFont = pValve->pSurface->CreateFontA();
			weaponFont = pValve->pSurface->CreateFontA();
			kukFont = pValve->pSurface->CreateFontA();
			pValve->pSurface->SetFontGlyphSet(pFont, "Verdana", 12, 180, 0, 0, FONTFLAG_OUTLINE);
			pValve->pSurface->SetFontGlyphSet(weaponFont, "autism", 16, 800, 0, 0, FONTFLAG_DROPSHADOW);
			pValve->pSurface->SetFontGlyphSet(labelFont, "Verdana", 12, 800, 0, 0, FONTFLAG_ANTIALIAS);
			pValve->pSurface->SetFontGlyphSet(espFont, "Verdana", 12, 800, 0, 0, FONTFLAG_DROPSHADOW);
			pValve->pSurface->SetFontGlyphSet(oBlock, "Pixelig Cursief", 19, 800, 0, 0, FONTFLAG_ANTIALIAS);
			pValve->pSurface->SetFontGlyphSet(xFont, "Impact", 45, 500, 0, 0, FONTFLAG_ANTIALIAS, FONTFLAG_OUTLINE);
			pValve->pSurface->SetFontGlyphSet(kukFont, "Roboto", 14, 800, 0, 0, FONTFLAG_ANTIALIAS);
			paneeel = vguiPanel;
		}
	}



	if (paneeel == vguiPanel) {

		
		const char* faggotnigger2 = ("\n%s", asctime(timeinfo));
		if (vars::misc_watermarks) {

			PKAZOR->DrawString(10, 10, Color(255, 255, 255, 255), pFont, "PARALLAX.CC");
		}
		if (vars::misc_time) {
			if (vars::misc_watermarks) PKAZOR->DrawString(10, 23, Color(255, 255, 255, 255), pFont, faggotnigger2);
			else PKAZOR->DrawString(10, 10, Color(255, 255, 255, 255), pFont, faggotnigger2);
		}
		if (cocksz) {
			doLoad();
			//Sleep(1);
			cocksz = false;
		}

		




		ToggleUpp();
		if (GetAsyncKeyState(VK_F9)) pValve->pEngine->ExecuteClientCmd("disconnect;map aim_ag_texture2;sv_cheats 1;bot_stop 1;mp_warmuptime 32186387126378812381;mp_respawn_on_death_ct 1;mp_buy_anywhere 1");
		// le esp initz. 

		
		if (pValve->pEngine->IsConnected() && pValve->pEngine->IsInGame()) {
			C_BaseEntity* pLocal = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
			if (pLocal) {
				Namespam();
				CTag();
				Chatspam();
				if (vars::espworld)
					MakeWorldModels();
				if (vars::esp_active)
					WriteVisuals();

				if (vars::rage_active)
				{
					auto difference = abs(abs(pLocal->GetEyeAngles().y) - abs(pLocal->GetLowerBodyYawTarget()));

					PKAZOR->DrawString(10, 910, difference > 35 ? Color(0, 255, 0, 255) : Color(255, 0, 0, 255), xFont, "LBY");
				}

				speedBar();
			
				if (vars::esp_crosshair) {
					if (vars::esp_chsize > 29) {
						PKAZOR->DrawLine(CenterX, CenterY, CenterX, CenterY - vars::esp_chsize, PKAZOR->Rainbow());
					    PKAZOR->DrawLine(CenterX, CenterY - vars::esp_chsize, CenterX + vars::esp_chsize, CenterY - vars::esp_chsize, PKAZOR->Rainbow());
					    
					    PKAZOR->DrawLine(CenterX, CenterY, CenterX + vars::esp_chsize, CenterY, PKAZOR->Rainbow());
					    PKAZOR->DrawLine(CenterX + vars::esp_chsize, CenterY, CenterX + vars::esp_chsize, CenterY + vars::esp_chsize, PKAZOR->Rainbow());
					    
					    PKAZOR->DrawLine(CenterX, CenterY, CenterX, CenterY + vars::esp_chsize, PKAZOR->Rainbow());
					    PKAZOR->DrawLine(CenterX, CenterY + vars::esp_chsize, CenterX - vars::esp_chsize, CenterY + vars::esp_chsize, PKAZOR->Rainbow());
					    
					    PKAZOR->DrawLine(CenterX, CenterY, CenterX - vars::esp_chsize, CenterY, PKAZOR->Rainbow());
					    PKAZOR->DrawLine(CenterX - vars::esp_chsize, CenterY, CenterX - vars::esp_chsize, CenterY - vars::esp_chsize, PKAZOR->Rainbow());
					    if (!nigger) {
					    	pValve->pEngine->ExecuteClientCmd("crosshair 0");
					    	nigger = true;
					    }
					}
					else {
						PKAZOR->FillRGBA(CenterX - (vars::esp_chsize / 2), CenterY, vars::esp_chsize, 1, Color(30, 233, 30));
						PKAZOR->FillRGBA(CenterX, CenterY - (vars::esp_chsize / 2), 1, vars::esp_chsize, Color(30, 233, 30));
					}

				}
				else {
					if (nigger) {
						pValve->pEngine->ExecuteClientCmd("crosshair 1");
						nigger = false;
					}
				}

			}

		}
		Radar();
		static bool pFixer = false;
		static bool slideUp = false;

		if (vars::MenuDrop == 0 || vars::MenuDrop == 1) {
			menut = 255;
			if (isOpend) {
				pValve->pEngine->ExecuteClientCmd("cl_mouseenable 0");
				GetCursorPos(&Cur);
				PKAZOR->DrawMenu(Settings::StartX, Settings::StartY, 572, 315);
				PKAZOR->grabMouse(Cur.x, Cur.y);
			}
		}
		else if (vars::MenuDrop == 2) {
			menut = 255;
			static int slidein = -320;
			if (isOpend) {
				if (slidein < Settings::StartY) {
					if (pFixer)
						slidein += 17;
				}
				else {
					pFixer = false;
				}
				pValve->pEngine->ExecuteClientCmd("cl_mouseenable 0");
				GetCursorPos(&Cur);
				PKAZOR->DrawMenu(Settings::StartX, slidein, 572, 315);
				PKAZOR->grabMouse(Cur.x, Cur.y);
			}
			else {
				pFixer = true;
				if (slidein > -320) {
					slidein -= 17;
					PKAZOR->DrawMenu(Settings::StartX, slidein, 572, 315);
				}
			}
		}
		else if (vars::MenuDrop == 3) {
			menut = 255;
			static int slidein = ScreenH + 320;
			if (isOpend) {
				if (slidein > Settings::StartY) {
					if (pFixer)
						slidein -= 17;
				}
				else {
					pFixer = false;
				}
				pValve->pEngine->ExecuteClientCmd("cl_mouseenable 0");
				GetCursorPos(&Cur);
				PKAZOR->DrawMenu(Settings::StartX, slidein, 572, 315);
				PKAZOR->grabMouse(Cur.x, Cur.y);
			}
			else {
				pFixer = true;
				if (slidein < ScreenH + 320) {
					slidein += 17;
					PKAZOR->DrawMenu(Settings::StartX, slidein, 572, 315);
				}
			}
		}
		else if (vars::MenuDrop == 4) {
			if (isOpend) {
				if (menut < 255) {
					menut += 10;
				}
				if (menut > 255)
					menut = 255;
				if (menut > 0 && menut <= 255) {

					pValve->pEngine->ExecuteClientCmd("cl_mouseenable 0");
					GetCursorPos(&Cur);
					PKAZOR->DrawMenu(Settings::StartX, Settings::StartY, 572, 315);
					PKAZOR->grabMouse(Cur.x, Cur.y);
				}
			}
			else {
				if (menut > 0) {
					PKAZOR->DrawMenu(Settings::StartX, Settings::StartY, 572, 315);
					menut -= 10;
				}
			}
		}
		//PKAZOR->PopUpMessage("Hi my name shinez", "XDDDDDDD", "RrRrRrRrRrR", Color(vars::menur, vars::menug, vars::menub));
	}
}




struct PlayerAA
{
	C_BaseEntity* player;
	Vector angle;

	PlayerAA(C_BaseEntity* player, Vector angle)
	{
		this->player = player;
		this->angle = angle;
	}
};

extern std::vector<int64_t> Players;
std::vector<int64_t> Players = {};
std::vector<PlayerAA> player_data;


cGameEvent gEvent;

typedef bool(__thiscall* hkdFireEvent)(void* ecx, IGameEvent*);
hkdFireEvent oFireEventClientSide;


//start_halftime
void cGameEvent::RegisterSelf() {
	g_pGameEventManager->AddListener(this, "player_hurt", false);
	g_pGameEventManager->AddListener(this, "round_start", false);
	g_pGameEventManager->AddListener(this, "round_end", false);
	g_pGameEventManager->AddListener(this, "round_mvp", false);
	g_pGameEventManager->AddListener(this, "player_death", false);
	g_pGameEventManager->AddListener(this, "start_halftime", false);
}

bool __fastcall hkFireEventClientSide(void* ecx, void* edx, IGameEvent* pEvent)
{
	if (!pEvent)
		return oFireEventClientSide(ecx, pEvent);


	if (strcmp(pEvent->GetName(), "round_start") == 0 && vars::misc_roundsay)
	{
		pValve->pEngine->ExecuteClientCmd("say HTTPS://PARALLAX.CC - Premium Rage & Legit Cheat");
		
	}

	if (strcmp(pEvent->GetName(), "player_death") == 0 && vars::misc_killnotification)
	{
		player_info_t pInfo;
		pValve->pEngine->GetPlayerInfo(pValve->pEngine->GetLocalPlayer(), &pInfo);
		if (pInfo.userID == pEvent->GetInt("attacker", 0)) {
			int xId = pEvent->GetInt("userid", 0);
			bool getHeadshot = pEvent->GetBool("headshot", false);
			int Wallbang = pEvent->GetInt("penetrated", 0);

			
			std::stringstream ss;
			player_info_t xinfo;
			pValve->pEngine->GetPlayerInfo(pValve->pEngine->GetPlayerForUserID(xId), &xinfo);
			if (getHeadshot && Wallbang > 1) {
				ss << "say PARALLAX: " << xinfo.name << " @ 1tapped thru" << Wallbang << "walls";
			}
			else if (getHeadshot && Wallbang == 1) {
				ss << "say PARALLAX: " << xinfo.name << " @ beheaded";
			}
			else if(getHeadshot && !Wallbang) {
				ss << "say PARALLAX: " << xinfo.name << " @ 1tap't";
			}
			else if (Wallbang == 1) {
				ss << "say PARALLAX: " << xinfo.name << " @ penetrated";
			}
			else if (Wallbang > 1) {
				ss << "say PARALLAX: " << xinfo.name << " @ penetrated through" << Wallbang << "walls";
			}
			else {
				ss << "say PARALLAX: " << xinfo.name << " @ raped";
		
			}

			pValve->pEngine->ExecuteClientCmd(ss.str().c_str());
		}
	}
	if (strcmp(pEvent->GetName(), "player_connect_full") != 0 && strcmp(pEvent->GetName(), "cs_game_disconnected") != 0)
		return oFireEventClientSide(ecx, pEvent);

	if (pEvent->GetInt("userid", 0) && pValve->pEngine->GetPlayerForUserID(pEvent->GetInt("userid", 0)) != pValve->pEngine->GetLocalPlayer())
		return oFireEventClientSide(ecx, pEvent);

	Players.clear();
	return oFireEventClientSide(ecx, pEvent);
}

void* g_pViewRender;


typedef void(__thiscall* RenderViewFn)(void*, CViewSetup &setup, CViewSetup &hudViewSetup, int nClearFlags, int whatToDraw);
RenderViewFn oRenderView;





void __fastcall hkRenderView(void* thisptr, void*, CViewSetup &setup, CViewSetup &hudViewSetup, int nClearFlags, int whatToDraw)
{
	if (vars::misc_fovfactor && vars::misc_fovchange == 2)
		setup.fovViewmodel = vars::misc_fovfactor;
	oRenderView(thisptr, setup, hudViewSetup, nClearFlags, whatToDraw);
}
int spamtick = 0;
void radiospam() {
	if (vars::radiospam) {
		spamtick++;
		if (spamtick >= 250) { pValve->pEngine->ExecuteClientCmd("go"); spamtick = 0; }
		
		
	}
}

static int ticks = 0;
int ticksMax = 10;
void fakelag(CUserCmd* cmd, C_BaseEntity* plo, bool& bSendPacket) {


	if (vars::misc_fakelag > 0) {
		if (vars::inair && (plo->Flags() & FL_ONGROUND)) {
			if (vars::rage_active && vars::aa_fake) {
				switchFake = !switchFake;
				if (switchFake)
					bSendPacket = true;
				else
					bSendPacket = false;
			}
			return;
			
		}


		if (vars::flagMode < 2) {
			if (cmd->buttons & IN_ATTACK)
			{
				bSendPacket = true;
				return;
			}

			if (ticks >= ticksMax)
			{
				bSendPacket = true;
				ticks = 0;
			}
			else
			{

				if (plo->GetVelocity().Length2D() > 200)
					bSendPacket = ticks < 10 - vars::misc_fakelag;
				else {
					bSendPacket = ticks < 15 - 14;
				}
			}

			ticks++;
		}
		if (vars::flagMode == 2) {
			if (cmd->buttons & IN_ATTACK)
			{
				bSendPacket = true;
				return;
			}
			static int dTick = 0;
			if (dTick > vars::misc_fakelag)
				dTick = 0;

			if (ticks >= ticksMax)
			{
				bSendPacket = true;
				ticks = 0;
			}
			else
			{
				bSendPacket = ticks < 10 - dTick;
			}

			ticks++;
			dTick++;

		}
		if (vars::flagMode == 3) {
			static int random = 0;
			srand(time(NULL));

			random = rand() % vars::misc_fakelag + 1;

			if (cmd->buttons & IN_ATTACK)
			{
				bSendPacket = true;
				return;
			}

			if (ticks >= ticksMax)
			{
				bSendPacket = true;
				ticks = 0;
			}
			else
			{
				bSendPacket = ticks < 11 - random;
			}

			ticks++;

		}
	}
	else if (vars::misc_fakelag < 1) {
		
		if (vars::rage_active && vars::aa_fake) {
			switchFake = !switchFake;
			if (switchFake)
				bSendPacket = true;
			else
				bSendPacket = false;
		}
	
	}
}

typedef void(__stdcall* hkdOverrideView)(CViewSetup*);
hkdOverrideView oOverrideView;
void __stdcall hkOverrideView(CViewSetup* pSetup) {
	C_BaseEntity* pLocal = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());

	if (pValve->pEngine->IsConnected() && pValve->pEngine->IsInGame()) {
		if (vars::misc_fovchange == 3 && vars::misc_fovfactor) {
			if (pLocal->IsScoped() && !vars::misc_thirdperson)
				return;
			if (pLocal->Health() < 1)
				return;

			if (pLocal->IsScoped() && vars::misc_thirdperson)
				pSetup->fov = 90;
			else
				pSetup->fov = vars::misc_fovfactor;
		}
	
	}

	oOverrideView(pSetup);
}

void moonwalk(CUserCmd* pCmd) {
	C_BaseEntity* pLocal = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
	if (vars::moonwalk && pLocal->MoveType() == MOVETYPE_WALK)
	{
		if (pCmd->forwardmove > 0)
		{
			pCmd->buttons |= IN_BACK;
			pCmd->buttons &= ~IN_FORWARD;
		}

		if (pCmd->forwardmove < 0)
		{
			pCmd->buttons |= IN_FORWARD;
			pCmd->buttons &= ~IN_BACK;
		}

		if (pCmd->sidemove < 0)
		{
			pCmd->buttons |= IN_MOVERIGHT;
			pCmd->buttons &= ~IN_MOVELEFT;
		}

		if (pCmd->sidemove > 0)
		{
			pCmd->buttons |= IN_MOVELEFT;
			pCmd->buttons &= ~IN_MOVERIGHT;
		}
	}
}



void bunnies(CUserCmd* pCmd) {
	C_BaseEntity* pLocal = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
	if (vars::minvel > pLocal->GetVelocity().Length2D()) return;
	if (!vars::misc_bhop)
		return;

	static bool bLastJumped = false;
	static bool bShouldFake = false;


	if (!pLocal)
		return;

	if (pLocal->MoveType() == MOVETYPE_LADDER || pLocal->MoveType() == MOVETYPE_NOCLIP)
		return;
	
	

	if (!bLastJumped && bShouldFake)
	{
		
		
		
		bShouldFake = false;
		pCmd->buttons |= IN_JUMP;
		
	}
	else if (pCmd->buttons & IN_JUMP)
	{
		if (pLocal->Flags() & FL_ONGROUND)
		{
			bLastJumped = true;
			bShouldFake = true;
		}
		else
		{
			
			pCmd->buttons &= ~IN_JUMP;
			bLastJumped = false;
			
		}
	}
	else
	{
		bLastJumped = false;
		bShouldFake = false;
	}
	
}
float TheThinkingTime = 0.0f;
float TheTimer = 0.0f;
float TheDelay = 0.2f;
void FakelagFix(C_BaseEntity* localShit, CUserCmd* pCmd) {
	float TheCurrentTime = localShit->TickBase();
	TheTimer += TheCurrentTime - TheThinkingTime;
	TheThinkingTime += TheCurrentTime * pValve->pGlobals->curtime;

	if (TheTimer > TheDelay) {
		pValve->pGlobals->interpolation_amount = 0;
		while (TheTimer > TheDelay)
			TheTimer -= TheDelay;
	}
}

void RageSilent(CUserCmd* pCmd, C_BaseCombatWeapon* pWeapon, C_BaseEntity* pLocalEntity, bool& bSendPacket, Vector oldAngle, float sidemove, float forwardmove) {
	if (!vars::rage_psilent)
		return;
	float servertime = pLocalEntity->TickBase() * pValve->pGlobals->interval_per_tick;
	float nextprimaryattack = pLocalEntity->NextAttack();

	bool bAttack = true;
	if (nextprimaryattack > servertime)
		bAttack = false;
	static int iChoked = 0;
	if (pCmd->buttons & IN_ATTACK && bAttack && iChoked < 12) {
		bSendPacket = false;
		iChoked++;
	}
	else {
		bSendPacket = true;
		iChoked = 0;
	}

	if (bSendPacket) {
		pCmd->forwardmove = forwardmove;
		pCmd->sidemove = sidemove;
		pCmd->viewangles = oldAngle;
	}
}

class GOTV {
public:
	class CHLTVFrame;

	class CHLTVDemoRecorder
	{
	public:
		char _pad[0x540];
		bool			m_bIsRecording;
		int				m_nFrameCount;
		float			m_nStartTick;
		int				m_SequenceInfo;
		int				m_nDeltaTick;
		int				m_nSignonTick;
		//bf_write m_MessageData; // temp buffer for all network messages
	};
	class CHLTVServer
	{
	public:
		char _pad[0x5040];
		CHLTVDemoRecorder m_DemoRecorder;
	};
};

bool AntiGOTV() {
	static bool wasactivegotv = false;
	if (vars::gotv) {
		static DWORD dwHLTVServer;
		static GOTV::CHLTVServer** hltv;
		if (!wasactivegotv) {
			dwHLTVServer = zFindPattern("engine.dll", (PBYTE)"\xBE\x00\x00\x00\x00\x8B\x0E\x85\xC9\x74\x1E\xD4\x89\x02\x8B\x01", "x????xxxxxx") + 0x1;
			hltv = *(GOTV::CHLTVServer***)dwHLTVServer;
			wasactivegotv = true;
		}

		if (wasactivegotv)
			if ((int)((pValve->pGlobals->curtime*pValve->pGlobals->interval_per_tick) - (*hltv)->m_DemoRecorder.m_nStartTick) % 4 == 0) {
				return true;
			}
	}
	else
		wasactivegotv = false;
	return false;
}


void MakePerfectSilent(CUserCmd* pCmd, C_BaseCombatWeapon* pWeapon, C_BaseEntity* pLocalEntity, bool& bSendPacket, Vector oldAngle, float sidemove, float forwardmove) {
	float servertime = pLocalEntity->TickBase() * pValve->pGlobals->interval_per_tick;
	float nextprimaryattack = pLocalEntity->NextAttack();

	bool bAttack = true;
	if (nextprimaryattack > servertime)
		bAttack = false;
	static float iChoked = 0.0;
	if (!AntiGOTV())
		bSendPacket = false;

	if (pCmd->buttons & IN_ATTACK && bAttack && iChoked < 0.5f) {
		bSendPacket = false;
		iChoked++;
	}
	else {
		bSendPacket = true;
		iChoked = 0.0;
	}

	if (bSendPacket) {
		pCmd->forwardmove = forwardmove;
		pCmd->sidemove = sidemove;
		pCmd->viewangles = oldAngle;
	}
}



bool isAirstucking = false;
bool __stdcall hkCreateMove(float flSampleTime, CUserCmd* pCmd) {
	pValve->oCreateMove(flSampleTime, pCmd);
	if (!pCmd->command_number)
		return true;
	C_BaseEntity* pLocal = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());

	if (!pLocal)
		return false;
	if (!pLocal->IsValid())
		return false;
	

	C_BaseCombatWeapon* pWeapon = pLocal->Active();

	if (!pWeapon) return false;

	PDWORD pEBP;
	__asm mov pEBP, ebp;
	bool& bSendPacket = *(bool*)(*pEBP - 0x1C);

	Update(pCmd);
	if (pValve->pEngine->IsConnected() && pValve->pEngine->IsInGame()) {
		float sidemove = pCmd->sidemove;
		float forwardmove = pCmd->forwardmove;
		Vector origView = pCmd->viewangles;
		Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
		Vector qAimAngles;
		qAimAngles.Init(0.0f, pCmd->viewangles.y, 0.0f);
		C::AngleVectors(qAimAngles, &viewforward, &viewright, &viewup);
		//static ConVar* cl_interpolate = pCvar->FindVar("cl_interpolate");
		//if (cl_interpolate->fValue != 0)
		//	cl_interpolate->SetValue(0);
		

		
		int tickBase = pLocal->TickBase();

		float oldCurTime = pValve->pGlobals->curtime;
		float oldFrameTime = pValve->pGlobals->frametime;
		if (pLocal->GetLifeState() == 0) {
			bunnies(pCmd);
			
			pValve->pGlobals->curtime = pLocal->TickBase() * pValve->pGlobals->interval_per_tick;
			pValve->pGlobals->frametime = pValve->pGlobals->interval_per_tick;
			
			CUserCmd oldcmd;
			
			memcpy(&oldcmd, pCmd, sizeof(CUserCmd));
			
			CMoveData move_data;
			memset(&move_data, 0, sizeof(move_data));
			
			pMoveHelper->SetHost(pLocal);
			
			pPrediction->SetupMove(pLocal, pCmd, pMoveHelper, &move_data);
			pGameMovement->ProcessMovement(pLocal, &move_data);
			
			pGameMovement->StartTrackPredictionErrors(pLocal);
			pPrediction->FinishMove(pLocal, pCmd, &move_data);

			if (vars::misc_airstuck) {
				if (GetAsyncKeyState(vars::misc_airstuckey) & 0x8000) {
					if (pCmd->buttons & IN_ATTACK)
						return;
					if (pCmd->buttons & IN_ATTACK2)
						return;
					if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
						return;
					if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
						return;

					pCmd->tick_count = INT_MAX - (99 + pLocal->GetVelocity().Length2D() * 20000);
					isAirstucking = true;
				}
				else {
					isAirstucking = false;
				}
			}
			else {
				isAirstucking = false;
			}

			if (isAirstucking)
				return false;

			if (vars::rage_active && !isAirstucking) {
			
				pValve->pGlobals->interpolation_amount = 0;
				RAGEBOT(pCmd, pLocal, pWeapon, bSendPacket);
				MakeRecoil(pCmd, pLocal);
				
				MakeAutoPistol(pCmd, pWeapon);
			
				if (vars::rage_psilent) {
					RageSilent(pCmd, pWeapon, pLocal, bSendPacket, origView, sidemove, forwardmove);
				}

				FakelagFix(pLocal, pCmd);
			
			}

			if (!vars::rage_active && !isAirstucking) {

				LEGITBOT(pCmd, pLocal, pWeapon, bSendPacket);
				AccuracyBoost(pCmd, pLocal, pWeapon, bSendPacket);
				Triggerbot(pCmd, pLocal, pWeapon, bSendPacket);
				

				if ((xactive && xpsilent) || aActive) {
					MakePerfectSilent(pCmd, pWeapon, pLocal, bSendPacket, origView, sidemove, forwardmove);
					RagePsilentAim(pCmd, pLocal, pWeapon, origView, forwardmove, sidemove, bSendPacket);
				}
				
			}
			
			//pCmd->tick_count += TICKS_TO_TIME(pValve->pGlobals->interval_per_tick);
			radiospam();
			shit(pWeapon);
			doorspammer(pCmd);
			//CTag();

			if (vars::moonwalk)
				moonwalk(pCmd);


			if ((pCmd->buttons & IN_JUMP) & 0x8000 && !(pLocal->Flags() & FL_ONGROUND) && vars::misc_duck) {
				pCmd->buttons |= IN_DUCK;
			}
			bool fl = true;
			if (vars::misc_fakelag == 0)
				fl = false;


			fakelag(pCmd, pLocal,bSendPacket);
			if (!isAirstucking)
				MakeAntiAim(pCmd, pLocal, pWeapon, bSendPacket, fl);

			if (vars::misc_autostrafe && pLocal->GetVelocity().Length2D() > vars::minvel) {
				teleStrafer(pCmd, pLocal, bSendPacket);

			}

			
			
			pHuvud(pCmd, pLocal, bSendPacket, pWeapon);
			if (vars::misc_pitch > 1 || vars::misc_yaw > 1 || vars::headfix) {
				C::AngleVectors(qAimAngles, &viewforward, &viewright, &viewup);
				if (pCmd->viewangles.x > 89 || pCmd->viewangles.x < -89) {
					qAimAngles.Init(pCmd->viewangles.x, pCmd->viewangles.y, 0.f);
				}
				else {
					qAimAngles.Init(0.0f, pCmd->viewangles.y, 0.0f);
				}


				C::AngleVectors(qAimAngles, &aimforward, &aimright, &aimup);
				Vector vForwardNorm;		C::NormalizeCAngle(viewforward, vForwardNorm);
				Vector vRightNorm;			C::NormalizeCAngle(viewright, vRightNorm);
				Vector vUpNorm;				C::NormalizeCAngle(viewup, vUpNorm);

				float forward = pCmd->forwardmove;
				float right = pCmd->sidemove;
				float up = pCmd->upmove;
				if (forward > 450) forward = 450;
				if (right > 450) right = 450;
				if (up > 450) up = 450;
				if (forward < -450) forward = -450;
				if (right < -450) right = -450;
				if (up < -450) up = -450;
				pCmd->forwardmove = DotProduct(forward * vForwardNorm, aimforward) + DotProduct(right * vRightNorm, aimforward) + DotProduct(up * vUpNorm, aimforward);
				pCmd->sidemove = DotProduct(forward * vForwardNorm, aimright) + DotProduct(right * vRightNorm, aimright) + DotProduct(up * vUpNorm, aimright);
				pCmd->upmove = DotProduct(forward * vForwardNorm, aimup) + DotProduct(right * vRightNorm, aimup) + DotProduct(up * vUpNorm, aimup);
				if (forward > 450) forward = 450;
				if (right > 450) right = 450;
				if (up > 450) up = 450;
				if (forward < -450) forward = -450;
				if (right < -450) right = -450;
				if (up < -450) up = -450;

			}
			pGameMovement->FinishTrackPredictionErrors(pLocal);
			pMoveHelper->SetHost(NULL);
			pValve->pGlobals->curtime = oldCurTime;
			pValve->pGlobals->frametime = oldFrameTime;
			pWeapon->UpdateAccuracyPenalty();
			
		}
		
		else {
			pMoveHelper = **reinterpret_cast<IMoveHelper***>(PatternSearch("client.dll", (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B\x45\x00\x51\x8B\xD4\x89\x02\x8B\x01", "xx????xx?xxxxxxx", NULL, NULL) + 2);
		}
		tpangle.x = pCmd->viewangles.x;
		tpangle.z = pCmd->viewangles.z;
		if (bSendPacket)
			tpangle.y = pCmd->viewangles.y;
	
		pCmd->viewangles.Clamp();

	}
	
	return false;

}





void PatchSingleBYTE(DWORD adr, BYTE value)
{
	DWORD OldProtection;
	VirtualProtect((LPVOID)adr, 1, PAGE_READWRITE, &OldProtection);
	*(BYTE*)(adr) = value;
	VirtualProtect((LPVOID)adr, 1, OldProtection, &OldProtection);
}
bool BoolOnce = false;


float OldLowerBodyYaws[64];
float OldYawDeltas[64];
void __stdcall hkFrameStage(ClientFrameStage_t curstage) {


	C_BaseEntity* pLocalEntity = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
	
	static int offset1 = offsets.m_Local + 0x64; // Visual.
	static int offset2 = offsets.m_Local + 0x70; // Punch.

	Vector* viewPunch = nullptr;
	Vector* aimPunch = nullptr;

	Vector viewPunchReal, aimPunchReal;

	
	if (curstage == FRAME_RENDER_START && (pValve->pEngine->IsConnected() && pValve->pEngine->IsInGame())) {
		if (pLocalEntity->IsValid() && pLocalEntity->Health() > 0) {

			for (int i = 1; i <= 64; i++)
			{
				C_BaseEntity* player = (C_BaseEntity*)pValve->pEntList->GetClientEntity(i);

				if (!player
					|| player == pLocalEntity)
					continue;
			

				*(int*)((uintptr_t)player + 0xA30) = pValve->pGlobals->framecount; //we'll skip occlusion checks now
				*(int*)((uintptr_t)player + 0xA28) = 0;//clear occlusion flags
			}

			*reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(pValve->pInput) + 0xA5) = vars::misc_thirdperson;
			if (*reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(pValve->pInput) + 0xA5))
			{
				*reinterpret_cast<Vector*>(reinterpret_cast<uintptr_t>(pLocalEntity) + offsets.dwDeadFlag + 0x4) = tpangle;
			}
		}
		else {
			*reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(pValve->pInput) + 0xA5) = false;
		}
	}
	else
	{
		*reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(pValve->pInput) + 0xA5) = false;
	}

	if (curstage == FRAME_RENDER_START)
	{
		if (pLocalEntity && vars::misc_novisrecoil)
		{
			viewPunch = (Vector*)((DWORD)pLocalEntity + offset1);
			aimPunch = (Vector*)((DWORD)pLocalEntity + offset2);

			if (viewPunch && aimPunch)
			{
				viewPunchReal = *viewPunch;
				aimPunchReal = *aimPunch;

				viewPunch->Init();
				aimPunch->Init();
			}
		}
		
	}

	pValve->oFrameStage(curstage);

	if (viewPunch && aimPunch) {
		if (vars::misc_novisrecoil) {
			*viewPunch = viewPunchReal;
			*aimPunch = aimPunchReal;
		}
	}

	if (curstage == FRAME_NET_UPDATE_POSTDATAUPDATE_START && (pValve->pEngine->IsConnected() && pValve->pEngine->IsInGame()))
	{
		if (vars::noflash)
			pLocalEntity->FlashAlpha() = 0.0f;
		else {
			pLocalEntity->FlashAlpha() = 255.f;
		}

		
		for (int i = 1; i < 64; ++i)
		{
			C_BaseEntity* player = (C_BaseEntity*)pValve->pEntList->GetClientEntity(i);
			
			if (!player
				|| player == pLocalEntity
				|| player->Dormant()
				|| player->Team() == pLocalEntity->Team())
				continue;
			
			if (vars::resolvemyass == 3) {
				// CBaseAnimating	0x28AC	m_nSequence

				float angle = 0.0f;
				int m_nSequence = *reinterpret_cast<int*>(DWORD(player) + 0x28AC);

				if (m_nSequence == 979) // ACT_CSGO_BALANCETURN_ADJUST
				{
					angle = player->GetLowerBodyYawTarget();
				}
				else
				{
					angle = 90 * shots_fired;
				}
				

				*(float*)((uintptr_t)player + offsets.m_iEyeAngles + 4) = player->GetEyeAngles().y;
				

				float yClamped = player->GetEyeAngles().y;
				while (yClamped < -180.0f)
					yClamped += 360.0f;

				while (yClamped > 180.0f)
					yClamped -= 360.0f;
				*(float*)((uintptr_t)player + offsets.m_iEyeAngles + 4) = yClamped;

			}
			else if (vars::resolvemyass == 2) {
				player_info_t entityInformation;
				pValve->pEngine->GetPlayerInfo(i, &entityInformation);
				//if (vars::Resolve[player->GetIndex()]) {


				if (std::find(Players.begin(), Players.end(), entityInformation.xuid) == Players.end())
				continue;


				player_data.push_back(PlayerAA(player, *player->Eyeangles()));

				player->Eyeangles()->y = player->GetLowerBodyYawTarget();
			
			}
		}
		
	}

	else if (curstage == FRAME_RENDER_END)
	{
		for (unsigned long i = 0; i < player_data.size(); i++)
		{
			PlayerAA player_aa_data = player_data[i];

			*player_aa_data.player->Eyeangles() = player_aa_data.angle;
		}
		player_data.clear();
	}
}




#include "SigScan.h"
#include "models.h"




typedef unsigned short(__fastcall* tFindMDL)(void*, void*, const char*);
tFindMDL oFindMDL;
unsigned short __fastcall hkFindMDL(void* ecx, void* edx, const char *pMDLRelativePath)
{

	string name = pMDLRelativePath;
	static bool knife = false;
	if (knife) {
		if (!strcmp(pMDLRelativePath, "models/weapons/v_knife_default_t.mdl"))
		{
			return oFindMDL(ecx, edx, "models/weapons/v_knife_m9_bay.mdl");
		}
		if (!strcmp(pMDLRelativePath, "models/weapons/v_knife_default_ct.mdl"))
		{
			return oFindMDL(ecx, edx, "models/weapons/v_knife_m9_bay.mdl");
		}
	}
	return oFindMDL(ecx, edx, pMDLRelativePath);
}

// -----===== INTERFACE =====------
void Valve::InitializeAll() {
	
		CreateInterface engine = (CreateInterface)GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");
		CreateInterface client = (CreateInterface)GetProcAddress(GetModuleHandleA("client.dll"), "CreateInterface");
		CreateInterface vgui = (CreateInterface)GetProcAddress(GetModuleHandleA("vgui2.dll"), "CreateInterface");
		CreateInterface surface = (CreateInterface)GetProcAddress(GetModuleHandleA("vguimatsurface.dll"), "CreateInterface");
		CreateInterface vstdlib = (CreateInterface)GetProcAddress(GetModuleHandleA("vstdlib.dll"), "CreateInterface");
		CreateInterface vprops = (CreateInterface)GetProcAddress(GetModuleHandleA("vphysics.dll"), "CreateInterface");
		CreateInterface matsystem = (CreateInterface)GetProcAddress(GetModuleHandleA("materialsystem.dll"), "CreateInterface");
		CreateInterface cache = (CreateInterface)GetProcAddress(GetModuleHandleA("datacache.dll"), "CreateInterface");



		CMDLCache* pCache;
		pSurface = (ISurface*)pVape->GetInterface("VGUI_Surface", "pSurface", surface);
		pPanel = (IPanel*)pVape->GetInterface("VGUI_Panel", "pPanel", vgui);
		pEngine = (IVEngineClient*)pVape->GetInterface("VEngineClient", "pEngine", engine);
		pClient = (IBaseClientDLL*)pVape->GetInterface("VClient", "pClient", client);
		pEntList = (IClientEntityList*)pVape->GetInterface("VClientEntityList", "pEntList", client);
		pOverlay = (IVDebugOverlay*)pVape->GetInterface("VDebugOverlay", "pOverlay", engine);
		pCvar = (ICvar*)pVape->GetInterface("VEngineCvar", "pCvar", vstdlib);
		pEngineTrace = (IEngineTrace*)pVape->GetInterface("EngineTraceClient", "pEngineTrace", engine);
		pProps = (IPhysicsSurfaceProps*)pVape->GetInterface("VPhysicsSurfaceProps", "pProps", vprops);
		pModelInfo = (IVModelInfo*)pVape->GetInterface("VModelInfoClient", "pModelInfo", engine);
		pMatSystem = (IVMaterialSystem*)pVape->GetInterface("VMaterialSystem", "pMatSystem", matsystem);
		pModelRender = (IVModelRender*)pVape->GetInterface("VEngineModel", "pModelRender", engine);
		pRenderView = (IVRenderView*)pVape->GetInterface("VEngineRenderView", "pRenderView", engine);
		pPrediction = (IPrediction*)client("VClientPrediction001", NULL);
		pGameMovement = (IGameMovement*)client("GameMovement001", NULL);
		pMoveHelper = **(IMoveHelper***)(xFindPattern("client.dll", "8B 0D ? ? ? ? 8B 46 08 68") + 2);
		pCache = (CMDLCache*)pVape->GetInterface("MDLCache", "pCache", cache);
		ViewRender = **(void***)((DWORD)xFindPattern("client.dll", "FF 50 14 E8 ? ? ? ? 5D") - 7);

		//RecvPropHook* g_sequence_hook;	


		time_t rawtime;
		struct tm * timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);


		g_pGameEventManager = (IGameEventManager*)engine("GAMEEVENTSMANAGER002", NULL);
		pValve->pEngine->ExecuteClientCmd("clear");
		pCvar->ConsoleColorPrintf(Color(0, 119, 255, 255), "================================================\n");
		pCvar->ConsoleColorPrintf(Color(0, 119, 255, 255), " TIME OF INJECTION:    ");
		pCvar->ConsoleColorPrintf(Color(255, 255, 0, 255), "%s\n", asctime(timeinfo));


		void** BaseClient = *(void***)pClient;
		xClient = *(IBaseClientDLL***)((DWORD)BaseClient[10] + 5);

		CVMTHookManager* chook;
		chook = new CVMTHookManager((DWORD**)pCache);

		// VMT's.
		clienthook = new CVMTHookManager((DWORD**)pClient);
		panelhook = new CVMTHookManager((DWORD**)pPanel);
		otherhook = new CVMTHookManager(*(DWORD***)xClient);
		modelhook = new CVMTHookManager((PDWORD*)pModelRender);
		renderhook = new CVMTHookManager((PDWORD*)ViewRender);
//		playsoundhook = new CVMTHookManager((PDWORD*)g_pPlaySound);

		CVMTHookManager* shinehook = NULL;
		shinehook = new CVMTHookManager((DWORD**)pPrediction);

		pInput = (CInput*)*(DWORD*)((DWORD)BaseClient[15] + 1);
		void** CInputVMT = *(void***)pInput;
		DWORD pCAM_Think = (DWORD)CInputVMT[31];
		PatchSingleBYTE(pCAM_Think + 0x41, 0x74);

		oRenderView = (RenderViewFn)renderhook->dwHookMethod((DWORD)hkRenderView, 6);
		oRunCommand = (tRunCommand)clienthook->dwHookMethod((DWORD)hkRunCommand, 19);
		oCreateMove = (ClientModeInternally)otherhook->dwHookMethod((DWORD)hkCreateMove, 24);
		oPaintTraverse = (tPaintTraverse)panelhook->dwHookMethod((DWORD)hkPaintTraverse, 41);
		oFrameStage = (tFrameStage)clienthook->dwHookMethod((DWORD)hkFrameStage, 36);
		oOverrideView = (hkdOverrideView)otherhook->dwHookMethod((DWORD)hkOverrideView, 18);
		oDrawModelExecute = (hkdDrawModelExecute)modelhook->dwHookMethod((DWORD)hkDrawModelExecute, 21);
		oPlaySound = (PlaySoundFn)otherhook->dwHookMethod((DWORD)hkPlaySound_CSGO, 82);

//		applyProxies();


		//oFindMDL = (tFindMDL)chook->dwHookMethod((DWORD)hkFindMDL, 10);

		PDWORD* pdwGameEventVMT = (PDWORD*)g_pGameEventManager;
		eventhook = new CVMTHookManager(pdwGameEventVMT);
		oFireEventClientSide = (hkdFireEvent)eventhook->dwHookMethod((DWORD)hkFireEventClientSide, 9);

		PDWORD pdwClient = (PDWORD)*(PDWORD)pClient;
		DWORD dwInitAddr = (DWORD)(pdwClient[0]);
		pGlobals = (CGlobalVarsBase*)*(PDWORD)*(PDWORD)(dwInitAddr + 0x1B);
		//for (DWORD dwIter = 0; dwIter <= 0xFF; dwIter++) {
		//	if (*(PBYTE)(dwInitAddr + dwIter - 1) == 0x08 && *(PBYTE)(dwInitAddr + dwIter) == 0xA3) { //0x1B
		//		pGlobals = (CGlobalVarsBase*)*(PDWORD)*(PDWORD)(dwInitAddr + dwIter + 1);
		//		break;
		//	}
		//}
	}




DWORD WINAPI Start(LPVOID lpdaslda) {
	while (!GetModuleHandleA("serverbrowser.dll"))
	{
		Sleep(250);
	}

	pValve->InitializeAll();
	pOffsets.Init();
	offsets.getEm();
	return 0;
}

BOOL APIENTRY DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Start, NULL, NULL, NULL);
	}
	return true;
}
