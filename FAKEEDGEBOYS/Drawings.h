POINT Cur;
int iSmoothFactor;
int iSmoothFactory;
bool SlideCFG = false;
bool doEins = false;
int menut = 0;
class kAZORDrawings {
public:
	void DrawBox(int x, int y, int w, int h, Color col);
	void DrawOutlinedBox(int x, int y, int w, int h, Color box, Color outline);
	void DrawOutlinedCircle(int x, int y, int radius, Color outline);
	void FillRGBA(int x, int y, int w, int h, Color col);
	void DrawGradient(int x, int y, int w, int h, Color col);
	void DrawLine(int x, int y, int xx, int yy, Color col);
	void DrawMenu(int& x, int& y, int w, int h);
	void DrawTab(int x, int y, const char* pszString, int iCount, int& iTab);
	void DrawString(int x, int y, Color clr, unsigned long font, const char *pszText);
	void Draw_wChar(int x, int y, Color clr, unsigned long font, const wchar_t *pszText);
	void DrawHealthbarVertical(int x, int y, int w, int h, Color color, int health, int tr);
	void DrawButton(int x, int y, const char* pszString, int iCount, bool& toggled);
	void addTickSlider(int x, int y, const char* pszString, int iCount, int max, int min, int& value);
	void SetKey(int x, int y, const char* pszString, int iCount, bool& isToggled, int& keyCode);
	void DrawSlider(int x, int y, int w, int min, int max, int& value, const char* pszString, int iCount, Color col);
	void DrawSliderFloat(int x, int y, int w, float min, float max, float& value, const char* pszString, int iCount, Color col);
	void DrawDropdown(int x, int y, int w, int h, int max, int& iColumn, const char* pString, const char* pszString[], int iCount, bool& isOpend);
	void drawBigButton(int x, int y, int w, int h, const char* pszString, int iCount, bool& var);
	void DoParalellogram(int x, int y, int w, int h, Color col);
	void DrawArrow(int x, int y);
	void CreateTab(const char* pTitle, int x, int y, int w, int h, bool bDrawOutline = false, Color pColor = Color(50, 50, 50, 255), const char* pTooltip = 0);
	Color Rainbow();
	void PopUpMessage(const char* Line1, const char* Line2, const char* Line3, Color col);
	void grabMouse(int x, int y);
	RECT GetViewport();
	void SpectatorList(int& x, int& y);
	int TweakColor(int c1, int c2, int variation);
	void tintAreaDegrade(int x, int y, int w, int h, int r1, int g1, int b1, int a1, int r2, int g2, int b2, int a2, int variation);
	void DrawPlayerList(int x, int y, int w, int h);
	void DrawPlayerButton(int x, int y, int w, int h, const char* pszName, Color color);
	void DrawStringiCount(int x, int y, const char* pszString, int iCount);
	void TextW(bool cent, int font, int x, int y, Color color, wchar_t *pszString);
	void DrawStringMiddle(unsigned long FONT, bool bCenter, int x, int y, Color c, const char *fmt);
	void DrawLabelBox(int x, int y, int w, int boxWidth, int h, const char* pszString, Color col, int iCount);
	void DrawShineMark(int x, int y);
	void DrawSmallHealthbar(int x, int y, int w, int h, int Health);
	void DrawPlayerListInt(int& x, int& y, int w, int h);
	void SwitchPlayerCount(int x, int y, int w, int h, int& playerCount, int iCount, const char* pszString);
};
int rifle_aamode = 0;
int rifle_bone = 0;
bool rifle_aactive = false;
int rifle_float_x = 0;
int rifle_float_y = 0;
int rifle_curvevalue = 0;
int rifle_fov = 0.0f;
bool rifle_team = false;
int rifle_aimkey = 0;
bool rifle_active = false;
int rifle_smoothx = 0;
int rifle_smoothy = 0;
bool rifle_psilent = false;
bool rifle_curve = false;
int rifle_aimtime = 0;

int pistol_aamode = 0;
int pistol_bone = 0;
bool pistol_aactive = false;
int pistol_float_x = 0;
int pistol_float_y = 0;
int pistol_curvevalue = 0;
int pistol_fov = 0.0f;
bool pistol_team = false;
int pistol_aimkey = 0;
bool pistol_active = false;
int pistol_smoothx = 0;
int pistol_smoothy = 0;
bool pistol_psilent = false;
bool pistol_curve = false;
int pistol_aimtime = 0;

int sniper_aamode = 0;
int sniper_bone = 0;
bool sniper_aactive = false;
int sniper_float_x = 0;
int sniper_float_y = 0;
int sniper_curvevalue = 0;
int sniper_fov = 0.0f;
bool sniper_team = false;
int sniper_aimkey = 0;
bool sniper_active = false;
int sniper_smoothx = 0;
int sniper_smoothy = 0;
bool sniper_psilent = false;
bool sniper_curve = false;
int sniper_aimtime = 0;

int smg_aamode = 0;
int smg_bone = 0;
bool smg_aactive = false;
int smg_float_x = 0;
int smg_float_y = 0;
int smg_curvevalue = 0;
int smg_fov = 0.0f;
bool smg_team = false;
int smg_aimkey = 0;
bool smg_active = false;
int smg_smoothx = 0;
int smg_smoothy = 0;
bool smg_psilent = false;
bool smg_curve = false;
int smg_aimtime = 0;

int heavy_aamode = 0;
int heavy_bone = 0;
bool heavy_aactive = false;
int heavy_float_x = 0;
int heavy_float_y = 0;
int heavy_curvevalue = 0;
int heavy_fov = 0.0f;
bool heavy_team = false;
int heavy_aimkey = 0;
bool heavy_active = false;
int heavy_smoothx = 0;
int heavy_smoothy = 0;
bool heavy_psilent = false;
bool heavy_curve = false;
int heavy_aimtime = 0;

int rifled, riflec, riflekey;
bool rifleh, riflea;
int pistold, pistolc, pistolkey;
bool pistolh, pistola;
int smgd, smgc, smgkey;
bool smgh, smga;
int heavyd, heavyc, heavykey;
bool heavyh, heavya;
int sniperd, sniperc, sniperkey;
bool sniperh, snipera;

bool rifle_e, pistol_e, sniper_e, smg_e, heavy_e;
bool rifle_r, pistol_r, sniper_r, smg_r, heavy_r;
bool rifle_s, pistol_s, sniper_s, smg_s, heavy_s;

#define CenterX GetSystemMetrics(SM_CXSCREEN) / 2
#define CenterY GetSystemMetrics(SM_CYSCREEN) / 2
#define ScreenH GetSystemMetrics(SM_CYSCREEN)
#define ScreenW GetSystemMetrics(SM_CXSCREEN)

namespace Settings {
	int StartX = 125;
	int StartY = 120;

	int radarsize = 140;
	int RadarX = 85;
	int RadarY = 85;

	int SpecX = 20;
	int SpecY = 20;

	int PlayerX = 40;
	int PlayerY = 40;

	int WeaponX = 820;
	int WeaponY = 200;

	int iTab = 0;
	int keyCode = 0;
	bool menuOpened = false;
	bool setkeyStatement = false;
}



namespace vars {
	bool legit_usesmooth = false;
	int randmizeXd = 0;
	bool legit_active = false;
	bool debug = false;
	bool ragdoll = false;
	bool legit_psilent = false;
	int misc_edge = 0;
	bool rage_active = false;
	bool rage_autoshoot = false;
	bool rage_nospread = false;
	bool aa_fake = false;
	bool rage_awpbody = false;
	bool rage_psilent = false;
	int MenuDrop = 0;
	int legit_fov = false;
	int radarscale = 10;
	bool legit_wpns = false;
	bool asuswalls = false;
	bool esp_dlight = false;
	bool doorspam = false;
	bool autorest = false;
	bool accuracyboost = false;
	int hsMode = 0;
	int minvel = 0;
	bool headfix = false;
	bool autoaccept = false;
	bool visonly = false;
	bool legit_trigg = false;
	bool autoss = false;
	bool rage_hitscan = false;

	int	menur = 195;
	int	menug = 144;
	int	menub = 212;
	/*Color(vars::menur, vars::menug,vars::menub, 255));*/


	bool rage_enginepred = false;
	bool rage_autoscope = false;
	bool aim_playerlist_ignore = false;
	bool rage_autopistol = false; 
	bool rage_hitchance = false;
	bool legit_head = false;
	int flagMode = 0;
	bool velocitybar = false;
	bool rage_step = false;
	int velorpedvalue = 0;
	bool chams_enemies = false;
	bool espworld = false;
	bool legit_team = false;
	bool trigvis = true;
	int triggerkey = 0;
	float mindmg = 0;
	bool aim_curve = false;
	int spamKey = 0;
	int aim_curvevalue = 0.0f;
	bool legit_smart = false;
	bool rage_team = false;
	int hands_transparency = 100;
	int weapons_transparency = 100;
	bool velocitypred = true;
	bool rcs_enabled = false;
	bool rcs_randomize = false;
	bool rcs_standalone = false;
	int removeTrns = 0;
	bool rage_recoil = false;
	int resolvemyass = 0;
	int pred_tick = 25;
	int aimkey = 0;
	bool inair = false;
	bool rage_smart = false;
	bool rage_awall = false;
	bool legit_autopistol = false;
	bool aa_at_target = false;
	bool rage_autostop = false;
	int aim_awall_min_dmg = 0;
	int rcs_float_x = 0;
	int rcs_float_y = 0;
	int aim_hitscan_mode = 0;
	int aim_hitchanceF = 0;
	int aim_boner = 6;
	int aim_boner1 = 0;
	int aim_plist_hscan = 0;
	int tpkey = 0;
	int aim_bone = 6;
	bool radar = false;
	int aim_bone1 = 0;
	bool rage_autocrouch = false;
	bool dynamicaa = false;
	bool aim_recoil = false;
	int aim_player = 0;
	int aim_smooth = 5;
	int aim_time = 0;
	bool silenttrig = false;
	int aim_fov = 4.f;
	int aim_awall_factor = 20.f;
	int aim_speed = 180.f;

	int trigg_cooldown = 0;
	int trigg_delay = 0;
	int trigg_burst = 0;

	int chamselect = 0;
	bool misc_chatspam = false;
	bool misc_namechange = false;
	bool misc_speedhack = false;
	bool misc_novisrecoil = false;
	bool misc_bhop = false;
	bool misc_fakewalk = false;
	int misc_fakewalkkey = 0;
	bool misc_wd = false;
	bool misc_airstuck = false;
	bool chams_flat = false;
	int aim_mode = 0;
	int currentconfig = 0;
	bool esp_nosky = false;
	bool misc_ragespecvision = false;
	int misc_knife = 0;
	bool misc_teleport = false;
	bool misc_correctaa = false;
	bool misc_thirdperson = false;
	bool misc_autostrafe = false;
	int misc_clantag = 0;
	bool noflash = false;
	int crosshairsize = 0;
	bool misc_zang = false;
	int ct_transparency = 100;
	int t_transparency = 100;
	int wpn_chams = 0;
	bool misc_antiaim_client = false;
	bool misc_circle_strafe = false;
	bool misc_antiuntrust = true;
	bool misc_svcheats = false;
	bool knifechange = false;
	bool glovechange = false;
	int misc_fovchange = 0;
	bool misc_cstrafe = false;
	bool radiospam = false;
	bool misc_duck = false;
	bool misc_unfixedAA = false;
	bool misc_antiaim = true;
	bool bullettrace = false;
	int misc_knifechanger = 0;
	int misc_skinchanger = 0;
	int misc_glovechanger = 0;
	bool misc_hitmark = false;
	bool misc_killnotification = false;
	bool misc_roundsay = false;
	bool misc_playerlist = false;
	int misc_airstuckey = 0;
	int misc_spinfactor = 40;
	int misc_chatspamtype = 0;
	bool misc_watermarks = true;
	int misc_wd_left = 180;
	int misc_wd_right = 180;
	int misc_yaw = 0;
	int misc_pitch = 0;
	int misc_custom_y = 0;
	int misc_custom_x = 0;
	int misc_wd_r_trace = 5;
	int misc_wd_l_trace = 5;
	int misc_wd_left_trace = 1.0f;
	int misc_wd_right_trace = 1.0f;
	int misc_fakelag = 0;
	int misc_fovfactor = 0;
	int misc_vmfovfactor = 0;
	int misc_viewfov = 0;
	int misc_zval = 0;
	bool PlayerList[65] = { false };
	bool Friend[65] = { false };
	bool Resolve[65] = { false };
	bool Bodyaim[65] = { false };
	bool SkipESP[65] = { false };
	bool onkey = false;
	int espKey = 0;
	bool Feature2[65] = { false };
	bool Feature1[65] = { false };

	bool antires = false;

	bool esp_active = false;
	bool esp_crosshair = false;
	bool esp_box = false;
	bool esp_healthbar = false;
	bool esp_name = false;
	int esp_chsize = 7;
	int esp_hands = 0;
	int esp_weapons = 0;
	bool esp_chams = false;
	bool esp_xqz = false;
	bool esp_ignore = false;
	bool esp_chrome = false;
	bool esp_vischams = false;
	bool esp_skeleton = false;
	int esp_boxstyle = 1;
	bool moonwalk = false;
	int chams_t_transparency = 100.f;
	int chams_ct_transparency = 100.f;
	int esp_select = 0;

	int esp_ct_visible_r = 71;
	int esp_ct_visible_g = 181;
	int esp_ct_visible_b = 0;

	int esp_t_visible_r = 255;
	bool dynText = false;
	int esp_t_visible_g = 255;
	int esp_t_visible_b = 0;

	int esp_ct_r = 0;
	int esp_ct_g = 60;
	int esp_ct_b = 255;
	bool baranim = false;
	int aaMode = 0;

	bool gotv = false;

	int esp_t_r = 255;
	int esp_t_g = 0;
	int esp_t_b = 0;

	int chams_ct_visible_r = 0;
	int chams_ct_visible_g = 255;
	int chams_ct_visible_b = 0;
		
	int chams_t_visible_r = 255;
	int chams_t_visible_g = 255;
	int chams_t_visible_b = 0;
		
	int chams_ct_r = 0;
	int chams_ct_g = 0;
	int chams_ct_b = 255;
		
	int chams_t_r = 255;
	int chams_t_g = 0;
	int chams_t_b = 0;

	int handsr = 255;
	int handsg = 0;
	bool misc_time = false;
	int handsb = 157;

	int weaponR = 0;
	int weaponG = 229;
	int weaponB = 255;

	int config_select = 0;

	bool dropdown1 = false;
	bool dropdown2 = false;
	bool dropdown3 = false;
	bool dropdown4 = false;
	bool dropdown5 = false;
	bool dropdown6 = false;
	bool dropdown7 = false;
	bool dropdown8 = false;
	bool dropdown9 = false;
	bool dropdown10 = false;
	bool dropdown11 = false;
	bool dropdown12 = false;
	bool skinchanger = false;
	bool dropdown13 = false;
	bool dropdown14 = false;
	bool dropdown15 = false;
	bool dropdown16 = false;
	bool dropdown17 = false;
	bool dropdown18 = false;
	bool dropdown19 = false;
}

void kAZORDrawings::DrawHealthbarVertical(int x, int y, int w, int h, Color color, int health, int tr) {
	Color dwHealth;

	int dHealth = health;
	if (dHealth > 100)
		dHealth = 100;

	dwHealth = Color(255, 255, 255, tr); //white


	if (health > 100)
		dwHealth = Color(0, 0, 255, tr);
	if (dHealth <= 100 && dHealth > 60)
		dwHealth = Color(131, 250, 107, tr);

	if (dHealth <= 60 && dHealth > 40)
		dwHealth = Color(250, 240, 107, tr);
	if (dHealth <= 40 && dHealth > 20)
		dwHealth = Color(255, 128, 0, tr);
	if (dHealth <= 20 && dHealth > 0)
		dwHealth = Color(200, 2, 33, tr);

	//x -= floor(w + 6);
	this->FillRGBA(floor(x), floor(y), w, h, Color(0, 0, 0, tr));

	int hw = floor((((h - 2)* dHealth) / 100));
	this->FillRGBA(floor(x) + 1, floor(y + (h - hw)) - 1, w / 2, hw, dwHealth);
}

const char* ESPBoxStyles[4] = {
	"Normal",
	"Normal",
	"Thick",
	"Edged"
};

const char* fovez[4] = {
	"Off",
	"Off",
	"Arms",
	"Full"
};

const char* knifer[4] = {
	"Off",
	"Off",
	"Left",
	"Right"
};

const char* Chamz[4] = {
	"Off",
	"Off",
	"Visible",
	"Full"
};

const char* fakelage[4] = {
	"Factor",
	"Factor",
	"Dynamic",
	"Random"
};


const char* handz[5] = {
	"None",
	"None",
	"Invisible",
	"Wireframe",
	"Chams"
};

const char* weaponz[5] = {
	"None",
	"None",
	"Invisible",
	"Wireframe",
	"Chams"
	//"Matrix"
};

const char* ColorSelections[4] = {
	"ESP", // 0
	"ESP", // 1
	"Chams", // 2
	"Other", // 3
};

bool fovezzz = false;

unsigned long pFont, xFont, oBlock, espFont, labelFont, tabFont, weaponFont, memeFont, kekFont, kukFont;
bool Janela[8][2];
POINT ClickPosicao;

bool MenuMovement(int &x, int &y, int w, int h, int index) {
	//Credits: Code64/CodeRed
	for (int i = 0; i < 8; i++)
		if (Janela[i][0] && i != index)
			return false;

	POINT Cur;
	GetCursorPos(&Cur);

	if (GetAsyncKeyState(VK_LBUTTON) < 0)
	{
		if (Cur.x > x && Cur.x < x + w && Cur.y >(y - 3) && Cur.y < (y - 3) + h || Janela[index][0])
		{
			Janela[index][0] = true;

			if (!Janela[index][1])
			{
				ClickPosicao.x = Cur.x - x;
				ClickPosicao.y = Cur.y - y;
				Janela[index][1] = true;

			}
		}
		else
		{
			Janela[index][0] = false;
			Janela[index][1] = false;
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) == 0 && Janela[index][0])
	{
		Janela[index][0] = false;
		Janela[index][1] = false;
	}

	if (Janela[index][0])
	{
		x = Cur.x - ClickPosicao.x;
		y = Cur.y - ClickPosicao.y;
	}

	return true;

}

bool SpecList(int &x, int &y, int w, int h, int index) {
	//Credits: Code64/CodeRed
	for (int i = 0; i < 8; i++)
		if (Janela[i][0] && i != index)
			return false;

	POINT Cur;
	GetCursorPos(&Cur);

	if (GetAsyncKeyState(VK_LBUTTON) < 0)
	{
		if (Cur.x > x && Cur.x < x + w && Cur.y >(y - 3) && Cur.y < (y - 3) + h || Janela[index][0])
		{
			Janela[index][0] = true;

			if (!Janela[index][1])
			{
				ClickPosicao.x = Cur.x - x;
				ClickPosicao.y = Cur.y - y;
				Janela[index][1] = true;

			}
		}
		else
		{
			Janela[index][0] = false;
			Janela[index][1] = false;
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) == 0 && Janela[index][0])
	{
		Janela[index][0] = false;
		Janela[index][1] = false;
	}

	if (Janela[index][0])
	{
		x = Cur.x - ClickPosicao.x;
		y = Cur.y - ClickPosicao.y;
	}

	return true;

}

void kAZORDrawings::TextW(bool cent, int font, int x, int y, Color color, wchar_t *pszString)
{
	if (cent)
	{
		int wide, tall;
		pValve->pSurface->GetTextSize(font, pszString, wide, tall);
		x -= wide / 2;
		y -= tall / 2;
	}
	pValve->pSurface->DrawSetTextColor(color);
	pValve->pSurface->DrawSetTextFont(font);
	pValve->pSurface->DrawSetTextPos(x, y);
	pValve->pSurface->DrawPrintText(pszString, (int)wcslen(pszString), FONT_DRAW_DEFAULT);
}

// Draw a string that can be set in center pos. [const char]
void kAZORDrawings::DrawStringMiddle(unsigned long FONT, bool bCenter, int x, int y, Color c, const char *fmt)
{
	wchar_t *pszStringWide = reinterpret_cast< wchar_t* >(malloc((strlen(fmt) + 1) * sizeof(wchar_t)));

	mbstowcs(pszStringWide, fmt, (strlen(fmt) + 1) * sizeof(wchar_t));

	this->TextW(bCenter, FONT, x, y, c, pszStringWide);

	free(pszStringWide);
}

