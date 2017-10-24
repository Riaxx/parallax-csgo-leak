struct ShinezBox { int x, y, w, h; };
DWORD GlowObject;
class DoEsp {
public:
	void Initialize();
	void DrawHealthbar(int x, int y, int w, int h, float Health);
	void DrawPlayerName(int x, int y, player_info_t pInfo);
	void DrawPlayerBox(C_BaseEntity* pEntity, Color clr, ShinezBox& shinezSize, int index);
	void InitializeWorldESP();
	void NonVisHB(int x, int y, int w, int h, float Health);
};

class TraceEngines {
public:
	bool IsVisible(C_BaseEntity* pEntity, C_BaseEntity* pLocal);
	bool IsVisibleHD(C_BaseEntity* pEntity, C_BaseEntity* pLocal, Vector& pBone);
	bool IsVisibleHDD(C_BaseEntity* pEntity, C_BaseEntity* pLocal, Vector& pBone, int hBox);
};
float transparency = 255.f;
extern TraceEngines* traceEngines;

bool FindPattern8(C_BaseEntity* pPlayer, Vector& Hitbox, int Bone) {
	matrix3x4 MatrixArray[128];

	if (!pPlayer->SetupBones(MatrixArray, 128, 0x100, 0))
		return false;

	Hitbox = Vector(MatrixArray[Bone][0][3], MatrixArray[Bone][1][3], MatrixArray[Bone][2][3]);
	return true;
}

Vector GetBonePosition(DWORD pEntity, int Hitbox, Vector& Bone) {
	Bone.x = *(float*)((DWORD)pEntity + 0x30 * Hitbox + 0xC);
	Bone.y = *(float*)((DWORD)pEntity + 0x30 * Hitbox + 0x1C);
	Bone.z = *(float*)((DWORD)pEntity + 0x30 * Hitbox + 0x2C);
	return Bone;
}
bool TraceEngines::IsVisible(C_BaseEntity* pEntity, C_BaseEntity* pLocal) {
	Ray_t rayer;
	CTraceFilter tracer;
	trace_t trace;

	tracer.pSkip = pLocal;

	rayer.Init(pLocal->GetEyePos(), pEntity->GetEyePos());
	pValve->pEngineTrace->TraceRay(rayer, 0x46004003, &tracer, &trace);
	return (trace.m_pEnt == pEntity || trace.fraction > 0.99f);
}

bool TraceEngines::IsVisibleHD(C_BaseEntity* pEntity, C_BaseEntity* pLocal, Vector& pBone) {
	Ray_t rayer;
	CTraceFilter tracer;
	trace_t trace;

	tracer.pSkip = pLocal;

	rayer.Init(pLocal->GetEyePos(), GetBonePosition(pEntity->BoneMatrix(), 6, pBone));
	pValve->pEngineTrace->TraceRay(rayer, 0x46004003, &tracer, &trace);
	return (trace.m_pEnt == pEntity || trace.fraction > 0.99f);
}

bool TraceEngines::IsVisibleHDD(C_BaseEntity* pEntity, C_BaseEntity* pLocal, Vector& pBone, int hBox) {
	Ray_t rayer;
	CTraceFilter tracer;
	trace_t trace;

	tracer.pSkip = pLocal;

	rayer.Init(pLocal->GetEyePos(), GetBonePosition(pEntity->BoneMatrix(), hBox, pBone));
	pValve->pEngineTrace->TraceRay(rayer, 0x4600400B, &tracer, &trace);
	return (trace.m_pEnt == pEntity || trace.fraction > 0.99f);
}

bool WorldToScreen(Vector& From, Vector& To) {
	return (pValve->pOverlay->ScreenPosition(From, To) != 1);
}

void DoEsp::DrawHealthbar(int x, int y, int w, int h, float Health) {
	PKAZOR->FillRGBA(x, y, w, h, Color(0, 0, 0, 230));
	UINT hw = (((w)* Health) / 100);
	PKAZOR->FillRGBA(x, y, hw, h, PKAZOR->Rainbow());
	PKAZOR->DrawBox(x, y, w, h, Color(0, 0, 0, 255));
}

void DoEsp::NonVisHB(int x, int y, int w, int h, float Health) {
	PKAZOR->FillRGBA(x, y, w, h, Color(0, 0, 0, transparency));
	UINT hw = (((w)* Health) / 100);
	PKAZOR->FillRGBA(x, y, hw, h, PKAZOR->Rainbow());
	PKAZOR->DrawBox(x, y, w, h, Color(0, 0, 0, transparency));
}

