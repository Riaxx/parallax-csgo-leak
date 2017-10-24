#define M_PI		3.14159265358979323846
#define M_RADPI 57.295779513082
#define PI 3.14159265358979323846f
#define M_PI_F		((float)(M_PI))
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
float gringox, gringoy;
bool rcsE, rcsS, rcsR;
namespace getEngine {
	Vector ClampAngles(Vector AngleToNormalize)
	{
		Vector vec = AngleToNormalize;
		if (vec.x > 89.0f && vec.x <= 180.0f)
		{
			vec.x = 89.0f;
		}
		while (vec.x > 180.f)
		{
			vec.x -= 360.f;
		}
		while (vec.x < -89.0f)
		{
			vec.x = -89.0f;
		}
		while (vec.y > 180.f)
		{
			vec.y -= 360.f;
		}
		while (vec.y < -180.f)
		{
			vec.y += 360.f;
		}

		vec.z = 0;
		return vec;
	}

	MODULEENTRY32 *GetModuleInfo(char *szModule)
	{
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
		static MODULEENTRY32 me32;
		ZeroMemory(&me32, sizeof(MODULEENTRY32));
		me32.dwSize = sizeof(MODULEENTRY32);

		Module32First(hSnapshot, &me32);
		while (Module32Next(hSnapshot, &me32))
		{
			if (!strcmp(szModule, me32.szModule))
			{
				CloseHandle(hSnapshot);
				return &me32;
			}
		}

		CloseHandle(hSnapshot);
		return 0;
	}


	bool DataCompare(const BYTE* pData, const BYTE* bMask, const char* pszMask)
	{
		for (; *pszMask; ++pszMask, ++pData, ++bMask)
			if (*pszMask == 'x' && *pData != *bMask)
				return false;
		return (*pszMask == 0);
	}

	DWORD dwFindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char *pszMask)
	{
		for (DWORD i = 0; i<dwLen; i++)
			if (DataCompare((BYTE*)(dwAddress + i), bMask, pszMask))
				return dwAddress + i;

		return 0;
	}

	DWORD FindPattern(char *szModule, BYTE *bMask, char *pszMask)
	{
		MODULEENTRY32 *me32 = GetModuleInfo(szModule);
		if (!me32)
			return 0;

		DWORD dwAddress = (DWORD)me32->modBaseAddr;
		DWORD dwLen = (DWORD)me32->modBaseSize;

		return dwFindPattern(dwAddress, dwLen, bMask, pszMask);
	}

	DWORD pFindPattern(std::string moduleName, std::string pattern)
	{
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
}

class vape {
public:
	void* GetInterface(const char* interfaceName, const char* ptrName, CreateInterface pInterface) {
		// den här funktionen ska tydligen få tag i alla interfaces automatiskt.
		char szDebugString[1024];

		std::string sinterface = "";
		std::string interfaceVersion = "0";

		for (int i = 0; i <= 99; i++) {
			sinterface = interfaceName;
			sinterface += interfaceVersion;
			sinterface += std::to_string(i);

			void* funcPtr = pInterface(sinterface.c_str(), NULL);

			if ((DWORD)funcPtr != 0x0) {

				sprintf_s(szDebugString, "%s: 0x%x (%s%s%i)", ptrName, (DWORD)funcPtr, interfaceName, interfaceVersion.c_str(), i);
				return funcPtr;
			}
			if (i >= 99 && interfaceVersion == "0") {
				interfaceVersion = "00";
				i = 0;
			}
			else if (i >= 99 && interfaceVersion == "00") {
				sprintf_s(szDebugString, "%s: 0x%x (error)", ptrName, (DWORD)funcPtr);
			}
		}
		// jupp.. det gjorde den. ;)
		return 0;
	}
};
extern vape* pVape;
vape* pVape = new vape();

bool isOpend = false;

bool keytg(int iKey)
{
	static bool bKeyPressed[256] = { false };

	if (HIWORD(GetKeyState(iKey)) != 0)
	{
		if (!bKeyPressed[iKey])
		{
			bKeyPressed[iKey] = true;
			return true;
		}
	}
	else
		bKeyPressed[iKey] = false;

	return false;
}

void ToggleUpp() {
	if (keytg(VK_INSERT)) {
		//if (GetAsyncKeyState(VK_INSERT) & 0x8000) return;
		isOpend = !isOpend;
		pValve->pEngine->ExecuteClientCmd("cl_mouseenable 1");
	}
}

namespace C {