Color kAZORDrawings::Rainbow() {

		static float x = 0, y = 0;
		static float r = 0, g = 0, b = 0;

		if (y >= 0.0f && y < 255.0f) {
			r = 255.0f;
			g = 0.0f;
			b = x;
		}
		else if (y >= 255.0f && y < 510.0f) {
			r = 255.0f - x;
			g = 0.0f;
			b = 255.0f;
		}
		else if (y >= 510.0f && y < 765.0f) {
			r = 0.0f;
			g = x;
			b = 255.0f;
		}
		else if (y >= 765.0f && y < 1020.0f) {
			r = 0.0f;
			g = 255.0f;
			b = 255.0f - x;
		}
		else if (y >= 1020.0f && y < 1275.0f) {
			r = x;
			g = 255.0f;
			b = 0.0f;
		}
		else if (y >= 1275.0f && y < 1530.0f) {
			r = 255.0f;
			g = 255.0f - x;
			b = 0.0f;
		}

		x += 1.90f; //increase this value to switch colors faster
		if (x >= 255.0f)
			x = 0.0f;

		y += 1.90f; //increase this value to switch colors faster
		if (y > 1530.0f)
			y = 0.0f;


		return Color((int)r, (int)g, (int)b, 255);
}


int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

void kAZORDrawings::DrawString(int x, int y, Color clr, unsigned long font, const char* pszText) {
	if (pszText == NULL)
		return;
	wchar_t szString[1024] = { '\0' };
	wsprintfW(szString, L"%S", pszText);
	pValve->pSurface->DrawSetTextPos(x, y);
	pValve->pSurface->DrawSetTextFont(font);
	pValve->pSurface->DrawSetTextColor(clr);
	pValve->pSurface->DrawPrintText(szString, wcslen(szString));
}

void kAZORDrawings::Draw_wChar(int x, int y, Color clr, unsigned long font, const wchar_t* pszText) {
	if (pszText == NULL)
		return;
	
	pValve->pSurface->DrawSetTextPos(x, y);
	pValve->pSurface->DrawSetTextFont(font);
	pValve->pSurface->DrawSetTextColor(clr);
	pValve->pSurface->DrawPrintText(pszText, wcslen(pszText));
}



int CalcPos(int iXStart, int iYStart, int iXEnd, int iYEnd) {
	int iRealXStart = ((1920 / 2) - (1920 / 2)) + iXStart;
	return Cur.x - iRealXStart;
}



void kAZORDrawings::DrawStringiCount(int x, int y, const char* pszString, int iCount) {
	y += iCount * 20;
	this->DrawString(x, y, Color(255, 255, 255, 255), labelFont, pszString);
}

RECT kAZORDrawings::GetViewport() {
		RECT Viewport = { 0, 0, 0, 0 };
		int w, h;
		pValve->pEngine->GetScreenSize(w, h);
		Viewport.right = w; Viewport.bottom = h;
		return Viewport;
}

void kAZORDrawings::SpectatorList(int& x, int& y) {
	if (!vars::misc_ragespecvision)
		return;

	C_BaseEntity* pLocal = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
	

	int getRagers = 0;
	this->FillRGBA(x, y, 180, 20, Color(37, 37, 37, 255));
	this->DrawString(x + 40, y + 34, Color(255, 255, 255, 255), labelFont, "Spectator List");
	this->DrawBox(x, y, 180, 20, Color(0, 0, 0, 255));
	for (int i = 0; i < pValve->pEntList->GetHighestEntityIndex(); i++) {
	
		C_BaseEntity *pEntity = pValve->pEntList->GetClientEntity(i);
		player_info_t pinfo;
		pValve->pEngine->GetPlayerInfo(i, &pinfo);
		
		if (pEntity &&  pEntity != pLocal) {
			if (!pEntity->Health() > 0) {
				ULONG GetTargets = *(ULONG*)((DWORD)pEntity + offsets.m_iObserveTarget);
				ULONG obs = GetTargets;

				if (obs) {
					C_BaseEntity *pTarget = pValve->pEntList->GetClientEntityFromHandle(obs);
					player_info_t pinfo2;
					if (pTarget)
					{
						pValve->pEngine->GetPlayerInfo(pTarget->GetIndex(), &pinfo2);
						char buf[255]; sprintf_s(buf, "%s -> %s", pinfo.name, pinfo2.name);
						
							this->FillRGBA(x, y + 20 + (getRagers * 20), 180, 20, Color(24, 24, 24, 255));
							this->DrawString(x + 4, y + 25 + (getRagers * 20), pTarget->GetIndex() == pLocal->GetIndex() ? Color(255, 255, 255, 255) : Color(255, 0, 0, 255), labelFont, buf);
							getRagers++;
					}
				}
			}
		}
	}
	MenuMovement(x, y, 180, 20, 1);
}
void kAZORDrawings::PopUpMessage(const char* Line1, const char* Line2, const char*Line3, Color col) {
	static int trr = 133;
	static bool isAccepted = false;
	if (trr) {
		this->FillRGBA(-2, -2, 9999, 9999, Color(col.r(), col.g(), col.b(), trr));
		this->DrawString((ScreenWidth / 2) - 130, (ScreenHeight / 2) - 60, Color(255, 255, 255, 255), pFont, Line1);
		this->DrawString((ScreenWidth / 2) - 130, (ScreenHeight / 2) - 45, Color(255, 255, 255, 255), pFont, Line2);
		this->DrawString((ScreenWidth / 2) - 130, (ScreenHeight / 2) - 30, Color(255, 255, 255, 255), pFont, Line3);
	}

}
bool IsKeyToggled(int iKey)
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

void kAZORDrawings::DrawTab(int x, int y, const char* pszString, int iCount, int& iTab) {
	GetCursorPos(&Cur);
	y += iCount * 19; // 50
	static unsigned int Last = 0;
	int h = 12;
	int predictedWidth = 100;
	if ((Cur.x > x) && (Cur.x < x + predictedWidth) && (Cur.y > y - 5) && (Cur.y < y + h)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 1 && GetTickCount() - Last > 150) {
			iTab = iCount;
			Last = GetTickCount();
		}
	}
	if (iCount != iTab) {
		this->DrawString(x + 2, y - 2, Color(106, 105, 100, menut), oBlock, pszString);
	}
	else {
		//this->FillRGBA(x, y - 3, predictedWidth - 3, h + 7, Color(vars::menur, vars::menug, vars::menub, 100));
		this->DrawString(x + 2, y - 2, Color(255, 255, 255, menut), oBlock, pszString);
	}
	//this->FillRGBA(x + 2, y, predictedWidth, h, Color(91, 91, 91, 255));
}

void kAZORDrawings::grabMouse(int x, int y) {

	FillRGBA(x + 1, y, 1, 17, Color(3, 6, 26, 255));
	for (int i = 0; i < 11; i++)
	FillRGBA(x + 2 + i, y + 1 + i, 1, 1, Color(3, 6, 26, 255));
	FillRGBA(x + 8, y + 12, 5, 1, Color(3, 6, 26, 255));
	FillRGBA(x + 8, y + 13, 1, 1, Color(3, 6, 26, 255));
	FillRGBA(x + 9, y + 14, 1, 2, Color(3, 6, 26, 255));
	FillRGBA(x + 10, y + 16, 1, 2, Color(3, 6, 26, 255));
	FillRGBA(x + 8, y + 18, 2, 1, Color(3, 6, 26, 255));
	FillRGBA(x + 7, y + 16, 1, 2, Color(3, 6, 26, 255));
	FillRGBA(x + 6, y + 14, 1, 2, Color(3, 6, 26, 255));
	FillRGBA(x + 5, y + 13, 1, 1, Color(3, 6, 26, 255));
	FillRGBA(x + 4, y + 14, 1, 1, Color(3, 6, 26, 255));
	FillRGBA(x + 3, y + 15, 1, 1, Color(3, 6, 26, 255));
	FillRGBA(x + 2, y + 16, 1, 1, Color(3, 6, 26, 255));
	for (int i = 0; i < 4; i++)
		FillRGBA(x + 2 + i, y + 2 + i, 1, 14 - (i * 2), Color(255 - (i * 4), 255 - (i * 4), 255 - (i * 4), 255));
	FillRGBA(x + 6, y + 6, 1, 8, Color(235, 235, 235, 255));
	FillRGBA(x + 7, y + 7, 1, 9, Color(231, 231, 231, 255));
	for (int i = 0; i < 4; i++)
	FillRGBA(x + 8 + i, y + 8 + i, 1, 4 - i, Color(227 - (i * 4), 227 - (i * 4), 227 - (i * 4), 255));
	FillRGBA(x + 8, y + 14, 1, 4, Color(207, 207, 207, 255));
	FillRGBA(x + 9, y + 16, 1, 2, Color(203, 203, 203, 255));
}



void kAZORDrawings::DrawBox(int x, int y, int w, int h, Color col) {
	pValve->pSurface->DrawSetColor(col);
	pValve->pSurface->DrawOutlinedRect(x, y, x + w, y + h);
}

void kAZORDrawings::DrawOutlinedBox(int x, int y, int w, int h, Color box, Color outline) {
	this->DrawBox(x, y, w, h, box);
	this->DrawBox(x - 1, y - 1, w + 2, h + 2, outline);
	this->DrawBox(x + 1, y + 1, w - 2, h - 2, outline);
}

void kAZORDrawings::FillRGBA(int x, int y, int w, int h, Color col) {
	pValve->pSurface->DrawSetColor(col);
	pValve->pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void kAZORDrawings::DrawGradient(int x, int y, int w, int h, Color col) {

}

/*void kAZORDrawings::DrawLine(int x, int y, int xx, int yy, Color col) {
	pValve->pSurface->DrawSetColor(col);
	pValve->pSurface->DrawLine(x, y, xx, yy);
}
*/


void kAZORDrawings::DoParalellogram(int x, int y, int w, int h, Color col) {
	for (int i = 0; i < 5; i++) {
		for (int i = 0; i < h; i++) {
			this->FillRGBA(x + w, y, w, 1, col);
			x--;
			y++;
		}
	}
}

void kAZORDrawings::DrawSlider(int x, int y, int w, int min, int max, int& value, const char* pszString, int iCount, Color col) {
	y += iCount * 20;
	GetCursorPos(&Cur);
	static unsigned int LastTick = 0;
	if ((Cur.x > x) && Cur.x < (x + w) - 2 && (Cur.y > y) && (Cur.y < y + 8)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			value = CalcPos(x, y, w, 8) / ((float)w / (float)(max));
		}
	}
	if (Cur.x >= (x + w) - 2 && Cur.x < x + w && Cur.y > y && Cur.y < y + 8)
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			value = max;
		}
	this->FillRGBA(x + 1, y + 3, value * ((float)w / (float)(max)) - 2, 6, col);
	this->DrawBox(x, y + 2, w, 8, Color(37, 37, 37, menut));
	char downSyndrom[255];
	sprintf(downSyndrom, "%i", value);
	this->DrawString(x + 1 + value * ((float)w / (float)(max)), y + 2, Color(255, 255, 255, menut), labelFont, downSyndrom);
	this->DrawString(x + 3, y - 10, Color(255, 255, 255, menut), labelFont, pszString);
}

void kAZORDrawings::DrawSliderFloat(int x, int y, int w, float min, float max, float& value, const char* pszString, int iCount, Color col) {
	y += iCount * 20;
	GetCursorPos(&Cur);
	static unsigned int LastTick = 0;
	if ((Cur.x > x) && (Cur.x < x + w) && (Cur.y > y) && (Cur.y < y + 8)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			value = CalcPos(x, y, w, 8) / ((float)w / (float)(max));
		}
	}
	this->FillRGBA(x, y + 2, value * ((float)w / (float)(max)), 8, col);
	this->DrawBox(x, y + 2, w, 8, Color(37, 37, 37, menut));
	char downSyndrom[255];
	sprintf(downSyndrom, "%.0f", value);
	this->DrawString(x + 1 + value * ((float)w / (float)(max)), y + 2, Color(255, 255, 255, 255), labelFont, downSyndrom);
	this->DrawString(x + 3, y -10, Color(255, 255, 255, menut), labelFont, pszString);
}

bool kankerneger = false;
void kAZORDrawings::DrawOutlinedCircle(int x, int y, int radius, Color outline) {
	pValve->pSurface->DrawSetColor(outline);
	pValve->pSurface->DrawOutlinedCircle(x, y, radius, radius * 10);
}

void kAZORDrawings::DrawButton(int x, int y, const char* pszString, int iCount, bool& toggled) {
	y += iCount * 20;
	GetCursorPos(&Cur);
	int w = 13, h = 13;
	static unsigned int Last = 0;
	if ((Cur.x > x) && (Cur.x < x + w) && (Cur.y > y) && (Cur.y < y + h)) {
		if (IsKeyToggled(VK_LBUTTON) && GetTickCount() - Last > 150) {
			toggled = !toggled;
			Last = GetTickCount();
		}
	}
	if (toggled) {
		this->FillRGBA(x + 3, y + 3, 7, 7, Color(vars::menur, vars::menug,vars::menub, menut));
	}

	this->DrawBox(x, y, w, h, Color(14, 14, 14, menut));
	this->DrawBox(x + 1, y + 1, w - 2, h - 2, Color(37, 37, 37, menut));
	this->DrawBox(x + 2, y + 2, w - 4, h - 4, Color(14, 14, 14, menut));
	this->DrawString(x + w + 6, y, Color(255, 255, 255, menut), labelFont, pszString);
}
const char* c[1] = {
	"kanker"
};
const char* getMouse[6] = {
	"Key",
	"Mouse 1",
	"Mouse 2",
	"Mouse 3",
	"Mouse X1",
	"Mouse X2"
};

const char* velBar[4] = {
	"Off",
	"Off",
	"Matchmaking",
	"High Speed"

};

const char* Resolver[4] = {
	"Off",
	"Off",
	"Simple",
	"Advanced"

};

const char* XROFL[5] = {
	"Off",
	"Off",
	"Upper",
	"Lower",
	"Fade"

};

const char* CoolDropDon[3] = {
	"Static",
	"Static",
	"Smart",

};

void kAZORDrawings::DrawLabelBox(int x, int y, int w, int boxWidth, int h, const char* pszString, Color col, int iCount) {
	y += iCount * 20;
	this->DrawBox(x, y, boxWidth, h, Color(37, 37, 37, 255));
	this->FillRGBA(x + 4, y - 2, w, 4, col);
	this->DrawString(x + 8, y - 8, Color(255, 255, 255, 255), labelFont, pszString);
}
/*void kAZORDrawings::DrawButton(int x, int y, const char* pszString, int iCount, bool& toggled) {
	y += iCount * 20;
	GetCursorPos(&Cur);
	int w = 13, h = 13;
	static unsigned int Last = 0;
	if ((Cur.x > x) && (Cur.x < x + w) && (Cur.y > y) && (Cur.y < y + h)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && GetTickCount() - Last > 150) {
			toggled = !toggled;
			Last = GetTickCount();
		}
	}
	if (toggled) {
		this->FillRGBA(x, y, w, h, Color(vars::menur, vars::menug,vars::menub, 255));
	}

	this->DrawBox(x, y, w, h, Color(14, 14, 14, 255));
	this->DrawBox(x + 1, y + 1, w - 2, h - 2, Color(37, 37, 37, 255));
	this->DrawBox(x + 2, y + 2, w - 4, h - 4, Color(14, 14, 14, 255));
	this->DrawString(x + w + 6, y, Color(255, 255, 255, 255), labelFont, pszString);
}
*/

void kAZORDrawings::addTickSlider(int x, int y, const char* pszString, int iCount, int max, int min, int& value) {
	GetCursorPos(&Cur);
	int w = 14, h = 13;
	int x2 = x + 80;
	y += iCount * 20;
	static unsigned int last = 0;


	char intfactor[255];
	
	
	this->FillRGBA(x + 1, y + 1, w - 2, h - 2, Color(79, 79, 79, menut));
	this->FillRGBA(x + 1, y + 1, w - 2, (h - 2) / 2, Color(105, 105, 105, menut));
	this->DrawString(x + 3, y , Color(255, 255, 255, menut), labelFont, "<");
	this->FillRGBA(x2 + 1, y + 1, w - 2, h - 2, Color(79, 79, 79, menut));
	this->FillRGBA(x2 + 1, y + 1, w - 2, (h - 2) / 2, Color(105, 105, 105, menut));
	this->DrawString(x + 84, y , Color(255, 255, 255, menut), labelFont, ">");
	
	if ((Cur.x > x) && (Cur.x < x + w) && (Cur.y > y) && (Cur.y < y + h)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			this->DrawString(x + 3, y, Color(vars::menur, vars::menug, vars::menub, menut), labelFont, "<");
			if (GetTickCount() - last > 70) {
				value--;
				last = GetTickCount();
			}
			
		}
	}

	if ((Cur.x > x2) && (Cur.x < x2 + w) && (Cur.y > y) && (Cur.y < y + h)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000){
			this->DrawString(x + 84, y, Color(vars::menur, vars::menug, vars::menub, menut), labelFont, ">");
			if (GetTickCount() - last > 70) {
				value++;
				last = GetTickCount();
			}
		}
	}

	if (value > max)
		value = max;

	if (value < min)
		value = min;
	sprintf(intfactor, "%s: %i", pszString, value);
	this->DrawString(x + 20, y, Color(255, 255, 255, menut), labelFont, intfactor);
}


void kAZORDrawings::SetKey(int x, int y, const char* pszString, int iCount, bool& isToggled, int& keyCode) {
	y += iCount * 20;
	GetCursorPos(&Cur);
	int w = 80;
	int h = 20;
	static unsigned int Last = 0;
	if ((Cur.x > x) && (Cur.x < x + w) && (Cur.y > y) && (Cur.y < y + h)) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // left
			keyCode = 1;
			isToggled = false;
		}
		else
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) { // right
			keyCode = 2;
			isToggled = false;

		}
		else
		if (GetAsyncKeyState(VK_MBUTTON) & 0x8000) { // middle
			keyCode = 3;
			isToggled = false;

		}
		else
		if (GetAsyncKeyState(VK_XBUTTON1) & 0x8000) { // side button 1
			keyCode = 4;
			isToggled = false;

		}
		else
		if (GetAsyncKeyState(VK_XBUTTON2) & 0x8000) { // side button 2
			keyCode = 5;
			isToggled = false;

		}
	}
	this->FillRGBA(x, y, w, h, Color(23, 23, 23, 255));

		if ((Cur.x > x) && (Cur.x < x + w) && (Cur.y > y) && (Cur.y < y + h)) {
			this->FillRGBA(x + 15, y, 2, h, Color(215, 111, 0, 255));
		}
		else {
			this->FillRGBA(x + 15, y, 2, h, Color(62, 62, 62, 255));
		}
	this->DrawString(x + 2, y + 2, Color(255, 255, 255, 255), pFont, "K");
	if (!keyCode == 0) {
	this->DrawString(x + 20, y + 2, Color(255, 255, 255, 255), pFont, getMouse[keyCode]);
	}
	else {
	this->DrawString(x + 20, y + 2, Color(255, 255, 255, 255), pFont, "Key");
	}
	this->DrawBox(x, y, w, h, Color(91, 91, 91, 255));
}