void DoEsp::DrawPlayerName(int x, int y, player_info_t pInfo) {
	PKAZOR->DrawString(x, y, Color(255, 255, 255, 255), xFont, pInfo.name);
}

void DrawLine2D(Vector& From, Vector& To, Color fat) {
	PKAZOR->DrawLine(From.x, From.y, To.x, To.y, fat);
}

void DrawLine2DOutline(Vector& From, Vector& To, Color fat) {
	PKAZOR->DrawLine(From.x, From.y, To.x, To.y, fat);
}
void DrawPlayerHealthBox(int x, int y, int w, int h, Color dwColor, int health, int maxHealth, int transparency) {



	Color dwHealth;



	dwHealth = Color(255, 255, 255, 255); //white


	if (health > 100)
		dwHealth = Color(0, 0, 255, transparency);
	if (health <= 100 && health > 60)
		dwHealth = Color(131, 250, 107, transparency);

	if (health <= 60 && health > 40)
		dwHealth = Color(250, 240, 107, transparency);
	if (health <= 40 && health > 20)
		dwHealth = Color(255, 128, 0, transparency);
	if (health <= 20 && health > 0)
		dwHealth = Color(200, 2, 33, transparency);

	//x -= floor(w + 6);
	PKAZOR->FillRGBA(floor(x), floor(y) - 1, w, h + 2, Color(10, 10, 10, transparency));

	int hw = floor((((h)* health) / maxHealth));
	PKAZOR->FillRGBA(floor(x) + 1, floor(y + (h - hw)), w / 2, hw, dwHealth);

}

Vector GetActualPos(C_BaseEntity* pPlayer, int Bone) {
	matrix3x4 boneMatrix[128];

	if (pPlayer->SetupBones(boneMatrix, 128, 256, pValve->pGlobals->curtime)) {
		return Vector(boneMatrix[Bone][0][3], boneMatrix[Bone][1][3], boneMatrix[Bone][2][3]);
	}
	return Vector(0, 0, 0);
}

Vector SetActualPos(C_BaseEntity* pPlayer, int Bone) {
	return GetActualPos(pPlayer, 6);
}