	void AntiAntiAimProxy(const CRecvProxyData *pData, void *pStruct, void *pOut)
	{
		float pfix = pData->m_Value.m_Float;

		pfix = -89;

		*(float*)pOut = pfix;
	}

	void SinCos(float a, float* s, float*c) {
		*s = sin(a);
		*c = cos(a);
	}

	void DoSmooth(int SmoothFactor, Vector& ParcismAngle, Vector& DstAngle) {

		Vector cDelta = { ParcismAngle.x - DstAngle.x, ParcismAngle.y - DstAngle.y, ParcismAngle.z - DstAngle.z };
		cDelta.Clamp();
		int iSmoothFactor = SmoothFactor * 3;
		if (vars::aim_smooth > 0) {
			DstAngle.x = ParcismAngle.x - cDelta.x / iSmoothFactor;
			DstAngle.y = ParcismAngle.y - cDelta.y / iSmoothFactor;
		}
		else if (iSmoothFactor == 0) {
			DstAngle.x = ParcismAngle.x - cDelta.x;
			DstAngle.y = ParcismAngle.y - cDelta.y;
		}

	}


	Vector CalcAngle2(Vector& src, Vector& dst, Vector& angles, C_BaseEntity* pLocal, C_BaseCombatWeapon* pWep) {
		Vector delta;
		delta.x = (src.x - dst.x);
		delta.y = (src.y - dst.y);
		delta.z = (src.z - dst.z);

		double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);

		if (vars::legit_wpns) {
			if (pWep->isRifle()) {
				rcsE = rifle_e;
				rcsS = rifle_s;
				rcsR = rifle_r;
				gringox = rifle_float_x;
				gringoy = rifle_float_y;
			}
			if (pWep->isPistol()) {
				rcsE = pistol_e;
				rcsS = pistol_s;
				rcsR = pistol_r;
				gringox = pistol_float_x;
				gringoy = pistol_float_y;
			}
			if (pWep->isSniper()) {
				rcsE = sniper_e;
				rcsS = sniper_s;
				rcsR = sniper_r;
				gringox = sniper_float_x;
				gringoy = sniper_float_y;
			}
			if (pWep->isSMG()) {
				rcsE = smg_e;
				rcsS = smg_s;
				rcsR = smg_r;
				gringox = smg_float_x;
				gringoy = smg_float_y;
			}
			if (pWep->isHeavy()) {
				rcsE = heavy_e;
				rcsS = heavy_s;
				rcsR = heavy_r;
				gringox = heavy_float_x;
				gringoy = heavy_float_y;
			}
		}
		else {
			rcsE = vars::rcs_enabled;
			rcsS = vars::rcs_standalone;
			rcsR = vars::rcs_randomize;
			gringox = vars::rcs_float_x;
			gringoy = vars::rcs_float_y;
		}
		
		