void kAZORDrawings::DrawDropdown(int x, int y, int w, int h, int max, int& iColumn, const char* pString, const char* pszString[], int iCount, bool& isOpend) {
	y += iCount * 20;
	this->DrawString(x + w + 2, y, Color(255, 255, 255, menut), labelFont, pString);
	GetCursorPos(&Cur);
	static unsigned int LastTick = 0;
	if ((Cur.x > x) && (Cur.x < x + w) && (Cur.y > y) && (Cur.y < y + h)) {
		if (IsKeyToggled(VK_LBUTTON) && GetTickCount() - LastTick > 200) {
			isOpend = !isOpend;
			LastTick = GetTickCount();
		}
	}

	if (isOpend) {
		this->FillRGBA(x, y - 2, w, h, Color(80, 80, 80, menut));
		this->DrawBox(x, y - 2, w, h, Color(0, 0, 0, menut));
		this->DrawString(x + 3, y, Color(255, 255, 255, menut), pFont, pszString[iColumn]);
		for (int i = 1; i < max; i++) {
			int kY = (y - 2) + i * 16;
			this->FillRGBA(x, (y - 2) + i * 16, w, h, Color(80, 80, 80, menut));
			this->DrawBox(x, (y - 2) + i * 16, w, h, Color(0, 0, 0, menut));
			this->DrawString(x + 3, y + i * 16, Color(255, 255, 255, menut), pFont, pszString[i]);
				if ((Cur.x > x) && (Cur.x < x + w) && (Cur.y > kY) && (Cur.y < kY + h)) {
					if ((Cur.x > x) && (Cur.x < x + w) && (Cur.y > kY) && (Cur.y < kY + h)) {
						this->FillRGBA(x, (y - 2) + i * 16, w, h, Color(40, 40, 40, menut));
						this->DrawBox(x, (y - 2) + i * 16, w, h, Color(0, 0, 0, menut));
						this->DrawString(x + 3, y + i * 16, Color(255, 255, 255, menut), pFont, pszString[i]);
					}
					else {
						this->FillRGBA(x, y + i * 20, w, h, Color(80, 80, 80, menut));
					}
					if (IsKeyToggled(VK_LBUTTON) && GetTickCount() - LastTick > 150) {
						iColumn = i;
						isOpend = false;
					}
				}
			}
		}
	if (!isOpend) {
		this->FillRGBA(x, y - 2, w, h, Color(80, 80, 80, menut));
		this->DrawBox(x, y - 2, w, h, Color(0, 0, 0, menut));
		this->DrawString(x + 3, y, Color(255, 255, 255, menut), pFont, pszString[iColumn]);
	}
}


const char* YAW[7] = {
	"Off",
	"Off",
	"Backward",
	"Forward",
	"Sideways",
	"Jitter",
	"TuiSpin"
};
const char* yuh[4] = {
	"Off",
	"Off",
	"Text",
	"Icons"
};
const char* Modess[6] = {
	"Off",
	"Off",
	"Simple",
	"Smart",
	"Advanced",
};

const char* Clantag[6] = {
	"None",
	"None",
	"Newline",
	"Valve",
	"Admin",
	"Dynamic"
};

const char* EDGEZ[5] = {
	"Off",
	"Off",
	"Normal",
	"Dirty",
	"Fake"
};

const char* PITCH[5] = {
	"Off",
	"Off",
	"Emotion",
	"Headbang",
	"Jitter"
};

const char* Chatspams[6] = {
	"None",
	"None",
	"parallax",
	"AIMWARE",
	"Interwebz",
	"UnityHacks"
};


const char* Bones[6] = {
	"Head",
	"Head",
	"Neck",
	"Chest",
	"Stomach",
	"Dick"
};

const char* BonesLejit[6] = {
	"Head",
	"Head",
	"Neck",
	"Chest",
	"Stomach",
	"Dick"
};

const char* Configz[7] = {
	"Default",
	"Default",
	"Legit",
	"Rage",
	"HvH #1",
	"HvH #2",
	"Secret"
};

const char* Knives[12] = {
	"None",
	"None",
	"Bayonet",
	"Bowie",
	"Butterfly",
	"Falchion",
	"Flip",
	"Gut",
	"Huntsman",
	"Karambit",
	"M9 Bayonet",
	"Daggers"
};

const char* Weapons2[34] = {
	"None",
	"None",
	"Glock-18",
	"Dual Berettas",
	"P250",
	"Tec-9",
	"CZ75-Auto",
	"Desert Eagle",
	"R8 Revolver",
	"USP-S",
	"P2000",
	"Five-Seven",
	"Nova",
	"XM1014",
	"Sawed-Off",
	"M249",
	"MAG-7",
	"MAC-10",
	"MP7",
	"UMP-45",
	"P90",
	"PP-Bizon",
	"MP9",
	"Galil AR",
	"AK-47",
	"SSG 08",
	"SG 553",
	"AWP",
	"G3SG1",
	"FAMAS",
	"M4A4",
	"M4A1-S",
	"AUG",
	"SCAR-20"
};

const char* Gloves[8] = {
	"None",
	"None",
	"Hand Wraps",
	"Moto",
	"Specialist",
	"Sport",
	"Bloodhound",
	"Driver"
};

const char* recoils[4] = {
	"None",
	"None",
	"RCS",
	"NoRecoil"
};


const char* Weapons[6] = {
	"Rifle",
	"Rifle",
	"Pistol",
	"Sniper",
	"SMG",
	"Heavy"
};


int kAZORDrawings::TweakColor(int c1, int c2, int variation) { // cred: kidua & esoterik. given out to viking.
	if (c1 == c2) { return c1; }
	else if (c1<c2) { c1 += variation; }
	else { c1 -= variation; }
	return c1;
}

void kAZORDrawings::tintAreaDegrade(int x, int y, int w, int h, int r1, int g1, int b1, int a1, int r2, int g2, int b2, int a2, int variation) { // cred: kidua & esoterik. given out to viking.
	for (int i = 0; i < w; i++) {
		FillRGBA(x + i, y, 1, h, Color(r1, g1, b1, a1));
		r1 = TweakColor(r1, r2, variation);
		g1 = TweakColor(g1, g2, variation);
		b1 = TweakColor(b1, b2, variation);
		a1 = TweakColor(a1, a2, variation);
	}
}
bool bPlayerOnce = false;
void kAZORDrawings::DrawSmallHealthbar(int x, int y, int w, int h, int Health) {
	this->FillRGBA(x, y, w, h, Color(0, 0, 0, 180));
	UINT hw = (((w)* Health) / 100);
	this->FillRGBA(x, y, hw, h, Color(0, 255, 0, 255));
	this->DrawBox(x, y, w, h, Color(0, 0, 0, 255));
}

int* xList = new int[2000];
int iPlayerTab = 0;
void kAZORDrawings::DrawPlayerList(int x, int y, int w, int h) {
	C_BaseEntity* LOCAL = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
	
	int iTotalPlayers = 0;
	bool bFoundPlayer = false;
	if (pValve->pEngine->IsConnected() && pValve->pEngine->IsInGame()) {
		
	}
	else {
		this->DrawString(x,  y, Color(255, 255, 255, menut), pFont, "You are not ingame or on a server.");
		this->DrawString(x,  y + 20, Color(255, 255, 255, menut), pFont, "Please join a server or start a match!");
		//iTotalPlayers = 0;
	}
	for (int i = 1; i < pValve->pEntList->GetHighestEntityIndex(); i++) {
		C_BaseEntity* ENTITY = (C_BaseEntity*)pValve->pEntList->GetClientEntity(i);
		if (!bPlayerOnce) {
			vars::Friend[ENTITY->GetIndex()] = false;
			bPlayerOnce = true;
		}
		if (!ENTITY)
			continue;

		if (ENTITY->Team() == LOCAL->Team())
			continue;

		if (ENTITY == LOCAL)
			continue;

		if (!pValve->pEngine->IsInGame())
			continue;

		if (!pValve->pEngine->IsConnected())
			continue;

		if (ENTITY->Team() != 2 && ENTITY->Team() != 3)
			continue;

		player_info_t pInfo;
		pValve->pEngine->GetPlayerInfo(i, &pInfo);

	

		char playerCorrrect[255];
		sprintf(playerCorrrect, "%s", pInfo.name);

		char reeeeeee[255];
		sprintf(reeeeeee, "Options for %s", pInfo.name);

		int gY = y + 0 + (20 * iTotalPlayers);

		//this->DrawBox(x, gY, 80, 20, Color(255, 255, 255, 180));
		this->DrawString(x, y + 0 + (20 * iTotalPlayers), Color(255, 255, 255, menut), pFont, playerCorrrect);
		if ((Cur.x > x) && (Cur.x < x + 80) && (Cur.y > y + 0 + (20 * iTotalPlayers)) && (Cur.y < y + 20 + (20 * iTotalPlayers))) {
			if (GetAsyncKeyState(VK_LBUTTON) & 1) {
				iPlayerTab = ENTITY->GetIndex();
			}
		}

		if (iPlayerTab == ENTITY->GetIndex() && ENTITY->GetIndex() > 0) {

			this->DrawString(x + 140, y - 20, Color(255, 255, 255, menut), labelFont, reeeeeee);
			this->DrawString(x, y + (20 * iTotalPlayers), Color(150, 150, 150, menut), pFont, playerCorrrect);

			this->DrawButton(x + 140, y, "Friend Player", 0, vars::Friend[i]);				/* [X]Friend Player		[X]Resolve Player*/
			this->DrawButton(x + 280, y, "Force Bodyaim", 0, vars::Bodyaim[i]);			/* [X]Hide From ESP		[X]*/


			this->DrawButton(x + 140, y, "Hide From ESP", 1, vars::SkipESP[i]);



		}
		iTotalPlayers++;

	}
	
}

void kAZORDrawings::DrawPlayerButton(int x, int y, int w, int h, const char* pszName, Color color) {
	this->FillRGBA(x, y, w, h, color);
	this->DrawBox(x, y, w, h, Color(0, 0, 0, 255));
	this->DrawString(x + 3, y + 1, Color(255, 255, 255, 255), pFont, pszName);
}
int* PlayerListArray = new int[1000];
bool PlayerFriend[10000] = { false };
bool PlayerCorrect[10000] = { false };
void kAZORDrawings::DrawPlayerListInt(int& x, int& y, int w, int h) {
	
	
	GetCursorPos(&Cur);
	if (!vars::misc_playerlist)
		return;

	this->FillRGBA(x, y, w, h, Color(37, 37, 37, 255));
	this->DrawString(x + 4, y + 2, Color(255, 255, 255, 255), labelFont, "Player List");
	this->DrawBox(x, y, w, h, Color(0, 0, 0, 255));

	C_BaseEntity* gLocal = (C_BaseEntity*)pValve->pEntList->GetClientEntity(pValve->pEngine->GetLocalPlayer());
	for (int i = 1; i < pValve->pEntList->GetHighestEntityIndex(); i++) {
		C_BaseEntity* gEntity = (C_BaseEntity*)pValve->pEntList->GetClientEntity(i);
		
		if (!gEntity)
			continue;

		player_info_t pinfo;
		pValve->pEngine->GetPlayerInfo(gEntity->GetIndex(), &pinfo);
		
		if (pValve->pEngine->IsConnected() && pValve->pEngine->IsInGame()) {
			bool isFriend = PlayerFriend[gEntity->GetIndex()];
			this->FillRGBA(x, y + gEntity->GetIndex() * h, w, h, Color(24, 24, 24, menut));
			this->DrawString(x + 4, y + gEntity->GetIndex() * h + 2, isFriend ? Color(0, 255, 0, menut) : Color(255, 255, 255, menut), labelFont, pinfo.name);
			int gY = y + h * gEntity->GetIndex();
			if ((Cur.x > x) && (Cur.x < x + w) && (Cur.y > y + h) && (Cur.y < gY + h)) {
				if (GetAsyncKeyState(VK_LBUTTON) & 1) {
					// 0 = Me.
					iPlayerTab = gEntity->GetIndex();
				}
			}
			if (iPlayerTab == gEntity->GetIndex() && gEntity->GetIndex() > 0) {
				this->FillRGBA(x - w - 2, y, w, 120, Color(24, 24, 24, menut));
				this->FillRGBA(x - w - 2, y, w, 20, Color(37, 37, 37, menut));
				this->DrawBox(x - w - 2, y, w, 20, Color(0, 0, 0, menut));
				this->DrawString(x - w - 2 + 4, y + 2, Color(255, 255, 255, menut), labelFont, pinfo.name);
				this->DrawButton(x - w - 2 + 10, y + 30, "Friend", 0, PlayerFriend[gEntity->GetIndex()]);
				this->DrawButton(x - w - 2 + 10, y + 30, "Correct", 1, PlayerCorrect[gEntity->GetIndex()]);
			}

			
		}
		if (PlayerCorrect[gEntity->GetIndex()] == true) {
			Vector NulledArmed;
			*(float*)((DWORD)gEntity + offsets.m_iEyeAngles) = -89.f;
		}
	}
	MenuMovement(x, y, w, 20, 2);
}

void kAZORDrawings::SwitchPlayerCount(int x, int y, int w, int h, int & playerCount, int iCount, const char * pszString) {
	
}

int ikz = 0;
int kkz = 0;
int kko = 1;


BOOL WritePrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int nInteger, LPCTSTR lpFileName) {
	TCHAR lpString[1024];
	wsprintf(lpString, "%d", nInteger);
	return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}