struct matrix3x4_tt
{
	matrix3x4_tt() {}
	matrix3x4_tt(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}
	void Init(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
	{
		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
	}

	matrix3x4_tt(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
	{
		Init(xAxis, yAxis, zAxis, vecOrigin);
	}
	float *operator[](int i)
	{
		return m_flMatVal[i];
	}
	const float *operator[](int i) const
	{
		return m_flMatVal[i];
	}
	float *Base()
	{
		return &m_flMatVal[0][0];
	}
	const float *Base() const
	{
		return &m_flMatVal[0][0];
	}

	float m_flMatVal[3][4];
};


float DotProductT(const float* a, const float* b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}
void VectorTransformA(const float *in1, const matrix3x4_tt& in2, float *out)
{

	out[0] = DotProductT(in1, in2[0]) + in2[0][3];
	out[1] = DotProductT(in1, in2[1]) + in2[1][3];
	out[2] = DotProductT(in1, in2[2]) + in2[2][3];
}

inline void VectorTransformZ(const Vector& in1, const matrix3x4_tt &in2, Vector &out)
{
	VectorTransformA(&in1.x, in2, &out.x);
}

bool GetBoxStatic(C_BaseEntity* pEntity, ShinezBox &result) {

	// Variables
	Vector  vOrigin, sMin, sMax, sOrigin,
		flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	// Get the locations

	vOrigin = pEntity->GetAbsOrigin();
	Vector min = pEntity->GetCollideable()->OBBMins() + vOrigin;
	Vector max = pEntity->GetCollideable()->OBBMaxs() + vOrigin;

	// Points of a 3d bounding box
	Vector points[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};


	// Get screen positions
	if (!WorldToScreen(points[3], flb) || !WorldToScreen(points[5], brt)
		|| !WorldToScreen(points[0], blb) || !WorldToScreen(points[4], frt)
		|| !WorldToScreen(points[2], frb) || !WorldToScreen(points[1], brb)
		|| !WorldToScreen(points[6], blt) || !WorldToScreen(points[7], flt))
		return false;

	// Put them in an array (maybe start them off in one later for speed?)
	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	// Init this shit
	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	// Find the bounding corners for our box
	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	// Width / height
	result.x = left;
	result.y = top;
	result.w = right - left;
	result.h = bottom - top;

	return true;
}
void ESPBoxes(int x, int y, int w, int h, Color color) {
	int VertLine = (((float)w) * (0.20f));
	int HorzLine = (((float)h) * (0.20f));

	//PKAZOR->FillRGBA(x, y - 5, w, 4, Color(0, 0, 255, 255)); test
	//övre vänstra
	PKAZOR->FillRGBA(x, y, VertLine, 3, Color(0, 0, 0, 255));													// bredd
	PKAZOR->FillRGBA(x, y, 3, HorzLine, Color(0, 0, 0, 255));													// höjd
	PKAZOR->FillRGBA(x + 1, y + 1, VertLine - 2, 1, Color(color));											// bredd
	PKAZOR->FillRGBA(x + 1, y + 1, 1, HorzLine - 2, Color(color));											// höjd

																											//nedre vänstra																							
	PKAZOR->FillRGBA(x, y + h - 3, VertLine, 3, Color(0, 0, 0, 255));											// bredd
	PKAZOR->FillRGBA(x, y + h - HorzLine, 3, HorzLine, Color(0, 0, 0, 255));									// höjd
	PKAZOR->FillRGBA(x + 1, y + 1 + h - 3, VertLine - 2, 1, Color(color));									// bredd
	PKAZOR->FillRGBA(x + 1, y + 1 + h - HorzLine, 1, HorzLine - 2, Color(color));								// höjd

																											//övre högra																							
	PKAZOR->FillRGBA(x + w - VertLine, y, VertLine, 3, Color(0, 0, 0, 255));									// bredd
	PKAZOR->FillRGBA(x + w - 3, y, 3, HorzLine, Color(0, 0, 0, 255));											// höjd
	PKAZOR->FillRGBA(x + 1 + w - VertLine, y + 1, VertLine - 2, 1, Color(color));								// bredd
	PKAZOR->FillRGBA(x + 1 + w - 3, y + 1, 1, HorzLine - 2, Color(color));									// höjd

																											//nedre högra
	PKAZOR->FillRGBA(x + w - VertLine, y + h - 3, VertLine, 3, Color(0, 0, 0, 255));							// bredd
	PKAZOR->FillRGBA(x + w - 3, y + h - HorzLine, 3, HorzLine, Color(0, 0, 0, 255));							// höjd
	PKAZOR->FillRGBA(x + 1 + w - VertLine, y + 1 + h - 3, VertLine - 2, 1, Color(color));						// bredd
	PKAZOR->FillRGBA(x + 1 + w - 3, y + 1 + h - HorzLine, 1, HorzLine - 2, Color(color));						// höjd

}

void EpicInterWebzBoxer(ShinezBox size, Color color) {
	int VertLine = (((float)size.w) * (0.20f));
	int HorzLine = (((float)size.h) * (0.20f));

	PKAZOR->FillRGBA(size.x, size.y - 1, VertLine, 1, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x + size.w - VertLine, size.y - 1, VertLine, 1, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x, size.y + size.h - 1, VertLine, 1, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x + size.w - VertLine, size.y + size.h - 1, VertLine, 1, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x - 1, size.y, 1, HorzLine, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x - 1, size.y + size.h - HorzLine, 1, HorzLine, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x + size.w - 1, size.y, 1, HorzLine, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x + size.w - 1, size.y + size.h - HorzLine, 1, HorzLine, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x, size.y, VertLine, 1, color);
	PKAZOR->FillRGBA(size.x + size.w - VertLine, size.y, VertLine, 1, color);
	PKAZOR->FillRGBA(size.x, size.y + size.h, VertLine, 1, color);
	PKAZOR->FillRGBA(size.x + size.w - VertLine, size.y + size.h, VertLine, 1, color);
	PKAZOR->FillRGBA(size.x, size.y, 1, HorzLine, color);
	PKAZOR->FillRGBA(size.x, size.y + size.h - HorzLine, 1, HorzLine, color);
	PKAZOR->FillRGBA(size.x + size.w, size.y, 1, HorzLine, color);
	PKAZOR->FillRGBA(size.x + size.w, size.y + size.h - HorzLine, 1, HorzLine, color);
}

void EpicInterWebzBoxer2(ShinezBox size, Color color) {
	int VertLine = (((float)size.w) * (0.20f));
	int HorzLine = (((float)size.h) * (0.20f));

	PKAZOR->FillRGBA(size.x, size.y - 1, VertLine, 1, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x + size.w - VertLine, size.y - 1, VertLine, 1, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x, size.y + size.h - 1, VertLine, 1, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x + size.w - VertLine, size.y + size.h - 1, VertLine, 1, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x - 1, size.y, 1, HorzLine, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x - 1, size.y + size.h - HorzLine, 1, HorzLine, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x + size.w - 1, size.y, 1, HorzLine, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x + size.w - 1, size.y + size.h - HorzLine, 1, HorzLine, Color(10, 10, 10, transparency));
	PKAZOR->FillRGBA(size.x, size.y, VertLine, 1, color);
	PKAZOR->FillRGBA(size.x + size.w - VertLine, size.y, VertLine, 1, color);
	PKAZOR->FillRGBA(size.x, size.y + size.h, VertLine, 1, color);
	PKAZOR->FillRGBA(size.x + size.w - VertLine, size.y + size.h, VertLine, 1, color);
	PKAZOR->FillRGBA(size.x, size.y, 1, HorzLine, color);
	PKAZOR->FillRGBA(size.x, size.y + size.h - HorzLine, 1, HorzLine, color);
	PKAZOR->FillRGBA(size.x + size.w, size.y, 1, HorzLine, color);
	PKAZOR->FillRGBA(size.x + size.w, size.y + size.h - HorzLine, 1, HorzLine, color);
}

#define BONE_USED_BY_HITBOX			0x00000100

Vector GetBonePos(int i, C_BaseEntity* pBaseEntity) {
	matrix3x4 boneMatrix[128];
	if (pBaseEntity->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, GetTickCount64()))
	{
		return Vector(boneMatrix[i][0][3], boneMatrix[i][1][3], boneMatrix[i][2][3]);
	}
	return Vector(0, 0, 0);
}

bool IsVisible(C_BaseEntity* pLoc, C_BaseEntity* pEnt) {
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = pLoc;

	ray.Init(pLoc->GetEyePos(), pEnt->GetEyePos());
	pValve->pEngineTrace->TraceRay(ray, 0x46004003, &filter, &tr);

	return (tr.m_pEnt == pEnt || tr.fraction > 0.99f);
}

void GetSkeletal(C_BaseEntity* pBaseEntity, C_BaseEntity* pLocalEntity) {
	studiohdr_t* pStudioHdr = pValve->pModelInfo->GetStudiomodel(pBaseEntity->GetModel());

	if (!pStudioHdr)
		return;

	Vector vParent, vChild, sParent, sChild;

	for (int j = 0; j < pStudioHdr->numbones; j++)
	{
		mstudiobone_t* pBone = pStudioHdr->GetBone(j);

		if (pBone && (pBone->flags & 0x100) && (pBone->parent != -1))
		{
			vChild = GetBonePos(j, pBaseEntity);
			vParent = GetBonePos(pBone->parent, pBaseEntity);
			bool bVis = IsVisible(pLocalEntity, pBaseEntity);
			bool bVisByBone = traceEngines->IsVisibleHDD(pBaseEntity, pLocalEntity, vParent, pBone->parent);
			if (WorldToScreen(vParent, sParent) && WorldToScreen(vChild, sChild)) {
				if (bVis)
					PKAZOR->DrawLine(sParent.x, sParent.y, sChild.x, sChild.y, Color(255, 255, 255, 255));
				else {
					if (!vars::visonly) {
						if (pBaseEntity->Team() == 2)
							PKAZOR->DrawLine(sParent.x, sParent.y, sChild.x, sChild.y, Color(255, 255, 255, vars::t_transparency * 2.55f));
						else if (pBaseEntity->Team() == 3)
							PKAZOR->DrawLine(sParent.x, sParent.y, sChild.x, sChild.y, Color(255, 255, 255, vars::ct_transparency * 2.55f));
					}
				}
				//PKAZOR->DrawString(sParent.x, sParent.y, Color(255, 255, 255, 255), labelFont, to_string(j).c_str());
			}
		}
	}
}


const char* getWeapons(C_BaseEntity* pEntity) {
	C_BaseCombatWeapon* m_pWeapon = pEntity->Active();
	char m_szPrintName[999];
	int iWeaponID = pEntity->GetWeapon();

	switch (iWeaponID) {
	case WEAPON_NONE: {strcpy(m_szPrintName, "Null"); break; }
	case WEAPON_KNIFE: {strcpy(m_szPrintName, "CT Knife"); break; }
	case WEAPON_KNIFE_T: {strcpy(m_szPrintName, "T Knife"); break; }
	case WEAPON_BAYONET: {strcpy(m_szPrintName, "Bayonet"); break; }
	case WEAPON_FLIP: {strcpy(m_szPrintName, "Flip Knife"); break; }
	case WEAPON_GUT: {strcpy(m_szPrintName, "Gut Knife"); break; }
	case WEAPON_KARAMBIT: {strcpy(m_szPrintName, "Karambit"); break; }
	case WEAPON_M9: {strcpy(m_szPrintName, "M9 Bayonet"); break; }
	case WEAPON_HUNTSMAN: {strcpy(m_szPrintName, "Huntsman Knife"); break; }
	case WEAPON_FALCHION: {strcpy(m_szPrintName, "Falchion Knife"); break; }
	case WEAPON_BOWIE: {strcpy(m_szPrintName, "Bowie Knife"); break; }
	case WEAPON_BUTTERFLY: {strcpy(m_szPrintName, "Butterfly Knife"); break; }
	case WEAPON_DAGGER: {strcpy(m_szPrintName, "Shadow Daggers"); break; }
	case WEAPON_DEAGLE: {strcpy(m_szPrintName, "Desert Eagle"); break; }
	case WEAPON_DUALBERETTAS: {strcpy(m_szPrintName, "Dual Berettas"); break; }
	case WEAPON_FIVESEVEN: {strcpy(m_szPrintName, "Five-SeveN"); break; }
	case WEAPON_GLOCK18: {strcpy(m_szPrintName, "Glock-18"); break; }
	case WEAPON_USP_S: {strcpy(m_szPrintName, "USP-S"); break; }
	case WEAPON_AK47: {strcpy(m_szPrintName, "AK-47"); break; }
	case WEAPON_AUG: {strcpy(m_szPrintName, "AUG"); break; }
	case WEAPON_AWP: {strcpy(m_szPrintName, "AWP"); break; }
	case WEAPON_FAMAS: {strcpy(m_szPrintName, "FAMAS"); break; }
	case WEAPON_G3SG1: {strcpy(m_szPrintName, "G3SG1"); break; }
	case WEAPON_GALILAR: {strcpy(m_szPrintName, "Galil-AR"); break; }
	case WEAPON_M249: {strcpy(m_szPrintName, "M249"); break; }
	case WEAPON_R8REVOLVER: {strcpy(m_szPrintName, "Revolver"); break; }
	case WEAPON_M4A4: {strcpy(m_szPrintName, "M4A4"); break; }
	case WEAPON_M4A1_SILENCER: {strcpy(m_szPrintName, "M4A1-S"); break; }
	case WEAPON_MAC10: {strcpy(m_szPrintName, "MAC-10"); break; }
	case WEAPON_P90: {strcpy(m_szPrintName, "P90"); break; }
	case WEAPON_UMP45: {strcpy(m_szPrintName, "UMP45"); break; }
	case WEAPON_XM1014: {strcpy(m_szPrintName, "XM1014"); break; }
	case WEAPON_BIZON: {strcpy(m_szPrintName, "PP-Bizon"); break; }
	case WEAPON_MAG7: {strcpy(m_szPrintName, "MAG-7"); break; }
	case WEAPON_NEGEV: {strcpy(m_szPrintName, "Negev"); break; }
	case WEAPON_SAWEDOFF: {strcpy(m_szPrintName, "Sawed-Off"); break; }
	case WEAPON_TEC9: {strcpy(m_szPrintName, "Tec-9"); break; }
	case WEAPON_ZEUS: {strcpy(m_szPrintName, "Zeus"); break; }
	case WEAPON_HPK2000: {strcpy(m_szPrintName, "P2000"); break; }
	case WEAPON_MP7: {strcpy(m_szPrintName, "MP7"); break; }
	case WEAPON_CZ75A: {strcpy(m_szPrintName, "CZ-75"); break; }
	case WEAPON_MP9: {strcpy(m_szPrintName, "MP9"); break; }
	case WEAPON_NOVA: {strcpy(m_szPrintName, "Nova"); break; }
	case WEAPON_P250: {strcpy(m_szPrintName, "P250"); break; }
	case WEAPON_SCAR20: {strcpy(m_szPrintName, "SCAR20"); break; }
	case WEAPON_SSG08: {strcpy(m_szPrintName, "SSG08"); break; }
	case WEAPON_SG553: {strcpy(m_szPrintName, "SG533"); break; }
	case WEAPON_FLASHBANG: {strcpy(m_szPrintName, "Flashbang"); break; }
	case WEAPON_HEGRENADE: {strcpy(m_szPrintName, "HE Grenade"); break; }
	case WEAPON_SMOKEGRENADE: {strcpy(m_szPrintName, "Smoke"); break; }
	case WEAPON_MOLOTOV: {strcpy(m_szPrintName, "Molotov"); break; }
	case WEAPON_DECOY: {strcpy(m_szPrintName, "Decoy"); break; }
	case WEAPON_INCGRENADE: {strcpy(m_szPrintName, "Incendiary Grenade"); break; }
	case WEAPON_C4: {strcpy(m_szPrintName, "C4"); break; }
	}
	return m_szPrintName;
}

extern DoEsp* PESP;
DoEsp* PESP = new DoEsp();