		if (rcsE) {
			if (rcsS && pLocal->shotsfired() > 2) {
				if (rcsR) {
					srand(NULL);
					float addRand;
					addRand = (rand() % 51) - 25;
					angles.x = (float)(atanf(delta.z / hyp) * M_RADPI - pLocal->GetPunch().x * (gringox + addRand) / 50);
					angles.y = (float)(atanf(delta.y / delta.x) * M_RADPI - pLocal->GetPunch().y * (gringoy + addRand) / 50);
				}
				else {
					angles.x = (float)(atanf(delta.z / hyp) * M_RADPI - pLocal->GetPunch().x * gringox / 50);
					angles.y = (float)(atanf(delta.y / delta.x) * M_RADPI - pLocal->GetPunch().y * gringoy / 50);
				}
			}
			else {
				if (rcsR) {
					srand(NULL);
					float addRand;
					addRand = (rand() % 51) - 25;
					angles.x = (float)(atanf(delta.z / hyp) * M_RADPI - pLocal->GetPunch().x * (gringox + addRand) / 50);
					angles.y = (float)(atanf(delta.y / delta.x) * M_RADPI - pLocal->GetPunch().y * (gringoy + addRand) / 50);
				}
				else {
					angles.x = (float)(atanf(delta.z / hyp) * M_RADPI - pLocal->GetPunch().x * gringox / 50);
					angles.y = (float)(atanf(delta.y / delta.x) * M_RADPI - pLocal->GetPunch().y * gringoy / 50);
				}
			}
			
		}
		else {
			angles.x = (float)(atanf(delta.z / hyp) * M_RADPI);
			angles.y = (float)(atanf(delta.y / delta.x) * M_RADPI);
		}
		angles.z = 0.0f;
		if (delta.x >= 0.0) { angles.y += 180.0f; }
		return angles;
	}


	Vector CalcAngle(Vector& src, Vector& dst, Vector& angles, C_BaseEntity* pLocal) {
		Vector delta;
		delta.x = (src.x - dst.x);
		delta.y = (src.y - dst.y);
		delta.z = (src.z - dst.z);

		double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
		angles.x = (float)(atanf(delta.z / hyp) * M_RADPI);
		angles.y = (float)(atanf(delta.y / delta.x) * M_RADPI);

		angles.z = 0.0f;
		if (delta.x >= 0.0) { angles.y += 180.0f; }
		return angles;
	}

	void AngleVectors(const Vector &angles, Vector *forward, Vector *right, Vector *up)
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos(DEG2RAD(angles[1]), &sy, &cy);
		SinCos(DEG2RAD(angles[0]), &sp, &cp);
		SinCos(DEG2RAD(angles[2]), &sr, &cr);

		if (forward)
		{
			forward->x = cp*cy;
			forward->y = cp*sy;
			forward->z = -sp;
		}

		if (right)
		{
			right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
			right->y = (-1 * sr*sp*sy + -1 * cr*cy);
			right->z = -1 * sr*cp;
		}

		if (up)
		{
			up->x = (cr*sp*cy + -sr*-sy);
			up->y = (cr*sp*sy + -sr*cy);
			up->z = cr*cp;
		}
	}

	void NiggerVectors(const Vector angles, Vector& forward)
	{
		float sp, sy, cp, cy;
		SinCos(DEG2RAD(angles[1]), &sy, &cy);
		SinCos(DEG2RAD(angles[0]), &sp, &cp);

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}

	void AngleVectors(const Vector &angles, Vector *forward)
	{
		float    sp, sy, cp, cy;

		sy = sin(DEG2RAD(angles[1]));
		cy = cos(DEG2RAD(angles[1]));
		sp = sin(DEG2RAD(angles[0]));
		cp = cos(DEG2RAD(angles[0]));


		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	void VectorAngles(const Vector &angles, Vector *forward) {
		Assert(s_bMathlibInitialized);
		Assert(forward);

		float	sp, sy, cp, cy;

		sy = sin(DEG2RAD(angles[1]));
		cy = cos(DEG2RAD(angles[1]));

		sp = sin(DEG2RAD(angles[0]));
		cp = cos(DEG2RAD(angles[0]));

		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	void NormalizeCAngle(Vector &vIn, Vector &vOut) {
		float flLen = vIn.Length();
		if (flLen == 0) {
			vOut.Init(0, 0, 1);
			return;
		}
		flLen = 1 / flLen;
		vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
	}

	void VectorTransform(const Vector in1, float in2[3][4], Vector &out)
	{
		out[0] = DotProduct(in1, Vector(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3];
		out[1] = DotProduct(in1, Vector(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3];
		out[2] = DotProduct(in1, Vector(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3];
	}
}

namespace A {
	float GetFOV(Vector CmdViewAngle, Vector LocalEyePos, Vector Destination, C_BaseEntity* pLocal) {
		Vector ang, aim;
		C::CalcAngle(LocalEyePos, Destination, ang, pLocal);
		C::VectorAngles(CmdViewAngle, &aim);
		C::VectorAngles(ang, &ang);

		float mag_s = std::sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
		float mag_d = mag_s;
		float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];
		float fov = std::acos(u_dot_v / (mag_s * mag_d)) * (180.f / M_PI_F);
		fov *= 1.4;
		return fov;
	}
	void MakeVector(const Vector& vIn, Vector& vOut)
	{
		float pitch = DEG2RAD(vIn.x);
		float yaw = DEG2RAD(vIn.y);
		float temp = cos(pitch);

		vOut.x = -temp * -cos(yaw);
		vOut.y = sin(yaw) * temp;
		vOut.z = -sin(pitch);
	}

	float GetFOV2(Vector& viewangles, Vector& vSrc, Vector& vEnd, C_BaseEntity* pLocal)
	{
		Vector vAng, vAim;

		C::CalcAngle(vSrc, vEnd, vAng, pLocal);
		MakeVector(viewangles, vAim);
		MakeVector(vAng, vAng);

		return RAD2DEG(acos(vAim.Dot(vAng)) / vAim.LengthSqr());
	}

}