bool jew = false;
void doSave() {
	const char * location = NULL;
	_wmkdir(L"C:\\parallax.int");
	std::string savePath = "C:\\parallax.int\\default.ini";
	std::string savePath2 = "C:\\parallax.int\\legit.ini";
	std::string savePath3 = "C:\\parallax.int\\rage.ini";
	std::string savePath4 = "C:\\parallax.int\\hvh1.ini";
	std::string savePath5 = "C:\\parallax.int\\hvh2.ini";
	std::string savePath6 = "C:\\parallax.int\\secret.ini";
	if (vars::config_select == 0 || vars::config_select == 1) {
		location = savePath.c_str();
	}
	else if (vars::config_select == 2) {
		location = savePath2.c_str();
	}
	else if (vars::config_select == 3) {
		location = savePath3.c_str();
	}
	else if (vars::config_select == 4) {
		location = savePath4.c_str();
	}
	else if (vars::config_select == 5) {
		location = savePath5.c_str();
	}
	else if (vars::config_select == 6) {
		location = savePath6.c_str();
	}


	WritePrivateProfileInt("legit", "var_w_configs", vars::legit_wpns, location);
	WritePrivateProfileInt("legit", "var_a_aimbot", vars::legit_active, location);
	WritePrivateProfileInt("legit", "var_a_aimkey", vars::aimkey, location);
	WritePrivateProfileInt("legit", "var_a_aimtime", vars::aim_time, location);
	WritePrivateProfileInt("legit", "var_a_psilent", vars::legit_psilent, location);
	WritePrivateProfileInt("legit", "var_a_bone", vars::aim_boner1, location);
	WritePrivateProfileInt("legit", "var_a_team", vars::legit_team, location);
	WritePrivateProfileInt("legit", "var_a_fov", vars::legit_fov, location);
	WritePrivateProfileInt("legit", "var_a_boost", vars::accuracyboost, location);
	WritePrivateProfileInt("legit", "var_a_smoothx", iSmoothFactor, location);
	WritePrivateProfileInt("legit", "var_a_smoothy", iSmoothFactory, location);
	WritePrivateProfileInt("legit", "var_r_enabled", vars::rcs_enabled, location);
	WritePrivateProfileInt("legit", "var_r_randomize", vars::rcs_randomize, location);
	WritePrivateProfileInt("legit", "var_r_delayed", vars::rcs_standalone, location);
	WritePrivateProfileInt("legit", "var_r_xscale", vars::rcs_float_x, location);
	WritePrivateProfileInt("legit", "var_r_yscale", vars::rcs_float_y, location);
	WritePrivateProfileInt("legit", "var_w_r_triggerbot", vars::legit_trigg, location);
	WritePrivateProfileInt("legit", "var_t_hsonly", vars::legit_head, location);
	WritePrivateProfileInt("legit", "var_t_triggerkey", vars::triggerkey, location);
	WritePrivateProfileInt("legit", "var_t_triggerdelay", vars::trigg_delay, location);
	WritePrivateProfileInt("legit", "var_t_triggercooldown", vars::trigg_cooldown, location);

	WritePrivateProfileInt("legit", "var_w_r_aimbot", rifle_active, location);
	WritePrivateProfileInt("legit", "var_w_r_aimkey", rifle_aimkey, location);
	WritePrivateProfileInt("legit", "var_w_r_aimtime", rifle_aimtime, location);
	WritePrivateProfileInt("legit", "var_w_r_bone", rifle_bone, location);
	WritePrivateProfileInt("legit", "var_w_r_team", rifle_team, location);
	WritePrivateProfileInt("legit", "var_w_r_smoothx", rifle_smoothx, location);
	WritePrivateProfileInt("legit", "var_w_r_smoothy", rifle_smoothy, location);
	WritePrivateProfileInt("legit", "var_w_r_curve", rifle_curve, location);
	WritePrivateProfileInt("legit", "var_w_r_curvevalue", rifle_curvevalue, location);
	WritePrivateProfileInt("legit", "var_w_r_psilent", rifle_psilent, location);
	WritePrivateProfileInt("legit", "var_w_r_fov", rifle_fov, location);
	WritePrivateProfileInt("legit", "var_w_r_enabled", rifle_e, location);
	WritePrivateProfileInt("legit", "var_w_r_randomize", rifle_r, location);
	WritePrivateProfileInt("legit", "var_w_r_delayed", rifle_s, location);
	WritePrivateProfileInt("legit", "var_w_r_rcsy", rifle_float_y, location);
	WritePrivateProfileInt("legit", "var_w_r_rcsx", rifle_float_x, location);
	WritePrivateProfileInt("legit", "var_w_r_triggerbot", riflea, location);
	WritePrivateProfileInt("legit", "var_w_r_hsonly", rifleh, location);
	WritePrivateProfileInt("legit", "var_w_r_triggerkey", riflekey, location);
	WritePrivateProfileInt("legit", "var_w_r_triggerdelay", rifled, location);
	WritePrivateProfileInt("legit", "var_w_r_triggercooldown", riflec, location);

	WritePrivateProfileInt("legit", "var_w_p_aimbot", pistol_active, location);
	WritePrivateProfileInt("legit", "var_w_p_aimkey", pistol_aimkey, location);
	WritePrivateProfileInt("legit", "var_w_p_aimtime", pistol_aimtime, location);
	WritePrivateProfileInt("legit", "var_w_p_bone", pistol_bone, location);
	WritePrivateProfileInt("legit", "var_w_p_team", pistol_team, location);
	WritePrivateProfileInt("legit", "var_w_p_smoothx", pistol_smoothx, location);
	WritePrivateProfileInt("legit", "var_w_p_smoothy", pistol_smoothy, location);
	WritePrivateProfileInt("legit", "var_w_p_curve", pistol_curve, location);
	WritePrivateProfileInt("legit", "var_w_p_curvevalue", pistol_curvevalue, location);
	WritePrivateProfileInt("legit", "var_w_p_psilent", pistol_psilent, location);
	WritePrivateProfileInt("legit", "var_w_p_fov", pistol_fov, location);
	WritePrivateProfileInt("legit", "var_w_p_enabled", pistol_e, location);
	WritePrivateProfileInt("legit", "var_w_p_randomize", pistol_r, location);
	WritePrivateProfileInt("legit", "var_w_p_delayed", pistol_s, location);
	WritePrivateProfileInt("legit", "var_w_p_rcsy", pistol_float_y, location);
	WritePrivateProfileInt("legit", "var_w_p_rcsx", pistol_float_x, location);
	WritePrivateProfileInt("legit", "var_w_p_triggerbot", pistola, location);
	WritePrivateProfileInt("legit", "var_w_p_hsonly", pistolh, location);
	WritePrivateProfileInt("legit", "var_w_p_triggerkey", pistolkey, location);
	WritePrivateProfileInt("legit", "var_w_p_triggerdelay", pistold, location);
	WritePrivateProfileInt("legit", "var_w_p_triggercooldown", pistolc, location);

	WritePrivateProfileInt("legit", "var_a_boostmode", vars::aaMode, location);
	WritePrivateProfileInt("legit", "var_r_a_boostmode", rifle_aamode, location);
	WritePrivateProfileInt("legit", "var_p_a_boostmode", pistol_aamode, location);
	WritePrivateProfileInt("legit", "var_s_a_boostmode", sniper_aamode, location);
	WritePrivateProfileInt("legit", "var_m_a_boostmode", smg_aamode, location);
	WritePrivateProfileInt("legit", "var_h_a_boostmode", heavy_aamode, location);


	WritePrivateProfileInt("legit", "var_w_s_aimbot", sniper_active, location);
	WritePrivateProfileInt("legit", "var_w_s_aimkey", sniper_aimkey, location);
	WritePrivateProfileInt("legit", "var_w_s_aimtime", sniper_aimtime, location);
	WritePrivateProfileInt("legit", "var_w_s_bone", sniper_bone, location);
	WritePrivateProfileInt("legit", "var_w_s_team", sniper_team, location);
	WritePrivateProfileInt("legit", "var_w_s_smoothx", sniper_smoothx, location);
	WritePrivateProfileInt("legit", "var_w_s_smoothy", sniper_smoothy, location);
	WritePrivateProfileInt("legit", "var_w_s_curve", sniper_curve, location);
	WritePrivateProfileInt("legit", "var_w_s_curvevalue", sniper_curvevalue, location);
	WritePrivateProfileInt("legit", "var_w_s_psilent", sniper_psilent, location);
	WritePrivateProfileInt("legit", "var_w_s_fov", sniper_fov, location);
	WritePrivateProfileInt("legit", "var_w_s_enabled", sniper_e, location);
	WritePrivateProfileInt("legit", "var_w_s_randomize", sniper_r, location);
	WritePrivateProfileInt("legit", "var_w_s_delayed", sniper_s, location);
	WritePrivateProfileInt("legit", "var_w_s_rcsy", sniper_float_y, location);
	WritePrivateProfileInt("legit", "var_w_s_rcsx", sniper_float_x, location);
	WritePrivateProfileInt("legit", "var_w_s_triggerbot", snipera, location);
	WritePrivateProfileInt("legit", "var_w_s_hsonly", sniperh, location);
	WritePrivateProfileInt("legit", "var_w_s_triggerkey", sniperkey, location);
	WritePrivateProfileInt("legit", "var_w_s_triggerdelay", sniperd, location);
	WritePrivateProfileInt("legit", "var_w_s_triggercooldown", sniperc, location);


	WritePrivateProfileInt("legit", "var_w_m_aimbot", smg_active, location);
	WritePrivateProfileInt("legit", "var_w_m_aimkey", smg_aimkey, location);
	WritePrivateProfileInt("legit", "var_w_m_aimtime", smg_aimtime, location);
	WritePrivateProfileInt("legit", "var_w_m_bone", smg_bone, location);
	WritePrivateProfileInt("legit", "var_w_m_team", smg_team, location);
	WritePrivateProfileInt("legit", "var_w_m_smoothx", smg_smoothy, location);
	WritePrivateProfileInt("legit", "var_w_m_smoothy", smg_smoothx, location);
	WritePrivateProfileInt("legit", "var_w_m_curve", smg_curve, location);
	WritePrivateProfileInt("legit", "var_w_m_curvevalue", smg_curvevalue, location);
	WritePrivateProfileInt("legit", "var_w_m_psilent", smg_psilent, location);
	WritePrivateProfileInt("legit", "var_w_m_fov", smg_fov, location);
	WritePrivateProfileInt("legit", "var_w_m_enabled", smg_e, location);
	WritePrivateProfileInt("legit", "var_w_m_randomize", smg_r, location);
	WritePrivateProfileInt("legit", "var_w_m_delayed", smg_s, location);
	WritePrivateProfileInt("legit", "var_w_m_rcsy", smg_float_y, location);
	WritePrivateProfileInt("legit", "var_w_m_rcsx", smg_float_x, location);
	WritePrivateProfileInt("legit", "var_w_m_triggerbot", smga, location);
	WritePrivateProfileInt("legit", "var_w_m_hsonly", smgh, location);
	WritePrivateProfileInt("legit", "var_w_m_triggerkey", smgkey, location);
	WritePrivateProfileInt("legit", "var_w_m_triggerdelay", smgd, location);
	WritePrivateProfileInt("legit", "var_w_m_triggercooldown", smgc, location);

	WritePrivateProfileInt("legit", "var_w_h_aimbot", heavy_active, location);
	WritePrivateProfileInt("legit", "var_w_h_aimkey", heavy_aimkey, location);
	WritePrivateProfileInt("legit", "var_w_h_aimtime", heavy_aimtime, location);
	WritePrivateProfileInt("legit", "var_w_h_bone", heavy_bone, location);
	WritePrivateProfileInt("legit", "var_w_h_team", heavy_team, location);
	WritePrivateProfileInt("legit", "var_w_h_smoothx", heavy_smoothx, location);
	WritePrivateProfileInt("legit", "var_w_h_smoothy", heavy_smoothy, location);
	WritePrivateProfileInt("legit", "var_w_h_curve", heavy_curve, location);
	WritePrivateProfileInt("legit", "var_w_h_curvevalue", heavy_curvevalue, location);
	WritePrivateProfileInt("legit", "var_w_h_psilent", heavy_psilent, location);
	WritePrivateProfileInt("legit", "var_w_h_fov", heavy_fov, location);
	WritePrivateProfileInt("legit", "var_w_h_rcsy", heavy_float_y, location);
	WritePrivateProfileInt("legit", "var_w_h_rcsx", heavy_float_x, location);
	WritePrivateProfileInt("legit", "var_w_h_triggerbot", heavya, location);
	WritePrivateProfileInt("legit", "var_w_h_hsonly", heavyh, location);
	WritePrivateProfileInt("legit", "var_w_h_triggerkey", heavykey, location);
	WritePrivateProfileInt("legit", "var_w_h_triggerdelay", heavyd, location);
	WritePrivateProfileInt("legit", "var_w_h_triggercooldown", heavyc, location);



	WritePrivateProfileInt("legit", "var_w_r_boost", rifle_aactive, location);
	WritePrivateProfileInt("legit", "var_w_p_boost", pistol_aactive, location);
	WritePrivateProfileInt("legit", "var_w_s_boost", sniper_aactive, location);
	WritePrivateProfileInt("legit", "var_w_m_boost", smg_aactive, location);
	WritePrivateProfileInt("legit", "var_w_h_boost", heavy_aactive, location);



	WritePrivateProfileInt("rage", "var_a_enabled", vars::rage_active, location);
	WritePrivateProfileInt("rage", "var_a_recoil", vars::aim_recoil, location);
	WritePrivateProfileInt("rage", "var_a_resolver", vars::resolvemyass, location);
	WritePrivateProfileInt("rage", "var_a_psilent", vars::rage_psilent, location);
	WritePrivateProfileInt("rage", "var_a_awpbody", vars::rage_awpbody, location);
	WritePrivateProfileInt("rage", "var_a_aimstep", vars::rage_step, location);
	WritePrivateProfileInt("rage", "var_a_smartaim", vars::rage_smart, location);
	WritePrivateProfileInt("rage", "var_a_enginepred", vars::rage_enginepred, location);
	WritePrivateProfileInt("rage", "var_a_team", vars::rage_team, location);
	WritePrivateProfileInt("rage", "var_a_bone", vars::aim_bone1, location);
	WritePrivateProfileInt("rage", "var_a_autopistol", vars::rage_autopistol, location);
	WritePrivateProfileInt("rage", "var_a_autoscope", vars::rage_autoscope, location);
	WritePrivateProfileInt("rage", "var_a_autoduck", vars::rage_autocrouch, location);
	WritePrivateProfileInt("rage", "var_a_autostop", vars::rage_autostop, location);
	WritePrivateProfileInt("rage", "var_a_autoshoot", vars::rage_autoshoot, location);
	WritePrivateProfileInt("rage", "var_a_autorest", vars::autorest, location);
	WritePrivateProfileInt("rage", "var_a_autowall", vars::rage_awall, location);
	WritePrivateProfileInt("rage", "var_a_nospread", vars::rage_nospread, location);
	//WritePrivateProfileInt("rage", "var_a_hitscan", vars::rage_hitscan, location);
	WritePrivateProfileInt("rage", "var_a_hitscanmode", vars::hsMode, location);
	WritePrivateProfileInt("rage", "var_a_awallfactor", vars::aim_awall_factor, location);
	WritePrivateProfileInt("rage", "var_a_fov", vars::aim_fov, location);
	WritePrivateProfileInt("rage", "var_a_speed", vars::aim_speed, location);
	WritePrivateProfileInt("rage", "var_a_hitchance", vars::aim_hitchanceF, location);

	WritePrivateProfileInt("visuals", "var_v_enabled", vars::esp_active, location);
	WritePrivateProfileInt("visuals", "var_v_menuanim", vars::MenuDrop, location);
	WritePrivateProfileInt("visuals", "var_v_baranim", vars::baranim, location);
	WritePrivateProfileInt("visuals", "var_v_titleanim", vars::dynText, location);
	WritePrivateProfileInt("visuals", "var_v_box", vars::esp_box, location);
	WritePrivateProfileInt("visuals", "var_v_boxstyle", vars::esp_boxstyle, location);
	WritePrivateProfileInt("visuals", "var_v_name", vars::esp_name, location);
	WritePrivateProfileInt("visuals", "var_v_health", vars::esp_healthbar, location);
	WritePrivateProfileInt("visuals", "var_v_weapons", vars::esp_weapons, location);
	WritePrivateProfileInt("visuals", "var_v_skeleton", vars::esp_skeleton, location);
	WritePrivateProfileInt("visuals", "var_v_chams", vars::chamselect, location);
	WritePrivateProfileInt("visuals", "var_v_hands", vars::esp_hands, location);
	WritePrivateProfileInt("visuals", "var_v_cweapons", vars::wpn_chams, location);
	WritePrivateProfileInt("visuals", "var_v_ct_r", vars::esp_ct_r, location);
	WritePrivateProfileInt("visuals", "var_v_ct_g", vars::esp_ct_g, location);
	WritePrivateProfileInt("visuals", "var_v_ct_b", vars::esp_ct_b, location);
	WritePrivateProfileInt("visuals", "var_v_t_r", vars::esp_t_r, location);
	WritePrivateProfileInt("visuals", "var_v_t_g", vars::esp_t_g, location);
	WritePrivateProfileInt("visuals", "var_v_t_b", vars::esp_t_b, location);
	WritePrivateProfileInt("visuals", "var_v_ct_visible_r", vars::esp_ct_visible_r, location);
	WritePrivateProfileInt("visuals", "var_v_ct_visible_g", vars::esp_ct_visible_g, location);
	WritePrivateProfileInt("visuals", "var_v_ct_visible_b", vars::esp_ct_visible_b, location);
	WritePrivateProfileInt("visuals", "var_v_t_visible_r", vars::esp_t_visible_r, location);
	WritePrivateProfileInt("visuals", "var_v_t_visible_g", vars::esp_t_visible_g, location);
	WritePrivateProfileInt("visuals", "var_v_t_visible_b", vars::esp_t_visible_b, location);
	WritePrivateProfileInt("visuals", "var_v_transparency_ct", vars::ct_transparency, location);
	WritePrivateProfileInt("visuals", "var_v_transparency_t", vars::t_transparency, location);
	WritePrivateProfileInt("visuals", "var_v_chams_ct_r", vars::chams_ct_r, location);
	WritePrivateProfileInt("visuals", "var_v_chams_ct_g", vars::chams_ct_g, location);
	WritePrivateProfileInt("visuals", "var_v_chams_ct_b", vars::chams_ct_b, location);
	WritePrivateProfileInt("visuals", "var_v_chams_t_r", vars::chams_t_r, location);
	WritePrivateProfileInt("visuals", "var_v_chams_t_g", vars::chams_t_g, location);
	WritePrivateProfileInt("visuals", "var_v_chams_t_b", vars::chams_t_b, location);
	WritePrivateProfileInt("visuals", "var_v_chams_ct_visible_r", vars::chams_ct_visible_r, location);
	WritePrivateProfileInt("visuals", "var_v_chams_ct_visible_g", vars::chams_ct_visible_g, location);
	WritePrivateProfileInt("visuals", "var_v_chams_ct_visible_b", vars::chams_ct_visible_b, location);
	WritePrivateProfileInt("visuals", "var_v_chams_t_visible_r", vars::chams_t_visible_r, location);
	WritePrivateProfileInt("visuals", "var_v_chams_t_visible_g", vars::chams_t_visible_g, location);
	WritePrivateProfileInt("visuals", "var_v_chams_t_visible_b", vars::chams_t_visible_b, location);
	WritePrivateProfileInt("visuals", "var_v_chams_transparency_ct", vars::chams_ct_transparency, location);
	WritePrivateProfileInt("visuals", "var_v_chams_transparency_t", vars::chams_t_transparency, location);
	WritePrivateProfileInt("visuals", "var_v_chams_ignore_team", vars::chams_enemies, location);
	WritePrivateProfileInt("visuals", "var_v_weapons_transparency", vars::weapons_transparency, location);
	WritePrivateProfileInt("visuals", "var_v_hands_transparency", vars::hands_transparency, location);
	WritePrivateProfileInt("visuals", "var_v_radarx", Settings::RadarX, location);
	WritePrivateProfileInt("visuals", "var_v_radary", Settings::RadarY, location);
	WritePrivateProfileInt("visuals", "var_v_crosshairsize", vars::esp_chsize, location);
	WritePrivateProfileInt("visuals", "var_v_radarsize", Settings::radarsize, location);

	WritePrivateProfileInt("visuals", "var_v_hands_r", vars::handsr, location);
	WritePrivateProfileInt("visuals", "var_v_hands_g", vars::handsg, location);
	WritePrivateProfileInt("visuals", "var_v_hands_b", vars::handsb, location);

	WritePrivateProfileInt("visuals", "var_v_weapons_r", vars::weaponR, location);
	WritePrivateProfileInt("visuals", "var_v_weapons_g", vars::weaponG, location);
	WritePrivateProfileInt("visuals", "var_v_weapons_b", vars::weaponB, location);
	
	WritePrivateProfileInt("visuals", "var_v_menu_r", vars::menur, location);
	WritePrivateProfileInt("visuals", "var_v_menu_g", vars::menug, location);
	WritePrivateProfileInt("visuals", "var_v_menu_b", vars::menub, location);
	WritePrivateProfileInt("visuals", "var_v_menu_t", vars::removeTrns, location);

	WritePrivateProfileInt("visuals", "var_v_crosshair", vars::esp_crosshair, location);
	WritePrivateProfileInt("visuals", "var_v_visonly", vars::visonly, location);
	WritePrivateProfileInt("visuals", "var_v_ignore_team", vars::esp_ignore, location);
	WritePrivateProfileInt("visuals", "var_v_watermark", vars::misc_watermarks, location);
	WritePrivateProfileInt("visuals", "var_v_localtime", vars::misc_time, location);
	WritePrivateProfileInt("visuals", "var_v_norecoil", vars::misc_novisrecoil, location);
	WritePrivateProfileInt("visuals", "var_v_world", vars::espworld, location);
	WritePrivateProfileInt("visuals", "var_v_barrel", vars::bullettrace, location);
	//var_m_thirdperson
	WritePrivateProfileInt("visuals", "var_v_noflash", vars::noflash, location);
	WritePrivateProfileInt("visuals", "var_v_radar", vars::radar, location);
	WritePrivateProfileInt("visuals", "var_v_espkey", vars::espKey, location);
	WritePrivateProfileInt("visuals", "var_v_esponkey", vars::onkey, location);

	WritePrivateProfileInt("misc", "var_m_antiuntrusted", vars::misc_antiuntrust, location);
	WritePrivateProfileInt("misc", "var_m_fakewalk_key", vars::misc_fakewalkkey, location);
	WritePrivateProfileInt("misc", "var_m_fakewalk", vars::misc_fakewalk, location);
	WritePrivateProfileInt("misc", "var_m_ragespecvision", vars::misc_ragespecvision, location);
	WritePrivateProfileInt("misc", "var_m_bhop", vars::misc_bhop, location);
	WritePrivateProfileInt("misc", "var_m_moon", vars::moonwalk, location);
	WritePrivateProfileInt("misc", "var_m_bhopminvel", vars::minvel, location);
	WritePrivateProfileInt("misc", "var_m_fovchanger", vars::misc_fovchange, location);
	WritePrivateProfileInt("misc", "var_m_fov", vars::misc_fovfactor, location);
	WritePrivateProfileInt("misc", "var_m_lefthand", vars::misc_knife, location);
	WritePrivateProfileInt("misc", "var_m_autostrafer", vars::misc_autostrafe, location);
	WritePrivateProfileInt("misc", "var_m_fakelag", vars::misc_fakelag, location);
	WritePrivateProfileInt("misc", "var_m_fakelagmode", vars::flagMode, location);
	WritePrivateProfileInt("misc", "var_m_fakelaginair", vars::inair, location);
	WritePrivateProfileInt("misc", "var_m_aircrouch", vars::misc_duck, location);
	WritePrivateProfileInt("misc", "var_m_airstuck", vars::misc_airstuck, location);
	WritePrivateProfileInt("misc", "var_m_airstuck_key", vars::misc_airstuckey, location);
	WritePrivateProfileInt("misc", "var_m_aa_yaw", vars::misc_yaw, location);
	WritePrivateProfileInt("misc", "var_m_aa_pitch", vars::misc_pitch, location);
	WritePrivateProfileInt("misc", "var_m_aa_fake", vars::aa_fake, location);
	WritePrivateProfileInt("misc", "var_m_aa_dyn", vars::dynamicaa, location);
	WritePrivateProfileInt("misc", "var_m_aa_antires", vars::antires, location);
	WritePrivateProfileInt("misc", "var_m_aa_edge", vars::misc_edge, location);
	WritePrivateProfileInt("misc", "var_m_aa_fakeangle", vars::pred_tick, location);
	WritePrivateProfileInt("misc", "var_m_aa_target", vars::aa_at_target, location);
	WritePrivateProfileInt("misc", "var_m_thirdperson", vars::misc_thirdperson, location);
	WritePrivateProfileInt("misc", "var_m_speedbar", vars::velocitybar, location);
	WritePrivateProfileInt("misc", "var_m_headglitch", vars::headfix, location);
	WritePrivateProfileInt("misc", "var_m_autoaccept", vars::autoaccept, location);
	WritePrivateProfileInt("misc", "var_m_doorspam", vars::doorspam, location);
	WritePrivateProfileInt("misc", "var_m_doorspamkey", vars::spamKey, location);
	WritePrivateProfileInt("misc", "var_m_hgangle", vars::randmizeXd, location);
	//skins
	WritePrivateProfileInt("SkinChanger", "var_m_skinchangerenabled", vars::skinchanger, location);
	WritePrivateProfileInt("KnifeChanger", "var_m_knifechangerenabled", vars::knifechange, location);
	WritePrivateProfileInt("GloveChanger", "var_m_glovechangerenabled", vars::glovechange, location);


}
bool niggar = false;
bool gaschamber = false;
void doLoad() {
	const char * location = NULL;
	std::string savePath = "C:\\parallax.int\\default.ini";
	std::string savePath2 = "C:\\parallax.int\\legit.ini";
	std::string savePath3 = "C:\\parallax.int\\rage.ini";
	std::string savePath4 = "C:\\parallax.int\\hvh1.ini";
	std::string savePath5 = "C:\\parallax.int\\hvh2.ini";
	std::string savePath6 = "C:\\parallax.int\\secret.ini";
	if (vars::config_select == 0 || vars::config_select == 1) {
		location = savePath.c_str();
	}
	else if (vars::config_select == 2) {
		location = savePath2.c_str();
	}
	else if (vars::config_select == 3) {
		location = savePath3.c_str();
	}
	else if (vars::config_select == 4) {
		location = savePath4.c_str();
	}
	else if (vars::config_select == 5) {
		location = savePath5.c_str();
	}
	else if (vars::config_select == 6) {
		location = savePath6.c_str();
	}
	vars::legit_wpns = GetPrivateProfileIntA("legit", "var_w_configs", vars::legit_wpns, location);
	vars::legit_active = GetPrivateProfileIntA("legit", "var_a_aimbot", vars::legit_active, location);
	vars::aimkey = GetPrivateProfileIntA("legit", "var_a_aimkey", vars::aimkey, location);
	vars::legit_psilent = GetPrivateProfileIntA("legit", "var_a_psilent", vars::legit_psilent, location);
	vars::aim_boner1 = GetPrivateProfileIntA("legit", "var_a_bone", vars::aim_boner1, location);
	vars::legit_team = GetPrivateProfileIntA("legit", "var_a_team", vars::legit_team, location);
	vars::accuracyboost = GetPrivateProfileIntA("legit", "var_a_boost", vars::accuracyboost, location);
	vars::legit_fov = GetPrivateProfileIntA("legit", "var_a_fov", vars::legit_fov, location);
	iSmoothFactor = GetPrivateProfileIntA("legit", "var_a_smoothx", iSmoothFactor, location);
	iSmoothFactory = GetPrivateProfileIntA("legit", "var_a_smoothy", iSmoothFactory, location);

	vars::rcs_enabled = GetPrivateProfileIntA("legit", "var_r_enabled", vars::rcs_enabled, location);
	vars::rcs_randomize = GetPrivateProfileIntA("legit", "var_r_randomize", vars::rcs_randomize, location);
	vars::rcs_standalone = GetPrivateProfileIntA("legit", "var_r_delayed", vars::rcs_standalone, location);

	vars::rcs_float_x = GetPrivateProfileIntA("legit", "var_r_xscale", vars::rcs_float_x, location);
	vars::rcs_float_y = GetPrivateProfileIntA("legit", "var_r_yscale", vars::rcs_float_y, location);
	
	
	vars::legit_trigg = GetPrivateProfileIntA("legit", "var_t_triggerbot", vars::legit_trigg, location);
	vars::legit_head = GetPrivateProfileIntA("legit", "var_t_hsonly", vars::legit_head, location);
	vars::triggerkey = GetPrivateProfileIntA("legit", "var_t_triggerkey", vars::triggerkey, location);
	vars::trigg_delay = GetPrivateProfileIntA("legit", "var_t_triggerdelay", vars::trigg_delay, location);
	vars::trigg_cooldown = GetPrivateProfileIntA("legit", "var_t_triggercooldown", vars::trigg_cooldown, location);



	vars::aaMode = GetPrivateProfileIntA("legit", "var_a_boostmode", vars::aaMode, location);
	rifle_aamode = GetPrivateProfileIntA("legit", "var_r_a_boostmode", rifle_aamode, location);
	pistol_aamode = GetPrivateProfileIntA("legit", "var_p_a_boostmode", pistol_aamode, location);
	sniper_aamode = GetPrivateProfileIntA("legit", "var_s_a_boostmode", sniper_aamode, location);
	smg_aamode = GetPrivateProfileIntA("legit", "var_m_a_boostmode", smg_aamode, location);
	heavy_aamode = GetPrivateProfileIntA("legit", "var_h_a_boostmode", heavy_aamode, location);



	rifle_active = GetPrivateProfileIntA("legit", "var_w_r_aimbot", rifle_active, location);
	rifle_fov = GetPrivateProfileIntA("legit", "var_w_r_fov", rifle_active, location);
	rifle_aactive = GetPrivateProfileIntA("legit", "var_w_r_boost", rifle_aactive, location);
	rifle_curve = GetPrivateProfileIntA("legit", "var_w_r_curve", rifle_curve, location);
	rifle_curvevalue = GetPrivateProfileIntA("legit", "var_w_r_curvevalue", rifle_curvevalue, location);
	rifle_smoothx = GetPrivateProfileIntA("legit", "var_w_r_smoothx", rifle_smoothx, location);
	rifle_smoothy = GetPrivateProfileIntA("legit", "var_w_r_smoothy", rifle_smoothy, location);
	rifle_aimkey = GetPrivateProfileIntA("legit", "var_w_r_aimkey", rifle_aimkey, location);
	rifle_bone = GetPrivateProfileIntA("legit", "var_w_r_bone", rifle_bone, location);
	rifle_psilent = GetPrivateProfileIntA("legit", "var_w_r_psilent", rifle_psilent, location);
	rifle_e = GetPrivateProfileIntA("legit", "var_w_r_enabled", rifle_e, location);
	rifle_r = GetPrivateProfileIntA("legit", "var_w_r_randomize", rifle_r, location);
	rifle_s = GetPrivateProfileIntA("legit", "var_w_r_delayed", rifle_s, location);
	rifle_float_x = GetPrivateProfileIntA("legit", "var_w_r_rcsx", rifle_float_x, location);
	rifle_float_y = GetPrivateProfileIntA("legit", "var_w_r_rcsy", rifle_float_y, location);
	riflea = GetPrivateProfileIntA("legit", "var_w_r_triggerbot", riflea, location);
	rifleh = GetPrivateProfileIntA("legit", "var_w_r_hsonly", rifleh, location);
	riflekey = GetPrivateProfileIntA("legit", "var_w_r_triggerkey", riflekey, location);
	rifled = GetPrivateProfileIntA("legit", "var_w_r_triggerdelay", rifled, location);
	riflec = GetPrivateProfileIntA("legit", "var_w_r_triggercooldown", riflec, location);



	pistol_active = GetPrivateProfileIntA("legit", "var_w_p_aimbot", pistol_active, location);
	pistol_fov = GetPrivateProfileIntA("legit", "var_w_p_fov", pistol_active, location);
	pistol_curve = GetPrivateProfileIntA("legit", "var_w_p_curve", pistol_curve, location);
	pistol_curvevalue = GetPrivateProfileIntA("legit", "var_w_p_curvevalue", pistol_curvevalue, location);
	pistol_smoothx = GetPrivateProfileIntA("legit", "var_w_p_smoothx", pistol_smoothx, location);
	pistol_smoothy = GetPrivateProfileIntA("legit", "var_w_p_smoothy", pistol_smoothy, location);
	pistol_aimkey = GetPrivateProfileIntA("legit", "var_w_p_aimkey", pistol_aimkey, location);
	pistol_bone = GetPrivateProfileIntA("legit", "var_w_p_bone", pistol_bone, location);
	pistol_aactive = GetPrivateProfileIntA("legit", "var_w_p_boost", pistol_aactive, location);
	pistol_psilent = GetPrivateProfileIntA("legit", "var_w_p_psilent", pistol_psilent, location);
	pistol_e = GetPrivateProfileIntA("legit", "var_w_p_enabled", pistol_e, location);
	pistol_r = GetPrivateProfileIntA("legit", "var_w_p_randomize", pistol_r, location);
	pistol_s = GetPrivateProfileIntA("legit", "var_w_p_delayed", pistol_s, location);
	pistol_float_x = GetPrivateProfileIntA("legit", "var_w_p_rcsx", pistol_float_x, location);
	pistol_float_y = GetPrivateProfileIntA("legit", "var_w_p_rcsy", pistol_float_y, location);
	pistola = GetPrivateProfileIntA("legit", "var_w_p_triggerbot", pistola, location);
	pistolh = GetPrivateProfileIntA("legit", "var_w_p_hsonly", pistolh, location);
	pistolkey = GetPrivateProfileIntA("legit", "var_w_p_triggerkey", pistolkey, location);
	pistold = GetPrivateProfileIntA("legit", "var_w_p_triggerdelay", pistold, location);
	pistolc = GetPrivateProfileIntA("legit", "var_w_p_triggercooldown", pistolc, location);

	

	sniper_active = GetPrivateProfileIntA("legit", "var_w_s_aimbot", sniper_active, location);
	sniper_fov = GetPrivateProfileIntA("legit", "var_w_s_fov", sniper_active, location);
	sniper_curve = GetPrivateProfileIntA("legit", "var_w_s_curve", sniper_curve, location);
	sniper_aactive = GetPrivateProfileIntA("legit", "var_w_s_boost", sniper_aactive, location);
	sniper_curvevalue = GetPrivateProfileIntA("legit", "var_w_s_curvevalue", sniper_curvevalue, location);
	sniper_smoothx = GetPrivateProfileIntA("legit", "var_w_s_smoothx", sniper_smoothx, location);
	sniper_smoothy = GetPrivateProfileIntA("legit", "var_w_s_smoothy", sniper_smoothy, location);
	sniper_aimkey = GetPrivateProfileIntA("legit", "var_w_s_aimkey", sniper_aimkey, location);
	sniper_bone = GetPrivateProfileIntA("legit", "var_w_s_bone", sniper_bone, location);
	sniper_psilent = GetPrivateProfileIntA("legit", "var_w_s_psilent", sniper_psilent, location);
	sniper_e = GetPrivateProfileIntA("legit", "var_w_s_enabled",   sniper_e, location);
	sniper_r = GetPrivateProfileIntA("legit", "var_w_s_randomize", sniper_r, location);
	sniper_s = GetPrivateProfileIntA("legit", "var_w_s_delayed",   sniper_s, location);
	sniper_float_x = GetPrivateProfileIntA("legit", "var_w_s_rcsx", sniper_float_x, location);
	sniper_float_y = GetPrivateProfileIntA("legit", "var_w_s_rcsy", sniper_float_y, location);
	snipera = GetPrivateProfileIntA("legit", "var_w_s_triggerbot", snipera, location);
	sniperh = GetPrivateProfileIntA("legit", "var_w_s_hsonly", sniperh, location);
	sniperkey = GetPrivateProfileIntA("legit", "var_w_s_triggerkey", sniperkey, location);
	sniperd = GetPrivateProfileIntA("legit", "var_w_s_triggerdelay", sniperd, location);
	sniperc = GetPrivateProfileIntA("legit", "var_w_s_triggercooldown", sniperc, location);


	smg_active = GetPrivateProfileIntA("legit", "var_w_m_aimbot", smg_active, location);
	smg_fov = GetPrivateProfileIntA("legit", "var_w_m_fov", smg_active, location);
	smg_curve = GetPrivateProfileIntA("legit", "var_w_m_curve", smg_curve, location);
	smg_aactive = GetPrivateProfileIntA("legit", "var_w_m_boost", smg_aactive, location);
	smg_curvevalue = GetPrivateProfileIntA("legit", "var_w_m_curvevalue", smg_curvevalue, location);
	smg_smoothx = GetPrivateProfileIntA("legit", "var_w_m_smoothx", smg_smoothx, location);
	smg_smoothy = GetPrivateProfileIntA("legit", "var_w_m_smoothy", smg_smoothy, location);
	smg_aimkey = GetPrivateProfileIntA("legit", "var_w_m_aimkey", smg_aimkey, location);
	smg_bone = GetPrivateProfileIntA("legit", "var_w_m_bone", smg_bone, location);
	smg_psilent = GetPrivateProfileIntA("legit", "var_w_m_psilent", smg_psilent, location);
	smg_e = GetPrivateProfileIntA("legit", "var_w_m_enabled",   smg_e, location);
	smg_r = GetPrivateProfileIntA("legit", "var_w_m_randomize",  smg_r, location);
	smg_s = GetPrivateProfileIntA("legit", "var_w_m_delayed",   smg_s, location);
	smg_float_x = GetPrivateProfileIntA("legit", "var_w_m_rcsx", smg_float_x, location);
	smg_float_y = GetPrivateProfileIntA("legit", "var_w_m_rcsy", smg_float_y, location);
	smga = GetPrivateProfileIntA("legit", "var_w_m_triggerbot", smga, location);
	smgh = GetPrivateProfileIntA("legit", "var_w_m_hsonly", smgh, location);
	smgkey = GetPrivateProfileIntA("legit", "var_w_m_triggerkey", smgkey, location);
	smgd = GetPrivateProfileIntA("legit", "var_w_m_triggerdelay", smgd, location);
	smgc = GetPrivateProfileIntA("legit", "var_w_m_triggercooldown", smgc, location);


	heavy_active = GetPrivateProfileIntA("legit", "var_w_h_aimbot", heavy_active, location);
	heavy_fov = GetPrivateProfileIntA("legit", "var_w_h_fov", heavy_active, location);
	heavy_curve = GetPrivateProfileIntA("legit", "var_w_h_curve", heavy_curve, location);
	heavy_aactive = GetPrivateProfileIntA("legit", "var_w_h_boost", heavy_aactive, location);
	heavy_curvevalue = GetPrivateProfileIntA("legit", "var_w_h_curvevalue", heavy_curvevalue, location);
	heavy_smoothx = GetPrivateProfileIntA("legit", "var_w_h_smoothx", heavy_smoothx, location);
	heavy_smoothy = GetPrivateProfileIntA("legit", "var_w_h_smoothy", heavy_smoothy, location);
	heavy_aimkey = GetPrivateProfileIntA("legit", "var_w_h_aimkey", heavy_aimkey, location);
	heavy_bone = GetPrivateProfileIntA("legit", "var_w_h_bone", heavy_bone, location);
	heavy_psilent = GetPrivateProfileIntA("legit", "var_w_h_psilent", heavy_psilent, location);
	heavy_e = GetPrivateProfileIntA("legit", "var_w_h_enabled",   heavy_e, location);
	heavy_r = GetPrivateProfileIntA("legit", "var_w_h_randomize", heavy_r, location);
	heavy_s = GetPrivateProfileIntA("legit", "var_w_h_delayed",   heavy_s, location);
	heavy_float_x = GetPrivateProfileIntA("legit", "var_w_h_rcsx", heavy_float_x, location);
	heavy_float_y = GetPrivateProfileIntA("legit", "var_w_h_rcsy", heavy_float_y, location);
	heavya = GetPrivateProfileIntA("legit", "var_w_h_triggerbot", heavya, location);
	heavyh = GetPrivateProfileIntA("legit", "var_w_h_hsonly", heavyh, location);
	heavykey = GetPrivateProfileIntA("legit", "var_w_h_triggerkey", heavykey, location);
	heavyd = GetPrivateProfileIntA("legit", "var_w_h_triggerdelay", heavyd, location);
	heavyc = GetPrivateProfileIntA("legit", "var_w_h_triggercooldown", heavyc, location);




	vars::rage_active = GetPrivateProfileIntA("rage", "var_a_enabled", vars::rage_active, location);
	vars::aim_recoil = GetPrivateProfileIntA("rage", "var_a_recoil", vars::aim_recoil, location);
	vars::resolvemyass = GetPrivateProfileIntA("rage", "var_a_resolver", vars::resolvemyass, location);
	vars::rage_psilent = GetPrivateProfileIntA("rage", "var_a_psilent", vars::rage_psilent, location);
	vars::rage_awpbody = GetPrivateProfileIntA("rage", "var_a_awpbody", vars::rage_awpbody, location);
	vars::rage_smart = GetPrivateProfileIntA("rage", "var_a_smartaim", vars::rage_smart, location);
	vars::rage_enginepred = GetPrivateProfileIntA("rage", "var_a_enginepred", vars::rage_enginepred, location);
	vars::rage_team = GetPrivateProfileIntA("rage", "var_a_team", vars::rage_team, location);
	vars::aim_bone1 = GetPrivateProfileIntA("rage", "var_a_bone", vars::aim_bone1, location);
	vars::rage_autopistol = GetPrivateProfileIntA("rage", "var_a_autopistol", vars::rage_autopistol, location);
	vars::rage_autoscope = GetPrivateProfileIntA("rage", "var_a_autoscope", vars::rage_autoscope, location);
	vars::rage_autocrouch = GetPrivateProfileIntA("rage", "var_a_autoduck", vars::rage_autocrouch, location);
	vars::rage_autostop = GetPrivateProfileIntA("rage", "var_a_autostop", vars::rage_autostop, location);
	vars::rage_autoshoot = GetPrivateProfileIntA("rage", "var_a_autoshoot", vars::rage_autoshoot, location);
	vars::autorest = GetPrivateProfileIntA("rage", "var_a_autorest", vars::autorest, location);
	vars::rage_awall = GetPrivateProfileIntA("rage", "var_a_autowall", vars::rage_awall, location);
	vars::rage_nospread = GetPrivateProfileIntA("rage", "var_a_nospread", vars::rage_nospread, location);
	//vars::rage_hitscan = GetPrivateProfileIntA("rage", "var_a_hitscan", vars::rage_hitscan, location);
	vars::pred_tick = GetPrivateProfileIntA("misc", "var_m_aa_fakeangle", vars::pred_tick, location);
	vars::hsMode = GetPrivateProfileIntA("rage", "var_a_hitscanmode", vars::hsMode, location);
	vars::aim_awall_factor = GetPrivateProfileIntA("rage", "var_a_awallfactor", vars::aim_awall_factor, location);
	vars::aim_fov = GetPrivateProfileIntA("rage", "var_a_fov", vars::aim_fov, location);
	vars::aim_hitchanceF = GetPrivateProfileIntA("rage", "var_a_hitchance", vars::aim_hitchanceF, location);

	vars::noflash = GetPrivateProfileIntA("visuals", "var_v_noflash", vars::noflash, location);
	vars::radar = GetPrivateProfileIntA("visuals", "var_v_radar", vars::radar, location);
	vars::espKey = GetPrivateProfileIntA("visuals", "var_v_espkey", vars::espKey, location);
	vars::onkey = GetPrivateProfileIntA("visuals", "var_v_esponkey", vars::onkey, location);
	vars::MenuDrop = GetPrivateProfileIntA("visuals", "var_v_menuanim", vars::MenuDrop, location);
	vars::dynText = GetPrivateProfileIntA("visuals", "var_v_titleanim", vars::dynText, location);
	vars::baranim = GetPrivateProfileIntA("visuals", "var_v_baranim", vars::baranim, location);
	vars::esp_active = GetPrivateProfileIntA("visuals", "var_v_enabled", vars::esp_active, location);
	vars::esp_box = GetPrivateProfileIntA("visuals", "var_v_box", vars::esp_box, location);
	vars::esp_boxstyle = GetPrivateProfileIntA("visuals", "var_v_boxstyle", vars::esp_boxstyle, location);
	vars::esp_name = GetPrivateProfileIntA("visuals", "var_v_name", vars::esp_name, location);
	vars::esp_healthbar = GetPrivateProfileIntA("visuals", "var_v_health", vars::esp_healthbar, location);
	vars::esp_weapons = GetPrivateProfileIntA("visuals", "var_v_weapons", vars::esp_weapons, location);
	vars::esp_skeleton = GetPrivateProfileIntA("visuals", "var_v_skeleton", vars::esp_skeleton, location);
	vars::chamselect = GetPrivateProfileIntA("visuals", "var_v_chams", vars::chamselect, location);
	vars::esp_hands = GetPrivateProfileIntA("visuals", "var_v_hands", vars::esp_hands, location);
	vars::wpn_chams = GetPrivateProfileIntA("visuals", "var_v_cweapons", vars::wpn_chams, location);
	vars::esp_ct_r = GetPrivateProfileIntA("visuals", "var_v_ct_r", vars::esp_ct_r, location);
	vars::esp_ct_g = GetPrivateProfileIntA("visuals", "var_v_ct_g", vars::esp_ct_g, location);
	vars::esp_ct_b = GetPrivateProfileIntA("visuals", "var_v_ct_b", vars::esp_ct_b, location);
	vars::esp_t_r = GetPrivateProfileIntA("visuals", "var_v_t_r", vars::esp_t_r, location);
	vars::esp_t_g = GetPrivateProfileIntA("visuals", "var_v_t_g", vars::esp_t_g, location);
	vars::esp_t_b = GetPrivateProfileIntA("visuals", "var_v_t_b", vars::esp_t_b, location);
	vars::esp_ct_visible_r = GetPrivateProfileIntA("visuals", "var_v_ct_visible_r", vars::esp_ct_visible_r, location);
	vars::esp_ct_visible_g = GetPrivateProfileIntA("visuals", "var_v_ct_visible_g", vars::esp_ct_visible_g, location);
	vars::esp_ct_visible_b = GetPrivateProfileIntA("visuals", "var_v_ct_visible_b", vars::esp_ct_visible_b, location);
	vars::esp_t_visible_r = GetPrivateProfileIntA("visuals", "var_v_t_visible_r", vars::esp_t_visible_r, location);
	vars::esp_t_visible_g = GetPrivateProfileIntA("visuals", "var_v_t_visible_g", vars::esp_t_visible_g, location);
	vars::esp_t_visible_b = GetPrivateProfileIntA("visuals", "var_v_t_visible_b", vars::esp_t_visible_b, location);
	vars::chams_ct_r = GetPrivateProfileIntA("visuals", "var_v_chams_ct_r", vars::chams_ct_r, location);
	vars::chams_ct_g = GetPrivateProfileIntA("visuals", "var_v_chams_ct_g", vars::chams_ct_g, location);
	vars::chams_ct_b = GetPrivateProfileIntA("visuals", "var_v_chams_ct_b", vars::chams_ct_b, location);
	vars::chams_t_r = GetPrivateProfileIntA("visuals", "var_v_chams_t_r", vars::chams_t_r, location);
	vars::chams_t_g = GetPrivateProfileIntA("visuals", "var_v_chams_t_g", vars::chams_t_g, location);
	vars::chams_t_b = GetPrivateProfileIntA("visuals", "var_v_chams_t_b", vars::chams_t_b, location);
	vars::chams_ct_visible_r = GetPrivateProfileIntA("visuals", "var_v_chams_ct_visible_r", vars::chams_ct_visible_r, location);
	vars::chams_ct_visible_g = GetPrivateProfileIntA("visuals", "var_v_chams_ct_visible_g", vars::chams_ct_visible_g, location);
	vars::chams_ct_visible_b = GetPrivateProfileIntA("visuals", "var_v_chams_ct_visible_b", vars::chams_ct_visible_b, location);
	vars::chams_t_visible_r = GetPrivateProfileIntA("visuals", "var_v_chams_t_visible_r", vars::chams_t_visible_r, location);
	vars::chams_t_visible_g = GetPrivateProfileIntA("visuals", "var_v_chams_t_visible_g", vars::chams_t_visible_g, location);
	vars::chams_t_visible_b = GetPrivateProfileIntA("visuals", "var_v_chams_t_visible_b", vars::chams_t_visible_b, location);
	vars::t_transparency = GetPrivateProfileIntA("visuals", "var_v_transparency_t", vars::t_transparency, location);
	vars::ct_transparency = GetPrivateProfileIntA("visuals", "var_v_transparency_ct", vars::ct_transparency, location);
	vars::chams_t_transparency = GetPrivateProfileIntA("visuals", "var_v_chams_transparency_t", vars::chams_t_transparency, location);
	vars::chams_ct_transparency = GetPrivateProfileIntA("visuals", "var_v_chams_transparency_ct", vars::chams_ct_transparency, location);
	vars::weapons_transparency = GetPrivateProfileIntA("visuals", "var_v_weapons_transparency", vars::weapons_transparency, location);
	vars::esp_chsize = GetPrivateProfileIntA("visuals", "var_v_crosshairsize", vars::esp_chsize, location);
	Settings::radarsize = GetPrivateProfileIntA("visuals", "var_v_radarsize", Settings::radarsize, location);
	Settings::RadarX = GetPrivateProfileIntA("visuals", "var_v_radarx", Settings::RadarX, location);
	Settings::RadarY = GetPrivateProfileIntA("visuals", "var_v_radary", Settings::RadarY, location);
	vars::hands_transparency = GetPrivateProfileIntA("visuals", "var_v_hands_transparency", vars::hands_transparency, location);
	//var_v_transparency_ct
	vars::weaponR = GetPrivateProfileIntA("visuals", "var_v_weapons_r", vars::weaponR, location);
	vars::weaponG = GetPrivateProfileIntA("visuals", "var_v_weapons_g", vars::weaponG, location);
	vars::weaponB = GetPrivateProfileIntA("visuals", "var_v_weapons_b", vars::weaponB, location);


	vars::menur = GetPrivateProfileIntA("visuals", "var_v_menu_r", vars::menur, location);
	vars::menug = GetPrivateProfileIntA("visuals", "var_v_menu_g", vars::menug, location);
	vars::menub = GetPrivateProfileIntA("visuals", "var_v_menu_b", vars::menub, location);
	vars::removeTrns = GetPrivateProfileIntA("visuals", "var_v_menu_t", vars::removeTrns, location);

	vars::handsr = GetPrivateProfileIntA("visuals", "var_v_hands_r", vars::handsr, location);
	vars::handsg = GetPrivateProfileIntA("visuals", "var_v_hands_g", vars::handsg, location);
	vars::handsb = GetPrivateProfileIntA("visuals", "var_v_hands_b", vars::handsb, location);
	

	vars::esp_crosshair = GetPrivateProfileIntA("visuals", "var_v_crosshair", vars::esp_crosshair, location);
	vars::esp_ignore = GetPrivateProfileIntA("visuals", "var_v_ignore_team", vars::esp_ignore, location);
	vars::chams_enemies = GetPrivateProfileIntA("visuals", "var_v_chams_ignore_team", vars::chams_enemies, location);
	vars::visonly = GetPrivateProfileIntA("visuals", "var_v_visonly", vars::visonly, location);
	vars::misc_watermarks = GetPrivateProfileIntA("visuals", "var_v_watermark", vars::misc_watermarks, location);
	vars::misc_time = GetPrivateProfileIntA("visuals", "var_v_localtime", vars::misc_time, location);
	vars::misc_novisrecoil = GetPrivateProfileIntA("visuals", "var_v_norecoil", vars::misc_novisrecoil, location);
	vars::espworld = GetPrivateProfileIntA("visuals", "var_v_world", vars::espworld, location);
	vars::bullettrace = GetPrivateProfileIntA("visuals", "var_v_barrel", vars::bullettrace, location);


	vars::misc_antiuntrust = GetPrivateProfileIntA("misc", "var_m_antiuntrusted", vars::misc_antiuntrust, location);
	vars::misc_fakewalk = GetPrivateProfileIntA("misc", "var_m_fakewalk", vars::misc_fakewalk, location);
	vars::misc_fakewalkkey = GetPrivateProfileIntA("misc", "var_m_fakewalk_key", vars::misc_fakewalkkey, location);
	vars::misc_ragespecvision = GetPrivateProfileIntA("misc", "var_m_ragespecvision", vars::misc_ragespecvision, location);
	vars::misc_bhop = GetPrivateProfileIntA("misc", "var_m_bhop", vars::misc_bhop, location);
	vars::moonwalk = GetPrivateProfileIntA("misc", "var_m_moon", vars::moonwalk, location);
	vars::minvel = GetPrivateProfileIntA("misc", "var_m_bhopminvel", vars::minvel, location);
	vars::misc_knife = GetPrivateProfileIntA("misc", "var_m_lefthand", vars::misc_knife, location);
	vars::misc_autostrafe = GetPrivateProfileIntA("misc", "var_m_autostrafer", vars::misc_autostrafe, location);
	vars::misc_fakelag = GetPrivateProfileIntA("misc", "var_m_fakelag", vars::misc_fakelag, location);
	vars::flagMode = GetPrivateProfileIntA("misc", "var_m_fakelagmode", vars::flagMode, location);
	vars::inair = GetPrivateProfileIntA("misc", "var_m_fakelaginair", vars::inair, location);
	vars::misc_duck = GetPrivateProfileIntA("misc", "var_m_aircrouch", vars::misc_duck, location);
	vars::misc_airstuck = GetPrivateProfileIntA("misc", "var_m_airstuck", vars::misc_airstuck, location);
	vars::misc_airstuckey = GetPrivateProfileIntA("misc", "var_m_airstuck_key", vars::misc_airstuckey, location);
	vars::misc_antiaim = GetPrivateProfileIntA("misc", "var_m_aa_enabled", vars::misc_antiaim, location);
	vars::misc_yaw = GetPrivateProfileIntA("misc", "var_m_aa_yaw", vars::misc_yaw, location);
	vars::misc_pitch = GetPrivateProfileIntA("misc", "var_m_aa_pitch", vars::misc_pitch, location);
	vars::antires = GetPrivateProfileIntA("misc", "var_m_aa_antires", vars::antires, location);
	vars::aa_fake = GetPrivateProfileIntA("misc", "var_m_aa_fake", vars::aa_fake, location);
	vars::dynamicaa = GetPrivateProfileIntA("misc", "var_m_aa_dyn", vars::dynamicaa, location);
	vars::misc_edge = GetPrivateProfileIntA("misc", "var_m_aa_edge", vars::misc_edge, location);
	vars::misc_thirdperson = GetPrivateProfileIntA("misc", "var_m_thirdperson", vars::misc_thirdperson, location);
	vars::velocitybar = GetPrivateProfileIntA("misc", "var_m_speedbar", vars::velocitybar, location);
	vars::headfix = GetPrivateProfileIntA("misc", "var_m_headglitch", vars::headfix, location);
	vars::autoaccept = GetPrivateProfileIntA("misc", "var_m_autoaccept", vars::autoaccept, location);
	vars::doorspam = GetPrivateProfileIntA("misc", "var_m_doorspam", vars::doorspam, location);
	vars::spamKey = GetPrivateProfileIntA("misc", "var_m_doorspamkey", vars::spamKey, location);
	vars::randmizeXd = GetPrivateProfileIntA("misc", "var_m_hgangle", vars::randmizeXd, location);
	vars::misc_unfixedAA = GetPrivateProfileIntA("misc", "var_m_aa_unfixed", vars::misc_unfixedAA, location);
	vars::aa_at_target = GetPrivateProfileIntA("misc", "var_m_aa_target", vars::aa_at_target, location);
	vars::misc_fovchange = GetPrivateProfileIntA("misc", "var_m_fovchanger", vars::misc_fovchange, location);
	vars::misc_fovfactor = GetPrivateProfileIntA("misc", "var_m_fov", vars::misc_fovfactor, location);
	//skins
	vars::skinchanger = GetPrivateProfileIntA("skins", "var_m_skinchanger", vars::skinchanger, location);
	vars::knifechange = GetPrivateProfileIntA("skins", "var_m_knifechanger", vars::knifechange, location);
	vars::glovechange = GetPrivateProfileIntA("skins", "var_m_glovechanger", vars::glovechange, location);
	
	

}
bool LoadCFG = false;
bool hitscenlel = false;
int knifeskin = 0;
int weaponskin = 0;
int gloveskin = 0;
void kAZORDrawings::drawBigButton(int x, int y, int w, int h, const char* pszString, int iCount, bool& var) {
	y += iCount * 20;
	GetCursorPos(&Cur);
	static unsigned int Last = 0;
	if ((Cur.x > x) && (Cur.x < x + w) && (Cur.y > y) && (Cur.y < y + h) && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
		if (pszString == "  Load") {
			doLoad();
			LoadCFG = true;
			SlideCFG = true;
		}
		if (pszString == "  Save") {
			doSave();
			LoadCFG = false;
			SlideCFG = true;
		}
		doEins = true;
		this->FillRGBA(x, y, w, h, Color(32, 32, 32, menut));
	}
	else {
		this->FillRGBA(x, y, w, h, Color(25, 25, 25, menut));
	}
	
	this->DrawBox(x, y, w, h, Color(40, 40, 40, menut));
	this->DrawString(x + 4, y + 2, Color(255, 255, 255, menut), labelFont, pszString);
}
void kAZORDrawings::DrawShineMark(int x, int y) {
	
}

void kAZORDrawings::DrawLine(int x, int y, int xx, int yy, Color col) {
	pValve->pSurface->DrawSetColor(col);
	pValve->pSurface->DrawLine(x, y, xx, yy);
}
int shotted;


bool niggor = false;
bool niggor2 = false;
bool niggor3 = false;
bool kanker = false;

int CORNERER = 0;
int WALLERER = 0;
int memeSparency = 255;
int memeSparency2 = 0;
void kAZORDrawings::DrawMenu(int& x, int& y, int w, int h) {
	//this->FillRGBA(x + 10, y + 10, w, h, Color(0, 0, 0, 120));
	this->FillRGBA(x, y, w, h, Color(16, 16, 16, menut - (vars::removeTrns * 2)));
	this->FillRGBA(x, y, w, h, Color(16, 16, 16, menut - (vars::removeTrns * 2)));
	this->DrawBox(x, y, w, h, Color(0, 0, 0, menut));
	this->DrawBox(x + 1, y + 1, w - 2, h - 2, Color(59, 61, 60, menut));
	this->DrawBox(x + 2, y + 2, w - 4, h - 4, Color(42, 42, 42, menut));
	this->DrawBox(x + 3, y + 3, w - 6, h - 6, Color(42, 42, 42, menut));
	this->DrawBox(x + 4, y + 4, w - 8, h - 8, Color(42, 42, 42, menut));
	this->DrawBox(x + 5, y + 5, w - 10, h - 10, Color(59, 61, 60, menut));
	this->DrawBox(x + 6, y + 6, w - 12, h - 12, Color(30, 30, 30, menut));
	if (vars::baranim) {
		static int red = vars::menur;
		static int green = vars::menug;
		static int blue = vars::menub;
		
		if ((vars::menub < 214 && vars::menub > 40) && (vars::menug < 214 && vars::menug > 40) && (vars::menur < 214 && vars::menur > 40)) {

			static float counter = 0;
			static int dummyCounter = 0;
			static bool switchit = false;
			dummyCounter++;
			if (dummyCounter > 39) {
				switchit = !switchit;
				dummyCounter = 0;
			}
			if (switchit) {
				counter += 1;
			}
			else {
				counter -= 1;
			}


			red = vars::menur + counter;

			green = vars::menug + counter;

			blue = vars::menub + counter;

		}
		else {
			red = vars::menur;
			green = vars::menug;
			blue = vars::menub;
		}
		this->DrawBox(x + 7, y + 7, w - 14, 1, Color(red, green, blue, menut));
		this->DrawBox(x + 7, y + 8, w - 14, 1, Color(red, green, blue, menut));
	}
	else {
		this->DrawBox(x + 7, y + 7, w - 14, 1, Color(vars::menur, vars::menug, vars::menub, menut));
		this->DrawBox(x + 7, y + 8, w - 14, 1, Color(vars::menur, vars::menug, vars::menub, menut));
	}
	
	//this->DrawOutlinedCircle(10, 10, 20, Color(255, 0, 0, 255));
	//this->DrawBox(x + 20, y + 20, 100, 40, Color(0, 100, 255, 255));
	if (Cur.x > x + 20 && Cur.x < x + 107 && Cur.y > y + 20 && Cur.y < y + 60) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			if (memeSparency > 50)
				memeSparency -= 4;
			if (memeSparency < 50)
				memeSparency = 50;

			if (memeSparency2 < 255)
				memeSparency2 += 2;
			if (memeSparency2 > 255)
				memeSparency2 = 255;
			
		}
		else {
			if (memeSparency < 255)
				memeSparency += 2;
			if (memeSparency > 255)
				memeSparency = 255;

			if (memeSparency2 > 0)
				memeSparency2 -= 5;
			if (memeSparency2 < 0)
				memeSparency2 = 0;
			
		}
		
	}
	else {
		if (memeSparency < 255)
			memeSparency += 2;
		if (memeSparency > 255)
			memeSparency = 255;

		if (memeSparency2 > 0)
			memeSparency2 -= 5;
		if (memeSparency2 < 0)
			memeSparency2 = 0;

	}
	if (vars::dynText) {
		if (menut >= 255) {
			this->Draw_wChar(x + 20, y + 20, Color(vars::menur, vars::menug, vars::menub, memeSparency), xFont, L"\u03a8");
			this->DrawString(x + 40, y + 34, Color(255, 255, 255, memeSparency2), labelFont, "PARALLAX");
		}
		else {
			this->Draw_wChar(x + 22, y + 22, Color(40, 40, 40, menut), xFont, L"\u03a8");
			this->Draw_wChar(x + 20, y + 20, Color(vars::menur, vars::menug, vars::menub, menut), xFont, L"\u03a8");
		}
	}
	else {
		this->Draw_wChar(x + 22, y + 22, Color(40, 40, 40, menut), xFont, L"\u03a8");
		this->Draw_wChar(x + 20, y + 20, Color(vars::menur, vars::menug, vars::menub, menut), xFont, L"\u03a8");
	}
	//this->DrawString(x + 20, y + 20, Color(195, 144, 212, 255), oBlock, "parallax");
	this->DrawTab(x + 20, y + 70, "LEGIT", 0, Settings::iTab);
	this->DrawTab(x + 20, y + 70, "RAGE", 1, Settings::iTab);
	this->DrawTab(x + 20, y + 70, "VISUALS", 2, Settings::iTab);
	this->DrawTab(x + 20, y + 70, "MISC", 3, Settings::iTab);
	this->DrawTab(x + 20, y + 70, "COLORS", 4, Settings::iTab);
	this->DrawTab(x + 20, y + 70, "PLAYERS", 5, Settings::iTab);
	this->DrawTab(x + 20, y + 70, "SKINS", 6, Settings::iTab);
	bool meme;
	//this->DrawButton(x + 19, y + 69, "Safemode", 10, vars::misc_antiuntrust);
	this->drawBigButton(x + 20, y + 90, 44, 17, "  Load", 8, meme);
	this->drawBigButton(x + 67, y + 90, 44, 17, "  Save", 8, meme);
	this->DrawDropdown(x + 19, y + 90, 93, 16, 7, vars::config_select, " ", Configz, 9, vars::dropdown16);
	
	//legit					
	if (Settings::iTab == 0) {


		this->DrawString(x + 140, y + 21, Color(255, 255, 255, menut), labelFont, "Aimbot");
		this->DrawString(x + 140, y + 21 + (5 *20), Color(255, 255, 255, menut), labelFont, "Accuracy Boost");
		this->DrawString(x + 280, y + 21, Color(255, 255, 255, menut), labelFont, "Triggerbot");
		this->DrawString(x + 280, y + 21 + (4 * 20), Color(255, 255, 255, menut), labelFont, "Recoil Control");
		this->DrawString(x + 420, y + 21, Color(255, 255, 255, menut), labelFont, "Configuration");
		this->DrawButton(x + 420, y + 41, "Weapon Configs", 0, vars::legit_wpns);
		
		this->DrawButton(x + 420, y + 41, "At Teammates", 2, vars::legit_team);
		this->DrawDropdown(x + 420, y + 41/*57*/, 60, 16, 6, vars::currentconfig, "Config", Weapons, 1, kanker);
		if (!vars::legit_wpns) {
			this->DrawButton(x + 140, y + 41, "Enabled", 0, vars::legit_active);
			this->addTickSlider(x + 140, y + 41, "Key", 1, 999, 0, vars::aimkey);
			this->DrawButton(x + 140, y + 41, "Silent", 3, vars::legit_psilent);
			this->DrawButton(x + 140, y + 41, "Enabled", 5, vars::accuracyboost);
		//	this->DrawButton(x + 420, y + 41, "Curvature", 3, vars::aim_curve);
			
			this->DrawButton(x + 280, y + 41, "Enabled", 4, vars::rcs_enabled);
			this->DrawButton(x + 280, y + 41, "Randomize", 5, vars::rcs_randomize);
			this->DrawButton(x + 280, y + 41, "Delayed", 6, vars::rcs_standalone);

			
			this->DrawDropdown(x + 140, y + 41/*57*/, 60, 16, 6, vars::aim_boner1, "Hitbox", BonesLejit, 2, vars::dropdown15);
			this->DrawSlider(x + 140, y + 30, 180, -1, 20, vars::legit_fov, "Aimbot FOV", 9, Color(vars::menur, vars::menug,vars::menub, menut));
			this->DrawSlider(x + 140, y + 33, 180, 1, 33, iSmoothFactor, "Aimbot X Smoothness", 10, Color(vars::menur, vars::menug,vars::menub, menut));
			this->DrawSlider(x + 140, y + 36, 180, 1, 33, iSmoothFactory, "Aimbot Y Smoothness", 11, Color(vars::menur, vars::menug, vars::menub, menut));
			//this->DrawSlider(x + 140, y + 36, 180, -1, 100, vars::aim_curvevalue, "Aimbot Curvature Value", 11, Color(vars::menur, vars::menug,vars::menub, 255));
			this->DrawSlider(x + 140, y + 39, 180, -5, 500, vars::aim_time, "Aimbot Time", 12, Color(vars::menur, vars::menug,vars::menub, menut));
			if (vars::aim_time == 2)
				vars::aim_time = 0;
			this->DrawSlider(x + 350, y + 30, 180, -1, 150, vars::rcs_float_x, "RCS X Amount", 9, Color(vars::menur, vars::menug,vars::menub, menut));
			this->DrawSlider(x + 350, y + 33, 180, -1, 150, vars::rcs_float_y, "RCS Y Amount", 10, Color(vars::menur, vars::menug,vars::menub, menut));


			this->DrawButton(x + 280, y + 41, "Enabled", 0, vars::legit_trigg);
			this->addTickSlider(x + 280, y + 41, "Key", 1, 999, 0, vars::triggerkey);
			this->DrawButton(x + 280, y + 41, "Head Only", 2, vars::legit_head);

			this->DrawSlider(x + 350, y + 36, 180, -1, 100, vars::trigg_delay, "Triggerbot Delay", 11, Color(vars::menur, vars::menug,vars::menub, menut));
			this->DrawSlider(x + 350, y + 39, 180, -1, 100, vars::trigg_cooldown, "Triggerbot Cooldown", 12, Color(vars::menur, vars::menug,vars::menub, menut));
			static bool roflx = false;
			this->DrawDropdown(x + 140, y + 41, 60, 16, 3, vars::aaMode, "Mode", CoolDropDon, 6, roflx);
		}
		if (vars::legit_wpns) {
			if (vars::currentconfig == 0 || vars::currentconfig == 1) {
				/*rifle*/
				this->DrawButton(x + 140, y + 41, "Enabled", 0, rifle_active);
				this->addTickSlider(x + 140, y + 41, "Key", 1, 999, 0, rifle_aimkey);
				this->DrawButton(x + 140, y + 41, "Silent", 3, rifle_psilent);
				this->DrawButton(x + 140, y + 41, "Enabled", 5, rifle_aactive);
				//this->DrawButton(x + 420, y + 41, "Curvature", 4, rifle_curve);

				this->DrawButton(x + 280, y + 41, "Enabled", 4, rifle_e);
				this->DrawButton(x + 280, y + 41, "Randomize", 5, rifle_r);
				this->DrawButton(x + 280, y + 41, "Delayed", 6, rifle_s);
				if (rifle_bone == 0 || rifle_bone == 1) {
					vars::aim_boner = 8;
				}
				else if (rifle_bone == 2) {
					vars::aim_boner = 7;
				}
				else if (rifle_bone == 3) {
					vars::aim_boner = 6;
				}
				else if (rifle_bone == 4) {
					vars::aim_boner = 5;
				}
				else if (rifle_bone == 5) {
					vars::aim_boner = 0;
				}
				this->DrawDropdown(x + 140, y + 41, 60, 16, 6, rifle_bone, "Hitbox", BonesLejit, 2, vars::dropdown15);
				this->DrawSlider(x + 140, y + 30, 180, -1, 20, rifle_fov, "Aimbot FOV", 9, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 140, y + 33, 180, 1, 30, rifle_smoothx, "Aimbot X Smoothness", 10, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 140, y + 36, 180, 1, 30, rifle_smoothy, "Aimbot Y Smoothness", 11, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 140, y + 39, 180, -5, 500, rifle_aimtime, "Aimbot Time", 12, Color(vars::menur, vars::menug,vars::menub, menut));
				if (rifle_aimtime == 2)
					rifle_aimtime = 0;
				this->DrawSlider(x + 350, y + 30, 180, -1, 150, rifle_float_x, "RCS X Amount", 9, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 350, y + 33, 180, -1, 150, rifle_float_y, "RCS Y Amount", 10, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawButton(x + 280, y + 41, "Enabled", 0, riflea);
				this->addTickSlider(x + 280, y + 41, "Key", 1, 999, 0, riflekey);
				this->DrawButton(x + 280, y + 41, "Head Only", 2, rifleh);

				this->DrawSlider(x + 350, y + 36, 180, -1, 100, rifled, "Triggerbot Delay", 11, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 350, y + 39, 180, -1, 100, riflec, "Triggerbot Cooldown", 12, Color(vars::menur, vars::menug,vars::menub, menut));
				static bool roflx = false;
				this->DrawDropdown(x + 140, y + 41, 60, 16, 3, rifle_aamode, "Mode", CoolDropDon, 6, roflx);
			}
			else if (vars::currentconfig == 2) {
				/*pistol*/
				this->DrawButton(x + 140, y + 41, "Enabled", 0, pistol_active);
				this->addTickSlider(x + 140, y + 41, "Key", 1, 999, 0, pistol_aimkey);
				this->DrawButton(x + 140, y + 41, "Silent", 3, pistol_psilent);
			//	this->DrawButton(x + 420, y + 41, "Curvature", 3, pistol_curve);
				this->DrawButton(x + 140, y + 41, "Enabled", 5, pistol_aactive);

				this->DrawButton(x + 280, y + 41, "Enabled", 4,    pistol_e);
				this->DrawButton(x + 280, y + 41, "Randomize", 5,  pistol_r);
				this->DrawButton(x + 280, y + 41, "Delayed", 6, pistol_s);
				if (pistol_bone == 0 | pistol_bone == 1) {
					vars::aim_boner = 8;
				}
				else if (pistol_bone == 2) {
					vars::aim_boner = 7;
				}
				else if (pistol_bone == 3) {
					vars::aim_boner = 6;
				}
				else if (pistol_bone == 4) {
					vars::aim_boner = 5;
				}
				else if (pistol_bone == 5) {
					vars::aim_boner = 0;
				}
			
				this->DrawDropdown(x + 140, y + 41/*57*/, 60, 16, 6, pistol_bone, "Hitbox", BonesLejit, 2, vars::dropdown15);
				this->DrawSlider(x + 140, y + 30, 180, -1, 20, pistol_fov, "Aimbot FOV", 9, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 140, y + 33, 180, 1, 30, pistol_smoothx, "Aimbot X Smoothness", 10, Color(vars::menur, vars::menug, vars::menub, menut));
				this->DrawSlider(x + 140, y + 36, 180, 1, 30, pistol_smoothy, "Aimbot Y Smoothness", 11, Color(vars::menur, vars::menug, vars::menub, menut));
				this->DrawSlider(x + 140, y + 39, 180, -5, 500, pistol_aimtime, "Aimbot Time", 12, Color(vars::menur, vars::menug,vars::menub, menut));
				if (pistol_aimtime == 2)
					pistol_aimtime = 0;
				this->DrawSlider(x + 350, y + 30, 180, -1, 150, pistol_float_x, "RCS X Amount", 9, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 350, y + 33, 180, -1, 150, pistol_float_y, "RCS Y Amount", 10, Color(vars::menur, vars::menug,vars::menub, menut));

				this->DrawButton(x + 280, y + 41, "Enabled", 0, pistola);
				this->addTickSlider(x + 280, y + 41, "Key", 1, 999, 0, pistolkey);
				this->DrawButton(x + 280, y + 41, "Head Only", 2, pistolh);

				this->DrawSlider(x + 350, y + 36, 180, -1, 100, pistold, "Triggerbot Delay", 11, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 350, y + 39, 180, -1, 100, pistolc, "Triggerbot Cooldown", 12, Color(vars::menur, vars::menug,vars::menub, menut));
				static bool roflx = false;
				this->DrawDropdown(x + 140, y + 41, 60, 16, 3, pistol_aamode, "Mode", CoolDropDon, 6, roflx);
			}
			else if (vars::currentconfig == 3) {
				/*sniper*/
				this->DrawButton(x + 140, y + 41, "Enabled", 0, sniper_active);
				this->addTickSlider(x + 140, y + 41, "Key", 1, 999, 0, sniper_aimkey);
				this->DrawButton(x + 140, y + 41, "Silent", 3, sniper_psilent);
			//	this->DrawButton(x + 420, y + 41, "Curvature", 3, sniper_curve);
				this->DrawButton(x + 140, y + 41, "Enabled", 5, sniper_aactive);
				this->DrawButton(x + 280, y + 41, "Enabled", 4,    sniper_e);
				this->DrawButton(x + 280, y + 41, "Randomize", 5,  sniper_r);
				this->DrawButton(x + 280, y + 41, "Delayed", 6, sniper_s);
				if (sniper_bone == 0 || sniper_bone == 1) {
					vars::aim_boner = 8;
				}
				else if (sniper_bone == 2) {
					vars::aim_boner = 7;
				}
				else if (sniper_bone == 3) {
					vars::aim_boner = 6;
				}
				else if (sniper_bone == 4) {
					vars::aim_boner = 5;
				}
				else if (sniper_bone == 5) {
					vars::aim_boner = 0;
				}
				this->DrawDropdown(x + 140, y + 41/*57*/, 60, 16, 6, sniper_bone, "Hitbox", BonesLejit, 2, vars::dropdown15);
				this->DrawSlider(x + 140, y + 30, 180, -1, 20, sniper_fov, "Aimbot FOV", 9, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 140, y + 33, 180, 1, 30, sniper_smoothx, "Aimbot X Smoothness", 10, Color(vars::menur, vars::menug, vars::menub, menut));
				this->DrawSlider(x + 140, y + 36, 180, 1, 30, sniper_smoothy, "Aimbot Y Smoothness", 11, Color(vars::menur, vars::menug, vars::menub, menut));
				
				this->DrawSlider(x + 140, y + 39, 180, -5, 500, sniper_aimtime, "Aimbot Time", 12, Color(vars::menur, vars::menug,vars::menub, menut));
				if (sniper_aimtime == 2)
					sniper_aimtime = 0;
				this->DrawSlider(x + 350, y + 30, 180, -1, 150, sniper_float_x, "RCS X Amount", 9, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 350, y + 33, 180, -1, 150, sniper_float_y, "RCS Y Amount", 10, Color(vars::menur, vars::menug,vars::menub, menut));

				this->DrawButton(x + 280, y + 41, "Enabled", 0, snipera);
				this->addTickSlider(x + 280, y + 41, "Key", 1, 999, 0, sniperkey);
				this->DrawButton(x + 280, y + 41, "Head Only", 2, sniperh);

				this->DrawSlider(x + 350, y + 36, 180, -1, 100, sniperd, "Triggerbot Delay", 11, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 350, y + 39, 180, -1, 100, sniperc, "Triggerbot Cooldown", 12, Color(vars::menur, vars::menug,vars::menub, menut));
				static bool roflx = false;
				this->DrawDropdown(x + 140, y + 41, 60, 16, 3, sniper_aamode, "Mode", CoolDropDon, 6, roflx);
			}
			else if (vars::currentconfig == 4) {
				/*smg*/
				this->DrawButton(x + 140, y + 41, "Enabled", 0, smg_active);
				this->addTickSlider(x + 140, y + 41, "Key", 1, 999, 0, smg_aimkey);
				this->DrawButton(x + 140, y + 41, "Silent", 3, smg_psilent);
				//this->DrawButton(x + 420, y + 41, "Curvature", 3, smg_curve);
				this->DrawButton(x + 140, y + 41, "Enabled", 5, smg_aactive);
				this->DrawButton(x + 280, y + 41, "Enabled", 4,    smg_e);
				this->DrawButton(x + 280, y + 41, "Randomize", 5,  smg_r);
				this->DrawButton(x + 280, y + 41, "Delayed", 6, smg_s);
				if (smg_bone == 0 || smg_bone == 1) {
					vars::aim_boner = 8;
				}
				else if (smg_bone == 2) {
					vars::aim_boner = 7;
				}
				else if (smg_bone == 3) {
					vars::aim_boner = 6;
				}
				else if (smg_bone == 4) {
					vars::aim_boner = 5;
				}
				else if (smg_bone == 5) {
					vars::aim_boner = 0;
				}
				this->DrawDropdown(x + 140, y + 41/*57*/, 60, 16, 6, smg_bone, "Hitbox", BonesLejit, 2, vars::dropdown15);
				this->DrawSlider(x + 140, y + 30, 180, -1, 20, smg_fov, "Aimbot FOV", 9, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 140, y + 33, 180, 1, 30,smg_smoothx, "Aimbot X Smoothness", 10, Color(vars::menur, vars::menug, vars::menub, menut));
				this->DrawSlider(x + 140, y + 36, 180, 1, 30,smg_smoothy, "Aimbot Y Smoothness", 11, Color(vars::menur, vars::menug, vars::menub, menut));
				this->DrawSlider(x + 140, y + 39, 180, -5, 500, smg_aimtime, "Aimbot Time", 12, Color(vars::menur, vars::menug,vars::menub, menut));
				if (smg_aimtime == 2)
					smg_aimtime = 0;
				this->DrawSlider(x + 350, y + 30, 180, -1, 150, smg_float_x, "RCS X Amount", 9, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 350, y + 33, 180, -1, 150, smg_float_y, "RCS Y Amount", 10, Color(vars::menur, vars::menug,vars::menub, menut));

				this->DrawButton(x + 280, y + 41, "Enabled", 0, smga);
				this->addTickSlider(x + 280, y + 41, "Key", 1, 999, 0, smgkey);
				this->DrawButton(x + 280, y + 41, "Head Only", 2, smgh);

				this->DrawSlider(x + 350, y + 36, 180, -1, 100, smgd, "Triggerbot Delay", 11, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 350, y + 39, 180, -1, 100, smgc, "Triggerbot Cooldown", 12, Color(vars::menur, vars::menug,vars::menub, menut));
				static bool roflx = false;
				this->DrawDropdown(x + 140, y + 41, 60, 16, 3, smg_aamode, "Mode", CoolDropDon, 6, roflx);
			}
			else if (vars::currentconfig == 5) {
				/*heavy*/
				this->DrawButton(x + 140, y + 41, "Enabled", 0, heavy_active);
				this->addTickSlider(x + 140, y + 41, "Key", 1, 999, 0, heavy_aimkey);
				this->DrawButton(x + 140, y + 41, "Silent", 3, heavy_psilent);
				this->DrawButton(x + 140, y + 41, "Enabled", 5, heavy_aactive);
				this->DrawButton(x + 280, y + 41, "Enabled", 4,   heavy_e);
				this->DrawButton(x + 280, y + 41, "Randomize", 5, heavy_r);
				this->DrawButton(x + 280, y + 41, "Delayed", 6,heavy_s);

				if (heavy_bone == 0 || heavy_bone == 1) {
					vars::aim_boner = 8;
				}
				else if (heavy_bone == 2) {
					vars::aim_boner = 7;
				}
				else if (heavy_bone == 3) {
					vars::aim_boner = 6;
				}
				else if (heavy_bone == 4) {
					vars::aim_boner = 5;
				}
				else if (heavy_bone == 5) {
					vars::aim_boner = 0;
				}
				this->DrawDropdown(x + 140, y + 41/*57*/, 60, 16, 6, heavy_bone, "Hitbox", BonesLejit, 2, vars::dropdown15);
				this->DrawSlider(x + 140, y + 30, 180, -1, 20, heavy_fov, "Aimbot FOV", 9, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 140, y + 33, 180, 1, 30, heavy_smoothx, "Aimbot X Smoothness", 10, Color(vars::menur, vars::menug, vars::menub, menut));
				this->DrawSlider(x + 140, y + 36, 180, 1, 30, heavy_smoothy, "Aimbot Y Smoothness", 11, Color(vars::menur, vars::menug, vars::menub, menut));
			
			
				this->DrawSlider(x + 140, y + 39, 180, -5, 500, heavy_aimtime, "Aimbot Time", 12, Color(vars::menur, vars::menug,vars::menub, menut));
				if (heavy_aimtime == 2)
					heavy_aimtime = 0;
				this->DrawSlider(x + 350, y + 30, 180, -1, 150, heavy_float_x, "RCS X Amount", 9, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 350, y + 33, 180, -1, 150, heavy_float_y, "RCS Y Amount", 10, Color(vars::menur, vars::menug,vars::menub, menut));


				this->DrawButton(x + 280, y + 41, "Enabled", 0, heavya);
				this->addTickSlider(x + 280, y + 41, "Key", 1, 999, 0, heavykey);
				this->DrawButton(x + 280, y + 41, "Head Only", 2, heavyh);

				this->DrawSlider(x + 350, y + 36, 180, -1, 100, heavyd, "Triggerbot Delay", 11, Color(vars::menur, vars::menug,vars::menub, menut));
				this->DrawSlider(x + 350, y + 39, 180, -1, 100, heavyc, "Triggerbot Cooldown", 12, Color(vars::menur, vars::menug,vars::menub, menut));
				static bool roflx = false;
				this->DrawDropdown(x + 140, y + 41, 60, 16, 3, heavy_aamode, "Mode", CoolDropDon, 6, roflx);
			}
		}

	
	}

	//rage
	if (Settings::iTab == 1) {
		this->DrawString(x + 140, y + 21, Color(255, 255, 255, menut), labelFont, "Aimbot");
		this->DrawString(x + 280, y + 21, Color(255, 255, 255, menut), labelFont, "Auto");
		this->DrawString(x + 420, y + 21, Color(255, 255, 255, menut), labelFont, "Anti-Aim");
		this->DrawButton(x + 140, y + 41, "Enabled", 0, vars::rage_active);
		//this->DrawButton(x + 140, y + 41, "Hitscan", 2, vars::rage_hitscan);
		this->DrawButton(x + 140, y + 41, "Silent", 3, vars::rage_psilent);
		this->DrawButton(x + 140, y + 41, "AWP Body", 6, vars::rage_awpbody);
		this->DrawButton(x + 140, y + 41, "Remove Recoil", 2, vars::aim_recoil);
		//this->DrawButton(x + 140, y + 41, "Remove Spread", 6, vars::rage_nospread);
		//this->DrawButton(x + 140, y + 41, "Resolve All", 6, vars::resolvemyass);
		static bool resDropw = false;
		
	
		this->DrawSlider(x + 140, y + 30, 390, 1, 100, vars::aim_awall_factor, "Minimum Damage", 9, Color(vars::menur, vars::menug,vars::menub, menut)); //Color(195, 144, 212, 255)
		this->DrawSlider(x + 140, y + 33, 390, 0.f, 180, vars::aim_fov, "FOV", 10, Color(vars::menur, vars::menug,vars::menub, menut));

		this->DrawSlider(x + 140, y + 36, 390, 0, 100, vars::aim_hitchanceF, "Hitchance", 11, Color(vars::menur, vars::menug,vars::menub, menut));

		this->DrawSlider(x + 140, y + 39, 390, -1, 180, vars::pred_tick, "Fake Angle", 12, Color(vars::menur, vars::menug,vars::menub, menut));

	

		this->DrawButton(x + 280, y + 41, "Autoshoot", 0, vars::rage_autoshoot);
		this->DrawButton(x + 280, y + 41, "Autopistol", 1, vars::rage_autopistol);
		this->DrawButton(x + 280, y + 41, "Autoscope", 2, vars::rage_autoscope);
		this->DrawButton(x + 280, y + 41, "Autoduck", 3, vars::rage_autocrouch);
		this->DrawButton(x + 280, y + 41, "Autostop", 4, vars::rage_autostop);
		this->DrawButton(x + 280, y + 41, "Autowall", 5, vars::rage_awall);
		this->DrawButton(x + 280, y + 41, "Autorest", 6, vars::autorest);
		
		this->DrawButton(x + 420, y + 41, "Fake", 3, vars::aa_fake);
		this->DrawButton(x + 420, y + 41, "At Targets", 4, vars::aa_at_target);
	
		this->DrawButton(x + 420, y + 41, "Overturn", 5, vars::antires);
		this->DrawButton(x + 420, y + 41, "Dynamic", 6, vars::dynamicaa);
		static bool carufha = false;
		if (!vars::dropdown1)
			this->DrawDropdown(x + 420, y + 41, 60, 16, 5, vars::misc_edge, "", EDGEZ, 2, carufha);
		if (!vars::dropdown12) {
			this->DrawDropdown(x + 420, y + 41, 60, 16, 5, vars::misc_edge, "", EDGEZ, 2, carufha);
			this->DrawDropdown(x + 420, y + 41, 60, 16, 7, vars::misc_yaw, "", YAW, 1, vars::dropdown1);
			
		}
	

		this->DrawDropdown(x + 420, y + 41, 60, 16, 5, vars::misc_pitch, "Pitch", PITCH, 0, vars::dropdown12);
		

		this->DrawString(x + 420 + 60 + 2, y + 41 + 20, Color(255, 255, 255, menut), labelFont, "Yaw");
		this->DrawString(x + 420 + 60 + 2, y + 41 + 40, Color(255, 255, 255, menut), labelFont, "Edge");
		this->DrawDropdown(x + 140, y + 41, 60, 16, 6, vars::aim_bone1, "Hitbox", Bones, 1, vars::dropdown10);
		if (vars::aim_bone1 == 0 || vars::aim_bone1 == 1) {
			vars::aim_bone = 8;
		}
		else if (vars::aim_bone1 == 2) {
			vars::aim_bone = 7;
		}
		else if (vars::aim_bone1 == 3) {
			vars::aim_bone = 6;
		}
		else if (vars::aim_bone1 == 4) {
			vars::aim_bone = 5;
		}
		else if (vars::aim_bone1 == 5) {
			vars::aim_bone = 0;
		}
		if (!vars::dropdown10)
			this->DrawDropdown(x + 140, y + 41, 60, 16, 5, vars::hsMode, "", Modess, 4, hitscenlel);


		this->DrawString(x + 140 + 60 + 2, y + 41 + 80, Color(255, 255, 255, menut), labelFont, "Hitscan");

		if (!hitscenlel)
			this->DrawDropdown(x + 140, y + 41, 60, 16, 4, vars::resolvemyass, "", Resolver, 5, resDropw);
		this->DrawString(x + 140 + 60 + 2, y + 41 + 100, Color(255, 255, 255, menut), labelFont, "Resolver");

	}


	// visuals
	if (Settings::iTab == 2) {
		this->DrawString(x + 140, y + 21, Color(255, 255, 255, menut), labelFont, "ESP");
		this->DrawString(x + 280, y + 21, Color(255, 255, 255, menut), labelFont, "Models");
		this->DrawString(x + 280, y + 21 + (5 * 20), Color(255, 255, 255, menut), labelFont, "Removals");
		this->DrawString(x + 280, y + 21 + (8 * 20), Color(255, 255, 255, menut), labelFont, "Hotkeys");
		this->DrawString(x + 420, y + 21 + (4 * 20), Color(255, 255, 255, menut), labelFont, "Other");
		this->DrawString(x + 420, y + 21, Color(255, 255, 255, menut), labelFont, "Menu");
		this->DrawButton(x + 140, y + 41, "Enabled", 0, vars::esp_active);
		this->DrawButton(x + 140, y + 41, "Box", 1, vars::esp_box);
		this->DrawButton(x + 140, y + 41, "Name", 3, vars::esp_name);
		this->DrawButton(x + 140, y + 41, "Health", 4, vars::esp_healthbar);
		this->DrawButton(x + 140, y + 41, "Skeleton", 6, vars::esp_skeleton);
		this->DrawButton(x + 140, y + 41, "Visible Only", 7, vars::visonly);
		this->DrawButton(x + 140, y + 41, "Aim Trace", 8, vars::bullettrace);
		this->DrawButton(x + 140, y + 41, "Enemies Only", 9, vars::esp_ignore);

		
		this->DrawButton(x + 420, y + 41, "Title Animation", 0, vars::dynText);
		this->DrawButton(x + 420, y + 41, "Bar Animation", 1, vars::baranim);

		static bool n34r = false;

		this->DrawButton(x + 420, y + 41, "World", 4, vars::espworld);
		
		this->DrawButton(x + 420, y + 41, "Watermark", 5, vars::misc_watermarks);
		this->DrawButton(x + 420, y + 41, "Local Time", 6, vars::misc_time);
		this->DrawButton(x + 420, y + 41, "Crosshair", 7, vars::esp_crosshair);

		this->DrawButton(x + 420, y + 41, "Velocity Bar", 8, vars::velocitybar);
		this->DrawButton(x + 420, y + 41, "Radar", 9, vars::radar);
	
		this->DrawButton(x + 280, y + 41, "Enemies Only", 1, vars::chams_enemies);
	
		this->DrawButton(x + 280, y + 41, "Remove Shake", 5, vars::misc_novisrecoil);
		this->DrawButton(x + 280, y + 41, "Remove Flash", 6, vars::noflash);

		this->DrawButton(x + 280, y + 41, "ESP On Key", 8, vars::onkey);
		this->addTickSlider(x + 280, y + 41, "Key", 9, 999, 0, vars::espKey);


		if (!niggar) {
			this->DrawDropdown(x + 280, y + 41, 60, 16, 5, vars::wpn_chams, "", weaponz, 3, gaschamber);
		}
		
			//this->DrawDropdown(x + 280, y + 41, 80, 16, 5, vars::wpn_chams, "Weapons", weaponz, 2, gaschamber);
		this->DrawDropdown(x + 280, y + 41,60, 16, 5, vars::esp_hands, "", handz, 2, niggar);
			
		
		
		this->DrawString(x + 280 + 60 + 2, y + 41, Color(255, 255, 255, menut), labelFont, "Chams");
		
		this->DrawString(x + 280 + 60 + 2, y + 81, Color(255, 255, 255, menut), labelFont, "Hands");
		this->DrawString(x + 280 + 60 + 2, y + 101, Color(255, 255, 255, menut), labelFont, "Weapons");
		this->DrawDropdown(x + 280, y + 41, 60, 16, 4, vars::chamselect, "", Chamz, 0, jew);
		
		static bool mama = false;
		this->DrawDropdown(x + 420, y + 41, 60, 16, 5, vars::MenuDrop, "Animation", XROFL, 2, mama);

		
		this->DrawDropdown(x + 140, y + 41, 60, 16, 4, vars::esp_weapons, "Weapons", yuh, 5, kankerneger);
		this->DrawDropdown(x + 140, y + 41, 60, 16, 4, vars::esp_boxstyle, "Style", ESPBoxStyles, 2, vars::dropdown3);
		this->DrawSlider(x + 140, y + 36, 390, 0, 30, vars::esp_chsize, "Crosshair Size", 11, Color(vars::menur, vars::menug, vars::menub, menut));
		this->DrawSlider(x + 140, y + 39, 390, -1, 350, Settings::radarsize, "Radar Size", 12, Color(vars::menur, vars::menug, vars::menub, menut));
	}
	
	//misc
	if (Settings::iTab == 3) {
		this->DrawString(x + 140, y + 21, Color(255, 255, 255, menut), labelFont, "Misc");
		this->DrawString(x + 420, y + 21, Color(255, 255, 255, menut), labelFont, "Display");
		this->DrawString(x + 420, y + 21 + (5 * 20), Color(255, 255, 255, menut), labelFont, "Fakelag");
		this->DrawString(x + 280, y + 21, Color(255, 255, 255, menut), labelFont, "Fun");
		// movement
		this->DrawButton(x + 140, y + 41, "Fakewalk", 0, vars::misc_fakewalk);
		this->addTickSlider(x + 140, y + 41, "Key", 1, 999, 0, vars::misc_fakewalkkey);
		this->DrawButton(x + 140, y + 41, "Bunny Hop", 2, vars::misc_bhop);
		this->DrawButton(x + 140, y + 41, "Airstrafe", 3, vars::misc_autostrafe);
		
		
		//preferances
		
		this->DrawButton(x + 140, y + 41, "Thirdperson", 6, vars::misc_thirdperson);
		this->DrawButton(x + 140, y + 41, "SpecList", 7, vars::misc_ragespecvision);

		//display
		this->DrawButton(x + 420, y + 41, "Chatspam", 1, vars::misc_chatspam);
		this->DrawButton(x + 420, y + 41, "Namespam", 2, vars::misc_namechange);
		//this->DrawButton(x + 420, y + 41, "Round Say", 3, vars::misc_roundsay);
		this->DrawButton(x + 420, y + 41, "Kill Notification", 3, vars::misc_killnotification);
		
		//fakelag
		this->DrawButton(x + 420, y + 41, "In Air Only", 6, vars::inair);

		//fun
		this->DrawButton(x + 280, y + 41, "Airstuck", 0, vars::misc_airstuck);
		this->addTickSlider(x + 280, y + 41, "Key", 1, 999, 0, vars::misc_airstuckey);
		this->DrawButton(x + 280, y + 41, "Moonwalk", 2, vars::moonwalk);
		this->DrawButton(x + 280, y + 41, "Doorspam", 3, vars::doorspam);
		this->addTickSlider(x + 280, y + 41, "Key", 4, 999, 0, vars::spamKey);
		this->DrawButton(x + 280, y + 41, "Headglitch", 5, vars::headfix);
		this->DrawButton(x + 280, y + 41, "AutoAccept", 6, vars::autoaccept);


		// sliders
		this->DrawSlider(x + 140, y + 30, 390, 90, 150, vars::misc_fovfactor, "FOV Slider", 9, Color(vars::menur, vars::menug,vars::menub, menut));
		this->DrawSlider(x + 140, y + 33, 390, -1, 10, vars::misc_fakelag, "Fakelag", 10, Color(vars::menur, vars::menug,vars::menub, menut));
		this->DrawSlider(x + 140, y + 36, 390, -1, 300, vars::minvel, "Bunny Hop Minimum Velocity", 11, Color(vars::menur, vars::menug,vars::menub, menut));
		this->DrawSlider(x + 140, y + 39, 390, -1, 180, vars::randmizeXd, "Headglitch Angle", 12, Color(vars::menur, vars::menug, vars::menub, menut));


		

		///dropdowns
		this->DrawDropdown(x + 420, y + 41, 60, 16, 6, vars::misc_clantag, "Clantag", Clantag, 0, vars::dropdown19);
		static bool nigerunge = false;
		if (!fovezzz)
			this->DrawDropdown(x + 140, y + 41, 60, 16, 4, vars::misc_knife, "", knifer, 5, nigerunge);
		this->DrawString(x + 140 + 62, y + 41 + (20 * 5), Color(255, 255, 255, menut), labelFont, "Knife");
		this->DrawDropdown(x + 140, y + 41, 60, 16, 4, vars::misc_fovchange, "FOV", fovez, 4, fovezzz);
		static bool opene = false;
		this->DrawDropdown(x + 420, y + 41, 60, 16, 4, vars::flagMode, "Mode", fakelage, 5, opene);
		
		

		

	}
	if (Settings::iTab == 4) {
		/*
		"CT ESP",
		"CT ESP",
		"T ESP",
		"CT Chams"
		"T Chams",
		"Other"
		*/
		this->DrawString(x + 140, y + 21, Color(255, 255, 255, menut), labelFont, "Colors");
	
		if (vars::esp_select == 0 || vars::esp_select == 1) {
			this->DrawString(x + 140, y + 52 - 7, Color(255, 255, 255, menut), labelFont, "Terrorists");
			this->DrawSlider(x + 140, y + 30, 180, -3, 255, vars::esp_t_r, "Red", 2, Color(vars::esp_t_r, vars::esp_t_g, vars::esp_t_b, menut));
			this->DrawSlider(x + 140, y + 33, 180, -3, 255, vars::esp_t_g, "Green", 3, Color(vars::esp_t_r, vars::esp_t_g, vars::esp_t_b, menut));
			this->DrawSlider(x + 140, y + 36, 180, -3, 255, vars::esp_t_b, "Blue", 4, Color(vars::esp_t_r, vars::esp_t_g, vars::esp_t_b, menut));
														 
			this->DrawSlider(x + 350, y + 30, 180, -3, 255, vars::esp_t_visible_r, "Visible Red", 2, Color(vars::esp_t_visible_r, vars::esp_t_visible_g, vars::esp_t_visible_b, menut));
			this->DrawSlider(x + 350, y + 33, 180, -3, 255, vars::esp_t_visible_g, "Visible Green", 3, Color(vars::esp_t_visible_r, vars::esp_t_visible_g, vars::esp_t_visible_b, menut));
			this->DrawSlider(x + 350, y + 36, 180, -3, 255, vars::esp_t_visible_b, "Visible Blue", 4, Color(vars::esp_t_visible_r, vars::esp_t_visible_g, vars::esp_t_visible_b, menut));
			if (menut >= 255)
				this->DrawSlider(x + 140, y + 39, 390, -1, 100, vars::t_transparency, "Transparency", 5, Color(255, 255, 255, vars::t_transparency * 2.55f));
			else
				this->DrawSlider(x + 140, y + 39, 390, -1, 100, vars::t_transparency, "Transparency", 5, Color(255, 255, 255, menut));

			this->DrawString(x + 140, y + 161 - 7, Color(255, 255, 255, menut), labelFont, "Counter-Terrorists");

			this->DrawSlider(x + 140, y + 39, 180, -3, 255, vars::esp_ct_r, "Red", 7, Color(vars::esp_ct_r, vars::esp_ct_g, vars::esp_ct_b, menut));
			this->DrawSlider(x + 140, y + 42, 180, -3, 255, vars::esp_ct_g, "Green", 8, Color(vars::esp_ct_r, vars::esp_ct_g, vars::esp_ct_b, menut));
			this->DrawSlider(x + 140, y + 45, 180, -3, 255, vars::esp_ct_b, "Blue", 9, Color(vars::esp_ct_r, vars::esp_ct_g, vars::esp_ct_b, menut));
														 
			this->DrawSlider(x + 350, y + 39, 180, -3, 255, vars::esp_ct_visible_r, "Visible Red", 7, Color(vars::esp_ct_visible_r, vars::esp_ct_visible_g, vars::esp_ct_visible_b, menut));
			this->DrawSlider(x + 350, y + 42, 180, -3, 255, vars::esp_ct_visible_g, "Visible Green", 8, Color(vars::esp_ct_visible_r, vars::esp_ct_visible_g, vars::esp_ct_visible_b, menut));
			this->DrawSlider(x + 350, y + 45, 180, -3, 255, vars::esp_ct_visible_b, "Visible Blue", 9, Color(vars::esp_ct_visible_r, vars::esp_ct_visible_g, vars::esp_ct_visible_b, menut));

			if (menut >= 255)
				this->DrawSlider(x + 140, y + 48, 390, -1, 100, vars::ct_transparency, "Transparency", 10, Color(255, 255, 255, vars::ct_transparency * 2.55f));
			else
				this->DrawSlider(x + 140, y + 48, 390, -1, 100, vars::ct_transparency, "Transparency", 10, Color(255, 255, 255, menut));
		}
		else if (vars::esp_select == 2) {
			this->DrawString(x + 140, y + 52 - 7, Color(255, 255, 255, menut), labelFont, "Terrorists");
			this->DrawSlider(x + 140, y + 30, 180, -3, 255, vars::chams_t_r, "Red", 2, Color(vars::chams_t_r, vars::chams_t_g, vars::chams_t_b, menut));
			this->DrawSlider(x + 140, y + 33, 180, -3, 255, vars::chams_t_g, "Green", 3, Color(vars::chams_t_r, vars::chams_t_g, vars::chams_t_b, menut));
			this->DrawSlider(x + 140, y + 36, 180, -3, 255, vars::chams_t_b, "Blue", 4, Color(vars::chams_t_r, vars::chams_t_g, vars::chams_t_b, menut));
														 
			this->DrawSlider(x + 350, y + 30, 180, -3, 255, vars::chams_t_visible_r, "Visible Red", 2, Color(vars::chams_t_visible_r, vars::chams_t_visible_g, vars::chams_t_visible_b, menut));
			this->DrawSlider(x + 350, y + 33, 180, -3, 255, vars::chams_t_visible_g, "Visible Green", 3, Color(vars::chams_t_visible_r, vars::chams_t_visible_g, vars::chams_t_visible_b, menut));
			this->DrawSlider(x + 350, y + 36, 180, -3, 255, vars::chams_t_visible_b, "Visible Blue", 4, Color(vars::chams_t_visible_r, vars::chams_t_visible_g, vars::chams_t_visible_b, menut));
			if (menut >= 255)
				this->DrawSlider(x + 140, y + 39, 390, -1, 100, vars::chams_t_transparency, "Transparency", 5, Color(255, 255, 255, vars::chams_t_transparency * 2.55f));
			else
				this->DrawSlider(x + 140, y + 39, 390, -1, 100, vars::chams_t_transparency, "Transparency", 5, Color(255, 255, 255, menut));

			this->DrawString(x + 140, y + 161 - 7, Color(255, 255, 255, menut), labelFont, "Counter-Terrorists");

			this->DrawSlider(x + 140, y + 39, 180, -3, 255, vars::chams_ct_r, "Red", 7, Color(vars::chams_ct_r, vars::chams_ct_g, vars::chams_ct_b, menut));
			this->DrawSlider(x + 140, y + 42, 180, -3, 255, vars::chams_ct_g, "Green", 8, Color(vars::chams_ct_r, vars::chams_ct_g, vars::chams_ct_b, menut));
			this->DrawSlider(x + 140, y + 45, 180, -3, 255, vars::chams_ct_b, "Blue", 9, Color(vars::chams_ct_r, vars::chams_ct_g, vars::chams_ct_b, menut));
														 
			this->DrawSlider(x + 350, y + 39, 180, -3, 255, vars::chams_ct_visible_r, "Visible Red", 7, Color(vars::chams_ct_visible_r, vars::chams_ct_visible_g, vars::chams_ct_visible_b, menut));
			this->DrawSlider(x + 350, y + 42, 180, -3, 255, vars::chams_ct_visible_g, "Visible Green", 8, Color(vars::chams_ct_visible_r, vars::chams_ct_visible_g, vars::chams_ct_visible_b, menut));
			this->DrawSlider(x + 350, y + 45, 180, -3, 255, vars::chams_ct_visible_b, "Visible Blue", 9, Color(vars::chams_ct_visible_r, vars::chams_ct_visible_g, vars::chams_ct_visible_b, menut));
			if (menut >= 255)
				this->DrawSlider(x + 140, y + 48, 390, -1, 100, vars::chams_ct_transparency, "Transparency", 10, Color(255, 255, 255, vars::chams_ct_transparency * 2.55f));
			else
				this->DrawSlider(x + 140, y + 48, 390, -1, 100, vars::chams_ct_transparency, "Transparency", 10, Color(255, 255, 255, menut));
		}


		if (vars::esp_select == 3) {
			this->DrawString(x + 140, y + 52 - 7, Color(255, 255, 255, menut), labelFont, "Weapons");
			this->DrawString(x + 350, y + 52 - 7, Color(255, 255, 255, menut), labelFont, "Hands");
			this->DrawSlider(x + 140, y + 30, 180, -3, 255, vars::weaponR, "Red", 2, Color(vars::weaponR, vars::weaponG, vars::weaponB, menut));
			this->DrawSlider(x + 140, y + 33, 180, -3, 255, vars::weaponG, "Green", 3, Color(vars::weaponR, vars::weaponG, vars::weaponB, menut));
			this->DrawSlider(x + 140, y + 36, 180, -3, 255, vars::weaponB, "Blue", 4, Color(vars::weaponR, vars::weaponG, vars::weaponB, menut));
			
			if (menut >= 255)
				this->DrawSlider(x + 140, y + 39, 180, -1, 100, vars::weapons_transparency, "Transparency", 5, Color(255, 255, 255, vars::weapons_transparency * 2.55f));
			else
				this->DrawSlider(x + 140, y + 39, 180, -1, 100, vars::weapons_transparency, "Transparency", 5, Color(255, 255, 255, menut));

			this->DrawSlider(x + 350, y + 30, 180, -3, 255, vars::handsr, "Hands Red", 2, Color(vars::handsr, vars::handsg, vars::handsb, menut));
			this->DrawSlider(x + 350, y + 33, 180, -3, 255, vars::handsg, "Hands Green", 3, Color(vars::handsr, vars::handsg, vars::handsb, menut));
			this->DrawSlider(x + 350, y + 36, 180, -3, 255, vars::handsb, "Hands Blue", 4, Color(vars::handsr, vars::handsg, vars::handsb, menut));
			if (menut >= 255)
				this->DrawSlider(x + 350, y + 39, 180, -1, 100, vars::hands_transparency, "Transparency", 5, Color(255, 255, 255, vars::hands_transparency * 2.55f));
			else
				this->DrawSlider(x + 350, y + 39, 180, -1, 100, vars::hands_transparency, "Transparency", 5, Color(255, 255, 255, menut));

			this->DrawString(x + 140, y + 161 - 7, Color(255, 255, 255, menut), labelFont, "Menu");

			this->DrawSlider(x + 140, y + 39, 390, -3, 255, vars::menur, "Red", 7, Color(vars::menur, vars::menug, vars::menub, menut));
			this->DrawSlider(x + 140, y + 42, 390, -3, 255, vars::menug, "Green", 8, Color(vars::menur, vars::menug, vars::menub, menut));
			this->DrawSlider(x + 140, y + 45, 390, -3, 255, vars::menub, "Blue", 9, Color(vars::menur, vars::menug, vars::menub, menut));
			this->DrawSlider(x + 140, y + 48, 390, -1, 20, vars::removeTrns, "Subtract Transparency", 10, Color(vars::menur, vars::menug, vars::menub, menut));

		}
		this->DrawDropdown(x + 140, y + 48, 100, 16, 4, vars::esp_select, "Selection", ColorSelections, 11, vars::dropdown14);

	}
	if (Settings::iTab == 5) {
		this->DrawString(x + 140, y + 21, Color(255, 255, 255, menut), labelFont, "Player List");
		this->DrawPlayerList(x + 140, y + 41, 0, 0);
	}
	//skinchanger
	if (Settings::iTab == 6) {
		//skins

		this->DrawString(x + 140, y + 21, Color(255, 255, 255, 255), labelFont, "Skin Changer");
		this->DrawButton(x + 140, y + 41, "Enabled", 0, vars::skinchanger);
		this->addTickSlider(x + 140, y + 41, "Skin", 2, 999, 0, weaponskin);
		this->DrawDropdown(x + 140, y + 41, 80, 16, 34, vars::misc_skinchanger, "Skin", Weapons2, 1, niggor2);

		//knives

		this->DrawString(x + 280, y + 21, Color(255, 255, 255, 255), labelFont, "Knife Changer");
		this->DrawButton(x + 280, y + 41, "Enabled", 0, vars::knifechange);
		this->addTickSlider(x + 280, y + 41, "Skin",2, 999, 0, knifeskin);
		this->DrawDropdown(x + 280, y + 41, 80, 16, 12, vars::misc_knifechanger, "Knife", Knives, 1, niggor);
		
		//gloves

		this->DrawString(x + 420, y + 21, Color(255, 255, 255, 255), labelFont, "Glove Changer");
		this->DrawButton(x + 420, y + 41, "Enabled", 0, vars::glovechange);
		this->addTickSlider(x + 420, y + 41, "Skin", 2, 999, 0, gloveskin);
		this->DrawDropdown(x + 420, y + 41, 80, 16, 8, vars::misc_glovechanger, "Skin", Gloves, 1, niggor3);
	}


	MenuMovement(x, y, w, 20, 1);
}


extern kAZORDrawings* PKAZOR;
kAZORDrawings* PKAZOR = new kAZORDrawings();

class shinezFunctions {
public:
	// Hacks that even kids with 1.72IQ can use goes here.
};

class mbeAntiUntrust {
public:
	// Gay functions goes here.
};
