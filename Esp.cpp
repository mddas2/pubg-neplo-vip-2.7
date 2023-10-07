#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#pragma warning(disable : 4996)
//#include "api/KeyAuth.hpp"
#include "api/xorstr.hpp"
#include"SimpleIni.h"
#include<D3DX11tex.h>
#define LOADER_BRAND "Loader base"
#include "Esp.h"
#include <iostream>
#include <fstream>
#include "imguipp.h"
#include "Unicode.h"
#include "utf.h"
#include "Main.h"
#include "api/xor.h"
#include<direct.h>
#include <urlmon.h>    
#pragma comment(lib, "Urlmon")

using namespace std;

bool fight = true;
//char key[60] = "";
std::string str = "mddascorn";
bool login = true;
bool SaveUsers = true;
bool savekey = true;
bool loader_active = true;
D3DMATRIX Esp::ViewMatrix;
static bool Bot = true;
static bool Player = true;
std::string tim;
char str1[60] = "";
float overlaycolor = 0.0f;
int teamids;

ImVec4 linescolors;// = { 1.0f,1.0f,1.0f,1.0f };
ImVec4 bonescolors = { 1.0f,1.0f,1.0f,1.0f };
ImVec4 fullboxcolor;// = { 1.0f,1.0f,1.0f,1.0f };
ImVec4 cornerboxcolor;// = { 1.0f,1.0f,1.0f,1.0f };
ImVec4 whitecolr = { 1.0f,1.0f,1.0f,1.0f };
IDirect3DTexture9* logoS = nullptr;

ImVec4 blinescolors;
ImVec4 bbonescolors;
ImVec4 bfullboxcolor;
ImVec4 bcornerboxcolor;
bool driving = true;
ImColor col;
bool unload = false;

static auto Flags2 = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
static auto Flags21 = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
static auto Flags22 = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
namespace Settings
{
	static int Tab = 5;
}
bool watermark = true;
int currIndex;
float popcorn = 0.5f;
float popcorn2 = 0.450f;
ImVec4 colorr;
int Emu_Int = 0;
int item_current_Emu = 0;
int currentengine = 0;
int item_current_Aim = 0;
int skelesec = 0;
//  (DX11::pDevice, &logo, sizeof(logo), 462, 462, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &logggo);
ImVec4 to_vec4(float r, float g, float b, float a)
{
	return ImVec4(r / 255.0, g / 255.0, b / 255.0, a / 255.0);


}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
std::string GetCurrentDirectory()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}
inline bool FileExist(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
void Esp::LoadConfig(std::string Path) {
	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile(Path.c_str());
	//	if (rc < 0) { std::cout << "File not found"; };
	if (FileExist(Path))
	{
		bool State = ini.GetBoolValue("Key", "UserKeyState");
		if (State == true)
		{
			std::string Key = ini.GetValue("Key", "UserKey");
			if (Key != "")
			{
				strcpy(str1, Key.c_str());
				SaveUsers = true;
			}

		}

	}
	/* if (ini.GetValue("Key", "UserKey")=="123")
	 {

	 }*/
}


std::string ws2s(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

void WriteConfig(std::string Path, std::string Key, bool State) {
	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile(Path.c_str());
	if (rc < 0) {
		//	std::cout << "File not found";
	};
	if (State == true)
	{
		ini.SetBoolValue("Key", "UserKeyState", true);
	}
	else
	{
		ini.SetBoolValue("Key", "UserKeyState", false);
	}
	ini.SetValue("Key", "UserKey", Key.c_str());

	ini.SaveFile(Path.c_str());
}
float fround(float var)
{
	float value = (int)(var * 100 + .5);
	return (float)value / 100;
}
RGBA floattod3d(float Col[])
{
	RGBA ret = { 0 };
	ret.R = (Col[0] * 255);
	ret.G = (Col[1] * 255);
	ret.B = (Col[2] * 255);
	ret.A = (Col[3] * 255);
	return ret;
}

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}


void WriteResToDisk(std::string PathFile, LPWSTR File_WITHARG)
{
	HRSRC myResource = ::FindResource(NULL, File_WITHARG, RT_RCDATA);
	unsigned int myResourceSize = ::SizeofResource(NULL, myResource);
	HGLOBAL myResourceData = ::LoadResource(NULL, myResource);
	void* pMyExecutable = ::LockResource(myResourceData);
	std::ofstream f(PathFile, std::ios::out | std::ios::binary);
	f.write((char*)pMyExecutable, myResourceSize);
	f.close();
}
static void HelpMarkerQuestionMark(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
string ShowMenuTwo = "";

std::string wideToMultiByte(std::wstring const& wideString)
{
	std::string ret;
	std::string buff(MB_CUR_MAX, '\0');

	for (wchar_t const& wc : wideString)
	{
		int mbCharLen = std::wctomb(&buff[0], wc);

		if (mbCharLen < 1) { break; }

		for (int i = 0; i < mbCharLen; ++i)
		{
			ret += buff[i];
		}
	}

	return ret;
}

bool ProcessInlineHexColor(const char* start, const char* end, ImVec4& color)
{
	const int hexCount = (int)(end - start);
	if (hexCount == 6 || hexCount == 8)
	{
		char hex[9];
		strncpy(hex, start, hexCount);
		hex[hexCount] = 0;

		unsigned int hexColor = 0;
		if (sscanf(hex, "%x", &hexColor) > 0)
		{
			color.x = static_cast<float>((hexColor & 0x00FF0000) >> 16) / 255.0f;
			color.y = static_cast<float>((hexColor & 0x0000FF00) >> 8) / 255.0f;
			color.z = static_cast<float>((hexColor & 0x000000FF)) / 255.0f;
			color.w = 1.0f;

			if (hexCount == 8)
			{
				color.w = static_cast<float>((hexColor & 0xFF000000) >> 24) / 255.0f;
			}

			return true;
		}
	}

	return false;
}
///Settings
int nsize = 14;
static int skelee = 0;
static int linne = 0;
static int hpbt = 0;
static int boxe = 0;
static int aimbp = 0;
int dissize = 14;
int hp = 14;
int vehisize = 15;
bool marco1 = false;
bool nothingm = true;
bool nothinga = false;
const char ColorMarkerStart = '{';
const char ColorMarkerEnd = '}';
#pragma region Color
float m16[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float AKM[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float AWM[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float AWMimmo[] = { 0.942f, 0.300f, 0.073f, 1.000f };
float AirAttack[] = { 1.000f, 0.000f, 0.000f, 1.000f };
float scarl[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float m762[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float M24[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float GROZZA[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float scope8x[] = { 0.866f, 0.128f, 0.081f, 1.000f };
float kar98[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float Airdrop[] = { 0.279f, 0.990f, 0.812f, 1.000f };
float Flare[] = { 0.866f, 0.128f, 0.081f, 1.000f };
float Flaregun[] = { 1.0f, 0.60f,0.05f, 1.0f };

float dp[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float mg3[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float scope4x[] = { 0.937f, 0.063f, 0.937f, 1.000f };
float scope3x[] = { 0.874f, 0.484f, 0.106f, 1.000f };
float bag[] = { 0.529f, 0.127f, 0.903f, 1.000f };
float armer[] = { 0.591f, 1.000f, 0.237f, 1.000f };
float helmat[] = { 0.726f, 0.070f, 0.908f, 1.000f };
float mosin[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float aug[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float g36[] = { 0.671f, 0.217f, 1.000f, 1.000f };
float assm[] = { 1.000f, 0.217f, 0.762f, 1.000f };
float Grandes[] = { 1.000f, 0.396f, 0.357f, 1.000f };
float ammo7[] = { 0.984f, 0.871f, 0.043f, 1.000f };
float ammo5[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float madkit[] = { 0.952f, 0.558f, 0.129f, 1.000f };
float playerline[] = { 0.591f, 1.000f, 0.237f, 1.000f };
float playercorner[] = { 1.0f, 0.70f,0.30f, 1.0f };
float playerbox[] = { 1.0f, 1.0f,0.0f, 1.0f };
float lotbox[] = { 1.0f, 1.0f,0.0f, 1.0f };
// ARGB
float helthbar[] = { 0.950f, 0.125f, 0.125f, 1.0f };
float boxColor[] = { 0.950f, 0.125f, 0.125f, 1.0f };
float cornerColor[] = { 0.950f, 0.125f, 0.125f, 1.0f };
float crosshairColor[] = { 0.950f, 0.125f, 0.125f, 1.0f };
float bot[] = { 0.016f, 0.725f, 0.929f, 1.0f };
float player[] = { 0.950f, 0.125f, 0.125f, 1.0f };
float vehicle[] = { 1.000f, 1.000f, 0.000f, 1.000f };
//RGB
float botcorner[] = { 0.050f, 0.125f, 0.925f, 1.0f };
float botline[] = { 0.050f, 0.025f, 0.925f, 1.0f };
float circle[] = { 0.950f, 0.125f, 0.125f, 1.0f };
float enemy[] = { 255, 255, 255, 255 };
float botbox[] = { 0.950f, 0.125f, 0.925f, 1.0f };
float bone[] = { 0.950f, 0.125f, 0.125f, 1.0f };
float fillrect[] = { 0.950f, 0.125f, 0.125f, 1.0f };
float nam[] = { 1.000f, 1.000f, 0.000f, 1.000f };
float nambar[] = { 0.880f, 0.185f, 0.25f, 1.0f };
float bothealth[] = { 0.95f, 0.125f, 0.825f, 1.0f };
float botname[] = { 0.050f, 0.825f, 0.185f, 1.0f };
float playerhealth[] = { 0.50f, 0.725f, 0.105f, 1.0f };
float textcolor[] = { 0.500f, 0.150f, 0.125f, 1.0f };
float skelec[] = { 255, 255, 255, 255 };

float Granades[] = { 0.990f, 0.995f, 0.995f, 1.0f };
float health[] = { 0.108f, 1.000f, 1.000f, 1.000f };
float deadbox[] = { 0.737f, 1.000f, 0.000f, 1.000f };
float deadboxitem[] = { 1.000f, 0.100f, 0.401f, 1.000f };
float airdrop[] = { 1.000f, 0.695f, 0.323f, 1.000f };
float airdropitem[] = { 0.300f, 0.695f, 0.323f, 1.000f };
float scopetextcolor[] = { 0.000f, 0.995f, 0.995f, 1.000f };
float allitem[] = { 0.034f, 1.000f, 0.040f, 1.000f };
float scope6x[] = { 0.120f, 0.955f, 0.125f, 1.0f };
float botbone[] = { 0.050f, 0.025f, 0.925f, 1.0f };
float playerbone[] = { 0.986f, 0.952f, 0.209f, 1.000f };
float magicline[] = { 255, 0, 0, 255 };
float bgcorner[] = { 0.000f, 1.000f, 0.964f, 1.000f };
float fovcirclecolor[] = { 255, 0, 0, 255 };
float fovcirclecolorq[] = { 255, 0, 0, 255 };
float fovcirclecolors[] = { 255, 0, 0, 255 };
float fovcirclecolorw[] = { 255, 0, 0, 255 };

float weapont[] = { 255,255,0,255 };
float hpt[] = { 255, 255, 255, 255 };
float plancolor[] = { 0.737f, 1.000f, 0.000f, 1.000f };
float dotss[] = { 0.950f, 0.125f, 0.925f, 1.0f };
float Esp_Item_AKM_Color[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float M249[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float MK12[] = { 1.00f, 0.796f, 0.715f, 1.0f };

float Esp_Item_M762_Color[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float Esp_Item_Mk47Mutant_Color[] = { 1.00f, 0.76f, 0.15f, 1.0f };
float Esp_Item_DP28_Color[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float Esp_Item_SCARL_Color[] = { 0.00f, 1.0f, 0.0f, 1.0f };
float Esp_Item_M416_Color[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float Esp_Item_M16A4_Color[] = { 0.00f, 1.0f, 0.0f, 1.0f };
float Esp_Item_G36C_Color[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float Esp_Item_QBZ_Color[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float Esp_Item_QBU_Color[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float Esp_Item_SLR_Color[] = { 0.627f, 0.102f, 0.941f, 1.000f };
float Esp_Item_SKS_Color[] = { 0.627f, 0.102f, 0.941f, 1.000f };
float Esp_Item_Mini14_Color[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float Esp_Item_M24_Color[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float Esp_Item_Kar98k_Color[] = { 1.000f, 0.647f, 0.000f, 1.000f };
float Esp_Item_PP19_Color[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float Esp_Item_TommyGun_Color[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float Esp_Item_MP5K_Color[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float Esp_Item_UMP9_Color[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float Esp_Item_Vector_Color[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float Esp_Item_Uzi_Color[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float Esp_Item_762mm_Color[] = { 0.984f, 0.871f, 0.043f, 1.000f };
float Esp_Item_556mm_Color[] = { 0.000f, 1.000f, 0.318f, 1.000f };
float Esp_Item_9mm_Color[] = { 1.000f, 0.000f, 0.337f, 1.000f };
float Esp_Item_45ACP_Color[] = { 1.00f, 0.96f, 0.56f, 1.0f };
float Esp_Item_Holo_Color[] = { 0.000f, 0.682f, 1.000f, 1.000f };
float Esp_Item_x2_Color[] = { 0.000f, 0.682f, 1.000f, 1.000f };
float Esp_Item_x3_Color[] = { 0.000f, 0.682f, 1.000f, 1.000f };
float Esp_Item_x4_Color[] = { 0.000f, 0.682f, 1.000f, 1.000f };

float Esp_Item_x6_Color[] = { 1.000f, 0.000f, 0.000f, 1.000f };

float Esp_Item_x8_Color[] = { 1.000f, 0.000f, 0.000f, 1.000f };

float Esp_Item_Bag1_Color[] = { 0.000f, 0.682f, 1.000f, 1.000f };

float Esp_Item_Bag2_Color[] = { 0.627f, 0.102f, 0.941f, 1.000f };

float Esp_Item_Bag3_Color[] = { 1.000f, 0.647f, 0.000f, 1.000f };

float Esp_Item_Armor1_Color[] = { 0.000f, 0.682f, 1.000f, 1.000f };

float Esp_Item_Armor2_Color[] = { 0.627f, 0.102f, 0.941f, 1.000f };

float Esp_Item_Armor3_Color[] = { 1.000f, 0.647f, 0.000f, 1.000f };

float Esp_Item_Helmet1_Color[] = { 0.000f, 0.682f, 1.000f, 1.000f };

float Esp_Item_Helmet2_Color[] = { 0.627f, 0.102f, 0.941f, 1.000f };

float Esp_Item_Helmet3_Color[] = { 1.000f, 0.647f, 0.000f, 1.000f };

float Esp_Item_Frag_Color[] = { 1.000f, 1.000f, 0.000f, 1.000f };

float Esp_Item_Smoke_Color[] = { 1.000f, 1.000f, 0.000f, 1.000f };

float Esp_Item_Molotof_Color[] = { 1.000f, 1.000f, 0.000f, 1.000f };

float Esp_Item_MedKit_Color[] = { 1.000f, 0.753f, 0.796f, 1.000f };

float Esp_Item_FirstAidKit_Color[] = { 1.000f, 0.753f, 0.796f, 1.000f };

float Esp_Item_Painkiller_Color[] = { 1.000f, 0.753f, 0.796f, 1.000f };

float Esp_Item_EnergyDrink_Color[] = { 1.000f, 0.753f, 0.796f, 1.000f };

float Esp_Item_AdrenalineSyringe_Color[] = { 1.000f, 0.753f, 0.796f, 1.000f };

float Esp_Item_FlareGun_Color[] = { 1.000f, 0.000f, 0.000f, 1.000f };

float Esp_Item_Flare_Color[] = { 1.000f, 0.000f, 0.000f, 1.000f };

float Esp_Item_AirDrop_Color[] = { 1.000f, 0.647f, 0.000f, 1.000f };

#pragma endregion

#pragma region fount size
int AWMS = 15;
int M416S = 15;
int SCARS = 15;
int M762S = 15;
int KARS = 15;
int VECTORS = 15;
int UZIS = 15;
int UMP9S = 15;
int SKSS = 15;
int QBZS = 15;
int QBUS = 15;
int PPS = 15;
int SLRS = 15;
int TOMMYS = 15;
int MP5KS = 15;
int M249s = 15;
int MINIS = 15;
int M24S = 15;
int MK47S = 15;
int DPS = 15;
int G36CS = 15;
int AUGS = 15;
int AKMS = 15;
int Bag3S = 15;
int Helmet3S = 15;
int FLARES = 15;
int FLAREGS = 15;
int Armor3S = 15;
int MK12S = 15;
int M249S = 15;
int Armor2S = 15;
int Armor1S = 15;
int Helmet2S = 15;
int Helmet1S = 15;
int M16A4S = 15;
int HOLOS = 15;
int Bag2S = 15;
int Bag1S = 15;
int AMO9S = 15;
int AMO7S = 15;
int AMO5S = 15;
int AMO45S = 15;
int AMO300S = 15;
int SCOPE2S = 15;
int SCOPE3S = 15;
int SCOPE4S = 15;
int SCOPE6S = 15;
int SCOPE8S = 15;
int PAINS = 15;
int MEDS = 15;
int FIRSTS = 15;
int ADRES = 15;
int ENRES = 15;
int SMOKES = 15;
int MOLOS = 15;
int FRAGS = 15;



#pragma endregion

#pragma region font size Attchment
static int BP_QK_Choke_Pickup_C_1s = 15;
static int BP_QK_Mid_Compensator_Pickup_C_1s = 15;
static int BP_QK_Sniper_Compensator_Pickup_C_1s = 15;
static int BP_QK_Mid_FlashHider_Pickup_C_1s = 15;
static int BP_QK_Sniper_FlashHider_Pickup_C_1s = 15;
static int BP_QK_Mid_Suppressor_Pickup_C_1s = 15;
static int BP_QK_Sniper_Suppressor_Pickup_C_1s = 15;
static int BP_QK_Large_Compensator_Pickup_C_1s = 15;
static int BP_QK_Large_FlashHider_Pickup_C_1s = 15;
static int BP_QK_Large_Suppressor_Pickup_C_1s = 15;
static int BP_QK_DuckBill_Pickup_C_1s = 15;
static int BP_WB_Angled_Pickup_C_1s = 15;
static int BP_WB_Vertical_Pickup_C_1s = 15;
static int BP_WB_LightGrip_Pickup_C_1s = 15;
static int BP_WB_HalfGrip_Pickup_C_1s = 15;
static int BP_WB_ThumbGrip_Pickup_C_1s = 15;
static int BP_WB_Lasersight_Pickup_C_1s = 15;
static int BP_MZJ_HD_Pickup_C_1s = 15;
static int BP_MZJ_QX_Pickup_C_1s = 15;
static int BP_MZJ_SideRMR_Pickup_C_1s = 15;
static int BP_ZDD_Sniper_Pickup_C_1s = 15;
static int BP_QT_UZI_Pickup_C_1s = 15;
static int BP_QT_A_Pickup_C_1s = 15;
static int BP_QT_Sniper_Pickup_C_1s = 15;
static int BP_ZDD_Crossbow_Q_Pickup_C_1s = 15;
static int BP_DJ_Mid_E_Pickup_C_1s = 15;
static int BP_DJ_Mid_Q_Pickup_C_1s = 15;
static int BP_DJ_Mid_EQ_Pickup_C_1s = 15;
static int BP_DJ_Sniper_E_Pickup_C_1s = 15;
static int BP_DJ_Sniper_Q_Pickup_C_1s = 15;
static int BP_DJ_Sniper_EQ_Pickup_C_1s = 15;
static int BP_DJ_Large_E_Pickup_C_1s = 15;
static int BP_DJ_Large_Q_Pickup_C_1s = 15;
static int BP_DJ_Large_EQ_Pickup_C_1s = 15;
////////////////////////////////////////////
static int BP_Pistol_P92_Wrapper_C_1s = 15;
static int BP_Pistol_P1911_Wrapper_C_1s = 15;
static int BP_Pistol_R1895_Wrapper_C_1s = 15;
static int BP_Pistol_P18C_Wrapper_C_1s = 15;
static int BP_Pistol_R45_Wrapper_C_1s = 15;
static int BP_Pistol_Vz61_Wrapper_C_1s = 15;
static int BP_Pistol_DesertEagle_Wrapper_C_1s = 15;
static int BP_ShotGun_SawedOff_Wrapper_C_1s = 15;
//////////////////////////////////////////////
static int BP_ShotGun_S686_Wrapper_C_1s = 15;
static int BP_ShotGun_S1897_Wrapper_C_1s = 15;
static int BP_ShotGun_S12K_Wrapper_C_1s = 15;
static int BP_ShotGun_DP12_Wrapper_C_1s = 15;
static int BP_ShotGun_M1014_Wrapper_C_1s = 15;
/////////////////////////////////////////////
static int BP_WEP_Machete_Pickup_C_1s = 15;
static int BP_WEP_Cowbar_Pickup_C_1s = 15;
static int BP_WEP_Sickle_Pickup_C_1s = 15;
static int BP_WEP_Pan_Pickup_C_1s = 15;
////////////////////////////////////////////
static int BP_Sniper_VSS_Wrapper_C_1s = 15;
static int BP_WEP_Mk14_Pickup_C_1s = 15;
static int BP_Sniper_Win94_Wrapper_C_1s = 15;
static int BP_Sniper_QBU_Wrapper_C_1s = 15;
static int BP_Sniper_Mosin_Wrapper_C_1s = 15;
static int BP_Sniper_MK12_Wrapper_C_1s = 15;
#pragma endregion

#pragma region Attichment collors
float Esp_Item_Tokenf_Color[] = { 1.000f, 1.000f, 0.000f, 1.000f };
float BP_QK_Choke_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QK_Mid_Compensator_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QK_Sniper_Compensator_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QK_Mid_FlashHider_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QK_Sniper_FlashHider_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QK_Mid_Suppressor_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QK_Sniper_Suppressor_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QK_Large_Compensator_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QK_Large_FlashHider_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QK_Large_Suppressor_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QK_DuckBill_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_WB_Angled_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_WB_Vertical_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_WB_LightGrip_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_WB_HalfGrip_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_WB_ThumbGrip_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_WB_Lasersight_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_MZJ_HD_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_MZJ_QX_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_MZJ_SideRMR_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_ZDD_Sniper_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QT_UZI_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QT_A_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_QT_Sniper_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_ZDD_Crossbow_Q_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_DJ_Mid_E_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_DJ_Mid_Q_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_DJ_Mid_EQ_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_DJ_Sniper_E_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_DJ_Sniper_Q_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_DJ_Sniper_EQ_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_DJ_Large_E_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_DJ_Large_Q_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_DJ_Large_EQ_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
///////////////////////////////////////////////////////////////
float BP_Pistol_P92_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_Pistol_P1911_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_Pistol_R1895_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_Pistol_P18C_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_Pistol_R45_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_Pistol_Vz61_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_Pistol_DesertEagle_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_ShotGun_SawedOff_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_ShotGun_S686_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_ShotGun_S1897_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_ShotGun_S12K_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_ShotGun_DP12_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_ShotGun_M1014_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_WEP_Machete_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_WEP_Cowbar_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_WEP_Sickle_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_WEP_Pan_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_Sniper_VSS_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_WEP_Mk14_Pickup_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_Sniper_Win94_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_Sniper_QBU_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_Sniper_Mosin_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };
float BP_Sniper_MK12_Wrapper_C_1[] = { 1.0f, 0.60f,0.05f, 1.0f };




#pragma endregion

void TextWithColors(const char* fmt, ...)
{
	char tempStr[4096];

	va_list argPtr;
	va_start(argPtr, fmt);
	_vsnprintf(tempStr, sizeof(tempStr), fmt, argPtr);
	va_end(argPtr);
	tempStr[sizeof(tempStr) - 1] = '\0';

	bool pushedColorStyle = false;
	const char* textStart = tempStr;
	const char* textCur = tempStr;
	while (textCur < (tempStr + sizeof(tempStr)) && *textCur != '\0')
	{
		if (*textCur == ColorMarkerStart)
		{
			// Print accumulated text
			if (textCur != textStart)
			{
				ImGui::TextUnformatted(textStart, textCur);
				ImGui::SameLine(0.0f, 0.0f);
			}

			// Process color code
			const char* colorStart = textCur + 1;
			do
			{
				++textCur;
			} while (*textCur != '\0' && *textCur != ColorMarkerEnd);

			// Change color
			if (pushedColorStyle)
			{
				ImGui::PopStyleColor();
				pushedColorStyle = false;
			}

			ImVec4 textColor;
			if (ProcessInlineHexColor(colorStart, textCur, textColor))
			{
				ImGui::PushStyleColor(ImGuiCol_Text, textColor);
				pushedColorStyle = true;
			}

			textStart = textCur + 1;
		}
		else if (*textCur == '\n')
		{
			// Print accumulated text an go to next line
			ImGui::TextUnformatted(textStart, textCur);
			textStart = textCur + 1;
		}

		++textCur;
	}

	if (textCur != textStart)
	{
		ImGui::TextUnformatted(textStart, textCur);
	}
	else
	{
		ImGui::NewLine();
	}

	if (pushedColorStyle)
	{
		ImGui::PopStyleColor();
	}
}


void  WriteSetting(std::string Path)
{
	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile(Path.c_str());
	if (rc < 0) { std::cout << "File not found"; };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("M416", str.append(std::to_string(i)).c_str(), fround(m16[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("AWM", str.append(std::to_string(i)).c_str(), fround(AWM[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("AWMimmo", str.append(std::to_string(i)).c_str(), fround(AWMimmo[i] * 255)); } //{ 0.942f, 0.300f, 0.073f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("AirAttack", str.append(std::to_string(i)).c_str(), fround(AirAttack[i] * 255)); } //{ 1.000f, 0.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("scarl", str.append(std::to_string(i)).c_str(), fround(scarl[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("m762", str.append(std::to_string(i)).c_str(), fround(m762[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("M24", str.append(std::to_string(i)).c_str(), fround(M24[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("GROZZA", str.append(std::to_string(i)).c_str(), fround(GROZZA[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("scope8x", str.append(std::to_string(i)).c_str(), fround(scope8x[i] * 255)); } //{ 0.866f, 0.128f, 0.081f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("kar98", str.append(std::to_string(i)).c_str(), fround(kar98[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Airdrop", str.append(std::to_string(i)).c_str(), fround(Airdrop[i] * 255)); } //{ 0.279f, 0.990f, 0.812f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Flare", str.append(std::to_string(i)).c_str(), fround(Flare[i] * 255)); } //{ 0.866f, 0.128f, 0.081f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Flaregun", str.append(std::to_string(i)).c_str(), fround(Flaregun[i] * 255)); } //{ 1.0f, 0.60f,0.05f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("dp", str.append(std::to_string(i)).c_str(), fround(dp[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("mg3", str.append(std::to_string(i)).c_str(), fround(mg3[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("scope4x", str.append(std::to_string(i)).c_str(), fround(scope4x[i] * 255)); } //{ 0.937f, 0.063f, 0.937f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("scope3x", str.append(std::to_string(i)).c_str(), fround(scope3x[i] * 255)); } //{ 0.874f, 0.484f, 0.106f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("bag", str.append(std::to_string(i)).c_str(), fround(bag[i] * 255)); } //{ 0.529f, 0.127f, 0.903f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("armer", str.append(std::to_string(i)).c_str(), fround(armer[i] * 255)); } //{ 0.591f, 1.000f, 0.237f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("helmat", str.append(std::to_string(i)).c_str(), fround(helmat[i] * 255)); } //{ 0.726f, 0.070f, 0.908f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("mosin", str.append(std::to_string(i)).c_str(), fround(mosin[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("aug", str.append(std::to_string(i)).c_str(), fround(aug[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("g36", str.append(std::to_string(i)).c_str(), fround(g36[i] * 255)); } //{ 0.671f, 0.217f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("assm", str.append(std::to_string(i)).c_str(), fround(assm[i] * 255)); } //{ 1.000f, 0.217f, 0.762f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Grandes", str.append(std::to_string(i)).c_str(), fround(Grandes[i] * 255)); } //{ 1.000f, 0.396f, 0.357f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("ammo7", str.append(std::to_string(i)).c_str(), fround(ammo7[i] * 255)); } //{ 0.984f, 0.871f, 0.043f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("ammo5", str.append(std::to_string(i)).c_str(), fround(ammo5[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("madkit", str.append(std::to_string(i)).c_str(), fround(madkit[i] * 255)); } //{ 0.952f, 0.558f, 0.129f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("playerline", str.append(std::to_string(i)).c_str(), fround(playerline[i] * 255)); } //{ 0.591f, 1.000f, 0.237f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("playercorner", str.append(std::to_string(i)).c_str(), fround(playercorner[i] * 255)); } //{ 1.0f, 0.70f,0.30f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("playerbox", str.append(std::to_string(i)).c_str(), fround(playerbox[i] * 255)); } //{ 1.0f, 1.0f,0.0f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("lotbox", str.append(std::to_string(i)).c_str(), fround(lotbox[i] * 255)); } //{ 1.0f, 1.0f,0.0f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("helthbar", str.append(std::to_string(i)).c_str(), fround(helthbar[i] * 255)); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("boxColor", str.append(std::to_string(i)).c_str(), fround(boxColor[i] * 255)); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("cornerColor", str.append(std::to_string(i)).c_str(), fround(cornerColor[i] * 255)); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("crosshairColor", str.append(std::to_string(i)).c_str(), fround(crosshairColor[i] * 255)); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("bot", str.append(std::to_string(i)).c_str(), fround(bot[i] * 255)); } //{ 0.016f, 0.725f, 0.929f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("player", str.append(std::to_string(i)).c_str(), fround(player[i] * 255)); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("vehicle", str.append(std::to_string(i)).c_str(), fround(vehicle[i] * 255)); } //{ 1.000f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("botcorner", str.append(std::to_string(i)).c_str(), fround(botcorner[i] * 255)); } //{ 0.050f, 0.125f, 0.925f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("botline", str.append(std::to_string(i)).c_str(), fround(botline[i] * 255)); } //{ 0.050f, 0.025f, 0.925f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("circle", str.append(std::to_string(i)).c_str(), fround(circle[i] * 255)); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("enemy", str.append(std::to_string(i)).c_str(), fround(enemy[i] * 255)); } //{ 255, 255, 255, 255 };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("botbox", str.append(std::to_string(i)).c_str(), fround(botbox[i] * 255)); } //{ 0.950f, 0.125f, 0.925f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("bone", str.append(std::to_string(i)).c_str(), fround(bone[i] * 255)); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("fillrect", str.append(std::to_string(i)).c_str(), fround(fillrect[i] * 255)); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("nam", str.append(std::to_string(i)).c_str(), fround(nam[i] * 255)); } //{ 1.000f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("nambar", str.append(std::to_string(i)).c_str(), fround(nambar[i] * 255)); } //{ 0.880f, 0.185f, 0.25f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("bothealth", str.append(std::to_string(i)).c_str(), fround(bothealth[i] * 255)); } //{ 0.95f, 0.125f, 0.825f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("botname", str.append(std::to_string(i)).c_str(), fround(botname[i] * 255)); } //{ 0.050f, 0.825f, 0.185f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("playerhealth", str.append(std::to_string(i)).c_str(), fround(playerhealth[i] * 255)); } //{ 0.50f, 0.725f, 0.105f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("textcolor", str.append(std::to_string(i)).c_str(), fround(textcolor[i] * 255)); } //{ 0.500f, 0.150f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Granades", str.append(std::to_string(i)).c_str(), fround(Granades[i] * 255)); } //{ 0.990f, 0.995f, 0.995f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("health", str.append(std::to_string(i)).c_str(), fround(health[i] * 255)); } //{ 0.108f, 1.000f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("deadbox", str.append(std::to_string(i)).c_str(), fround(deadbox[i] * 255)); } //{ 0.737f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("deadboxitem", str.append(std::to_string(i)).c_str(), fround(deadboxitem[i] * 255)); } //{ 1.000f, 0.100f, 0.401f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("airdrop", str.append(std::to_string(i)).c_str(), fround(airdrop[i] * 255)); } //{ 1.000f, 0.695f, 0.323f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("airdropitem", str.append(std::to_string(i)).c_str(), fround(airdropitem[i] * 255)); } //{ 0.300f, 0.695f, 0.323f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("scopetextcolor", str.append(std::to_string(i)).c_str(), fround(scopetextcolor[i] * 255)); } //{ 0.000f, 0.995f, 0.995f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("allitem", str.append(std::to_string(i)).c_str(), fround(allitem[i] * 255)); } //{ 0.034f, 1.000f, 0.040f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("scope6x", str.append(std::to_string(i)).c_str(), fround(scope6x[i] * 255)); } //{ 0.120f, 0.955f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("botbone", str.append(std::to_string(i)).c_str(), fround(botbone[i] * 255)); } //{ 0.050f, 0.025f, 0.925f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("playerbone", str.append(std::to_string(i)).c_str(), fround(playerbone[i] * 255)); } //{ 0.986f, 0.952f, 0.209f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("magicline", str.append(std::to_string(i)).c_str(), fround(magicline[i] * 255)); } //{ 255, 0, 0, 255 };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("bgcorner", str.append(std::to_string(i)).c_str(), fround(bgcorner[i] * 255)); } //{ 0.000f, 1.000f, 0.964f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("fovcirclecolor", str.append(std::to_string(i)).c_str(), fround(fovcirclecolor[i] * 255)); } //{ 255, 0, 0, 255 };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("weapont", str.append(std::to_string(i)).c_str(), fround(weapont[i] * 255)); } //{ 255,255,0,255 };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("skelec", str.append(std::to_string(i)).c_str(), fround(skelec[i] * 255)); } //{ 255, 255, 255, 255 };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("hpt", str.append(std::to_string(i)).c_str(), fround(hpt[i] * 255)); } //{ 255, 255, 255, 255 };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("plancolor", str.append(std::to_string(i)).c_str(), fround(plancolor[i] * 255)); } //{ 0.737f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("dotss", str.append(std::to_string(i)).c_str(), fround(dotss[i] * 255)); } //{ 0.950f, 0.125f, 0.925f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_AKM_Color[]", str.append(std::to_string(i)).c_str(), fround(Esp_Item_AKM_Color[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("M249", str.append(std::to_string(i)).c_str(), fround(M249[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("MK12", str.append(std::to_string(i)).c_str(), fround(MK12[i] * 255)); } //{ 1.00f, 0.796f, 0.715f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_M762_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_M762_Color[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Mk47Mutant_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Mk47Mutant_Color[i] * 255)); } //{ 1.00f, 0.76f, 0.15f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_DP28_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_DP28_Color[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_SCARL_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_SCARL_Color[i] * 255)); } //{ 0.00f, 1.0f, 0.0f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_M416_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_M416_Color[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_M16A4_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_M16A4_Color[i] * 255)); } //{ 0.00f, 1.0f, 0.0f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_G36C_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_G36C_Color[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_QBZ_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_QBZ_Color[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_QBU_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_QBU_Color[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_SLR_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_SLR_Color[i] * 255)); } //{ 0.627f, 0.102f, 0.941f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_SKS_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_SKS_Color[i] * 255)); } //{ 0.627f, 0.102f, 0.941f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Mini14_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Mini14_Color[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_M24_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_M24_Color[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Kar98k_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Kar98k_Color[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_PP19_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_PP19_Color[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_TommyGun_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_TommyGun_Color[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_MP5K_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_MP5K_Color[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_UMP9_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_UMP9_Color[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Vector_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Vector_Color[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Uzi_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Uzi_Color[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_762mm_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_762mm_Color[i] * 255)); } //{ 0.984f, 0.871f, 0.043f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_556mm_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_556mm_Color[i] * 255)); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_9mm_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_9mm_Color[i] * 255)); } //{ 1.000f, 0.000f, 0.337f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_45ACP_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_45ACP_Color[i] * 255)); } //{ 1.00f, 0.96f, 0.56f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Holo_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Holo_Color[i] * 255)); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_x2_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_x2_Color[i] * 255)); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_x3_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_x3_Color[i] * 255)); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_x4_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_x4_Color[i] * 255)); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_x6_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_x6_Color[i] * 255)); } //{ 1.000f, 0.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_x8_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_x8_Color[i] * 255)); } //{ 1.000f, 0.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Bag1_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Bag1_Color[i] * 255)); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Bag2_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Bag2_Color[i] * 255)); } //{ 0.627f, 0.102f, 0.941f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Bag3_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Bag3_Color[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Armor1_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Armor1_Color[i] * 255)); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Armor1_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Armor1_Color[i] * 255)); } //{ 0.627f, 0.102f, 0.941f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Armor3_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Armor3_Color[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Helmet1_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Helmet1_Color[i] * 255)); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Helmet2_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Helmet2_Color[i] * 255)); } //{ 0.627f, 0.102f, 0.941f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Helmet3_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Helmet3_Color[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Frag_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Frag_Color[i] * 255)); } //{ 1.000f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Smoke_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Smoke_Color[i] * 255)); } //{ 1.000f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Molotof_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Molotof_Color[i] * 255)); } //{ 1.000f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_MedKit_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_MedKit_Color[i] * 255)); } //{ 1.000f, 0.753f, 0.796f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_FirstAidKit_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_FirstAidKit_Color[i] * 255)); } //{ 1.000f, 0.753f, 0.796f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Painkiller_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Painkiller_Color[i] * 255)); } //{ 1.000f, 0.753f, 0.796f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_EnergyDrink_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_EnergyDrink_Color[i] * 255)); } //{ 1.000f, 0.753f, 0.796f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_AdrenalineSyringe_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_AdrenalineSyringe_Color[i] * 255)); } //{ 1.000f, 0.753f, 0.796f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_FlareGun_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_FlareGun_Color[i] * 255)); } //{ 1.000f, 0.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_Flare_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_Flare_Color[i] * 255)); } //{ 1.000f, 0.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_AirDrop_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_AirDrop_Color[i] * 255)); } //{ 1.000f, 0.647f, 0.000f, 1.000f };

#pragma region item colors Attchment
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QK_Choke_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QK_Choke_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QK_Mid_Compensator_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QK_Mid_Compensator_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QK_Sniper_Compensator_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QK_Sniper_Compensator_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QK_Mid_FlashHider_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QK_Mid_FlashHider_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QK_Sniper_FlashHider_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QK_Sniper_FlashHider_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QK_Mid_Suppressor_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QK_Mid_Suppressor_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QK_Sniper_Suppressor_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QK_Sniper_Suppressor_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QK_Large_Compensator_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QK_Large_Compensator_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QK_Large_FlashHider_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QK_Large_FlashHider_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QK_Large_Suppressor_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QK_Large_Suppressor_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QK_DuckBill_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QK_DuckBill_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_WB_Angled_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_WB_Angled_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_WB_Vertical_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_WB_Vertical_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_WB_LightGrip_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_WB_LightGrip_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_WB_HalfGrip_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_WB_HalfGrip_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_WB_ThumbGrip_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_WB_ThumbGrip_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_WB_Lasersight_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_WB_Lasersight_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_MZJ_HD_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_MZJ_HD_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_MZJ_QX_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_MZJ_QX_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_MZJ_SideRMR_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_MZJ_SideRMR_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_ZDD_Sniper_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_ZDD_Sniper_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QT_UZI_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QT_UZI_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QT_A_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QT_A_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_QT_Sniper_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_QT_Sniper_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_ZDD_Crossbow_Q_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_ZDD_Crossbow_Q_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_DJ_Mid_E_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_DJ_Mid_E_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_DJ_Mid_Q_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_DJ_Mid_Q_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_DJ_Mid_EQ_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_DJ_Mid_EQ_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_DJ_Sniper_E_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_DJ_Sniper_E_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_DJ_Sniper_Q_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_DJ_Sniper_Q_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_DJ_Sniper_EQ_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_DJ_Sniper_EQ_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_DJ_Large_E_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_DJ_Large_E_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_DJ_Large_Q_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_DJ_Large_Q_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_DJ_Large_EQ_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_DJ_Large_EQ_Pickup_C_1[i] * 255)); }

	//////////////////////////////

	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_Pistol_P92_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_Pistol_P92_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_Pistol_P1911_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_Pistol_P1911_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_Pistol_R1895_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_Pistol_R1895_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_Pistol_P18C_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_Pistol_P18C_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_Pistol_R45_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_Pistol_R45_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_Pistol_Vz61_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_Pistol_Vz61_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_Pistol_DesertEagle_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_Pistol_DesertEagle_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_ShotGun_SawedOff_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_ShotGun_SawedOff_Wrapper_C_1[i] * 255)); }
	////////////////////////////////////////
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_ShotGun_S686_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_ShotGun_S686_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_ShotGun_S1897_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_ShotGun_S1897_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_ShotGun_S12K_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_ShotGun_S12K_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_ShotGun_DP12_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_ShotGun_DP12_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_ShotGun_M1014_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_ShotGun_M1014_Wrapper_C_1[i] * 255)); }
	////////////////////////////////////////
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_WEP_Machete_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_WEP_Machete_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_WEP_Cowbar_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_WEP_Cowbar_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_WEP_Sickle_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_WEP_Sickle_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_WEP_Pan_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_WEP_Pan_Pickup_C_1[i] * 255)); }
	////////////////////////////////////////
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_Sniper_VSS_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_Sniper_VSS_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_WEP_Mk14_Pickup_C_1", str.append(std::to_string(i)).c_str(), fround(BP_WEP_Mk14_Pickup_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_Sniper_Win94_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_Sniper_Win94_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_Sniper_QBU_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_Sniper_QBU_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_Sniper_Mosin_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_Sniper_Mosin_Wrapper_C_1[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("BP_Sniper_MK12_Wrapper_C_1", str.append(std::to_string(i)).c_str(), fround(BP_Sniper_MK12_Wrapper_C_1[i] * 255)); }
	//////////////////////////////////////////
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("AWMimmo", str.append(std::to_string(i)).c_str(), fround(AWMimmo[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_45ACP_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_45ACP_Color[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_9mm_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_9mm_Color[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_556mm_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_556mm_Color[i] * 255)); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; ini.SetLongValue("Esp_Item_762mm_Color", str.append(std::to_string(i)).c_str(), fround(Esp_Item_762mm_Color[i] * 255)); }





#pragma endregion
#pragma region Settings Attichment
	ini.SetBoolValue("Esp", "BP_QK_Choke_Pickup_C_1", Setting::BP_QK_Choke_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QK_Mid_Compensator_Pickup_C_1", Setting::BP_QK_Mid_Compensator_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QK_Sniper_Compensator_Pickup_C_1", Setting::BP_QK_Sniper_Compensator_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QK_Mid_FlashHider_Pickup_C_1", Setting::BP_QK_Mid_FlashHider_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QK_Sniper_FlashHider_Pickup_C_1 ", Setting::BP_QK_Sniper_FlashHider_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QK_Mid_Suppressor_Pickup_C_1", Setting::BP_QK_Mid_Suppressor_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QK_Sniper_Suppressor_Pickup_C_1", Setting::BP_QK_Sniper_Suppressor_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QK_Large_Compensator_Pickup_C_1", Setting::BP_QK_Large_Compensator_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QK_Large_FlashHider_Pickup_C_1", Setting::BP_QK_Large_FlashHider_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QK_Large_Suppressor_Pickup_C_1", Setting::BP_QK_Large_Suppressor_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QK_DuckBill_Pickup_C_1", Setting::BP_QK_DuckBill_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_WB_Angled_Pickup_C_1", Setting::BP_WB_Angled_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_WB_Vertical_Pickup_C_1", Setting::BP_WB_Vertical_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_WB_LightGrip_Pickup_C_1", Setting::BP_WB_LightGrip_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_WB_HalfGrip_Pickup_C_1", Setting::BP_WB_HalfGrip_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_WB_ThumbGrip_Pickup_C_1", Setting::BP_WB_ThumbGrip_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_WB_Lasersight_Pickup_C_1", Setting::BP_WB_Lasersight_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_MZJ_HD_Pickup_C_1", Setting::BP_MZJ_HD_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_MZJ_QX_Pickup_C_1", Setting::BP_MZJ_QX_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_MZJ_SideRMR_Pickup_C_1", Setting::BP_MZJ_SideRMR_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_ZDD_Sniper_Pickup_C_1", Setting::BP_ZDD_Sniper_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QT_UZI_Pickup_C_1", Setting::BP_QT_UZI_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QT_A_Pickup_C_1", Setting::BP_QT_A_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_QT_Sniper_Pickup_C_1", Setting::BP_QT_Sniper_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_ZDD_Crossbow_Q_Pickup_C_1", Setting::BP_ZDD_Crossbow_Q_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_DJ_Mid_E_Pickup_C_1", Setting::BP_DJ_Mid_E_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_DJ_Mid_Q_Pickup_C_1", Setting::BP_DJ_Mid_Q_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_DJ_Mid_EQ_Pickup_C_1", Setting::BP_DJ_Mid_EQ_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_DJ_Sniper_E_Pickup_C_1", Setting::BP_DJ_Sniper_E_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_DJ_Sniper_Q_Pickup_C_1", Setting::BP_DJ_Sniper_Q_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_DJ_Sniper_EQ_Pickup_C_1", Setting::BP_DJ_Sniper_EQ_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_DJ_Large_E_Pickup_C_1", Setting::BP_DJ_Large_E_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_DJ_Large_Q_Pickup_C_1", Setting::BP_DJ_Large_Q_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_DJ_Large_EQ_Pickup_C_1", Setting::BP_DJ_Large_EQ_Pickup_C_1);
	////////////////////////////////////////////////////////////////////////////////////////
	ini.SetBoolValue("Esp", "BP_Pistol_P92_Wrapper_C_1", Setting::BP_Pistol_P92_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_Pistol_P1911_Wrapper_C_1", Setting::BP_Pistol_P1911_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_Pistol_R1895_Wrapper_C_1", Setting::BP_Pistol_R1895_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_Pistol_P18C_Wrapper_C_1", Setting::BP_Pistol_P18C_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_Pistol_R45_Wrapper_C_1", Setting::BP_Pistol_R45_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_Pistol_Vz61_Wrapper_C_1", Setting::BP_Pistol_Vz61_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_Pistol_DesertEagle_Wrapper_C_1", Setting::BP_Pistol_DesertEagle_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_ShotGun_SawedOff_Wrapper_C_1", Setting::BP_ShotGun_SawedOff_Wrapper_C_1);
	///////////////////////////////////////////////////////////////////////////////////////////
	ini.SetBoolValue("Esp", "BP_ShotGun_S686_Wrapper_C_1", Setting::BP_ShotGun_S686_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_ShotGun_S1897_Wrapper_C_1", Setting::BP_ShotGun_S1897_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_ShotGun_S12K_Wrapper_C_1", Setting::BP_ShotGun_S12K_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_ShotGun_DP12_Wrapper_C_1", Setting::BP_ShotGun_DP12_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_ShotGun_M1014_Wrapper_C_1", Setting::BP_ShotGun_M1014_Wrapper_C_1);
	////////////////////////////////////////////////////////////////////////////////////////////
	ini.SetBoolValue("Esp", "BP_WEP_Machete_Pickup_C_1", Setting::BP_WEP_Machete_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_WEP_Cowbar_Pickup_C_1", Setting::BP_WEP_Cowbar_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_WEP_Sickle_Pickup_C_1", Setting::BP_WEP_Sickle_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_WEP_Pan_Pickup_C_1", Setting::BP_WEP_Pan_Pickup_C_1);
	///////////////////////////////////////////////////////////////////////////////////////////
	ini.SetBoolValue("Esp", "BP_Sniper_VSS_Wrapper_C_1", Setting::BP_Sniper_VSS_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_WEP_Mk14_Pickup_C_1", Setting::BP_WEP_Mk14_Pickup_C_1);
	ini.SetBoolValue("Esp", "BP_Sniper_Win94_Wrapper_C_1", Setting::BP_Sniper_Win94_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_Sniper_QBU_Wrapper_C_1", Setting::BP_Sniper_QBU_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_Sniper_Mosin_Wrapper_C_1", Setting::BP_Sniper_Mosin_Wrapper_C_1);
	ini.SetBoolValue("Esp", "BP_Sniper_MK12_Wrapper_C_1", Setting::BP_Sniper_MK12_Wrapper_C_1);
	//////////////////////////////////////////////////////////////////////////////////////////

#pragma endregion
#pragma region Font size Attchment
	std::string str1 = "BP_QK_Choke_Pickup_C_1";
	std::string str2 = "BP_QK_Mid_Compensator_Pickup_C_1";
	std::string str3 = "BP_QK_Sniper_Compensator_Pickup_C_1";
	std::string str4 = "BP_QK_Mid_FlashHider_Pickup_C_1";
	std::string str5 = "BP_QK_Sniper_FlashHider_Pickup_C_1";
	std::string str6 = "BP_QK_Mid_Suppressor_Pickup_C_1";
	std::string str7 = "BP_QK_Sniper_Suppressor_Pickup_C_1";
	std::string str8 = "BP_QK_Large_Compensator_Pickup_C_1";
	std::string str9 = "BP_QK_Large_FlashHider_Pickup_C_1";
	std::string str10 = "BP_QK_Large_Suppressor_Pickup_C_1";
	std::string str11 = "BP_QK_DuckBill_Pickup_C_1";
	std::string str12 = "BP_WB_Angled_Pickup_C_1";
	std::string str13 = "BP_WB_Vertical_Pickup_C_1";
	std::string str14 = "BP_WB_LightGrip_Pickup_C_1";
	std::string str15 = "BP_WB_HalfGrip_Pickup_C_1";
	std::string str16 = "BP_WB_ThumbGrip_Pickup_C_1";
	std::string str17 = "BP_WB_Lasersight_Pickup_C_1";
	std::string str18 = "BP_MZJ_HD_Pickup_C_1";
	std::string str19 = "BP_MZJ_QX_Pickup_C_1";
	std::string str20 = "BP_MZJ_SideRMR_Pickup_C_1";
	std::string str21 = "BP_ZDD_Sniper_Pickup_C_1";
	std::string str22 = "BP_QT_UZI_Pickup_C_1";
	std::string str23 = "BP_QT_A_Pickup_C_1";
	std::string str24 = "BP_QT_Sniper_Pickup_C_1";
	std::string str25 = "BP_ZDD_Crossbow_Q_Pickup_C_1";
	std::string str26 = "BP_DJ_Mid_E_Pickup_C_1";
	std::string str27 = "BP_DJ_Mid_Q_Pickup_C_1";
	std::string str28 = "BP_DJ_Mid_EQ_Pickup_C_1";
	std::string str29 = "BP_DJ_Sniper_E_Pickup_C_1";
	std::string str30 = "BP_DJ_Sniper_Q_Pickup_C_1";
	std::string str31 = "BP_DJ_Sniper_EQ_Pickup_C_1";
	std::string str32 = "BP_DJ_Large_E_Pickup_C_1";
	std::string str33 = "BP_DJ_Large_Q_Pickup_C_1";
	std::string str34 = "BP_DJ_Large_EQ_Pickup_C_1";
	std::string str35 = "BP_Pistol_P92_Wrapper_C_1";
	std::string str36 = "BP_Pistol_P1911_Wrapper_C_1";
	std::string str37 = "BP_Pistol_R1895_Wrapper_C_1";
	std::string str38 = "BP_Pistol_P18C_Wrapper_C_1";
	std::string str39 = "BP_Pistol_R45_Wrapper_C_1";
	std::string str40 = "BP_Pistol_Vz61_Wrapper_C_1";
	std::string str41 = "BP_Pistol_DesertEagle_Wrapper_C_1";
	std::string str42 = "BP_ShotGun_SawedOff_Wrapper_C_1";
	std::string str43 = "BP_ShotGun_S686_Wrapper_C_1";
	std::string str44 = "BP_ShotGun_S1897_Wrapper_C_1";
	std::string str45 = "BP_ShotGun_S12K_Wrapper_C_1";
	std::string str46 = "BP_ShotGun_DP12_Wrapper_C_1";
	std::string str47 = "BP_ShotGun_M1014_Wrapper_C_1";
	std::string str48 = "BP_WEP_Machete_Pickup_C_1";
	std::string str49 = "BP_WEP_Cowbar_Pickup_C_1";
	std::string str50 = "BP_WEP_Sickle_Pickup_C_1";
	std::string str51 = "BP_WEP_Pan_Pickup_C_1";
	std::string str52 = "BP_Sniper_VSS_Wrapper_C_1";
	std::string str53 = "BP_WEP_Mk14_Pickup_C_1";
	std::string str54 = "BP_Sniper_Win94_Wrapper_C_1";
	std::string str55 = "BP_Sniper_QBU_Wrapper_C_1";
	std::string str56 = "BP_Sniper_Mosin_Wrapper_C_1";
	std::string str57 = "BP_Sniper_MK12_Wrapper_C_1";
	ini.SetLongValue("Font_Size", str1.c_str(), fround(BP_QK_Choke_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str2.c_str(), fround(BP_QK_Mid_Compensator_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str3.c_str(), fround(BP_QK_Sniper_Compensator_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str4.c_str(), fround(BP_QK_Mid_FlashHider_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str5.c_str(), fround(BP_QK_Sniper_FlashHider_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str6.c_str(), fround(BP_QK_Mid_Suppressor_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str7.c_str(), fround(BP_QK_Sniper_Suppressor_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str8.c_str(), fround(BP_QK_Large_Compensator_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str9.c_str(), fround(BP_QK_Large_FlashHider_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str10.c_str(), fround(BP_QK_Large_Suppressor_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str11.c_str(), fround(BP_QK_DuckBill_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str12.c_str(), fround(BP_WB_Angled_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str13.c_str(), fround(BP_WB_Vertical_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str14.c_str(), fround(BP_WB_LightGrip_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str15.c_str(), fround(BP_WB_HalfGrip_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str16.c_str(), fround(BP_WB_ThumbGrip_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str17.c_str(), fround(BP_WB_Lasersight_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str18.c_str(), fround(BP_MZJ_HD_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str19.c_str(), fround(BP_MZJ_QX_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str20.c_str(), fround(BP_MZJ_SideRMR_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str21.c_str(), fround(BP_ZDD_Sniper_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str22.c_str(), fround(BP_QT_UZI_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str23.c_str(), fround(BP_QT_A_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str24.c_str(), fround(BP_QT_Sniper_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str25.c_str(), fround(BP_ZDD_Crossbow_Q_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str26.c_str(), fround(BP_DJ_Mid_E_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str27.c_str(), fround(BP_DJ_Mid_Q_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str28.c_str(), fround(BP_DJ_Mid_EQ_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str29.c_str(), fround(BP_DJ_Sniper_E_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str30.c_str(), fround(BP_DJ_Sniper_Q_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str31.c_str(), fround(BP_DJ_Sniper_EQ_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str32.c_str(), fround(BP_DJ_Large_E_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str33.c_str(), fround(BP_DJ_Large_Q_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str34.c_str(), fround(BP_DJ_Large_EQ_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str35.c_str(), fround(BP_Pistol_P92_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str36.c_str(), fround(BP_Pistol_P1911_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str37.c_str(), fround(BP_Pistol_R1895_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str38.c_str(), fround(BP_Pistol_P18C_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str39.c_str(), fround(BP_Pistol_R45_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str40.c_str(), fround(BP_Pistol_Vz61_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str41.c_str(), fround(BP_Pistol_DesertEagle_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str42.c_str(), fround(BP_ShotGun_SawedOff_Wrapper_C_1s));


	ini.SetLongValue("Font_Size", str43.c_str(), fround(BP_ShotGun_S686_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str44.c_str(), fround(BP_ShotGun_S1897_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str45.c_str(), fround(BP_ShotGun_S12K_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str46.c_str(), fround(BP_ShotGun_DP12_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str47.c_str(), fround(BP_ShotGun_M1014_Wrapper_C_1s));

	ini.SetLongValue("Font_Size", str48.c_str(), fround(BP_WEP_Machete_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str49.c_str(), fround(BP_WEP_Cowbar_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str50.c_str(), fround(BP_WEP_Sickle_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str51.c_str(), fround(BP_WEP_Pan_Pickup_C_1s));


	ini.SetLongValue("Font_Size", str52.c_str(), fround(BP_Sniper_VSS_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str53.c_str(), fround(BP_WEP_Mk14_Pickup_C_1s));
	ini.SetLongValue("Font_Size", str54.c_str(), fround(BP_Sniper_Win94_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str55.c_str(), fround(BP_Sniper_QBU_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str56.c_str(), fround(BP_Sniper_Mosin_Wrapper_C_1s));
	ini.SetLongValue("Font_Size", str57.c_str(), fround(BP_Sniper_MK12_Wrapper_C_1s));



#pragma endregion

	ini.SetBoolValue("Esp", "playerBone", Setting::playerBone);
	ini.SetBoolValue("Esp", "pline", Setting::pline);
	ini.SetBoolValue("Esp", "Distancee", Setting::Distancee);
	ini.SetBoolValue("Esp", "phealth", Setting::phealth);
	ini.SetBoolValue("Esp", "pname", Setting::pname);
	ini.SetBoolValue("Esp", "pcorner", Setting::pcorner);
	ini.SetBoolValue("Esp", "Item", Setting::Item);
	ini.SetBoolValue("Esp", "deadbox", Setting::deadbox);
	ini.SetBoolValue("Esp", "Vehicle", Setting::Vehicle);
	ini.SetBoolValue("Esp", "TotalEnemy", Setting::TotalEnemy);
	ini.SetBoolValue("Esp", "grw", Setting::grw);
	ini.SetBoolValue("Esp", "molow", Setting::molow);
	ini.SetBoolValue("Esp", "fovcircle", Setting::fovcircle);
	ini.SetBoolValue("Esp", "knocked", Setting::knocked);
	ini.SetBoolValue("Esp", "MAgicline", Setting::MAgicline);
	ini.SetBoolValue("Esp", "Esp_Item_M416", Setting::Esp_Item_M416);
	ini.SetBoolValue("Esp", "Esp_Item_SCARL", Setting::Esp_Item_SCARL);
	ini.SetBoolValue("Esp", "Esp_Item_AKM", Setting::Esp_Item_AKM);
	ini.SetBoolValue("Esp", "Esp_Item_M762", Setting::Esp_Item_M762);
	ini.SetBoolValue("Esp", "Esp_Item_DP28", Setting::Esp_Item_DP28);
	ini.SetBoolValue("Esp", "Esp_Item_Awm", Setting::Esp_Item_Awm);
	ini.SetBoolValue("Esp", "Esp_Item_Kar98k", Setting::Esp_Item_Kar98k);
	ini.SetBoolValue("Esp", "Esp_Item_FlareGun", Setting::Esp_Item_FlareGun);
	ini.SetBoolValue("Esp", "Esp_Item_G36C", Setting::Esp_Item_G36C);
	ini.SetBoolValue("Esp", "Esp_Item_QBZ", Setting::Esp_Item_QBZ);
	ini.SetBoolValue("Esp", "Esp_Item_SLR", Setting::Esp_Item_SLR);
	ini.SetBoolValue("Esp", "Esp_Item_QBU", Setting::Esp_Item_QBU);
	ini.SetBoolValue("Esp", "Esp_Item_SKS", Setting::Esp_Item_SKS);
	ini.SetBoolValue("Esp", "Esp_Item_Mini14", Setting::Esp_Item_Mini14);
	ini.SetBoolValue("Esp", "Esp_Item_PP19", Setting::Esp_Item_PP19);
	ini.SetBoolValue("Esp", "Esp_Item_TommyGun", Setting::Esp_Item_TommyGun);
	ini.SetBoolValue("Esp", "Esp_Item_MP5K", Setting::Esp_Item_MP5K);
	ini.SetBoolValue("Esp", "Esp_Item_UMP9", Setting::Esp_Item_UMP9);
	ini.SetBoolValue("Esp", "Esp_Item_Vector", Setting::Esp_Item_Vector);
	ini.SetBoolValue("Esp", "Esp_Item_Uzi", Setting::Esp_Item_Uzi);
	ini.SetBoolValue("Esp", "Esp_Item_Mk47Mutant", Setting::Esp_Item_Mk47Mutant);
	ini.SetBoolValue("Esp", "Esp_Item_Frag", Setting::Esp_Item_Frag);
	ini.SetBoolValue("Esp", "Esp_Item_Smoke", Setting::Esp_Item_Smoke);
	ini.SetBoolValue("Esp", "Esp_Item_Molotof", Setting::Esp_Item_Molotof);
	ini.SetBoolValue("Esp", "Esp_Item_MedKit", Setting::Esp_Item_MedKit);
	ini.SetBoolValue("Esp", "Esp_Item_FirstAidKit", Setting::Esp_Item_FirstAidKit);
	ini.SetBoolValue("Esp", "Esp_Item_Painkiller", Setting::Esp_Item_Painkiller);
	ini.SetBoolValue("Esp", "Esp_Item_EnergyDrink", Setting::Esp_Item_EnergyDrink);
	ini.SetBoolValue("Esp", "Esp_Item_AdrenalineSyringe", Setting::Esp_Item_AdrenalineSyringe);
	ini.SetBoolValue("Esp", "Esp_Item_Bag1", Setting::Esp_Item_Bag1);
	ini.SetBoolValue("Esp", "Esp_Item_Bag2", Setting::Esp_Item_Bag2);
	ini.SetBoolValue("Esp", "Esp_Item_Bag3", Setting::Esp_Item_Bag3);
	ini.SetBoolValue("Esp", "Esp_Item_Helmet1", Setting::Esp_Item_Helmet1);
	ini.SetBoolValue("Esp", "Esp_Item_Helmet2", Setting::Esp_Item_Helmet2);
	ini.SetBoolValue("Esp", "Esp_Item_Helmet3", Setting::Esp_Item_Helmet3);
	ini.SetBoolValue("Esp", "Esp_Item_Armor1", Setting::Esp_Item_Armor1);
	ini.SetBoolValue("Esp", "Esp_Item_Armor2", Setting::Esp_Item_Armor2);
	ini.SetBoolValue("Esp", "Esp_Item_Armor3", Setting::Esp_Item_Armor3);
	ini.SetBoolValue("Esp", "Esp_Item_762mm", Setting::Esp_Item_762mm);
	ini.SetBoolValue("Esp", "Esp_Item_556mm", Setting::Esp_Item_556mm);
	ini.SetBoolValue("Esp", "Esp_Item_9mm", Setting::Esp_Item_9mm);
	ini.SetBoolValue("Esp", "Esp_Item_45ACP", Setting::Esp_Item_45ACP);
	ini.SetBoolValue("Esp", "Esp_Item_Awmimo", Setting::Esp_Item_Awmimo);
	ini.SetBoolValue("Esp", "Esp_Item_Holo", Setting::Esp_Item_Holo);
	ini.SetBoolValue("Esp", "Esp_Item_x2", Setting::Esp_Item_x2);
	ini.SetBoolValue("Esp", "Esp_Item_x3", Setting::Esp_Item_x3);
	ini.SetBoolValue("Esp", "Esp_Item_x4", Setting::Esp_Item_x4);
	ini.SetBoolValue("Esp", "Esp_Item_x6", Setting::Esp_Item_x6);
	ini.SetBoolValue("Esp", "Esp_Item_x8", Setting::Esp_Item_x8);
	ini.SetBoolValue("Esp", "playerdeadbox", Setting::playerdeadbox);
	ini.SetBoolValue("Esp", "Aimbot", Setting::Aimbot);
	ini.SetBoolValue("Esp", "borderlo", Setting::borderlo);
	ini.SetBoolValue("Esp", "marco1", marco1);
	ini.SetBoolValue("Esp", "nothingm", nothingm);
	ini.SetBoolValue("Esp", "nothinga", nothinga);



	/*Memory*/
	ini.SetBoolValue("Memory", "MagicBulletticked", Setting::MagicBulletticked);
	ini.SetBoolValue("Memory", "PREDICTION", Setting::PREDICTION);
	ini.SetBoolValue("Memory", "Legitrack", Setting::Legitrack);
	ini.SetBoolValue("Memory", "fastrun", Setting::fastrun);
	ini.SetBoolValue("Memory", "speedcar", Setting::speedcar);
	ini.SetBoolValue("Memory", "recoil", Setting::recoil);
	ini.SetBoolValue("Memory", "instanthit", Setting::instanthit);
	ini.SetBoolValue("Memory", "SkipKnocked", Setting::SkipKnocked);
	ini.SetBoolValue("Memory", "SkipBots", Setting::SkipBots);




	/*Memory Option*/
	std::string str418 = "magicv"; ini.SetLongValue("Memory_Option", str418.c_str(), fround(Setting::magicv));
	std::string str419 = "fastrv"; ini.SetLongValue("Memory_Option", str419.c_str(), fround(Setting::fastrv));
	std::string str420 = "fastrunkey"; ini.SetLongValue("Memory_Option", str420.c_str(), fround(Setting::fastrunkey));
	std::string str421 = "carsv"; ini.SetLongValue("Memory_Option", str421.c_str(), fround(Setting::carsv));
	std::string str422 = "instantv"; ini.SetLongValue("Memory_Option", str422.c_str(), fround(Setting::instantv));
	/* Size */
	std::string str = "Hp"; ini.SetLongValue("Font_Size", str.c_str(), fround(hp));
	std::string str401 = "Name"; ini.SetLongValue("Font_Size", str401.c_str(), fround(nsize));
	std::string str403 = "bbonesize"; ini.SetLongValue("Font_Size", str403.c_str(), fround(Setting::bbonesize));
	std::string str414 = "plinesize"; ini.SetLongValue("Font_Size", str414.c_str(), fround(Setting::plinesize));
	std::string str415 = "dissize"; ini.SetLongValue("Font_Size", str415.c_str(), fround(dissize));
	std::string str416 = "pcornersize"; ini.SetLongValue("Font_Size", str416.c_str(), fround(Setting::pcornersize));
	std::string str417 = "vehisize"; ini.SetLongValue("Font_Size", str417.c_str(), fround(vehisize));
	/* Option */
	std::string str402 = "Name_Option"; ini.SetLongValue("Option", str402.c_str(), fround(linne));
	std::string str404 = "skele_Option"; ini.SetLongValue("Option", str404.c_str(), fround(skelee));
	std::string str406 = "hpbt_Option"; ini.SetLongValue("Option", str406.c_str(), fround(hpbt));
	std::string str407 = "boxe_Option"; ini.SetLongValue("Option", str407.c_str(), fround(boxe));
	std::string str408 = "curraim_Option"; ini.SetLongValue("Option", str408.c_str(), fround(Setting::curraim));
	std::string str409 = "AimbotKey_Option"; ini.SetLongValue("Option", str409.c_str(), fround(Setting::AimbotKey));
	std::string str410 = "engine_Option"; ini.SetLongValue("Option", str410.c_str(), fround(Setting::engine));
	std::string str411 = "fovcircleredus_Option"; ini.SetLongValue("Option", str411.c_str(), fround(Setting::fovcircleredus));
	std::string str611 = "magicrange"; ini.SetLongValue("Option", str611.c_str(), fround(Setting::magicrange));
	std::string str412 = "Aimspeed_Option"; ini.SetLongValue("Option", str412.c_str(), fround(Setting::Aimspeed));
	std::string str423 = "Name_AWMS"; ini.SetLongValue("AWMS", str423.c_str(), fround(AWMS));
	std::string str425 = "Name_M416S"; ini.SetLongValue("M416S", str425.c_str(), fround(M416S));
	std::string str426 = "Name_SCARS"; ini.SetLongValue("SCARS", str426.c_str(), fround(SCARS));
	std::string str427 = "Name_M762S"; ini.SetLongValue("M762S", str427.c_str(), fround(M762S));
	std::string str428 = "Name_KARS"; ini.SetLongValue("KARS", str428.c_str(), fround(KARS));
	std::string str429 = "Name_VECTORS"; ini.SetLongValue("VECTORS", str429.c_str(), fround(VECTORS));
	std::string str430 = "Name_UZIS"; ini.SetLongValue("UZIS", str430.c_str(), fround(UZIS));
	std::string str431 = "Name_UMP9S"; ini.SetLongValue("UMP9S", str431.c_str(), fround(UMP9S));
	std::string str432 = "Name_SKSS"; ini.SetLongValue("SKSS", str432.c_str(), fround(SKSS));
	std::string str433 = "Name_QBZS"; ini.SetLongValue("QBZS", str433.c_str(), fround(QBZS));
	std::string str434 = "Name_QBUS"; ini.SetLongValue("QBUS", str434.c_str(), fround(QBUS));
	std::string str435 = "Name_PPS"; ini.SetLongValue("PPS", str435.c_str(), fround(PPS));
	std::string str436 = "Name_SLRS"; ini.SetLongValue("SLRS", str436.c_str(), fround(SLRS));
	std::string str437 = "Name_TOMMYS"; ini.SetLongValue("TOMMYS", str437.c_str(), fround(TOMMYS));
	std::string str438 = "Name_MP5KS"; ini.SetLongValue("MP5KS", str438.c_str(), fround(MP5KS));
	std::string str439 = "Name_MINIS"; ini.SetLongValue("MINIS", str439.c_str(), fround(MINIS));
	std::string str440 = "Name_M24S"; ini.SetLongValue("M24S", str440.c_str(), fround(M24S));
	std::string str441 = "Name_MK47S"; ini.SetLongValue("MK47S", str441.c_str(), fround(MK47S));
	std::string str442 = "Name_DPS"; ini.SetLongValue("DPS", str442.c_str(), fround(DPS));
	std::string str443 = "Name_G36CS"; ini.SetLongValue("G36CS", str443.c_str(), fround(G36CS));
	std::string str444 = "Name_AUGS"; ini.SetLongValue("AUGS", str444.c_str(), fround(AUGS));
	std::string str445 = "Name_AKMS"; ini.SetLongValue("AKMS", str445.c_str(), fround(AKMS));
	std::string str446 = "Name_Bag3S"; ini.SetLongValue("Bag3S", str446.c_str(), fround(Bag3S));
	std::string str447 = "Name_Helmet3S"; ini.SetLongValue("Helmet3S", str447.c_str(), fround(Helmet3S));
	std::string str448 = "Name_FLARES"; ini.SetLongValue("FLARES", str448.c_str(), fround(FLARES));
	std::string str449 = "Name_FLAREGS"; ini.SetLongValue("FLAREGS", str449.c_str(), fround(FLAREGS));
	std::string str450 = "Name_Armor3S"; ini.SetLongValue("Armor3S", str450.c_str(), fround(Armor3S));
	std::string str451 = "Name_MK12S"; ini.SetLongValue("MK12S", str451.c_str(), fround(MK12S));
	std::string str452 = "Name_M249S"; ini.SetLongValue("M249S", str452.c_str(), fround(M249S));
	std::string str453 = "Name_Armor2S"; ini.SetLongValue("Armor2S", str453.c_str(), fround(Armor2S));
	std::string str454 = "Name_Armor1S"; ini.SetLongValue("Armor1S", str454.c_str(), fround(Armor1S));
	std::string str455 = "Name_Helmet2S"; ini.SetLongValue("Helmet2S", str455.c_str(), fround(Helmet2S));
	std::string str456 = "Name_Helmet1S"; ini.SetLongValue("Helmet1S", str456.c_str(), fround(Helmet1S));
	std::string str457 = "Name_M16A4S"; ini.SetLongValue("M16A4S", str457.c_str(), fround(M16A4S));
	std::string str458 = "Name_HOLOS"; ini.SetLongValue("HOLOS", str458.c_str(), fround(HOLOS));
	std::string str459 = "Name_Bag2S"; ini.SetLongValue("Bag2S", str459.c_str(), fround(Bag2S));
	std::string str460 = "Name_Bag1S"; ini.SetLongValue("Bag1S", str460.c_str(), fround(Bag1S));
	std::string str461 = "Name_AMO9S"; ini.SetLongValue("AMO9S", str461.c_str(), fround(AMO9S));
	std::string str462 = "Name_AMO7S"; ini.SetLongValue("AMO7S", str462.c_str(), fround(AMO7S));
	std::string str463 = "Name_AMO5S"; ini.SetLongValue("AMO5S", str463.c_str(), fround(AMO5S));
	std::string str464 = "Name_AMO45S"; ini.SetLongValue("AMO45S", str464.c_str(), fround(AMO45S));
	std::string str465 = "Name_AMO300S"; ini.SetLongValue("AMO300S", str465.c_str(), fround(AMO300S));
	std::string str466 = "Name_SCOPE2S"; ini.SetLongValue("SCOPE2S", str466.c_str(), fround(SCOPE2S));
	std::string str467 = "Name_SCOPE3S"; ini.SetLongValue("SCOPE3S", str467.c_str(), fround(SCOPE3S));
	std::string str468 = "Name_SCOPE4S"; ini.SetLongValue("SCOPE4S", str468.c_str(), fround(SCOPE4S));
	std::string str469 = "Name_SCOPE6S"; ini.SetLongValue("SCOPE6S", str469.c_str(), fround(SCOPE6S));
	std::string str470 = "Name_SCOPE8S"; ini.SetLongValue("SCOPE8S", str470.c_str(), fround(SCOPE8S));
	std::string str471 = "Name_PAINS"; ini.SetLongValue("PAINS", str471.c_str(), fround(PAINS));
	std::string str472 = "Name_MEDS"; ini.SetLongValue("MEDS", str472.c_str(), fround(MEDS));
	std::string str473 = "Name_FIRSTS"; ini.SetLongValue("FIRSTS", str473.c_str(), fround(FIRSTS));
	std::string str474 = "Name_ADRES"; ini.SetLongValue("ADRES", str474.c_str(), fround(ADRES));
	std::string str475 = "Name_ENRES"; ini.SetLongValue("ENRES", str475.c_str(), fround(ENRES));
	std::string str476 = "Name_SMOKES"; ini.SetLongValue("SMOKES", str476.c_str(), fround(SMOKES));
	std::string str477 = "Name_MOLOS"; ini.SetLongValue("MOLOS", str477.c_str(), fround(MOLOS));
	std::string str478 = "Name_FRAGS"; ini.SetLongValue("FRAGS", str478.c_str(), fround(FRAGS));
	ini.SaveFile(Path.c_str());
}

void LoadSetting(std::string Path)
{
	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile(Path.c_str());
	if (rc < 0) { std::cout << "File not found"; };

#pragma region color attchment load
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QK_Choke_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QK_Choke_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QK_Mid_Compensator_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QK_Mid_Compensator_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QK_Sniper_Compensator_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QK_Sniper_Compensator_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QK_Mid_FlashHider_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QK_Mid_FlashHider_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QK_Sniper_FlashHider_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QK_Sniper_FlashHider_Pickup_C_1 ", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QK_Mid_Suppressor_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QK_Mid_Suppressor_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QK_Sniper_Suppressor_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QK_Sniper_Suppressor_Pickup_C_1 ", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QK_Large_Compensator_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QK_Large_Compensator_Pickup_C_1 ", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QK_Large_FlashHider_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QK_Large_FlashHider_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QK_Large_Suppressor_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QK_Large_Suppressor_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QK_DuckBill_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QK_DuckBill_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_WB_Angled_Pickup_C_1[i] = fround(ini.GetLongValue("BP_WB_Angled_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_WB_Vertical_Pickup_C_1[i] = fround(ini.GetLongValue("BP_WB_Vertical_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_WB_LightGrip_Pickup_C_1[i] = fround(ini.GetLongValue("BP_WB_LightGrip_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_WB_HalfGrip_Pickup_C_1[i] = fround(ini.GetLongValue("BP_WB_HalfGrip_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_WB_ThumbGrip_Pickup_C_1[i] = fround(ini.GetLongValue("BP_WB_ThumbGrip_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_WB_Lasersight_Pickup_C_1[i] = fround(ini.GetLongValue("BP_WB_Lasersight_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_MZJ_HD_Pickup_C_1[i] = fround(ini.GetLongValue("BP_MZJ_HD_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_MZJ_QX_Pickup_C_1[i] = fround(ini.GetLongValue("BP_MZJ_QX_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_MZJ_SideRMR_Pickup_C_1[i] = fround(ini.GetLongValue("BP_MZJ_SideRMR_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_ZDD_Sniper_Pickup_C_1[i] = fround(ini.GetLongValue("BP_ZDD_Sniper_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QT_UZI_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QT_UZI_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QT_A_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QT_A_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_QT_Sniper_Pickup_C_1[i] = fround(ini.GetLongValue("BP_QT_Sniper_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_ZDD_Crossbow_Q_Pickup_C_1[i] = fround(ini.GetLongValue("BP_ZDD_Crossbow_Q_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_DJ_Mid_E_Pickup_C_1[i] = fround(ini.GetLongValue("BP_DJ_Mid_E_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_DJ_Mid_Q_Pickup_C_1[i] = fround(ini.GetLongValue("BP_DJ_Mid_Q_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_DJ_Mid_EQ_Pickup_C_1[i] = fround(ini.GetLongValue("BP_DJ_Mid_EQ_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_DJ_Sniper_E_Pickup_C_1[i] = fround(ini.GetLongValue("BP_DJ_Sniper_E_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_DJ_Sniper_Q_Pickup_C_1[i] = fround(ini.GetLongValue("BP_DJ_Sniper_Q_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_DJ_Sniper_EQ_Pickup_C_1[i] = fround(ini.GetLongValue("BP_DJ_Sniper_EQ_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_DJ_Large_E_Pickup_C_1[i] = fround(ini.GetLongValue("BP_DJ_Large_E_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_DJ_Large_Q_Pickup_C_1[i] = fround(ini.GetLongValue("BP_DJ_Large_Q_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_DJ_Large_EQ_Pickup_C_1[i] = fround(ini.GetLongValue("BP_DJ_Large_EQ_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }

	///////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_Pistol_P92_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_Pistol_P92_Wrapper_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_Pistol_P1911_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_Pistol_P1911_Wrapper_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_Pistol_R1895_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_Pistol_R1895_Wrapper_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_Pistol_P18C_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_Pistol_P18C_Wrapper_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_Pistol_R45_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_Pistol_R45_Wrapper_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_Pistol_Vz61_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_Pistol_Vz61_Wrapper_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_Pistol_DesertEagle_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_Pistol_DesertEagle_Wrapper_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_ShotGun_SawedOff_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_ShotGun_SawedOff_Wrapper_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_WEP_Machete_Pickup_C_1[i] = fround(ini.GetLongValue("BP_WEP_Machete_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_WEP_Cowbar_Pickup_C_1[i] = fround(ini.GetLongValue("BP_WEP_Cowbar_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_WEP_Sickle_Pickup_C_1[i] = fround(ini.GetLongValue("BP_WEP_Sickle_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_WEP_Pan_Pickup_C_1[i] = fround(ini.GetLongValue("BP_WEP_Pan_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }

	////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_Sniper_VSS_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_Sniper_VSS_Wrapper_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_WEP_Mk14_Pickup_C_1[i] = fround(ini.GetLongValue("BP_WEP_Mk14_Pickup_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_Sniper_Win94_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_Sniper_Win94_Wrapper_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_Sniper_QBU_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_Sniper_QBU_Wrapper_C_1 ", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_Sniper_Mosin_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_Sniper_Mosin_Wrapper_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; BP_Sniper_MK12_Wrapper_C_1[i] = fround(ini.GetLongValue("BP_Sniper_MK12_Wrapper_C_1", str.append(std::to_string(i)).c_str()) / 255.0); }
	/////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_45ACP_Color[i] = fround(ini.GetLongValue("Esp_Item_45ACP_Color", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_9mm_Color[i] = fround(ini.GetLongValue("Esp_Item_9mm_Color", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_556mm_Color[i] = fround(ini.GetLongValue("Esp_Item_556mm_Color", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_762mm_Color[i] = fround(ini.GetLongValue("Esp_Item_762mm_Color", str.append(std::to_string(i)).c_str()) / 255.0); }

#pragma endregion

#pragma region settings 

	Setting::BP_QK_Choke_Pickup_C_1c = floattod3d(BP_QK_Choke_Pickup_C_1);
	Setting::BP_QK_Mid_Compensator_Pickup_C_1c = floattod3d(BP_QK_Mid_Compensator_Pickup_C_1);
	Setting::BP_QK_Sniper_Compensator_Pickup_C_1c = floattod3d(BP_QK_Sniper_Compensator_Pickup_C_1);
	Setting::BP_QK_Mid_FlashHider_Pickup_C_1c = floattod3d(BP_QK_Mid_FlashHider_Pickup_C_1);
	Setting::BP_QK_Sniper_FlashHider_Pickup_C_1c = floattod3d(BP_QK_Sniper_FlashHider_Pickup_C_1);
	Setting::BP_QK_Mid_Suppressor_Pickup_C_1c = floattod3d(BP_QK_Mid_Suppressor_Pickup_C_1);
	Setting::BP_QK_Sniper_Suppressor_Pickup_C_1c = floattod3d(BP_QK_Sniper_Suppressor_Pickup_C_1);
	Setting::BP_QK_Large_Compensator_Pickup_C_1c = floattod3d(BP_QK_Large_Compensator_Pickup_C_1);
	Setting::BP_QK_Large_FlashHider_Pickup_C_1c = floattod3d(BP_QK_Large_FlashHider_Pickup_C_1);
	Setting::BP_QK_Large_Suppressor_Pickup_C_1c = floattod3d(BP_QK_Large_Suppressor_Pickup_C_1);
	Setting::BP_QK_DuckBill_Pickup_C_1c = floattod3d(BP_QK_DuckBill_Pickup_C_1);
	Setting::BP_WB_Angled_Pickup_C_1c = floattod3d(BP_WB_Angled_Pickup_C_1);
	Setting::BP_WB_Vertical_Pickup_C_1c = floattod3d(BP_WB_Vertical_Pickup_C_1);
	Setting::BP_WB_LightGrip_Pickup_C_1c = floattod3d(BP_WB_LightGrip_Pickup_C_1);
	Setting::BP_WB_HalfGrip_Pickup_C_1c = floattod3d(BP_WB_HalfGrip_Pickup_C_1);
	Setting::BP_WB_ThumbGrip_Pickup_C_1c = floattod3d(BP_WB_ThumbGrip_Pickup_C_1);
	Setting::BP_WB_Lasersight_Pickup_C_1c = floattod3d(BP_WB_Lasersight_Pickup_C_1);
	Setting::BP_MZJ_HD_Pickup_C_1c = floattod3d(BP_MZJ_HD_Pickup_C_1);
	Setting::BP_MZJ_QX_Pickup_C_1c = floattod3d(BP_MZJ_QX_Pickup_C_1);
	Setting::BP_MZJ_SideRMR_Pickup_C_1c = floattod3d(BP_MZJ_SideRMR_Pickup_C_1);
	Setting::BP_ZDD_Sniper_Pickup_C_1c = floattod3d(BP_ZDD_Sniper_Pickup_C_1);
	Setting::BP_QT_UZI_Pickup_C_1c = floattod3d(BP_QT_UZI_Pickup_C_1);
	Setting::BP_QT_A_Pickup_C_1c = floattod3d(BP_QT_A_Pickup_C_1);
	Setting::BP_QT_Sniper_Pickup_C_1c = floattod3d(BP_QT_Sniper_Pickup_C_1);
	Setting::BP_ZDD_Crossbow_Q_Pickup_C_1c = floattod3d(BP_ZDD_Crossbow_Q_Pickup_C_1);
	Setting::BP_DJ_Mid_E_Pickup_C_1c = floattod3d(BP_DJ_Mid_E_Pickup_C_1);
	Setting::BP_DJ_Mid_Q_Pickup_C_1c = floattod3d(BP_DJ_Mid_Q_Pickup_C_1);
	Setting::BP_DJ_Mid_EQ_Pickup_C_1c = floattod3d(BP_DJ_Mid_EQ_Pickup_C_1);
	Setting::BP_DJ_Sniper_E_Pickup_C_1c = floattod3d(BP_DJ_Sniper_E_Pickup_C_1);
	Setting::BP_DJ_Sniper_Q_Pickup_C_1c = floattod3d(BP_DJ_Sniper_Q_Pickup_C_1);
	Setting::BP_DJ_Sniper_EQ_Pickup_C_1c = floattod3d(BP_DJ_Sniper_EQ_Pickup_C_1);
	Setting::BP_DJ_Large_E_Pickup_C_1c = floattod3d(BP_DJ_Large_E_Pickup_C_1);
	Setting::BP_DJ_Large_Q_Pickup_C_1c = floattod3d(BP_DJ_Large_Q_Pickup_C_1);
	Setting::BP_DJ_Large_EQ_Pickup_C_1c = floattod3d(BP_DJ_Large_EQ_Pickup_C_1);
	Setting::BP_Pistol_P92_Wrapper_C_1c = floattod3d(BP_Pistol_P92_Wrapper_C_1);
	Setting::BP_Pistol_P1911_Wrapper_C_1c = floattod3d(BP_Pistol_P1911_Wrapper_C_1);
	Setting::BP_Pistol_R1895_Wrapper_C_1c = floattod3d(BP_Pistol_R1895_Wrapper_C_1);
	Setting::BP_Pistol_P18C_Wrapper_C_1c = floattod3d(BP_Pistol_P18C_Wrapper_C_1);
	Setting::BP_Pistol_R45_Wrapper_C_1c = floattod3d(BP_Pistol_R45_Wrapper_C_1);
	Setting::BP_Pistol_Vz61_Wrapper_C_1c = floattod3d(BP_Pistol_Vz61_Wrapper_C_1);
	Setting::BP_Pistol_DesertEagle_Wrapper_C_1c = floattod3d(BP_Pistol_DesertEagle_Wrapper_C_1);
	Setting::BP_ShotGun_SawedOff_Wrapper_C_1c = floattod3d(BP_ShotGun_SawedOff_Wrapper_C_1);
	Setting::BP_ShotGun_S686_Wrapper_C_1c = floattod3d(BP_ShotGun_S686_Wrapper_C_1);
	Setting::BP_ShotGun_S1897_Wrapper_C_1c = floattod3d(BP_ShotGun_S1897_Wrapper_C_1);
	Setting::BP_ShotGun_S12K_Wrapper_C_1c = floattod3d(BP_ShotGun_S12K_Wrapper_C_1);
	Setting::BP_ShotGun_DP12_Wrapper_C_1c = floattod3d(BP_ShotGun_DP12_Wrapper_C_1);
	Setting::BP_ShotGun_M1014_Wrapper_C_1c = floattod3d(BP_ShotGun_M1014_Wrapper_C_1);
	Setting::BP_WEP_Machete_Pickup_C_1c = floattod3d(BP_WEP_Machete_Pickup_C_1);
	Setting::BP_WEP_Cowbar_Pickup_C_1c = floattod3d(BP_WEP_Cowbar_Pickup_C_1);
	Setting::BP_WEP_Sickle_Pickup_C_1c = floattod3d(BP_WEP_Sickle_Pickup_C_1);
	Setting::BP_WEP_Pan_Pickup_C_1c = floattod3d(BP_WEP_Pan_Pickup_C_1);
	Setting::BP_Sniper_VSS_Wrapper_C_1c = floattod3d(BP_Sniper_VSS_Wrapper_C_1);
	Setting::BP_WEP_Mk14_Pickup_C_1c = floattod3d(BP_WEP_Mk14_Pickup_C_1);
	Setting::BP_Sniper_Win94_Wrapper_C_1c = floattod3d(BP_Sniper_Win94_Wrapper_C_1);
	Setting::BP_Sniper_QBU_Wrapper_C_1c = floattod3d(BP_Sniper_QBU_Wrapper_C_1);
	Setting::BP_Sniper_Mosin_Wrapper_C_1c = floattod3d(BP_Sniper_Mosin_Wrapper_C_1);
	Setting::BP_Sniper_MK12_Wrapper_C_1c = floattod3d(BP_Sniper_MK12_Wrapper_C_1);

	Setting::LEsp_Item_762mm_Color = floattod3d(Esp_Item_762mm_Color); //{ 0.984f, 0.871f, 0.043f, 1.000f };
	Setting::LEsp_Item_556mm_Color = floattod3d(Esp_Item_556mm_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_9mm_Color = floattod3d(Esp_Item_9mm_Color); //{ 1.000f, 0.000f, 0.337f, 1.000f };
	Setting::LEsp_Item_45ACP_Color = floattod3d(Esp_Item_45ACP_Color); //{ 1.00f, 0.96f, 0.56f, 1.0f };

#pragma endregion

#pragma region Attchment Actives
	Setting::BP_QK_Choke_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QK_Choke_Pickup_C_1");
	Setting::BP_QK_Mid_Compensator_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QK_Mid_Compensator_Pickup_C_1");
	Setting::BP_QK_Sniper_Compensator_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QK_Sniper_Compensator_Pickup_C_1");
	Setting::BP_QK_Mid_FlashHider_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QK_Mid_FlashHider_Pickup_C_1");
	Setting::BP_QK_Sniper_FlashHider_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QK_Sniper_FlashHider_Pickup_C_1 ");
	Setting::BP_QK_Mid_Suppressor_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QK_Mid_Suppressor_Pickup_C_1");
	Setting::BP_QK_Sniper_Suppressor_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QK_Sniper_Suppressor_Pickup_C_1 ");
	Setting::BP_QK_Large_Compensator_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QK_Large_Compensator_Pickup_C_1 ");
	Setting::BP_QK_Large_FlashHider_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QK_Large_FlashHider_Pickup_C_1");
	Setting::BP_QK_Large_Suppressor_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QK_Large_Suppressor_Pickup_C_1");
	Setting::BP_QK_DuckBill_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QK_DuckBill_Pickup_C_1");
	Setting::BP_WB_Angled_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_WB_Angled_Pickup_C_1");
	Setting::BP_WB_Vertical_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_WB_Vertical_Pickup_C_1");
	Setting::BP_WB_LightGrip_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_WB_LightGrip_Pickup_C_1");
	Setting::BP_WB_HalfGrip_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_WB_HalfGrip_Pickup_C_1");
	Setting::BP_WB_ThumbGrip_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_WB_ThumbGrip_Pickup_C_1");
	Setting::BP_WB_Lasersight_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_WB_Lasersight_Pickup_C_1");
	Setting::BP_MZJ_HD_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_MZJ_HD_Pickup_C_1");
	Setting::BP_MZJ_QX_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_MZJ_QX_Pickup_C_1");
	Setting::BP_MZJ_SideRMR_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_MZJ_SideRMR_Pickup_C_1");
	Setting::BP_ZDD_Sniper_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_ZDD_Sniper_Pickup_C_1");
	Setting::BP_QT_UZI_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QT_UZI_Pickup_C_1");
	Setting::BP_QT_A_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QT_A_Pickup_C_1");
	Setting::BP_QT_Sniper_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_QT_Sniper_Pickup_C_1");
	Setting::BP_ZDD_Crossbow_Q_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_ZDD_Crossbow_Q_Pickup_C_1");
	Setting::BP_DJ_Mid_E_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_DJ_Mid_E_Pickup_C_1");
	Setting::BP_DJ_Mid_Q_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_DJ_Mid_Q_Pickup_C_1");
	Setting::BP_DJ_Mid_EQ_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_DJ_Mid_EQ_Pickup_C_1");
	Setting::BP_DJ_Sniper_E_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_DJ_Sniper_E_Pickup_C_1");
	Setting::BP_DJ_Sniper_Q_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_DJ_Sniper_Q_Pickup_C_1");
	Setting::BP_DJ_Sniper_EQ_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_DJ_Sniper_EQ_Pickup_C_1");
	Setting::BP_DJ_Large_E_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_DJ_Large_E_Pickup_C_1");
	Setting::BP_DJ_Large_Q_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_DJ_Large_Q_Pickup_C_1");
	Setting::BP_DJ_Large_EQ_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_DJ_Large_EQ_Pickup_C_1");
	Setting::BP_Pistol_P92_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_Pistol_P92_Wrapper_C_1");
	Setting::BP_Pistol_P1911_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_Pistol_P1911_Wrapper_C_1");
	Setting::BP_Pistol_R1895_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_Pistol_R1895_Wrapper_C_1");
	Setting::BP_Pistol_P18C_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_Pistol_P18C_Wrapper_C_1");
	Setting::BP_Pistol_R45_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_Pistol_R45_Wrapper_C_1");
	Setting::BP_Pistol_Vz61_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_Pistol_Vz61_Wrapper_C_1");
	Setting::BP_Pistol_DesertEagle_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_Pistol_DesertEagle_Wrapper_C_1");
	Setting::BP_ShotGun_SawedOff_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_ShotGun_SawedOff_Wrapper_C_1");
	Setting::BP_ShotGun_S686_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_ShotGun_S686_Wrapper_C_1");
	Setting::BP_ShotGun_S1897_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_ShotGun_S1897_Wrapper_C_1");
	Setting::BP_ShotGun_S12K_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_ShotGun_S12K_Wrapper_C_1");
	Setting::BP_ShotGun_DP12_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_ShotGun_DP12_Wrapper_C_1");
	Setting::BP_ShotGun_M1014_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_ShotGun_M1014_Wrapper_C_1");
	Setting::BP_WEP_Machete_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_WEP_Machete_Pickup_C_1");
	Setting::BP_WEP_Cowbar_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_WEP_Cowbar_Pickup_C_1");
	Setting::BP_WEP_Sickle_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_WEP_Sickle_Pickup_C_1");
	Setting::BP_WEP_Pan_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_WEP_Pan_Pickup_C_1");
	Setting::BP_Sniper_VSS_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_Sniper_VSS_Wrapper_C_1");
	Setting::BP_WEP_Mk14_Pickup_C_1 = ini.GetBoolValue("Esp", "BP_WEP_Mk14_Pickup_C_1");
	Setting::BP_Sniper_Win94_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_Sniper_Win94_Wrapper_C_1");
	Setting::BP_Sniper_QBU_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_Sniper_QBU_Wrapper_C_1");
	Setting::BP_Sniper_Mosin_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_Sniper_Mosin_Wrapper_C_1");
	Setting::BP_Sniper_MK12_Wrapper_C_1 = ini.GetBoolValue("Esp", "BP_Sniper_MK12_Wrapper_C_1");
	Setting::Esp_Item_45ACP = ini.GetBoolValue("Esp", "Esp_Item_45ACPm");
	Setting::Esp_Item_762mm = ini.GetBoolValue("Esp", "Esp_Item_762mmm");
	Setting::Esp_Item_556mm = ini.GetBoolValue("Esp", "Esp_Item_556mmm");
	Setting::Esp_Item_9mm = ini.GetBoolValue("Esp", "Esp_Item_9mmm");

#pragma endregion

#pragma region Font size attchment
	std::string str1 = "BP_QK_Choke_Pickup_C_1";
	std::string str2 = "BP_QK_Mid_Compensator_Pickup_C_1";
	std::string str3 = "BP_QK_Sniper_Compensator_Pickup_C_1";
	std::string str4 = "BP_QK_Mid_FlashHider_Pickup_C_1";
	std::string str5 = "BP_QK_Sniper_FlashHider_Pickup_C_1";
	std::string str6 = "BP_QK_Mid_Suppressor_Pickup_C_1";
	std::string str7 = "BP_QK_Sniper_Suppressor_Pickup_C_1";
	std::string str8 = "BP_QK_Large_Compensator_Pickup_C_1";
	std::string str9 = "BP_QK_Large_FlashHider_Pickup_C_1";
	std::string str10 = "BP_QK_Large_Suppressor_Pickup_C_1";
	std::string str11 = "BP_QK_DuckBill_Pickup_C_1";
	std::string str12 = "BP_WB_Angled_Pickup_C_1";
	std::string str13 = "BP_WB_Vertical_Pickup_C_1";
	std::string str14 = "BP_WB_LightGrip_Pickup_C_1";
	std::string str15 = "BP_WB_HalfGrip_Pickup_C_1";
	std::string str16 = "BP_WB_ThumbGrip_Pickup_C_1";
	std::string str17 = "BP_WB_Lasersight_Pickup_C_1";
	std::string str18 = "BP_MZJ_HD_Pickup_C_1";
	std::string str19 = "BP_MZJ_QX_Pickup_C_1";
	std::string str20 = "BP_MZJ_SideRMR_Pickup_C_1";
	std::string str21 = "BP_ZDD_Sniper_Pickup_C_1";
	std::string str22 = "BP_QT_UZI_Pickup_C_1";
	std::string str23 = "BP_QT_A_Pickup_C_1";
	std::string str24 = "BP_QT_Sniper_Pickup_C_1";
	std::string str25 = "BP_ZDD_Crossbow_Q_Pickup_C_1";
	std::string str26 = "BP_DJ_Mid_E_Pickup_C_1";
	std::string str27 = "BP_DJ_Mid_Q_Pickup_C_1";
	std::string str28 = "BP_DJ_Mid_EQ_Pickup_C_1";
	std::string str29 = "BP_DJ_Sniper_E_Pickup_C_1";
	std::string str30 = "BP_DJ_Sniper_Q_Pickup_C_1";
	std::string str31 = "BP_DJ_Sniper_EQ_Pickup_C_1";
	std::string str32 = "BP_DJ_Large_E_Pickup_C_1";
	std::string str33 = "BP_DJ_Large_Q_Pickup_C_1";
	std::string str34 = "BP_DJ_Large_EQ_Pickup_C_1";
	std::string str35 = "BP_Pistol_P92_Wrapper_C_1";
	std::string str36 = "BP_Pistol_P1911_Wrapper_C_1";
	std::string str37 = "BP_Pistol_R1895_Wrapper_C_1";
	std::string str38 = "BP_Pistol_P18C_Wrapper_C_1";
	std::string str39 = "BP_Pistol_R45_Wrapper_C_1";
	std::string str40 = "BP_Pistol_Vz61_Wrapper_C_1";
	std::string str41 = "BP_Pistol_DesertEagle_Wrapper_C_1";
	std::string str42 = "BP_ShotGun_SawedOff_Wrapper_C_1";
	std::string str43 = "BP_ShotGun_S686_Wrapper_C_1";
	std::string str44 = "BP_ShotGun_S1897_Wrapper_C_1";
	std::string str45 = "BP_ShotGun_S12K_Wrapper_C_1";
	std::string str46 = "BP_ShotGun_DP12_Wrapper_C_1";
	std::string str47 = "BP_ShotGun_M1014_Wrapper_C_1";
	std::string str48 = "BP_WEP_Machete_Pickup_C_1";
	std::string str49 = "BP_WEP_Cowbar_Pickup_C_1";
	std::string str50 = "BP_WEP_Sickle_Pickup_C_1";
	std::string str51 = "BP_WEP_Pan_Pickup_C_1";
	std::string str52 = "BP_Sniper_VSS_Wrapper_C_1";
	std::string str53 = "BP_WEP_Mk14_Pickup_C_1";
	std::string str54 = "BP_Sniper_Win94_Wrapper_C_1";
	std::string str55 = "BP_Sniper_QBU_Wrapper_C_1";
	std::string str56 = "BP_Sniper_Mosin_Wrapper_C_1";
	std::string str57 = "BP_Sniper_MK12_Wrapper_C_1";
	BP_QK_Choke_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str1.c_str()));
	BP_QK_Mid_Compensator_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str2.c_str()));
	BP_QK_Sniper_Compensator_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str3.c_str()));
	BP_QK_Mid_FlashHider_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str4.c_str()));
	BP_QK_Sniper_FlashHider_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str5.c_str()));
	BP_QK_Mid_Suppressor_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str6.c_str()));
	BP_QK_Sniper_Suppressor_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str7.c_str()));
	BP_QK_Large_Compensator_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str8.c_str()));
	BP_QK_Large_FlashHider_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str9.c_str()));
	BP_QK_Large_Suppressor_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str10.c_str()));
	BP_QK_DuckBill_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str11.c_str()));
	BP_WB_Angled_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str12.c_str()));
	BP_WB_Vertical_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str13.c_str()));
	BP_WB_LightGrip_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str14.c_str()));
	BP_WB_HalfGrip_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str15.c_str()));
	BP_WB_ThumbGrip_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str16.c_str()));
	BP_WB_Lasersight_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str17.c_str()));
	BP_MZJ_HD_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str18.c_str()));
	BP_MZJ_QX_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str19.c_str()));
	BP_MZJ_SideRMR_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str20.c_str()));
	BP_ZDD_Sniper_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str21.c_str()));
	BP_QT_UZI_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str22.c_str()));
	BP_QT_A_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str23.c_str()));
	BP_QT_Sniper_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str24.c_str()));
	BP_ZDD_Crossbow_Q_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str25.c_str()));
	BP_DJ_Mid_E_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str26.c_str()));
	BP_DJ_Mid_Q_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str27.c_str()));
	BP_DJ_Mid_EQ_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str28.c_str()));
	BP_DJ_Sniper_E_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str29.c_str()));
	BP_DJ_Sniper_Q_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str30.c_str()));
	BP_DJ_Sniper_EQ_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str31.c_str()));
	BP_DJ_Large_E_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str32.c_str()));
	BP_DJ_Large_Q_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str33.c_str()));
	BP_DJ_Large_EQ_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str34.c_str()));
	BP_Pistol_P92_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str35.c_str()));
	BP_Pistol_P1911_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str36.c_str()));
	BP_Pistol_R1895_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str37.c_str()));
	BP_Pistol_P18C_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str38.c_str()));
	BP_Pistol_R45_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str39.c_str()));
	BP_Pistol_Vz61_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str40.c_str()));
	BP_Pistol_DesertEagle_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str41.c_str()));
	BP_ShotGun_SawedOff_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str42.c_str()));
	BP_ShotGun_S686_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str43.c_str()));
	BP_ShotGun_S1897_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str44.c_str()));
	BP_ShotGun_S12K_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str45.c_str()));
	BP_ShotGun_DP12_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str46.c_str()));
	BP_ShotGun_M1014_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str47.c_str()));
	BP_WEP_Machete_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str48.c_str()));
	BP_WEP_Cowbar_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str49.c_str()));
	BP_WEP_Sickle_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str50.c_str()));
	BP_WEP_Pan_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str51.c_str()));
	BP_Sniper_VSS_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str52.c_str()));
	BP_WEP_Mk14_Pickup_C_1s = fround(ini.GetLongValue("Font_Size", str53.c_str()));
	BP_Sniper_Win94_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str54.c_str()));
	BP_Sniper_QBU_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str55.c_str()));
	BP_Sniper_Mosin_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str56.c_str()));
	BP_Sniper_MK12_Wrapper_C_1s = fround(ini.GetLongValue("Font_Size", str57.c_str()));

#pragma endregion

	for (int i = 0; i < 4; i++) { std::string str = "key"; m16[i] = fround(ini.GetLongValue("M416", str.append(std::to_string(i)).c_str()) / 255.0); }
	for (int i = 0; i < 4; i++) { std::string str = "key"; AWM[i] = fround(ini.GetLongValue("AWM", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; AWMimmo[i] = fround(ini.GetLongValue("AWMimmo", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.942f, 0.300f, 0.073f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; AirAttack[i] = fround(ini.GetLongValue("AirAttack", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; scarl[i] = fround(ini.GetLongValue("scarl", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; m762[i] = fround(ini.GetLongValue("m762", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; M24[i] = fround(ini.GetLongValue("M24", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; GROZZA[i] = fround(ini.GetLongValue("GROZZA", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; scope8x[i] = fround(ini.GetLongValue("scope8x", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.866f, 0.128f, 0.081f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; kar98[i] = fround(ini.GetLongValue("kar98", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Airdrop[i] = fround(ini.GetLongValue("Airdrop", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.279f, 0.990f, 0.812f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Flare[i] = fround(ini.GetLongValue("Flare", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.866f, 0.128f, 0.081f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Flaregun[i] = fround(ini.GetLongValue("Flaregun", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.0f, 0.60f,0.05f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; dp[i] = fround(ini.GetLongValue("dp", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; mg3[i] = fround(ini.GetLongValue("mg3", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; scope4x[i] = fround(ini.GetLongValue("scope4x", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.937f, 0.063f, 0.937f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; scope3x[i] = fround(ini.GetLongValue("scope3x", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.874f, 0.484f, 0.106f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; bag[i] = fround(ini.GetLongValue("bag", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.529f, 0.127f, 0.903f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; armer[i] = fround(ini.GetLongValue("armer", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.591f, 1.000f, 0.237f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; helmat[i] = fround(ini.GetLongValue("helmat", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.726f, 0.070f, 0.908f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; mosin[i] = fround(ini.GetLongValue("mosin", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; aug[i] = fround(ini.GetLongValue("aug", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; g36[i] = fround(ini.GetLongValue("g36", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.671f, 0.217f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; assm[i] = fround(ini.GetLongValue("assm", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.217f, 0.762f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Grandes[i] = fround(ini.GetLongValue("Grandes", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.396f, 0.357f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ammo7[i] = fround(ini.GetLongValue("ammo7", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.984f, 0.871f, 0.043f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; ammo5[i] = fround(ini.GetLongValue("ammo5", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; madkit[i] = fround(ini.GetLongValue("madkit", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.952f, 0.558f, 0.129f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; playerline[i] = fround(ini.GetLongValue("playerline", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.591f, 1.000f, 0.237f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; playercorner[i] = fround(ini.GetLongValue("playercorner", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.0f, 0.70f,0.30f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; playerbox[i] = fround(ini.GetLongValue("playerbox", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.0f, 1.0f,0.0f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; lotbox[i] = fround(ini.GetLongValue("lotbox", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.0f, 1.0f,0.0f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; helthbar[i] = fround(ini.GetLongValue("helthbar", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; boxColor[i] = fround(ini.GetLongValue("boxColor", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; cornerColor[i] = fround(ini.GetLongValue("cornerColor", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; crosshairColor[i] = fround(ini.GetLongValue("crosshairColor", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; bot[i] = fround(ini.GetLongValue("bot", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.016f, 0.725f, 0.929f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; player[i] = fround(ini.GetLongValue("player", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; vehicle[i] = fround(ini.GetLongValue("vehicle", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; botcorner[i] = fround(ini.GetLongValue("botcorner", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.050f, 0.125f, 0.925f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; botline[i] = fround(ini.GetLongValue("botline", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.050f, 0.025f, 0.925f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; circle[i] = fround(ini.GetLongValue("circle", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; enemy[i] = fround(ini.GetLongValue("enemy", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 255, 255, 255, 255 };
	for (int i = 0; i < 4; i++) { std::string str = "key"; botbox[i] = fround(ini.GetLongValue("botbox", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.950f, 0.125f, 0.925f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; bone[i] = fround(ini.GetLongValue("bone", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; fillrect[i] = fround(ini.GetLongValue("fillrect", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.950f, 0.125f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; nam[i] = fround(ini.GetLongValue("nam", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; nambar[i] = fround(ini.GetLongValue("nambar", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.880f, 0.185f, 0.25f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; bothealth[i] = fround(ini.GetLongValue("bothealth", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.95f, 0.125f, 0.825f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; botname[i] = fround(ini.GetLongValue("botname", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.050f, 0.825f, 0.185f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; playerhealth[i] = fround(ini.GetLongValue("playerhealth", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.50f, 0.725f, 0.105f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; textcolor[i] = fround(ini.GetLongValue("textcolor", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.500f, 0.150f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Granades[i] = fround(ini.GetLongValue("Granades", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.990f, 0.995f, 0.995f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; health[i] = fround(ini.GetLongValue("health", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.108f, 1.000f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; deadbox[i] = fround(ini.GetLongValue("deadbox", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.737f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; deadboxitem[i] = fround(ini.GetLongValue("deadboxitem", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.100f, 0.401f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; airdrop[i] = fround(ini.GetLongValue("airdrop", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.695f, 0.323f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; airdropitem[i] = fround(ini.GetLongValue("airdropitem", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.300f, 0.695f, 0.323f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; scopetextcolor[i] = fround(ini.GetLongValue("scopetextcolor", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 0.995f, 0.995f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; allitem[i] = fround(ini.GetLongValue("allitem", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.034f, 1.000f, 0.040f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; scope6x[i] = fround(ini.GetLongValue("scope6x", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.120f, 0.955f, 0.125f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; botbone[i] = fround(ini.GetLongValue("botbone", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.050f, 0.025f, 0.925f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; playerbone[i] = fround(ini.GetLongValue("playerbone", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.986f, 0.952f, 0.209f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; magicline[i] = fround(ini.GetLongValue("magicline", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 255, 0, 0, 255 };
	for (int i = 0; i < 4; i++) { std::string str = "key"; bgcorner[i] = fround(ini.GetLongValue("bgcorner", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.964f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; fovcirclecolor[i] = fround(ini.GetLongValue("fovcirclecolor", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 255, 0, 0, 255 };
	for (int i = 0; i < 4; i++) { std::string str = "key"; weapont[i] = fround(ini.GetLongValue("weapont", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 255,255,0,255 };
	for (int i = 0; i < 4; i++) { std::string str = "key"; skelec[i] = fround(ini.GetLongValue("skelec", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 255, 255, 255, 255 };
	for (int i = 0; i < 4; i++) { std::string str = "key"; hpt[i] = fround(ini.GetLongValue("hpt", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 255, 255, 255, 255 };
	for (int i = 0; i < 4; i++) { std::string str = "key"; plancolor[i] = fround(ini.GetLongValue("plancolor", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.737f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; dotss[i] = fround(ini.GetLongValue("dotss", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.950f, 0.125f, 0.925f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_AKM_Color[i] = fround(ini.GetLongValue("Esp_Item_AKM_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; M249[i] = fround(ini.GetLongValue("M249", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; MK12[i] = fround(ini.GetLongValue("MK12", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.00f, 0.796f, 0.715f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_M762_Color[i] = fround(ini.GetLongValue("Esp_Item_M762_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Mk47Mutant_Color[i] = fround(ini.GetLongValue("Esp_Item_Mk47Mutant_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.00f, 0.76f, 0.15f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_DP28_Color[i] = fround(ini.GetLongValue("Esp_Item_DP28_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_SCARL_Color[i] = fround(ini.GetLongValue("Esp_Item_SCARL_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.00f, 1.0f, 0.0f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_M416_Color[i] = fround(ini.GetLongValue("Esp_Item_M416_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_M16A4_Color[i] = fround(ini.GetLongValue("Esp_Item_M16A4_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.00f, 1.0f, 0.0f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_G36C_Color[i] = fround(ini.GetLongValue("Esp_Item_G36C_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_QBZ_Color[i] = fround(ini.GetLongValue("Esp_Item_QBZ_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_QBU_Color[i] = fround(ini.GetLongValue("Esp_Item_QBU_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_SLR_Color[i] = fround(ini.GetLongValue("Esp_Item_SLR_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.627f, 0.102f, 0.941f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_SKS_Color[i] = fround(ini.GetLongValue("Esp_Item_SKS_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.627f, 0.102f, 0.941f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Mini14_Color[i] = fround(ini.GetLongValue("Esp_Item_Mini14_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_M24_Color[i] = fround(ini.GetLongValue("Esp_Item_M24_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Kar98k_Color[i] = fround(ini.GetLongValue("Esp_Item_Kar98k_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_PP19_Color[i] = fround(ini.GetLongValue("Esp_Item_PP19_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_TommyGun_Color[i] = fround(ini.GetLongValue("Esp_Item_TommyGun_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_MP5K_Color[i] = fround(ini.GetLongValue("Esp_Item_MP5K_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_UMP9_Color[i] = fround(ini.GetLongValue("Esp_Item_UMP9_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Vector_Color[i] = fround(ini.GetLongValue("Esp_Item_Vector_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Uzi_Color[i] = fround(ini.GetLongValue("Esp_Item_Uzi_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_762mm_Color[i] = fround(ini.GetLongValue("Esp_Item_762mm_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.984f, 0.871f, 0.043f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_556mm_Color[i] = fround(ini.GetLongValue("Esp_Item_556mm_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 1.000f, 0.318f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_9mm_Color[i] = fround(ini.GetLongValue("Esp_Item_9mm_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.000f, 0.337f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_45ACP_Color[i] = fround(ini.GetLongValue("Esp_Item_45ACP_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.00f, 0.96f, 0.56f, 1.0f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Holo_Color[i] = fround(ini.GetLongValue("Esp_Item_Holo_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_x2_Color[i] = fround(ini.GetLongValue("Esp_Item_x2_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_x3_Color[i] = fround(ini.GetLongValue("Esp_Item_x3_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_x4_Color[i] = fround(ini.GetLongValue("Esp_Item_x4_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_x6_Color[i] = fround(ini.GetLongValue("Esp_Item_x6_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_x8_Color[i] = fround(ini.GetLongValue("Esp_Item_x8_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Bag1_Color[i] = fround(ini.GetLongValue("Esp_Item_Bag1_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Bag2_Color[i] = fround(ini.GetLongValue("Esp_Item_Bag2_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.627f, 0.102f, 0.941f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Bag3_Color[i] = fround(ini.GetLongValue("Esp_Item_Bag3_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Armor1_Color[i] = fround(ini.GetLongValue("Esp_Item_Armor1_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Armor1_Color[i] = fround(ini.GetLongValue("Esp_Item_Armor1_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.627f, 0.102f, 0.941f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Armor3_Color[i] = fround(ini.GetLongValue("Esp_Item_Armor3_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Helmet1_Color[i] = fround(ini.GetLongValue("Esp_Item_Helmet1_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.000f, 0.682f, 1.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Helmet2_Color[i] = fround(ini.GetLongValue("Esp_Item_Helmet2_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 0.627f, 0.102f, 0.941f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Helmet3_Color[i] = fround(ini.GetLongValue("Esp_Item_Helmet3_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Frag_Color[i] = fround(ini.GetLongValue("Esp_Item_Frag_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Smoke_Color[i] = fround(ini.GetLongValue("Esp_Item_Smoke_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Molotof_Color[i] = fround(ini.GetLongValue("Esp_Item_Molotof_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 1.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_MedKit_Color[i] = fround(ini.GetLongValue("Esp_Item_MedKit_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.753f, 0.796f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_FirstAidKit_Color[i] = fround(ini.GetLongValue("Esp_Item_FirstAidKit_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.753f, 0.796f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Painkiller_Color[i] = fround(ini.GetLongValue("Esp_Item_Painkiller_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.753f, 0.796f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_EnergyDrink_Color[i] = fround(ini.GetLongValue("Esp_Item_EnergyDrink_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.753f, 0.796f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_AdrenalineSyringe_Color[i] = fround(ini.GetLongValue("Esp_Item_AdrenalineSyringe_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.753f, 0.796f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_FlareGun_Color[i] = fround(ini.GetLongValue("Esp_Item_FlareGun_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_Flare_Color[i] = fround(ini.GetLongValue("Esp_Item_Flare_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.000f, 0.000f, 1.000f };
	for (int i = 0; i < 4; i++) { std::string str = "key"; Esp_Item_AirDrop_Color[i] = fround(ini.GetLongValue("Esp_Item_AirDrop_Color", str.append(std::to_string(i)).c_str()) / 255.0); } //{ 1.000f, 0.647f, 0.000f, 1.000f };

	Setting::M416 = floattod3d(m16); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LAKM = floattod3d(AKM); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LAWM = floattod3d(AWM); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LAWMimmo = floattod3d(AWMimmo); //{ 0.942f, 0.300f, 0.073f, 1.000f };
	Setting::LAirAttack = floattod3d(AirAttack); //{ 1.000f, 0.000f, 0.000f, 1.000f };
	Setting::Lscarl = floattod3d(scarl); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::Lm762 = floattod3d(m762); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LM24 = floattod3d(M24); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LGROZZA = floattod3d(GROZZA); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::Lscope8x = floattod3d(scope8x); //{ 0.866f, 0.128f, 0.081f, 1.000f };
	Setting::Lkar98 = floattod3d(kar98); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LAirdrop = floattod3d(Airdrop); //{ 0.279f, 0.990f, 0.812f, 1.000f };
	Setting::LFlare = floattod3d(Flare); //{ 0.866f, 0.128f, 0.081f, 1.000f };
	Setting::LFlaregun = floattod3d(Flaregun); //{ 1.0f, 0.60f,0.05f, 1.0f };
	Setting::Ldp = floattod3d(dp); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::Lmg3 = floattod3d(mg3); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::Lscope4x = floattod3d(scope4x); //{ 0.937f, 0.063f, 0.937f, 1.000f };
	Setting::Lscope3x = floattod3d(scope3x); //{ 0.874f, 0.484f, 0.106f, 1.000f };
	Setting::Lbag = floattod3d(bag); //{ 0.529f, 0.127f, 0.903f, 1.000f };
	Setting::Larmer = floattod3d(armer); //{ 0.591f, 1.000f, 0.237f, 1.000f };
	Setting::Lhelmat = floattod3d(helmat); //{ 0.726f, 0.070f, 0.908f, 1.000f };
	Setting::Lmosin = floattod3d(mosin); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::Laug = floattod3d(aug); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::Lg36 = floattod3d(g36); //{ 0.671f, 0.217f, 1.000f, 1.000f };
	Setting::Lassm = floattod3d(assm); //{ 1.000f, 0.217f, 0.762f, 1.000f };
	Setting::LGrandes = floattod3d(Grandes); //{ 1.000f, 0.396f, 0.357f, 1.000f };
	Setting::Lammo7 = floattod3d(ammo7); //{ 0.984f, 0.871f, 0.043f, 1.000f };
	Setting::Lammo5 = floattod3d(ammo5); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::Lmadkit = floattod3d(madkit); //{ 0.952f, 0.558f, 0.129f, 1.000f };
	Setting::Lplayerline = floattod3d(playerline); //{ 0.591f, 1.000f, 0.237f, 1.000f };
	Setting::Lplayercorner = floattod3d(playercorner); //{ 1.0f, 0.70f,0.30f, 1.0f };
	Setting::Lplayerbox = floattod3d(playerbox); //{ 1.0f, 1.0f,0.0f, 1.0f };
	Setting::Llotbox = floattod3d(lotbox); //{ 1.0f, 1.0f,0.0f, 1.0f };
	Setting::Lhelthbar = floattod3d(helthbar); //{ 0.950f, 0.125f, 0.125f, 1.0f };
	Setting::LboxColor = floattod3d(boxColor); //{ 0.950f, 0.125f, 0.125f, 1.0f };
	Setting::LcornerColor = floattod3d(cornerColor); //{ 0.950f, 0.125f, 0.125f, 1.0f };
	Setting::LcrosshairColor = floattod3d(crosshairColor); //{ 0.950f, 0.125f, 0.125f, 1.0f };
	Setting::Lbot = floattod3d(bot); //{ 0.016f, 0.725f, 0.929f, 1.0f };
	Setting::Lplayer = floattod3d(player); //{ 0.950f, 0.125f, 0.125f, 1.0f };
	Setting::Lvehicle = floattod3d(vehicle); //{ 1.000f, 1.000f, 0.000f, 1.000f };
	Setting::Lbotcorner = floattod3d(botcorner); //{ 0.050f, 0.125f, 0.925f, 1.0f };
	Setting::Lbotline = floattod3d(botline); //{ 0.050f, 0.025f, 0.925f, 1.0f };
	Setting::Lcircle = floattod3d(circle); //{ 0.950f, 0.125f, 0.125f, 1.0f };
	Setting::Lenemy = floattod3d(enemy); //{ 255, 255, 255, 255 };
	Setting::Lbotbox = floattod3d(botbox); //{ 0.950f, 0.125f, 0.925f, 1.0f };
	Setting::Lbone = floattod3d(bone); //{ 0.950f, 0.125f, 0.125f, 1.0f };
	Setting::Lfillrect = floattod3d(fillrect); //{ 0.950f, 0.125f, 0.125f, 1.0f };
	Setting::Lnam = floattod3d(nam); //{ 1.000f, 1.000f, 0.000f, 1.000f };
	Setting::Lnambar = floattod3d(nambar); //{ 0.880f, 0.185f, 0.25f, 1.0f };
	Setting::Lbothealth = floattod3d(bothealth); //{ 0.95f, 0.125f, 0.825f, 1.0f };
	Setting::Lbotname = floattod3d(botname); //{ 0.050f, 0.825f, 0.185f, 1.0f };
	Setting::Lplayerhealth = floattod3d(playerhealth); //{ 0.50f, 0.725f, 0.105f, 1.0f };
	Setting::Ltextcolor = floattod3d(textcolor); //{ 0.500f, 0.150f, 0.125f, 1.0f };
	Setting::LGranades = floattod3d(Granades); //{ 0.990f, 0.995f, 0.995f, 1.0f };
	Setting::Lhealth = floattod3d(health); //{ 0.108f, 1.000f, 1.000f, 1.000f };
	Setting::Ldeadbox = floattod3d(deadbox); //{ 0.737f, 1.000f, 0.000f, 1.000f };
	Setting::Ldeadboxitem = floattod3d(deadboxitem); //{ 1.000f, 0.100f, 0.401f, 1.000f };
	Setting::Lairdrop = floattod3d(airdrop); //{ 1.000f, 0.695f, 0.323f, 1.000f };
	Setting::Lairdropitem = floattod3d(airdropitem); //{ 0.300f, 0.695f, 0.323f, 1.000f };
	Setting::Lscopetextcolor = floattod3d(scopetextcolor); //{ 0.000f, 0.995f, 0.995f, 1.000f };
	Setting::Lallitem = floattod3d(allitem); //{ 0.034f, 1.000f, 0.040f, 1.000f };
	Setting::Lscope6x = floattod3d(scope6x); //{ 0.120f, 0.955f, 0.125f, 1.0f };
	Setting::Lbotbone = floattod3d(botbone); //{ 0.050f, 0.025f, 0.925f, 1.0f };
	Setting::Lplayerbone = floattod3d(playerbone); //{ 0.986f, 0.952f, 0.209f, 1.000f };
	Setting::Lmagicline = floattod3d(magicline); //{ 255, 0, 0, 255 };
	Setting::Lbgcorner = floattod3d(bgcorner); //{ 0.000f, 1.000f, 0.964f, 1.000f };
	Setting::Lfovcirclecolor = floattod3d(fovcirclecolor); //{ 255, 0, 0, 255 };
	Setting::Lweapont = floattod3d(weapont); //{ 255,255,0,255 };
	Setting::Lskelec = floattod3d(skelec); //{ 255, 255, 255, 255 };
	Setting::Lhpt = floattod3d(hpt); //{ 255, 255, 255, 255 };
	Setting::Lplancolor = floattod3d(plancolor); //{ 0.737f, 1.000f, 0.000f, 1.000f };
	Setting::Ldotss = floattod3d(dotss); //{ 0.950f, 0.125f, 0.925f, 1.0f };
	Setting::LEsp_Item_AKM_Color = floattod3d(Esp_Item_AKM_Color); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LM249 = floattod3d(M249); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LMK12 = floattod3d(MK12); //{ 1.00f, 0.796f, 0.715f, 1.0f };
	Setting::LEsp_Item_M762_Color = floattod3d(Esp_Item_M762_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_Mk47Mutant_Color = floattod3d(Esp_Item_Mk47Mutant_Color); //{ 1.00f, 0.76f, 0.15f, 1.0f };
	Setting::LEsp_Item_DP28_Color = floattod3d(Esp_Item_DP28_Color); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LEsp_Item_SCARL_Color = floattod3d(Esp_Item_SCARL_Color); //{ 0.00f, 1.0f, 0.0f, 1.0f };
	Setting::LEsp_Item_M416_Color = floattod3d(Esp_Item_M416_Color); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LEsp_Item_M16A4_Color = floattod3d(Esp_Item_M16A4_Color); //{ 0.00f, 1.0f, 0.0f, 1.0f };
	Setting::LEsp_Item_G36C_Color = floattod3d(Esp_Item_G36C_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_QBZ_Color = floattod3d(Esp_Item_QBZ_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_QBU_Color = floattod3d(Esp_Item_QBU_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_SLR_Color = floattod3d(Esp_Item_SLR_Color); //{ 0.627f, 0.102f, 0.941f, 1.000f };
	Setting::LEsp_Item_SKS_Color = floattod3d(Esp_Item_SKS_Color); //{ 0.627f, 0.102f, 0.941f, 1.000f };
	Setting::LEsp_Item_Mini14_Color = floattod3d(Esp_Item_Mini14_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_M24_Color = floattod3d(Esp_Item_M24_Color); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LEsp_Item_Kar98k_Color = floattod3d(Esp_Item_Kar98k_Color); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LEsp_Item_PP19_Color = floattod3d(Esp_Item_PP19_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_TommyGun_Color = floattod3d(Esp_Item_TommyGun_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_MP5K_Color = floattod3d(Esp_Item_MP5K_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_UMP9_Color = floattod3d(Esp_Item_UMP9_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_Vector_Color = floattod3d(Esp_Item_Vector_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_Uzi_Color = floattod3d(Esp_Item_Uzi_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_762mm_Color = floattod3d(Esp_Item_762mm_Color); //{ 0.984f, 0.871f, 0.043f, 1.000f };
	Setting::LEsp_Item_556mm_Color = floattod3d(Esp_Item_556mm_Color); //{ 0.000f, 1.000f, 0.318f, 1.000f };
	Setting::LEsp_Item_9mm_Color = floattod3d(Esp_Item_9mm_Color); //{ 1.000f, 0.000f, 0.337f, 1.000f };
	Setting::LEsp_Item_45ACP_Color = floattod3d(Esp_Item_45ACP_Color); //{ 1.00f, 0.96f, 0.56f, 1.0f };
	Setting::LEsp_Item_Holo_Color = floattod3d(Esp_Item_Holo_Color); //{ 0.000f, 0.682f, 1.000f, 1.000f };
	Setting::LEsp_Item_x2_Color = floattod3d(Esp_Item_x2_Color); //{ 0.000f, 0.682f, 1.000f, 1.000f };
	Setting::LEsp_Item_x3_Color = floattod3d(Esp_Item_x3_Color); //{ 0.000f, 0.682f, 1.000f, 1.000f };
	Setting::LEsp_Item_x4_Color = floattod3d(Esp_Item_x4_Color); //{ 0.000f, 0.682f, 1.000f, 1.000f };
	Setting::LEsp_Item_x6_Color = floattod3d(Esp_Item_x6_Color); //{ 1.000f, 0.000f, 0.000f, 1.000f };
	Setting::LEsp_Item_x8_Color = floattod3d(Esp_Item_x8_Color); //{ 1.000f, 0.000f, 0.000f, 1.000f };
	Setting::LEsp_Item_Bag1_Color = floattod3d(Esp_Item_Bag1_Color); //{ 0.000f, 0.682f, 1.000f, 1.000f };
	Setting::LEsp_Item_Bag2_Color = floattod3d(Esp_Item_Bag2_Color); //{ 0.627f, 0.102f, 0.941f, 1.000f };
	Setting::LEsp_Item_Bag3_Color = floattod3d(Esp_Item_Bag3_Color); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LEsp_Item_Armor1_Color = floattod3d(Esp_Item_Armor1_Color); //{ 0.000f, 0.682f, 1.000f, 1.000f };
	Setting::LEsp_Item_Armor1_Color = floattod3d(Esp_Item_Armor1_Color); //{ 0.627f, 0.102f, 0.941f, 1.000f };
	Setting::LEsp_Item_Armor3_Color = floattod3d(Esp_Item_Armor3_Color); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LEsp_Item_Helmet1_Color = floattod3d(Esp_Item_Helmet1_Color); //{ 0.000f, 0.682f, 1.000f, 1.000f };
	Setting::LEsp_Item_Helmet2_Color = floattod3d(Esp_Item_Helmet2_Color); //{ 0.627f, 0.102f, 0.941f, 1.000f };
	Setting::LEsp_Item_Helmet3_Color = floattod3d(Esp_Item_Helmet3_Color); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::LEsp_Item_Frag_Color = floattod3d(Esp_Item_Frag_Color); //{ 1.000f, 1.000f, 0.000f, 1.000f };
	Setting::LEsp_Item_Smoke_Color = floattod3d(Esp_Item_Smoke_Color); //{ 1.000f, 1.000f, 0.000f, 1.000f };
	Setting::LEsp_Item_Molotof_Color = floattod3d(Esp_Item_Molotof_Color); //{ 1.000f, 1.000f, 0.000f, 1.000f };
	Setting::LEsp_Item_MedKit_Color = floattod3d(Esp_Item_MedKit_Color); //{ 1.000f, 0.753f, 0.796f, 1.000f };
	Setting::LEsp_Item_FirstAidKit_Color = floattod3d(Esp_Item_FirstAidKit_Color); //{ 1.000f, 0.753f, 0.796f, 1.000f };
	Setting::LEsp_Item_Painkiller_Color = floattod3d(Esp_Item_Painkiller_Color); //{ 1.000f, 0.753f, 0.796f, 1.000f };
	Setting::LEsp_Item_EnergyDrink_Color = floattod3d(Esp_Item_EnergyDrink_Color); //{ 1.000f, 0.753f, 0.796f, 1.000f };
	Setting::LEsp_Item_AdrenalineSyringe_Color = floattod3d(Esp_Item_AdrenalineSyringe_Color); //{ 1.000f, 0.753f, 0.796f, 1.000f };
	Setting::LEsp_Item_FlareGun_Color = floattod3d(Esp_Item_FlareGun_Color); //{ 1.000f, 0.000f, 0.000f, 1.000f };
	Setting::LEsp_Item_Flare_Color = floattod3d(Esp_Item_Flare_Color); //{ 1.000f, 0.000f, 0.000f, 1.000f };
	Setting::LEsp_Item_AirDrop_Color = floattod3d(Esp_Item_AirDrop_Color); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	Setting::pname = ini.GetBoolValue("Esp", "pname");
	Setting::playerBone = ini.GetBoolValue("Esp", "playerBone");
	Setting::pline = ini.GetBoolValue("Esp", "pline");
	Setting::Distancee = ini.GetBoolValue("Esp", "Distancee");
	Setting::phealth = ini.GetBoolValue("Esp", "phealth");
	Setting::Name = ini.GetBoolValue("Esp", "Name");
	Setting::pcorner = ini.GetBoolValue("Esp", "pcorner");
	Setting::Item = ini.GetBoolValue("Esp", "Item");
	Setting::deadbox = ini.GetBoolValue("Esp", "deadbox");
	Setting::Vehicle = ini.GetBoolValue("Esp", "Vehicle");
	Setting::TotalEnemy = ini.GetBoolValue("Esp", "TotalEnemy");
	Setting::grw = ini.GetBoolValue("Esp", "grw");
	Setting::molow = ini.GetBoolValue("Esp", "molow");
	Setting::fovcircle = ini.GetBoolValue("Esp", "fovcircle");
	Setting::knocked = ini.GetBoolValue("Esp", "knocked");
	Setting::MAgicline = ini.GetBoolValue("Esp", "MAgicline");
	Setting::Esp_Item_M416 = ini.GetBoolValue("Esp", "Esp_Item_M416");
	Setting::Esp_Item_SCARL = ini.GetBoolValue("Esp", "Esp_Item_SCARL");
	Setting::Esp_Item_AKM = ini.GetBoolValue("Esp", "Esp_Item_AKM");
	Setting::Esp_Item_M762 = ini.GetBoolValue("Esp", "Esp_Item_M762");
	Setting::Esp_Item_DP28 = ini.GetBoolValue("Esp", "Esp_Item_DP28");
	Setting::Esp_Item_Awm = ini.GetBoolValue("Esp", "Esp_Item_Awm");
	Setting::Esp_Item_Kar98k = ini.GetBoolValue("Esp", "Esp_Item_Kar98k");
	Setting::Esp_Item_FlareGun = ini.GetBoolValue("Esp", "Esp_Item_FlareGun");
	Setting::Esp_Item_G36C = ini.GetBoolValue("Esp", "Esp_Item_G36C");
	Setting::Esp_Item_QBZ = ini.GetBoolValue("Esp", "Esp_Item_QBZ");
	Setting::Esp_Item_SLR = ini.GetBoolValue("Esp", "Esp_Item_SLR");
	Setting::Esp_Item_QBU = ini.GetBoolValue("Esp", "Esp_Item_QBU");
	Setting::Esp_Item_SKS = ini.GetBoolValue("Esp", "Esp_Item_SKS");
	Setting::Esp_Item_Mini14 = ini.GetBoolValue("Esp", "Esp_Item_Mini14");
	Setting::Esp_Item_PP19 = ini.GetBoolValue("Esp", "Esp_Item_PP19");
	Setting::Esp_Item_TommyGun = ini.GetBoolValue("Esp", "Esp_Item_TommyGun");
	Setting::Esp_Item_MP5K = ini.GetBoolValue("Esp", "Esp_Item_MP5K");
	Setting::Esp_Item_UMP9 = ini.GetBoolValue("Esp", "Esp_Item_UMP9");
	Setting::Esp_Item_Vector = ini.GetBoolValue("Esp", "Esp_Item_Vector");
	Setting::Esp_Item_Uzi = ini.GetBoolValue("Esp", "Esp_Item_Uzi");
	Setting::Esp_Item_Mk47Mutant = ini.GetBoolValue("Esp", "Esp_Item_Mk47Mutant");
	Setting::Esp_Item_Frag = ini.GetBoolValue("Esp", "Esp_Item_Frag");
	Setting::Esp_Item_Smoke = ini.GetBoolValue("Esp", "Esp_Item_Smoke");
	Setting::Esp_Item_Molotof = ini.GetBoolValue("Esp", "Esp_Item_Molotof");
	Setting::Esp_Item_MedKit = ini.GetBoolValue("Esp", "Esp_Item_MedKit");
	Setting::Esp_Item_FirstAidKit = ini.GetBoolValue("Esp", "Esp_Item_FirstAidKit");
	Setting::Esp_Item_Painkiller = ini.GetBoolValue("Esp", "Esp_Item_Painkiller");
	Setting::Esp_Item_EnergyDrink = ini.GetBoolValue("Esp", "Esp_Item_EnergyDrink");
	Setting::Esp_Item_AdrenalineSyringe = ini.GetBoolValue("Esp", "Esp_Item_AdrenalineSyringe");
	Setting::Esp_Item_Bag1 = ini.GetBoolValue("Esp", "Esp_Item_Bag1");
	Setting::Esp_Item_Bag2 = ini.GetBoolValue("Esp", "Esp_Item_Bag2");
	Setting::Esp_Item_Bag3 = ini.GetBoolValue("Esp", "Esp_Item_Bag3");
	Setting::Esp_Item_Helmet1 = ini.GetBoolValue("Esp", "Esp_Item_Helmet1");
	Setting::Esp_Item_Helmet2 = ini.GetBoolValue("Esp", "Esp_Item_Helmet2");
	Setting::Esp_Item_Helmet3 = ini.GetBoolValue("Esp", "Esp_Item_Helmet3");
	Setting::Esp_Item_Armor1 = ini.GetBoolValue("Esp", "Esp_Item_Armor1");
	Setting::Esp_Item_Armor2 = ini.GetBoolValue("Esp", "Esp_Item_Armor2");
	Setting::Esp_Item_Armor3 = ini.GetBoolValue("Esp", "Esp_Item_Armor3");
	Setting::Esp_Item_762mm = ini.GetBoolValue("Esp", "Esp_Item_762mm");
	Setting::Esp_Item_556mm = ini.GetBoolValue("Esp", "Esp_Item_556mm");
	Setting::Esp_Item_9mm = ini.GetBoolValue("Esp", "Esp_Item_9mm");
	Setting::Esp_Item_45ACP = ini.GetBoolValue("Esp", "Esp_Item_45ACP");
	Setting::Esp_Item_Awmimo = ini.GetBoolValue("Esp", "Esp_Item_Awmimo");
	Setting::Esp_Item_Holo = ini.GetBoolValue("Esp", "Esp_Item_Holo");
	Setting::Esp_Item_x2 = ini.GetBoolValue("Esp", "Esp_Item_x2");
	Setting::Esp_Item_x3 = ini.GetBoolValue("Esp", "Esp_Item_x3");
	Setting::Esp_Item_x4 = ini.GetBoolValue("Esp", "Esp_Item_x4");
	Setting::Esp_Item_x6 = ini.GetBoolValue("Esp", "Esp_Item_x6");
	Setting::Esp_Item_x8 = ini.GetBoolValue("Esp", "Esp_Item_x8");
	Setting::playerdeadbox = ini.GetBoolValue("Esp", "playerdeadbox");
	Setting::Aimbot = ini.GetBoolValue("Esp", "Aimbot");
	Setting::borderlo = ini.GetBoolValue("Esp", "borderlo");
	marco1 = ini.GetBoolValue("Esp", "marco1");


	/*Memory*/
	Setting::MagicBulletticked = ini.GetBoolValue("Memory", "MagicBulletticked");
	Setting::PREDICTION = ini.GetBoolValue("Memory", "PREDICTION");
	Setting::Legitrack = ini.GetBoolValue("Memory", "Legitrack");

	Setting::fastrun = ini.GetBoolValue("Memory", "fastrun");
	Setting::SkipKnocked = ini.GetBoolValue("Memory", "SkipKnocked");
	Setting::SkipBots = ini.GetBoolValue("Memory", "SkipBots");
	Setting::speedcar = ini.GetBoolValue("Memory", "speedcar");
	Setting::recoil = ini.GetBoolValue("Memory", "recoil");
	Setting::instanthit = ini.GetBoolValue("Memory", "instanthit");


	/*Memory Option*/
	std::string str418 = "magicv"; Setting::magicv = fround(ini.GetLongValue("Memory_Option", str418.c_str()));
	std::string str419 = "fastrv"; Setting::fastrv = fround(ini.GetLongValue("Memory_Option", str419.c_str()));
	std::string str420 = "fastrunkey"; Setting::fastrunkey = fround(ini.GetLongValue("Memory_Option", str420.c_str()));
	std::string str421 = "carsv"; Setting::carsv = fround(ini.GetLongValue("Memory_Option", str421.c_str()));
	std::string str422 = "instantv"; Setting::instantv = fround(ini.GetLongValue("Memory_Option", str422.c_str()));
	std::string str = "Hp"; hp = fround(ini.GetLongValue("Font_Size", str.c_str()));
	std::string str401 = "Name"; nsize = fround(ini.GetLongValue("Font_Size", str401.c_str()));
	std::string str403 = "pbonesize"; Setting::bbonesize = fround(ini.GetLongValue("Font_Size", str403.c_str()));
	std::string str414 = "plinesize"; Setting::plinesize = fround(ini.GetLongValue("Font_Size", str414.c_str()));
	std::string str415 = "dissize"; dissize = fround(ini.GetLongValue("Font_Size", str415.c_str()));
	std::string str416 = "pcornersize"; Setting::pcornersize = fround(ini.GetLongValue("Font_Size", str416.c_str()));
	std::string str402 = "Name_Option"; linne = fround(ini.GetLongValue("Option", str402.c_str()));
	std::string str404 = "skele_Option"; skelee = fround(ini.GetLongValue("Option", str404.c_str()));
	std::string str406 = "hpbt_Option"; hpbt = fround(ini.GetLongValue("Option", str406.c_str()));
	std::string str407 = "boxe_Option"; boxe = fround(ini.GetLongValue("Option", str407.c_str()));
	std::string str408 = "curraim_Option"; Setting::curraim = fround(ini.GetLongValue("Option", str408.c_str()));
	std::string str409 = "AimbotKey_Option"; Setting::AimbotKey = fround(ini.GetLongValue("Option", str409.c_str()));
	std::string str410 = "engine_Option"; Setting::engine = fround(ini.GetLongValue("Option", str410.c_str()));
	std::string str411 = "fovcircleredus_Option"; Setting::fovcircleredus = fround(ini.GetLongValue("Option", str411.c_str()));
	std::string str611 = "magicrange"; Setting::magicrange = fround(ini.GetLongValue("Option", str611.c_str()));
	std::string str412 = "Aimspeed_Option"; Setting::Aimspeed = fround(ini.GetLongValue("Option", str412.c_str()));

	std::string str423 = "Name_AWMS"; AWMS = fround(ini.GetLongValue("AWMS", str423.c_str()));
	std::string str425 = "Name_M416S"; M416S = fround(ini.GetLongValue("M416S", str425.c_str()));
	std::string str426 = "Name_SCARS"; SCARS = fround(ini.GetLongValue("SCARS", str426.c_str()));
	std::string str427 = "Name_M762S"; M762S = fround(ini.GetLongValue("M762S", str427.c_str()));
	std::string str428 = "Name_KARS"; KARS = fround(ini.GetLongValue("KARS", str428.c_str()));
	std::string str429 = "Name_VECTORS"; VECTORS = fround(ini.GetLongValue("VECTORS", str429.c_str()));
	std::string str430 = "Name_UZIS"; UZIS = fround(ini.GetLongValue("UZIS", str430.c_str()));
	std::string str431 = "Name_UMP9S"; UMP9S = fround(ini.GetLongValue("UMP9S", str431.c_str()));
	std::string str432 = "Name_SKSS"; SKSS = fround(ini.GetLongValue("SKSS", str432.c_str()));
	std::string str433 = "Name_QBZS"; QBZS = fround(ini.GetLongValue("QBZS", str433.c_str()));
	std::string str434 = "Name_QBUS"; QBUS = fround(ini.GetLongValue("QBUS", str434.c_str()));
	std::string str435 = "Name_PPS"; PPS = fround(ini.GetLongValue("PPS", str435.c_str()));
	std::string str436 = "Name_SLRS"; SLRS = fround(ini.GetLongValue("SLRS", str436.c_str()));
	std::string str437 = "Name_TOMMYS"; TOMMYS = fround(ini.GetLongValue("TOMMYS", str437.c_str()));
	std::string str438 = "Name_MP5KS"; MP5KS = fround(ini.GetLongValue("MP5KS", str438.c_str()));
	std::string str439 = "Name_MINIS"; MINIS = fround(ini.GetLongValue("MINIS", str439.c_str()));
	std::string str440 = "Name_M24S"; M24S = fround(ini.GetLongValue("M24S", str440.c_str()));
	std::string str441 = "Name_MK47S"; MK47S = fround(ini.GetLongValue("MK47S", str441.c_str()));
	std::string str442 = "Name_DPS"; DPS = fround(ini.GetLongValue("DPS", str442.c_str()));
	std::string str443 = "Name_G36CS"; G36CS = fround(ini.GetLongValue("G36CS", str443.c_str()));
	std::string str444 = "Name_AUGS"; AUGS = fround(ini.GetLongValue("AUGS", str444.c_str()));
	std::string str445 = "Name_AKMS"; AKMS = fround(ini.GetLongValue("AKMS", str445.c_str()));
	std::string str446 = "Name_Bag3S"; Bag3S = fround(ini.GetLongValue("Bag3S", str446.c_str()));
	std::string str447 = "Name_Helmet3S"; Helmet3S = fround(ini.GetLongValue("Helmet3S", str447.c_str()));
	std::string str448 = "Name_FLARES"; FLARES = fround(ini.GetLongValue("FLARES", str448.c_str()));
	std::string str449 = "Name_FLAREGS"; FLAREGS = fround(ini.GetLongValue("FLAREGS", str449.c_str()));
	std::string str450 = "Name_Armor3S"; Armor3S = fround(ini.GetLongValue("Armor3S", str450.c_str()));
	std::string str451 = "Name_MK12S"; MK12S = fround(ini.GetLongValue("MK12S", str451.c_str()));
	std::string str452 = "Name_M249S"; M249S = fround(ini.GetLongValue("M249S", str452.c_str()));
	std::string str453 = "Name_Armor2S"; Armor2S = fround(ini.GetLongValue("Armor2S", str453.c_str()));
	std::string str454 = "Name_Armor1S"; Armor1S = fround(ini.GetLongValue("Armor1S", str454.c_str()));
	std::string str455 = "Name_Helmet2S"; Helmet2S = fround(ini.GetLongValue("Helmet2S", str455.c_str()));
	std::string str456 = "Name_Helmet1S"; Helmet1S = fround(ini.GetLongValue("Helmet1S", str456.c_str()));
	std::string str457 = "Name_M16A4S"; M16A4S = fround(ini.GetLongValue("M16A4S", str457.c_str()));
	std::string str458 = "Name_HOLOS"; HOLOS = fround(ini.GetLongValue("HOLOS", str458.c_str()));
	std::string str459 = "Name_Bag2S"; Bag2S = fround(ini.GetLongValue("Bag2S", str459.c_str()));
	std::string str460 = "Name_Bag1S"; Bag1S = fround(ini.GetLongValue("Bag1S", str460.c_str()));
	std::string str461 = "Name_AMO9S"; AMO9S = fround(ini.GetLongValue("AMO9S", str461.c_str()));
	std::string str462 = "Name_AMO7S"; AMO7S = fround(ini.GetLongValue("AMO7S", str462.c_str()));
	std::string str463 = "Name_AMO5S"; AMO5S = fround(ini.GetLongValue("AMO5S", str463.c_str()));
	std::string str464 = "Name_AMO45S"; AMO45S = fround(ini.GetLongValue("AMO45S", str464.c_str()));
	std::string str465 = "Name_AMO300S"; AMO300S = fround(ini.GetLongValue("AMO300S", str465.c_str()));
	std::string str466 = "Name_SCOPE2S"; SCOPE2S = fround(ini.GetLongValue("SCOPE2S", str466.c_str()));
	std::string str467 = "Name_SCOPE3S"; SCOPE3S = fround(ini.GetLongValue("SCOPE3S", str467.c_str()));
	std::string str468 = "Name_SCOPE4S"; SCOPE4S = fround(ini.GetLongValue("SCOPE4S", str468.c_str()));
	std::string str469 = "Name_SCOPE6S"; SCOPE6S = fround(ini.GetLongValue("SCOPE6S", str469.c_str()));
	std::string str470 = "Name_SCOPE8S"; SCOPE8S = fround(ini.GetLongValue("SCOPE8S", str470.c_str()));
	std::string str471 = "Name_PAINS"; PAINS = fround(ini.GetLongValue("PAINS", str471.c_str()));
	std::string str472 = "Name_MEDS"; MEDS = fround(ini.GetLongValue("MEDS", str472.c_str()));
	std::string str473 = "Name_FIRSTS"; FIRSTS = fround(ini.GetLongValue("FIRSTS", str473.c_str()));
	std::string str474 = "Name_ADRES"; ADRES = fround(ini.GetLongValue("ADRES", str474.c_str()));
	std::string str475 = "Name_ENRES"; ENRES = fround(ini.GetLongValue("ENRES", str475.c_str()));
	std::string str476 = "Name_SMOKES"; SMOKES = fround(ini.GetLongValue("SMOKES", str476.c_str()));
	std::string str477 = "Name_MOLOS"; MOLOS = fround(ini.GetLongValue("MOLOS", str477.c_str()));
	std::string str478 = "Name_FRAGS"; FRAGS = fround(ini.GetLongValue("FRAGS", str478.c_str()));
}
#include <D3dx9tex.h>
#pragma comment(lib, "D3dx9")
LPDIRECT3DDEVICE9        g_pd3dDevice;

bool LoadTextureFromFile(LPCWSTR filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)	
{
	// Load texture from disk
	PDIRECT3DTEXTURE9 texture;

	HRESULT hr = D3DXCreateTextureFromFile(g_pd3dDevice, filename, &texture);
	if (hr != S_OK)
		return false;

	// Retrieve description of the texture surface so we can access its size
	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;
	return true;
}
void NationFlag(VECTOR3 Screen, AActor& AActor, int PosX, int PosY, int X, int Y)
{

	if (AActor.Nation == "JM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::JMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "G1")
	{
		DX11::ImGui_DX11::DrawImage(DX11::G1FLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AF")
	{
		DX11::ImGui_DX11::DrawImage(DX11::AFFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AL")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ALFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "DZ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::DZFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AS")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ASFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AD")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ADFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AO")
	{
		DX11::ImGui_DX11::DrawImage(DX11::AOFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AI")
	{
		DX11::ImGui_DX11::DrawImage(DX11::AIFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AQ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::AQFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::AGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ARFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::AMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AW")
	{
		DX11::ImGui_DX11::DrawImage(DX11::AWFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AU")
	{
		DX11::ImGui_DX11::DrawImage(DX11::AUFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AT")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ATFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AZ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::AZFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BS")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BSFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BH")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BHFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BD")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BDFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BB")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BBFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BY")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BYFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BZ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BZFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BJ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BJFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BT")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BTFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BO")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BOFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BQ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BQFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BA")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BAFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BW")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BWFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BV")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BVFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "IO")
	{
		DX11::ImGui_DX11::DrawImage(DX11::IOFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BN")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BNFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BF")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BFFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BI")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BIFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CV")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CVFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "KH")
	{
		DX11::ImGui_DX11::DrawImage(DX11::KHFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CA")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CAFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "KY")
	{
		DX11::ImGui_DX11::DrawImage(DX11::KYFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CF")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CFFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TD")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TDFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CL")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CLFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CN")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CNFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CX")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CXFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CC")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CCFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CO")
	{
		DX11::ImGui_DX11::DrawImage(DX11::COFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "KM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::KMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CD")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CDFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CK")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CKFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "HR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::HRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CU")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CUFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CW")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CWFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CY")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CYFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CZ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CZFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CI")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CIFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "DK")
	{
		DX11::ImGui_DX11::DrawImage(DX11::DKFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "DJ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::DJFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "DM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::DMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "DO")
	{
		DX11::ImGui_DX11::DrawImage(DX11::DOFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "EC")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ECFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "EG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::EGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SV")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SVFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GQ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GQFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "ER")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ERFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "EE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::EEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SZ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SZFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "ET")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ETFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "FK")
	{
		DX11::ImGui_DX11::DrawImage(DX11::FKFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "FO")
	{
		DX11::ImGui_DX11::DrawImage(DX11::FOFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "FJ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::FJFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "FI")
	{
		DX11::ImGui_DX11::DrawImage(DX11::FIFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "FR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::FRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GF")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GFFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PF")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PFFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TF")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TFFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GA")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GAFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "DE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::DEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GH")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GHFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GI")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GIFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GL")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GLFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GD")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GDFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GP")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GPFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GU")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GUFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GT")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GTFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GN")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GNFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GW")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GWFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GY")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GYFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "HT")
	{
		DX11::ImGui_DX11::DrawImage(DX11::HTFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "HM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::HMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "VA")
	{
		DX11::ImGui_DX11::DrawImage(DX11::VAFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "HN")
	{
		DX11::ImGui_DX11::DrawImage(DX11::HNFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "HK")
	{
		DX11::ImGui_DX11::DrawImage(DX11::HKFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "HU")
	{
		DX11::ImGui_DX11::DrawImage(DX11::HUFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "JP")
	{
		DX11::ImGui_DX11::DrawImage(DX11::JPFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "JE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::JEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "JO")
	{
		DX11::ImGui_DX11::DrawImage(DX11::JOFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "KZ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::KZFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "KE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::KEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "KI")
	{
		DX11::ImGui_DX11::DrawImage(DX11::KIFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "KP")
	{
		DX11::ImGui_DX11::DrawImage(DX11::KPFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "KR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::KRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "KW")
	{
		DX11::ImGui_DX11::DrawImage(DX11::KWFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "KG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::KGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "LA")
	{
		DX11::ImGui_DX11::DrawImage(DX11::LAFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "LV")
	{
		DX11::ImGui_DX11::DrawImage(DX11::LVFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "LB")
	{
		DX11::ImGui_DX11::DrawImage(DX11::LBFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "LS")
	{
		DX11::ImGui_DX11::DrawImage(DX11::LSFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "LR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::LRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "LY")
	{
		DX11::ImGui_DX11::DrawImage(DX11::LYFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "LI")
	{
		DX11::ImGui_DX11::DrawImage(DX11::LIFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "LT")
	{
		DX11::ImGui_DX11::DrawImage(DX11::LTFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "LU")
	{
		DX11::ImGui_DX11::DrawImage(DX11::LUFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MO")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MOFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MW")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MWFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MY")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MYFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MV")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MVFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "ML")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MLFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MT")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MTFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MH")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MHFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MQ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MQFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MU")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MUFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "YT")
	{
		DX11::ImGui_DX11::DrawImage(DX11::YTFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MX")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MXFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "FM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::FMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MD")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MDFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MC")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MCFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MN")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MNFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "ME")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MS")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MSFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MA")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MAFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MZ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MZFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "NA")
	{
		DX11::ImGui_DX11::DrawImage(DX11::NAFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "NR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::NRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "NP")
	{
		DX11::ImGui_DX11::DrawImage(DX11::NPFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "NL")
	{
		DX11::ImGui_DX11::DrawImage(DX11::NLFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "NC")
	{
		DX11::ImGui_DX11::DrawImage(DX11::NCFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "NZ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::NZFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "NI")
	{
		DX11::ImGui_DX11::DrawImage(DX11::NIFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "NE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::NEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "NG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::NGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "NU")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MUFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "NF")
	{
		DX11::ImGui_DX11::DrawImage(DX11::NFFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MP")
	{
		DX11::ImGui_DX11::DrawImage(DX11::NPFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "NO")
	{
		DX11::ImGui_DX11::DrawImage(DX11::NOFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "OM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::OMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PK")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PKFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PW")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PWFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PS")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PSFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PA")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PAFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PY")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PYFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PH")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PHFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PN")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PNFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PL")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PLFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PT")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PTFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "QA")
	{
		DX11::ImGui_DX11::DrawImage(DX11::QAFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MK")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MKFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "RO")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ROFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "RU")
	{
		DX11::ImGui_DX11::DrawImage(DX11::RUFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "RW")
	{
		DX11::ImGui_DX11::DrawImage(DX11::RWFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "RE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::REFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "BL")
	{
		DX11::ImGui_DX11::DrawImage(DX11::BLFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SH")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SHFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "KN")
	{
		DX11::ImGui_DX11::DrawImage(DX11::KNFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "LC")
	{
		DX11::ImGui_DX11::DrawImage(DX11::LCFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "MF")
	{
		DX11::ImGui_DX11::DrawImage(DX11::MFFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "PM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::PMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "VC")
	{
		DX11::ImGui_DX11::DrawImage(DX11::VCFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "WS")
	{
		DX11::ImGui_DX11::DrawImage(DX11::WSFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "ST")
	{
		DX11::ImGui_DX11::DrawImage(DX11::STFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SA")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SAFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SN")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SNFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "RS")
	{
		DX11::ImGui_DX11::DrawImage(DX11::RSFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SC")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SCFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SL")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SLFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SX")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SXFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SK")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SKFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SI")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SIFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SB")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SBFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SO")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SOFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "ZA")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ZAFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GS")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GSFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SS")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SSFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "ES")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ESFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "LK")
	{
		DX11::ImGui_DX11::DrawImage(DX11::LKFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SD")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SDFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SJ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SJFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "CH")
	{
		DX11::ImGui_DX11::DrawImage(DX11::CHFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "SY")
	{
		DX11::ImGui_DX11::DrawImage(DX11::SYFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TW")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TWFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TJ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TJFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TZ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TZFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TH")
	{
		DX11::ImGui_DX11::DrawImage(DX11::THFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TL")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TLFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TK")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TKFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TO")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TOFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TT")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TTFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TN")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TNFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TC")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TCFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "TV")
	{
		DX11::ImGui_DX11::DrawImage(DX11::TVFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "UG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::UGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "UA")
	{
		DX11::ImGui_DX11::DrawImage(DX11::UAFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::AEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "GB")
	{
		DX11::ImGui_DX11::DrawImage(DX11::GBFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "US")
	{
		DX11::ImGui_DX11::DrawImage(DX11::USFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "UY")
	{
		DX11::ImGui_DX11::DrawImage(DX11::UYFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "UZ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::UZFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "VU")
	{
		DX11::ImGui_DX11::DrawImage(DX11::VUFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "VE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::VEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "VN")
	{
		DX11::ImGui_DX11::DrawImage(DX11::VNFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "VG")
	{
		DX11::ImGui_DX11::DrawImage(DX11::VGFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "VI")
	{
		DX11::ImGui_DX11::DrawImage(DX11::VIFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "WF")
	{
		DX11::ImGui_DX11::DrawImage(DX11::WFFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "EH")
	{
		DX11::ImGui_DX11::DrawImage(DX11::EHFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "YE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::YEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "ZM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ZMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "ZW")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ZWFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "AX")
	{
		DX11::ImGui_DX11::DrawImage(DX11::AXFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "IS")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ISFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "IN")
	{
		DX11::ImGui_DX11::DrawImage(DX11::INFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "ID")
	{
		DX11::ImGui_DX11::DrawImage(DX11::IDFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "IR")
	{
		DX11::ImGui_DX11::DrawImage(DX11::IRFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "IQ")
	{
		DX11::ImGui_DX11::DrawImage(DX11::IQFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "IE")
	{
		DX11::ImGui_DX11::DrawImage(DX11::IEFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "IM")
	{
		DX11::ImGui_DX11::DrawImage(DX11::IMFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "IL")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ILFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
	if (AActor.Nation == "IT")
	{
		DX11::ImGui_DX11::DrawImage(DX11::ITFLAG, Screen.X - PosX, Screen.Y - PosY, X, Y);
	}
}




void RotateTriangle(std::array<VECTOR3, 3>& points, float rotation)
{
	const auto points_center = (points.at(0) + points.at(1) + points.at(2)) / 3;
	for (auto& point : points)
	{
		point = point - points_center;

		const auto temp_x = point.X;
		const auto temp_y = point.Y;

		const auto theta = DEG2RAD(rotation);
		const auto c = cosf(theta);
		const auto s = sinf(theta);

		point.X = temp_x * c - temp_y * s;
		point.Y = temp_x * s + temp_y * c;

		point = point + points_center;
	}
}

ImVec2 pos;
ImDrawList* draw;
float dpi_scale = 1.f;

void LegitTab()
{
	if (subtabs == 0)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##Aimbot", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{
				ImGui::ColorEdit4("Player Name", (float*)&Colors::magiclinevvisile, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
				ImGui::SameLine();
				ImGui::Checkbox("ESP Name", &Setting::pname);
				ImGui::SameLine();
				ImGui::Checkbox("Icon Player Flag", &Setting::pflag);
				ImGui::Checkbox("ESP Item", &Setting::Item);
				ImGui::SameLine();
				ImGui::Checkbox("Less Important Loot", &Setting::impitems);
				ImGui::Checkbox("ESP Health", &Setting::phealth);
				ImGui::Checkbox("Player Lines", &Setting::pline);
				ImGui::SameLine();
				ImGui::Checkbox("Offscreen Lines", &Setting::enemyoffscreen);
				ImGui::Checkbox("Player weapon", &Setting::playerweapon);
				ImGui::ColorEdit4("Player Bone", (float*)&Colors::playerbone, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
				ImGui::SameLine();
				ImGui::Checkbox("ESP Skeleton", &Setting::playerBone);
				ImGui::SameLine();
				ImGui::ColorEdit4("#Player Bone", (float*)&Colors::targetenemybone, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
				ImGui::SameLine();
				ImGui::Text("Target Enemy");
				ImGui::PushItemWidth(100);
				ImGui::SliderFloat("Skeleton Size", &Setting::pbonesize, 0.1f, 3.f, "%.3f");
				ImGui::ColorEdit4("pFull box", (float*)&Colors::playerbox, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
				ImGui::SameLine();
				ImGui::Checkbox("ESP BOX", &Setting::pfullbox);
				ImGui::ColorEdit4("pCorner Box", (float*)&Colors::playercorner, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
				ImGui::SameLine();
				ImGui::Checkbox("Corner Box", &Setting::pcorner);

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
	}
	if (subtabs == 1)
	{
 
	}
	if (subtabs == 2)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##Aimbot", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{
				//ImGui::Checkbox("Checkbox", &checkbox);
				//ImGui::SliderInt("SliderInt", &sliderint, 0, 100);
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
	}
}

void VisualsTab()
{

	if (subtabs == 0)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##Aimbot", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{
				//ImGui::Checkbox("Checkbox", &checkbox);
				//ImGui::SliderInt("SliderInt", &sliderint, 0, 100);
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
	}

	if (subtabs == 1)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##Aimbot", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{
				ImGui::Checkbox("Bullet Track", &Setting::MagicBulletticked);

				if (Setting::MagicBulletticked)
				{
					if (ImGui::TreeNodeEx("Aiming Settings"))
					{



						const char* aimb[] = { "Head", "Body", "Pelvis", "Auto" };
						const char* combo_label = aimb[Setting::curraim];
						if (ImGui::BeginCombo("Aim Position", combo_label))
						{
							for (int n = 0; n < IM_ARRAYSIZE(aimb); n++)
							{
								const bool is_selected = (Setting::curraim == n);
								if (ImGui::Selectable(aimb[n], is_selected))
									Setting::curraim = n;
								if (is_selected)
									ImGui::SetItemDefaultFocus();
							}
							ImGui::EndCombo();
						}
						ImGui::Text("Aim Key"); ImGui::SameLine(); ImGui::Hotkey("Aim Key", &Setting::AimbotKey, ImVec2(180.0f, 24));

						ImGui::Text("Aim Range"); ImGui::SameLine(); ImGui::SliderInt("Range", &Setting::magicrange, 0.0f, 300.0f);

						ImGui::Checkbox("FOV BASED TRACKING", &Setting::fovcircle);
						ImGui::SameLine();
						ImGui::ColorEdit4("FOV COLOR", Setting::fovcirclecolor, ImGuiColorEditFlags_NoInputs);
						if (Setting::fovcircle)
						{
							ImGui::SameLine();
							ImGui::SetNextItemWidth(210);

							ImGui::SliderFloat("FOV Size", &Setting::fovcircleredus, 20.0f, 400.0f);
						}
						ImGui::Checkbox("PREDICTION ", &Setting::PREDICTION);
						ImGui::Checkbox("Legit Tracking ", &Setting::Legitrack);
						ImGui::Checkbox("Skip Knocked", &Setting::SkipKnocked);
						ImGui::Checkbox("Skip BOTs", &Setting::SkipBots);



						ImGui::Unindent();
						ImGui::TreePop();
					}
				}			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
	}












}

int my_image_width = 20;
int my_image_height = 20;
PDIRECT3DTEXTURE9 my_texture = NULL;
void MiscTab()
{
	if (subtabs == 0)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##AR", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{
			
				if (ImGui::BeginTable("AR", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH   ))
				{
				
						ImGui::TableNextRow();

						ImGui::TableNextColumn();
						ImGui::Text("Name");
						ImGui::Checkbox("M416", &Setting::Esp_Item_M416);
						ImGui::Checkbox("SCAR-L", &Setting::Esp_Item_SCARL);
						ImGui::Checkbox("AKM", &Setting::Esp_Item_AKM);
						ImGui::Checkbox("M762", &Setting::Esp_Item_M762);
						ImGui::Checkbox("G36C", &Setting::Esp_Item_G36C);
						ImGui::Checkbox("QBZ", &Setting::Esp_Item_QBZ);
						ImGui::Checkbox("Mk47-Mutant", &Setting::Esp_Item_Mk47Mutant);

						ImGui::TableNextColumn();
						ImGui::Text("size");
						ImGui::SliderInt("01", &M416S, 0, 25);
						ImGui::SliderInt("02", &SCARS, 0, 25);
						ImGui::SliderInt("03", &AKMS, 0, 25);
						ImGui::SliderInt("05", &M762S, 0, 25);
						ImGui::SliderInt("11", &G36CS, 0, 25);
						ImGui::SliderInt("12", &QBZS, 0, 25);
						ImGui::SliderInt("23", &MK47S, 0, 25);

						ImGui::TableNextColumn();
						ImGui::Text("color");
						ImGui::ColorEdit4("M416", (float*)&m16, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
						ImGui::ColorEdit4("SCAR-L", (float*)&scarl, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
						ImGui::ColorEdit4("AKM", (float*)&AKM, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
						ImGui::ColorEdit4("M762", Esp_Item_M762_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
						ImGui::ColorEdit4("G36C", (float*)&Esp_Item_G36C_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
						ImGui::ColorEdit4("QBZ", (float*)&Esp_Item_QBZ_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
						ImGui::ColorEdit4("Mk47-Mutant", (float*)&Esp_Item_Mk47Mutant_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);


					ImGui::EndTable();
				}
			
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
	if (subtabs == 1)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##Sniper", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{

				if (ImGui::BeginTable("Sniper", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH))
				{

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Name");
					ImGui::Checkbox("AWM", &Setting::Esp_Item_Awm);
					ImGui::Checkbox("M24", &Setting::Esp_Item_M24);
					ImGui::Checkbox("KAR98", &Setting::Esp_Item_Kar98k);
					ImGui::Checkbox("SLR", &Setting::Esp_Item_SLR);
					ImGui::Checkbox("SKS", &Setting::Esp_Item_SKS);
					ImGui::Checkbox("Mini14", &Setting::Esp_Item_Mini14);
					ImGui::Checkbox("VSS", &Setting::BP_Sniper_VSS_Wrapper_C_1);
					ImGui::Checkbox("Mk14", &Setting::BP_WEP_Mk14_Pickup_C_1);
					ImGui::Checkbox("Win94", &Setting::BP_Sniper_Win94_Wrapper_C_1);
					ImGui::Checkbox("QBU", &Setting::BP_Sniper_QBU_Wrapper_C_1);
					ImGui::Checkbox("MosinNagant", &Setting::BP_Sniper_Mosin_Wrapper_C_1);
					ImGui::Checkbox("Mk12", &Setting::BP_Sniper_MK12_Wrapper_C_1);

					ImGui::TableNextColumn();
					ImGui::Text("size");
					ImGui::SliderInt("07", &AWMS, 0, 25);
					ImGui::SliderInt("08", &M24S, 0, 25);
					ImGui::SliderInt("09", &KARS, 0, 25);
					ImGui::SliderInt("14", &SLRS, 0, 25);
					ImGui::SliderInt("15", &SKSS, 0, 25);
					ImGui::SliderInt("16", &MINIS, 0, 25);
					ImGui::SliderInt("052", &BP_Sniper_VSS_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("053", &BP_WEP_Mk14_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("054", &BP_Sniper_Win94_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("055", &BP_Sniper_QBU_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("056", &BP_Sniper_Mosin_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("057", &BP_Sniper_MK12_Wrapper_C_1s, 0, 25);

					ImGui::TableNextColumn();
					ImGui::Text("color");
					ImGui::ColorEdit4("AMW", (float*)&AWM, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("M24", (float*)&M24, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("kar98", (float*)&kar98, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("SLR", (float*)&Esp_Item_SLR_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("SKS", (float*)&Esp_Item_SKS_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("Mini14", (float*)&Esp_Item_Mini14_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_Sniper_VSS_Wrapper_C_1", BP_Sniper_VSS_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_WEP_Mk14_Pickup_C_1", BP_WEP_Mk14_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_Sniper_Win94_Wrapper_C_1", BP_Sniper_Win94_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_Sniper_QBU_Wrapper_C_1", BP_Sniper_QBU_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_Sniper_Mosin_Wrapper_C_1", BP_Sniper_Mosin_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_Sniper_MK12_Wrapper_C_1", BP_Sniper_MK12_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);

					ImGui::EndTable();
				}

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
	if (subtabs == 2)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##SMG", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{

				if (ImGui::BeginTable("SMG", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH))
				{

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Name");
					ImGui::Checkbox("Uzi", &Setting::Esp_Item_Uzi);
					ImGui::Checkbox("UMP45", &Setting::Esp_Item_UMP9);
					ImGui::Checkbox("Vector", &Setting::Esp_Item_Vector);
					ImGui::Checkbox("Tommy Gun", &Setting::Esp_Item_TommyGun);
					ImGui::Checkbox("PP19", &Setting::Esp_Item_PP19);
					ImGui::Checkbox("MP5K", &Setting::Esp_Item_MP5K);

					ImGui::TableNextColumn();
					ImGui::Text("size");
					ImGui::SliderInt("22", &UZIS, 0, 25);
					ImGui::SliderInt("20", &UMP9S, 0, 25);
					ImGui::SliderInt("21", &VECTORS, 0, 25);
					ImGui::SliderInt("18", &TOMMYS, 0, 25);
					ImGui::SliderInt("17", &PPS, 0, 25);
					ImGui::SliderInt("19", &MP5KS, 0, 25);


					ImGui::TableNextColumn();
					ImGui::Text("color");
					ImGui::ColorEdit4("Uzi", (float*)&Esp_Item_Uzi_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("UMP9", (float*)&Esp_Item_UMP9_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("Vector", (float*)&Esp_Item_Vector_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("Tommy", (float*)&Esp_Item_TommyGun_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("PP19", (float*)&Esp_Item_PP19_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("MP5K", (float*)&Esp_Item_MP5K_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);

					ImGui::EndTable();
				}

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
	if (subtabs == 3)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##LMG", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{

				if (ImGui::BeginTable("LMG", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH))
				{

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Name");
					ImGui::Checkbox("DP28", &Setting::Esp_Item_DP28);
					ImGui::Checkbox("M249", &Setting::Esp_Item_M249);

					ImGui::TableNextColumn();
					ImGui::Text("size");
					ImGui::SliderInt("066", &DPS, 0, 25);
					ImGui::SliderInt("099", &M249s, 0, 25);


					ImGui::TableNextColumn();
					ImGui::Text("color");
					ImGui::ColorEdit4("DP28", Esp_Item_DP28_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("M249", M249, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);

					ImGui::EndTable();
				}

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
	if (subtabs == 4)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##SHOTGUN", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{

				if (ImGui::BeginTable("SHOTGUN", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH))
				{

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Name");
					ImGui::Checkbox("S686", &Setting::BP_ShotGun_S686_Wrapper_C_1);
					ImGui::Checkbox("S1897", &Setting::BP_ShotGun_S1897_Wrapper_C_1);
					ImGui::Checkbox("S12K", &Setting::BP_ShotGun_S12K_Wrapper_C_1);
					ImGui::Checkbox("DP12", &Setting::BP_ShotGun_DP12_Wrapper_C_1);
					ImGui::Checkbox("M1014 Shotgun", &Setting::BP_ShotGun_M1014_Wrapper_C_1);

					ImGui::TableNextColumn();
					ImGui::Text("size");
					ImGui::SliderInt("047", &BP_ShotGun_S686_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("048", &BP_ShotGun_S1897_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("049", &BP_ShotGun_S12K_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("050", &BP_ShotGun_DP12_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("051", &BP_ShotGun_M1014_Wrapper_C_1s, 0, 25);

					ImGui::TableNextColumn();
					ImGui::Text("color");
					ImGui::ColorEdit4("BP_ShotGun_S686_Wrapper_C_1", BP_ShotGun_S686_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_ShotGun_S1897_Wrapper_C_1", BP_ShotGun_S1897_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_ShotGun_S12K_Wrapper_C_1", BP_ShotGun_S12K_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_ShotGun_DP12_Wrapper_C_1", BP_ShotGun_DP12_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_ShotGun_M1014_Wrapper_C_1", BP_ShotGun_M1014_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);

					ImGui::EndTable();
				}

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
	if (subtabs == 5)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##SCOPE", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{

				if (ImGui::BeginTable("SCOPE", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH))
				{

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Name");
					ImGui::Checkbox("Holo", &Setting::Esp_Item_Holo);
					ImGui::Checkbox("x2", &Setting::Esp_Item_x2);
					ImGui::Checkbox("x3", &Setting::Esp_Item_x3);
					ImGui::Checkbox("x4", &Setting::Esp_Item_x4);
					ImGui::Checkbox("x6", &Setting::Esp_Item_x6);
					ImGui::Checkbox("x8", &Setting::Esp_Item_x8);

					ImGui::TableNextColumn();
					ImGui::Text("size");
					ImGui::SliderInt("38", &HOLOS, 0, 25);
					ImGui::SliderInt("39", &SCOPE2S, 0, 25);
					ImGui::SliderInt("40", &SCOPE3S, 0, 25);
					ImGui::SliderInt("41", &SCOPE4S, 0, 25);
					ImGui::SliderInt("42", &SCOPE6S, 0, 25);
					ImGui::SliderInt("43", &SCOPE8S, 0, 25);


					ImGui::TableNextColumn();
					ImGui::Text("color");
					ImGui::ColorEdit4("Holo", (float*)&Esp_Item_Holo_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("2X", Esp_Item_x2_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("3X", Esp_Item_x3_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("4X", Esp_Item_x4_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("6X", Esp_Item_x6_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("8X", Esp_Item_x8_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);

					ImGui::EndTable();
				}

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
	if (subtabs == 6)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##ATTACHMENT", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{

				if (ImGui::BeginTable("ATTACHMENT", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH))
				{

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Name");
					ImGui::Checkbox("Choke", &Setting::BP_QK_Choke_Pickup_C_1);
					ImGui::Checkbox("Compensator|SMG", &Setting::BP_QK_Mid_Compensator_Pickup_C_1);
					ImGui::Checkbox("Compensator (Snipers)", &Setting::BP_QK_Sniper_Compensator_Pickup_C_1);
					ImGui::Checkbox("Flash Hider (SMG)", &Setting::BP_QK_Mid_FlashHider_Pickup_C_1);
					ImGui::Checkbox("Flash Hider (Snipers)", &Setting::BP_QK_Sniper_FlashHider_Pickup_C_1);
					ImGui::Checkbox("Suppressor (SMG)", &Setting::BP_QK_Mid_Suppressor_Pickup_C_1);
					ImGui::Checkbox("Suppressor (Snipers)", &Setting::BP_QK_Sniper_Suppressor_Pickup_C_1);
					ImGui::Checkbox("Compensator (AR)", &Setting::BP_QK_Large_Compensator_Pickup_C_1);
					ImGui::Checkbox("Flash Hider (AR)", &Setting::BP_QK_Large_FlashHider_Pickup_C_1);
					ImGui::Checkbox("Suppressor (AR)", &Setting::BP_QK_Large_Suppressor_Pickup_C_1);
					ImGui::Checkbox("Duckbill (Shotguns)", &Setting::BP_QK_DuckBill_Pickup_C_1);
					ImGui::Checkbox("Angled Foregrip", &Setting::BP_WB_Angled_Pickup_C_1);
					ImGui::Checkbox("Vertical Foregrip", &Setting::BP_WB_Vertical_Pickup_C_1);
					ImGui::Checkbox("Light Grip", &Setting::BP_WB_LightGrip_Pickup_C_1);
					ImGui::Checkbox("Half Grip", &Setting::BP_WB_HalfGrip_Pickup_C_1);
					ImGui::Checkbox("Thumb Grip", &Setting::BP_WB_ThumbGrip_Pickup_C_1);
					ImGui::Checkbox("Laser Sight", &Setting::BP_WB_Lasersight_Pickup_C_1);
					ImGui::Checkbox("Canted Sight", &Setting::BP_MZJ_SideRMR_Pickup_C_1);
					ImGui::Checkbox("Bullet Loop (Shotguns, Sniper Rifles)", &Setting::BP_ZDD_Sniper_Pickup_C_1);
					ImGui::Checkbox("Stock (Micro UZI)", &Setting::BP_QT_UZI_Pickup_C_1);
					ImGui::Checkbox("Tactical Stock (Rifles, SMG)", &Setting::BP_QT_A_Pickup_C_1);
					ImGui::Checkbox("Cheek Pad (Snipers)", &Setting::BP_QT_Sniper_Pickup_C_1);
					ImGui::Checkbox("Quiver (Crossbow)", &Setting::BP_ZDD_Crossbow_Q_Pickup_C_1);
					ImGui::Checkbox("Extended Mag (SMG, Pistols)", &Setting::BP_DJ_Mid_E_Pickup_C_1);
					ImGui::Checkbox("Quickdraw Mag (SMG, Pistols)", &Setting::BP_DJ_Mid_Q_Pickup_C_1);
					ImGui::Checkbox("Extended Quickdraw Mag (SMG, Pistols)", &Setting::BP_DJ_Mid_EQ_Pickup_C_1);
					ImGui::Checkbox("Extended Mag (Snipers)", &Setting::BP_DJ_Sniper_E_Pickup_C_1);
					ImGui::Checkbox("Quickdraw Mag (Snipers)", &Setting::BP_DJ_Sniper_Q_Pickup_C_1);
					ImGui::Checkbox("Extended Quickdraw Mag (Snipers)", &Setting::BP_DJ_Sniper_EQ_Pickup_C_1);
					ImGui::Checkbox("Extended Quickdraw Mag (AR)", &Setting::BP_DJ_Large_E_Pickup_C_1);
					ImGui::Checkbox("Quickdraw Mag (AR)", &Setting::BP_DJ_Large_Q_Pickup_C_1);
					ImGui::Checkbox("Extended Quickdraw Mag (AR)", &Setting::BP_DJ_Large_EQ_Pickup_C_1);

					ImGui::TableNextColumn();
					ImGui::Text("size");
					ImGui::SliderInt("001", &BP_QK_Choke_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("002", &BP_QK_Mid_Compensator_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("003", &BP_QK_Sniper_Compensator_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("004", &BP_QK_Mid_FlashHider_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("005", &BP_QK_Sniper_FlashHider_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("006", &BP_QK_Mid_Suppressor_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("007", &BP_QK_Sniper_Suppressor_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("008", &BP_QK_Large_Compensator_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("009", &BP_QK_Large_FlashHider_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("010", &BP_QK_Large_Suppressor_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("011", &BP_QK_DuckBill_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("012", &BP_WB_Angled_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("013", &BP_WB_Vertical_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("014", &BP_WB_LightGrip_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("015", &BP_WB_HalfGrip_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("016", &BP_WB_ThumbGrip_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("017", &BP_WB_Lasersight_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("020", &BP_MZJ_SideRMR_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("021", &BP_ZDD_Sniper_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("022", &BP_QT_UZI_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("023", &BP_QT_A_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("024", &BP_QT_Sniper_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("025", &BP_ZDD_Crossbow_Q_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("026", &BP_DJ_Mid_E_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("027", &BP_DJ_Mid_Q_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("028", &BP_DJ_Mid_EQ_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("029", &BP_DJ_Sniper_E_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("030", &BP_DJ_Sniper_Q_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("031", &BP_DJ_Sniper_EQ_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("032", &BP_DJ_Large_E_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("033", &BP_DJ_Large_Q_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("034", &BP_DJ_Large_EQ_Pickup_C_1s, 0, 25);

					ImGui::TableNextColumn();
					ImGui::Text("color");
					ImGui::ColorEdit4("BP_QK_Choke_Pickup_C_1", BP_QK_Choke_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QK_Mid_Compensator_Pickup_C_1", BP_QK_Mid_Compensator_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QK_Sniper_Compensator_Pickup_C_1 ", BP_QK_Sniper_Compensator_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QK_Mid_FlashHider_Pickup_C_1", BP_QK_Mid_FlashHider_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QK_Sniper_FlashHider_Pickup_C_1", BP_QK_Sniper_FlashHider_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QK_Mid_Suppressor_Pickup_C_1", BP_QK_Mid_Suppressor_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QK_Sniper_Suppressor_Pickup_C_1", BP_QK_Sniper_Suppressor_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QK_Large_Compensator_Pickup_C_1", BP_QK_Large_Compensator_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QK_Large_FlashHider_Pickup_C_1", BP_QK_Large_FlashHider_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QK_Large_Suppressor_Pickup_C_1", BP_QK_Large_Suppressor_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QK_DuckBill_Pickup_C_1", BP_QK_DuckBill_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_WB_Angled_Pickup_C_1", BP_WB_Angled_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_WB_Vertical_Pickup_C_1", BP_WB_Vertical_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_WB_LightGrip_Pickup_C_1", BP_WB_LightGrip_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_WB_HalfGrip_Pickup_C_1", BP_WB_HalfGrip_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_WB_ThumbGrip_Pickup_C_1", BP_WB_ThumbGrip_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_WB_Lasersight_Pickup_C_1", BP_WB_Lasersight_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_MZJ_SideRMR_Pickup_C_1", BP_MZJ_SideRMR_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_ZDD_Sniper_Pickup_C_1", BP_ZDD_Sniper_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QT_UZI_Pickup_C_1", BP_QT_UZI_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QT_A_Pickup_C_1", BP_QT_A_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_QT_Sniper_Pickup_C_1", BP_QT_Sniper_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_ZDD_Crossbow_Q_Pickup_C_1", BP_ZDD_Crossbow_Q_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_DJ_Mid_E_Pickup_C_1", BP_DJ_Mid_E_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_DJ_Mid_Q_Pickup_C_1", BP_DJ_Mid_Q_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_DJ_Mid_EQ_Pickup_C_1", BP_DJ_Mid_EQ_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_DJ_Sniper_E_Pickup_C_1", BP_DJ_Sniper_E_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_DJ_Sniper_Q_Pickup_C_1", BP_DJ_Sniper_Q_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_DJ_Sniper_EQ_Pickup_C_1", BP_DJ_Sniper_EQ_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_DJ_Large_E_Pickup_C_1", BP_DJ_Large_E_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_DJ_Large_Q_Pickup_C_1", BP_DJ_Large_Q_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_DJ_Large_EQ_Pickup_C_1", BP_DJ_Large_EQ_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::EndTable();
				}

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
	if (subtabs == 7)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##PISTOL", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{

				if (ImGui::BeginTable("table2", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH))
				{

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Name");
					ImGui::Checkbox("P92", &Setting::BP_Pistol_P92_Wrapper_C_1);
					ImGui::Checkbox("P1911", &Setting::BP_Pistol_P1911_Wrapper_C_1);
					ImGui::Checkbox("R1895", &Setting::BP_Pistol_R1895_Wrapper_C_1);
					ImGui::Checkbox("P18C", &Setting::BP_Pistol_P18C_Wrapper_C_1);
					ImGui::Checkbox("R45", &Setting::BP_Pistol_R45_Wrapper_C_1);
					ImGui::Checkbox("Vz61", &Setting::BP_Pistol_Vz61_Wrapper_C_1);
					ImGui::Checkbox("Desert Eagle", &Setting::BP_Pistol_DesertEagle_Wrapper_C_1);
					ImGui::Checkbox("Sawed-off", &Setting::BP_ShotGun_SawedOff_Wrapper_C_1);

					ImGui::TableNextColumn();
					ImGui::Text("size");
					ImGui::SliderInt("035", &BP_Pistol_P92_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("036", &BP_Pistol_P1911_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("037", &BP_Pistol_R1895_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("038", &BP_Pistol_P18C_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("039", &BP_Pistol_R45_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("040", &BP_Pistol_Vz61_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("041", &BP_Pistol_DesertEagle_Wrapper_C_1s, 0, 25);
					ImGui::SliderInt("042", &BP_ShotGun_SawedOff_Wrapper_C_1s, 0, 25);

					ImGui::TableNextColumn();
					ImGui::Text("color");
					ImGui::ColorEdit4("BP_Pistol_P92_Wrapper_C_1", BP_Pistol_P92_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_Pistol_P1911_Wrapper_C_1", BP_Pistol_P1911_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_Pistol_R1895_Wrapper_C_1", BP_Pistol_R1895_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_Pistol_P18C_Wrapper_C_1", BP_Pistol_P18C_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_Pistol_R45_Wrapper_C_1", BP_Pistol_R45_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_Pistol_Vz61_Wrapper_C_1", BP_Pistol_Vz61_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_Pistol_DesertEagle_Wrapper_C_1", BP_Pistol_DesertEagle_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_ShotGun_SawedOff_Wrapper_C_1", BP_ShotGun_SawedOff_Wrapper_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::EndTable();
				}

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
	if (subtabs == 8)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##MELEE", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{

				if (ImGui::BeginTable("MELEE", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH))
				{

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Name");
					ImGui::Checkbox("Machete", &Setting::BP_WEP_Machete_Pickup_C_1);
					ImGui::Checkbox("Crowbar", &Setting::BP_WEP_Cowbar_Pickup_C_1);
					ImGui::Checkbox("Sickle", &Setting::BP_WEP_Sickle_Pickup_C_1);
					ImGui::Checkbox("Pan", &Setting::BP_WEP_Pan_Pickup_C_1);

					ImGui::TableNextColumn();
					ImGui::Text("size");
					ImGui::SliderInt("043", &BP_WEP_Machete_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("044", &BP_WEP_Cowbar_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("045", &BP_WEP_Sickle_Pickup_C_1s, 0, 25);
					ImGui::SliderInt("046", &BP_WEP_Pan_Pickup_C_1s, 0, 25);

					ImGui::TableNextColumn();
					ImGui::Text("color");
					ImGui::ColorEdit4("BP_WEP_Machete_Pickup_C_1", BP_WEP_Machete_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_WEP_Cowbar_Pickup_C_1 ", BP_WEP_Cowbar_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_WEP_Sickle_Pickup_C_1 ", BP_WEP_Sickle_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
					ImGui::ColorEdit4("BP_WEP_Pan_Pickup_C_1", BP_WEP_Pan_Pickup_C_1, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);

					ImGui::EndTable();
				}

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
	if (subtabs == 9)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##AMMO", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{

				if (ImGui::BeginTable("AMMO", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH))
				{

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Name");
					ImGui::Checkbox("7.62mm", &Setting::Esp_Item_762mm);
					ImGui::Checkbox("5.56mm", &Setting::Esp_Item_556mm);
					ImGui::Checkbox("9mm", &Setting::Esp_Item_9mm);
					ImGui::Checkbox("45ACP", &Setting::Esp_Item_45ACP);
					ImGui::Checkbox("AWM Ammo", &Setting::Esp_Item_Awmimo);

					ImGui::TableNextColumn();
					ImGui::Text("size");
					ImGui::SliderInt("32", &AMO7S, 0, 25);
					ImGui::SliderInt("34", &AMO5S, 0, 25);
					ImGui::SliderInt("35", &AMO9S, 0, 25);
					ImGui::SliderInt("36", &AMO7S, 0, 25);
					ImGui::SliderInt("37", &AMO300S, 0, 25);


					ImGui::TableNextColumn();
					ImGui::Text("color");
					ImGui::ColorEdit4("762mm", (float*)&Esp_Item_762mm_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("556mm", (float*)&Esp_Item_556mm_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("9mm", (float*)&Esp_Item_9mm_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("45ACP", (float*)&Esp_Item_45ACP_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("awm ammo", (float*)&AWMimmo, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);

					ImGui::EndTable();
				}

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
	if (subtabs == 10)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##GEARS", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{

				if (ImGui::BeginTable("GEARS", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH))
				{

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Name");
					ImGui::Checkbox("Helmet 1", &Setting::Esp_Item_Helmet1);
					ImGui::Checkbox("Helmet 2", &Setting::Esp_Item_Helmet2);
					ImGui::Checkbox("Helmet 3", &Setting::Esp_Item_Helmet3);
					ImGui::Checkbox("Armor 1", &Setting::Esp_Item_Armor1);
					ImGui::Checkbox("Armor 2", &Setting::Esp_Item_Armor2);
					ImGui::Checkbox("Armor 3", &Setting::Esp_Item_Armor3);
					ImGui::Checkbox("Bag 1", &Setting::Esp_Item_Bag1);
					ImGui::Checkbox("Bag 2", &Setting::Esp_Item_Bag2);
					ImGui::Checkbox("Bag 3", &Setting::Esp_Item_Bag3);

					ImGui::TableNextColumn();
					ImGui::Text("size");
					ImGui::SliderInt("27", &Helmet1S, 0, 25);
					ImGui::SliderInt("28", &Helmet2S, 0, 25);
					ImGui::SliderInt("29", &Helmet3S, 0, 25);
					ImGui::SliderInt("30", &Armor1S, 0, 25);
					ImGui::SliderInt("31", &Armor2S, 0, 25);
					ImGui::SliderInt("32", &Armor3S, 0, 25);
					ImGui::SliderInt("24", &Bag1S, 0, 25);
					ImGui::SliderInt("25", &Bag2S, 0, 25);
					ImGui::SliderInt("26", &Bag3S, 0, 25);


					ImGui::TableNextColumn();
					ImGui::Text("color");
					ImGui::ColorEdit4("Helmet 1", Esp_Item_Helmet1_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Helmet 2", Esp_Item_Helmet2_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Helmet 3", Esp_Item_Helmet3_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Armor 1", Esp_Item_Armor1_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Armor 2", Esp_Item_Armor2_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Armor 3", Esp_Item_Armor3_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Bag 1", Esp_Item_Bag1_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Bag 2", Esp_Item_Bag2_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Bag 3", Esp_Item_Bag3_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);

					ImGui::EndTable();
				}

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
	if (subtabs == 11)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##HEALTH", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{

				if (ImGui::BeginTable("HEALTH", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH))
				{

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Checkbox("Med Kit", &Setting::Esp_Item_MedKit);
					ImGui::Checkbox("First Aid Kit", &Setting::Esp_Item_FirstAidKit);
					ImGui::Checkbox("Painkiller", &Setting::Esp_Item_Painkiller);
					ImGui::Checkbox("Energy Drink", &Setting::Esp_Item_EnergyDrink);
					ImGui::Checkbox("Adrenaline Syringe", &Setting::Esp_Item_AdrenalineSyringe);

					ImGui::TableNextColumn();
					ImGui::Text("size");
					ImGui::SliderInt("48", &MEDS, 0, 25);
					ImGui::SliderInt("47", &FIRSTS, 0, 25);
					ImGui::SliderInt("46", &PAINS, 0, 25);
					ImGui::SliderInt("45", &ENRES, 0, 25);
					ImGui::SliderInt("44", &ADRES, 0, 25);


					ImGui::TableNextColumn();
					ImGui::Text("color");
					ImGui::ColorEdit4("Med Kit", Esp_Item_MedKit_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("First Aid Kit", Esp_Item_FirstAidKit_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Painkiller", Esp_Item_Painkiller_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Energy Drink", Esp_Item_EnergyDrink_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Adrenaline Syringe", Esp_Item_AdrenalineSyringe_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);

					ImGui::EndTable();
				}

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
	if (subtabs == 12)
	{
		ImGui::SetCursorPos(ImVec2(20 + barsize, 80));
		ImGui::BeginChild("##OTHER", ImVec2(760 - barsize, 420), false, ImGuiWindowFlags_Background);
		{
			ImGui::SetCursorPos(ImVec2(15, 15));
			ImGui::BeginGroup();
			{

				if (ImGui::BeginTable("OTHER", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH))
				{

					ImGui::TableNextRow();


					ImGui::TableNextColumn();
					ImGui::Text("Name");

					ImGui::Checkbox("Frag", &Setting::Esp_Item_Frag);
					ImGui::Checkbox("Smoke", &Setting::Esp_Item_Smoke);
					ImGui::Checkbox("Molotof", &Setting::Esp_Item_Molotof);
					ImGui::Checkbox("Dead box", &Setting::deadbox);
					ImGui::Checkbox("Box item list", &Setting::playerdeadbox);

					ImGui::TableNextColumn();
					ImGui::Text("size");		

					ImGui::SliderInt("49", &FRAGS, 0, 25);
					ImGui::SliderInt("50", &SMOKES, 0, 25);
					ImGui::SliderInt("51", &MOLOS, 0, 25);


					ImGui::TableNextColumn();
					ImGui::Text("color");
					ImGui::ColorEdit4("Frag", Esp_Item_Frag_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Smoke", Esp_Item_Smoke_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Molotof", Esp_Item_Molotof_Color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Dead Box ", (float*)&deadbox, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4("Dead Boxi ", (float*)&deadboxitem, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs);


					ImGui::EndTable();
				}

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();

	}
}

void ConfigTab()
{

}




void DrawMenux()
{


	if (FileExist("C:\\icons"))
	{

	}
	else 
	{
		mkdir("C:\\icons");
	}

	static auto Name = "Menu";
	static auto Flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::StyleColorsDark();

	style->Alpha = 1.f;
	style->WindowRounding = 8;
	style->FramePadding = ImVec2(4, 0);
	style->WindowPadding = ImVec2(0, 0);
	style->ItemInnerSpacing = ImVec2(4, 4);
	style->ItemSpacing = ImVec2(15, 15);
	style->FrameRounding = 12;
	style->ScrollbarSize = 2.f;
	style->ScrollbarRounding = 12.f;
	style->PopupRounding = 4.f;


	ImVec4* colors = ImGui::GetStyle().Colors;

	colors[ImGuiCol_ChildBg] = ImColor(26, 30, 35, 0);
	colors[ImGuiCol_Border] = ImVec4(255, 255, 255, 0);
	colors[ImGuiCol_FrameBg] = ImColor(18, 19, 23, 255);
	colors[ImGuiCol_FrameBgActive] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_FrameBgHovered] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_Header] = ImColor(141, 142, 144, 255);
	colors[ImGuiCol_HeaderActive] = ImColor(141, 142, 144, 255);
	colors[ImGuiCol_HeaderHovered] = ImColor(141, 142, 144, 255);
	colors[ImGuiCol_PopupBg] = ImColor(141, 142, 144, 255);
	colors[ImGuiCol_Button] = ImColor(160, 30, 30, 255);
	colors[ImGuiCol_ButtonHovered] = ImColor(190, 45, 35, 255);
	colors[ImGuiCol_ButtonActive] = ImColor(220, 60, 40, 255);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(110 / 255.f, 122 / 255.f, 200 / 255.f, 1.f);
	colors[ImGuiCol_SliderGrab] = ImVec4(255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f);

	static ImVec4 active = to_vec4(235, 134, 52, 255);
	static ImVec4 inactive = to_vec4(24, 71, 94, 102);
	static int viclestyle = 0;

	ImGui::SetNextWindowSize(ImVec2(810, 590));

	ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus);
	{
		static int x = 800 * dpi_scale, y = 520 * dpi_scale;
		pos = ImGui::GetWindowPos();
		draw = ImGui::GetWindowDrawList();

		ImGui::SetWindowSize(ImVec2(ImFloor(x * dpi_scale), ImFloor(y * dpi_scale)));

		draw->AddRectFilled(pos, ImVec2(pos.x + 800, pos.y + 520), ImColor(36, 40, 49), 8);
		draw->AddRectFilled(pos, ImVec2(pos.x + barsize, pos.y + 520), ImColor(56, 62, 74), 8, 5);
		draw->AddRectFilled(ImVec2(pos.x + 60, pos.y), ImVec2(pos.x + 800, pos.y + 60), ImColor(56, 62, 74), 8, 2);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		ImGui::BeginChild("##TABS", ImVec2(barsize, 520));
		{
			ImGui::BeginChild("##Logo", ImVec2(barsize, 60));
			{
				ImGui::GetCurrentWindow()->DrawList->AddRectFilled(pos, ImVec2(pos.x + barsize, pos.y + 60), ImColor(81, 87, 101), 8, 1);
				ImGui::GetCurrentWindow()->DrawList->AddRect(ImVec2(pos.x + barsize / 2 - 10, pos.y + 20), ImVec2(pos.x + barsize / 2 + 10, pos.y + 40), ImColor(255, 255, 255), 36, 7, 3);
			}
			ImGui::EndChild();

			ImGui::BeginGroup();
			{
				if (ImGui::tab("ESP", ICON_FA_PUZZLE_PIECE, 0 == tabs)) tabs = 0;
				//if (ImGui::tab("VISUALS", ICON_FA_EYE, 1 == tabs)) tabs = 1;
				//if (ImGui::tab("AIMBOT", ICON_FA_BULLSEYE, 2 == tabs)) tabs = 2;
				//if (ImGui::tab("MEMORY", ICON_FA_MAGIC, 3 == tabs)) tabs = 3;
				//if (ImGui::tab("SETTINGS", ICON_FA_COGS, 4 == tabs)) tabs = 4;
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
		if (ImGui::IsItemHovered())
		{
			if (barsize < 200)
				barsize += 10;
		}
		else
		{
			if (barsize > 60)
				barsize -= 10;
		}
		ImGui::SameLine();
		ImGui::BeginChild("##SUBTABS", ImVec2(800 - barsize, 60));
		{
			if (tabs == 0)
			{
				ImGui::BeginGroup();
				{
					if (ImGui::sub("MAIN SETTINGS", 0 == subtabs)) subtabs = 0;
					ImGui::SameLine();
					//if (ImGui::sub("MISC SETTINGS", 1 == subtabs)) subtabs = 1;
					//ImGui::SameLine();
					//if (ImGui::sub("ITEMS SETTINGS", 2 == subtabs)) subtabs = 2;
				}
				ImGui::EndGroup();
			}
			if (tabs == 1)
			{
				ImGui::BeginGroup();
				{
					if (ImGui::sub("Aimbot", 0 == subtabs)) subtabs = 0;
					ImGui::SameLine();
					if (ImGui::sub("Magic Bollet", 1 == subtabs)) subtabs = 1;
				}
				ImGui::EndGroup();
			}
			if (tabs == 2)
			{
				ImGui::BeginGroup();
				{
					if (ImGui::sub2("AR RIFLE", 0 == subtabs)) subtabs = 0;
					ImGui::SameLine();
					if (ImGui::sub2("SN RIFLE", 1 == subtabs)) subtabs = 1;
					ImGui::SameLine();
					if (ImGui::sub3("SMG", 2 == subtabs)) subtabs = 2;
					ImGui::SameLine();
					if (ImGui::sub3("LMG", 3 == subtabs)) subtabs = 3;
					ImGui::SameLine();
					if (ImGui::sub2("SHOTGUN", 4 == subtabs)) subtabs = 4;
					ImGui::SameLine();
					if (ImGui::sub3("SCOPE", 5 == subtabs)) subtabs = 5;
					ImGui::SameLine();
					if (ImGui::sub4("ATTACHMENT", 6 == subtabs)) subtabs = 6;
					ImGui::SameLine();
					if (ImGui::sub3("PISTOL", 7 == subtabs)) subtabs = 7;
					ImGui::SameLine();
					if (ImGui::sub2("MELEE", 8 == subtabs)) subtabs = 8;
					ImGui::SameLine();
					if (ImGui::sub3("AMMO", 9 == subtabs)) subtabs = 9;
					ImGui::SameLine();
					if (ImGui::sub3("GEARS", 10 == subtabs)) subtabs = 10;
					ImGui::SameLine();
					if (ImGui::sub2("HEALTH", 11 == subtabs)) subtabs = 11;	
					ImGui::SameLine();
					if (ImGui::sub3("OTHER", 12 == subtabs)) subtabs = 12;

				}
				ImGui::EndGroup();
			}
			if (tabs == 3)
			{
				ImGui::BeginGroup();
				{
					if (ImGui::sub("Aimbot", 0 == subtabs)) subtabs = 0;
					ImGui::SameLine();
					if (ImGui::sub("Triggerbot", 1 == subtabs)) subtabs = 1;
				}
				ImGui::EndGroup();
			}
			if (tabs == 4)
			{
				ImGui::BeginGroup();
				{
					if (ImGui::sub("Aimbot", 0 == subtabs)) subtabs = 0;
					ImGui::SameLine();
					if (ImGui::sub("Triggerbot", 1 == subtabs)) subtabs = 1;
				}
				ImGui::EndGroup();
			}
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
		switch (tabs)
		{
		case 0: LegitTab();   break;
		case 1: VisualsTab();   break;
		case 2: MiscTab();   break;
		case 3: ConfigTab();   break;
		}

	}
	ImGui::End();


}
LinearColor RandomColor(float Rate) {

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

	x += Rate; //increase this value to switch colors faster
	if (x >= 255.0f)
		x = 0.0f;

	y += Rate; //increase this value to switch colors faster
	if (y > 1530.0f)
		y = 0.0f;


	return { (float)r, (float)g, (float)b, 255 };
}
void ImGuiTextRGB(const char* fmt)
{


	static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;


	auto isFrames = ImGui::GetFrameCount();

	if (isFrames % 1 == 0) {

		if (isGreen == 0.01f && isBlue == 0.0f) {
			isRed += 0.01f;
		}

		if (isRed > 0.99f && isBlue == 0.0f) {
			isRed = 1.0f;
			isGreen += 0.01f;
		}

		if (isGreen > 0.99f && isBlue == 0.0f) {
			isGreen = 1.0f;
			isRed -= 0.01f;
		}

		if (isRed < 0.01f && isGreen == 1.0f) {
			isRed = 0.0f;
			isBlue += 0.01f;
		}

		if (isBlue > 0.99f && isRed == 0.0f) {
			isBlue = 1.0f;
			isGreen -= 0.01f;
		}
		if (isGreen < 0.01f && isBlue == 1.0f) {
			isGreen = 0.0f;
			isRed += 0.01f;
		}
		if (isRed > 0.99f && isGreen == 0.0f) {
			isRed = 1.0f;
			isBlue -= 0.01f;
		}
		if (isBlue < 0.01f && isGreen == 0.0f) {
			isBlue = 0.0f;
			isRed -= 0.01f;
			if (isRed < 0.01f)
				isGreen = 0.01f;
		}
		ImGui::PushFont(DX11::ImGui_DX11::pic);
		ImGui::PushStyleColor(ImGuiCol_Text, ImColor(isRed, isBlue, isGreen, 8.0f).Value);
		ImGui::Text(fmt);

		ImGui::PopFont();
		ImGui::PopStyleColor();

	}


}
void DrawSideMenu()
{
	ShowMenuTwo = "AORUS VIP";
	DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 20, ShowMenuTwo, 80, DX11Window::Height / 2 - 108, DX11::ImGui_DX11::Color::Yellow, true);

	if (Setting::MagicBulletticked)
	{
		ShowMenuTwo = "F2 : Magic Bullet ";
		DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 18, ShowMenuTwo, 80, DX11Window::Height / 2 - 90, DX11::ImGui_DX11::Color::Green, true);
	}
	else
	{
		ShowMenuTwo = "F2 : Magic Bullet ";
		DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 18, ShowMenuTwo, 80, DX11Window::Height / 2 - 90, DX11::ImGui_DX11::Color::Red, true);

	}

	if (Setting::fightmode)
	{
		ShowMenuTwo = "F3 : Fight Mode ";
		DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 18, ShowMenuTwo, 80, DX11Window::Height / 2 - 72, DX11::ImGui_DX11::Color::Green, true);
	}
	else
	{
		ShowMenuTwo = "F3 : Fight Mode  ";
		DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 18, ShowMenuTwo, 80, DX11Window::Height / 2 - 72, DX11::ImGui_DX11::Color::Red, true);

	}

}

static int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
void DrawTotalEnemies() {


	//	ImGui::SetNextWindowSize(ImVec2(155.0f, 35.0f));
	ImGuiIO& Io = ImGui::GetIO();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
	if (Data::NetDriver > 0)
	{
		if (Data::AActorList.size() > 0)
		{

			ImGui::PushStyleColor(ImGuiCol_WindowBg, to_vec4(0, 0, 0, 255));
			ImGui::PushStyleColor(ImGuiCol_Border, to_vec4(255, 0, 0, 255));


			ImGui::SetNextWindowPos(ImVec2({ (DX11Window::Width / 2.0f) }, Io.DisplaySize.y * 0.1f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.1f));
			if (ImGui::Begin("ene", 0, Flags21))
			{
				std::string Text1 = " ";
				std::string Text2 = " ";
				std::string Text3 = " ";
				if (Data::AActorList.size() > 0)
				{
					if ((Data::AActorList.size() - Data::ABotList.size()) > 0)
					{

						Text1.append(ICON_FA_USER"  PLAYERS: ");
						Text1.append(std::to_string((Data::AActorList.size() - Data::ABotList.size())));
						if (Data::ABotList.size() == 0)
						{
							Text3.append("      ");

						}
						else
						{
							Text2.append(" ");
							Text2.append(ICON_FA_USER"  BOTS: ");
							Text2.append(std::to_string(Data::ABotList.size()));
							Text2.append(" ");
						}
						Text3.append(ICON_FA_USER ICON_FA_USER"  TEAMS: ");
						Text3.append(std::to_string(Data::AliveTeamNum));


					}

					else if (Data::ABotList.size() > 0)
					{


						Text2.append(ICON_FA_USER"  BOTS: ");
						Text2.append(std::to_string(Data::ABotList.size()));
					}


				}

				ImGui::PushStyleColor(ImGuiCol_Text, to_vec4(255, 0, 0, 255));
				ImGui::Text(Text1.c_str());

				if (Data::ABotList.size() > 0)
				{

					ImGui::SameLine();
					ImGui::PushStyleColor(ImGuiCol_Text, to_vec4(0, 255, 0, 255));
					ImGui::Text(Text2.c_str());
					ImGui::PopStyleColor();
				}

				ImGui::SameLine();
				ImGui::Text(Text3.c_str());
				ImGui::PopStyleColor();



				ImGui::End();
			}
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, to_vec4(0, 0, 0, 255));
			ImGui::PushStyleColor(ImGuiCol_Border, to_vec4(255, 255, 0, 255));

			ImGui::SetNextWindowPos(ImVec2({ (DX11Window::Width / 2.0f) }, Io.DisplaySize.y * 0.1f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.1f));
			if (ImGui::Begin("ene", 0, Flags21))
			{
				std::string Text1 = "";



				TextWithColors("  {FF0000}NO ONE IS     {00FFE1}NEAR YOU ");

			}
			ImGui::PushStyleColor(ImGuiCol_Text, to_vec4(255, 0, 0, 255));

			ImGui::PopStyleColor();
			ImGui::End();

		}

	}
	else
	{






		ImGui::PushStyleColor(ImGuiCol_WindowBg, to_vec4(0, 0, 0, 255));
		ImGui::PushStyleColor(ImGuiCol_Border, to_vec4(255, 255, 0, 255));
		ImGui::SetNextWindowPos(ImVec2({ (DX11Window::Width / 2.0f) }, Io.DisplaySize.y * 0.1f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.1f));
		if (ImGui::Begin("ene", 0, Flags21))
		{
			/*	std::string Text1 = "";

					Text1 = ICON_FA_HOME" [You Are in]";
					TextWithColors(ICON_FA_HOME" {#cccccc} [You Are in] : {00FF0F}   Lobby    {#cccccc}" ICON_FA_CLOCK "  [Since] : " );
					ImGui::SameLine();*/

					/* std::string Text = ICON_FA_HOME"  (You Are in): {00FF0F} Lobby";
				Memory::RestoreHook();

				std::string Alive1 = ICON_FA_CLOCK"  (Since): {00FF0F} ";


				TextWithColors(Text.c_str());
				ImGui::SameLine();
				Alive1.append(std::to_string(10));
				TextWithColors(Alive1.c_str());*/
				//	int time = //time2();

			TextWithColors(ICON_FA_HOME" {cccccc} [You Are in] : {00FF0F}  Lobby    {cccccc}" ICON_FA_CLOCK "  [Since] : ");

			int minutes = Data::TimeRemind / 60;
			int hours = minutes / 60;
			string LobbyTime = "{00FF0F}" + (to_string(hours) + ":").append(to_string(minutes % 60) + ":").append(to_string(Data::TimeRemind % 60));
			ImGui::SameLine();
			TextWithColors(LobbyTime.c_str());
			//ImGui::Text(LobbyTime.c_str());
			ImGui::End();
		}
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void Drawgameinfo()
{
	/*if (!Data::AlivePlayerNum == 1)
	{
		ImGui::SetNextWindowSize(ImVec2(160.0f, 185.0f));
	}*/
	ImGuiIO& Io = ImGui::GetIO();

	ImGui::PushStyleColor(ImGuiCol_WindowBg, to_vec4(0, 0, 0, 150));
	ImGui::PushStyleColor(ImGuiCol_Border, to_vec4(255, 255, 0, 255));
	ImGui::SetNextWindowPos(ImVec2(Io.DisplaySize.x * 0.5f, Io.DisplaySize.y * 0.1f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.1f));
	if (ImGui::Begin(" \xef\x81\xae  GAME STATISTICS ", 0, Flags22))
	{

		if (Data::NetDriver > 0)
		{

			if (Data::AliveTeamNum == 1)
			{
				ImGui::Text("Winner Winner Chicken Dinner");

			}
			else

			{
				//ImGui::SetNextWindowSize(ImVec2(160.0f, 185.0f));
				std::string Text1 = "";
				std::string Text2 = "";
				std::string Text3 = "";
				std::string Text4 = "";
				std::string Text5 = "";
				std::string Text6 = "";
				std::string Text7 = "";
				std::string Text8 = "";




				Text1 = ICON_FA_USER" PLAYERS: ";

				//	std::string Text1 = "";

				Text1.append(std::to_string((Data::AActorList.size() - Data::ABotList.size())));


				Text2.append(ICON_FA_USER" BOTS:  ");
				Text2.append(std::to_string(Data::ABotList.size()));

				Text3.append(" ALIVE PLAYERS:  ");
				Text3.append(std::to_string(Data::AlivePlayerNum));

				Text4.append(" Teams:  ");
				Text4.append(std::to_string(Data::AliveTeamNum));

				Text5.append(" ZoneID:  ");
				if (Data::CurCircleWave == -1)
				{
					Data::CurCircleWave = 0;
				}
				Text5.append(std::to_string(Data::CurCircleWave));

				Text6.append(" GameID:  ");
				Text6.append(std::to_string(Data::GameModeID));

				Text7.append(" ELAPSED TIME:  ");

				int minutes = Data::TimeRemind / 60;

				string GameTime = (to_string(minutes % 60) + "m ").append(to_string(Data::TimeRemind % 60) + "s");
				Text7.append(GameTime);


				Text8.append(" GAME TYPE:  ");

				Text8.append(Data::GameType);

				//:Text1.append(std::to_string(Data::PlayerNumPerTeam));
				ImGui::Spacing;
				ImGui::Spacing;
				ImGui::Text(Text1.c_str());
				ImGui::Text(Text2.c_str());
				ImGui::Text(Text3.c_str());
				ImGui::Text(Text4.c_str());
				ImGui::Text(Text5.c_str());
				ImGui::Text(Text6.c_str());
				ImGui::Text(Text7.c_str());
				ImGui::Text(Text8.c_str());
				ImGui::Spacing;
			}
		}
		else
		{
			time_t t; // t passed as argument in function time()
			struct tm* tt; // decalring variable for localtime()
			std::time(&t); //passing argument to time()
			tt = localtime(&t);
			//cout << "Current Day, Date and Time is = " << asctime(tt);
			std::string tim;
			tim = asctime(tt);
			string Lobby = " AORUS VIP";
			ImGui::Text(Lobby.c_str());
			string GAMELOOP = " GAMELOOP";

			string TIME = " TIME:" + tim;

			ImGui::Text(GAMELOOP.c_str());
			ImGui::Text(TIME.c_str());

		}

		ImGui::End();
	}
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void DrawRadarHUD(MinimalViewInfo Camera, AActor Player, int Distance, int xAxis, int yAxis, int width, int height, ImVec4 color)
{

	ImGui::SetNextWindowSize(ImVec2(Setting::RadarLength, Setting::RadarWidth));
	ImGuiIO& Io = ImGui::GetIO();

	ImGui::PushStyleColor(ImGuiCol_WindowBg, to_vec4(0, 0, 0, 108));
	ImGui::PushStyleColor(ImGuiCol_Border, to_vec4(255, 255, 0, 200));
	ImGui::SetNextWindowPos(ImVec2(50, (Io.DisplaySize.y / 2) + 100), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.1f));
	if (ImGui::Begin("     ", 0, Flags21))
	{


		{

			ImVec2 wind = ImGui::GetWindowSize();
			ImVec2 wind2 = ImGui::GetWindowPos();



			bool out = false;
			VECTOR3 siz;
			siz.X = wind.x;
			siz.Y = wind.y;
			VECTOR3 pos;
			pos.X = wind2.x;
			pos.Y = wind2.y;
			float RadarCenterX = pos.X + (siz.X / 2);
			float RadarCenterY = pos.Y + (siz.Y / 2);
			//DX11::ImGui_DX11::DrawOutlineBox(pos.X, pos.Y, siz.X, siz.Y, ImVec4(0, 0, 0, 1.f), 1.0f);
			//DX11::ImGui_DX11::DrawBox(pos.X, pos.Y, siz.X, siz.Y, .1, 0, 0, 0, .1, true);


			/*DX11::ImGui_DX11::IMGUIDRAWLINE(RadarCenterX, RadarCenterY, pos.X, pos.Y, ImVec4(255, 0, 0, 255), 1.0f);
			DX11::ImGui_DX11::IMGUIDRAWLINE(RadarCenterX, RadarCenterY, pos.X + siz.X, pos.Y, ImVec4(255, 0, 0, 255), 1.0f);
			DX11::ImGui_DX11::IMGUIDRAWLINE(pos.X, RadarCenterY, pos.X + siz.X, RadarCenterY, ImVec4(color), 1.0f);
			DX11::ImGui_DX11::IMGUIDRAWLINE(RadarCenterX, RadarCenterY, RadarCenterX, pos.Y + siz.Y, ImVec4(color), 1.0f);*/
			DX11::ImGui_DX11::IMGUIDRAWCIRCLE(RadarCenterX, RadarCenterY, 3, ImVec4(color), 2.0f);
			VECTOR3 ddddd;
			ddddd.X = siz.X;
			ddddd.Y = siz.Y;
			ddddd.Z = 0;
			VECTOR3 single = WorldToRadar(Camera.Rotation.Yaw, Player.Position, Data::CameraCache.POV.Location, pos.X, pos.Y, ddddd, out);

			if (Distance < Setting::PlayerMAxDistance)
			{
				DX11::ImGui_DX11::IMGUIDRAWCIRCLE(single.X, single.Y, 3, ImVec4(color), 2.0f);
			}



		}
		ImGui::End();
	}
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();



}
void random_color(int iTick)
{
	ImVec4(sin(5.f * iTick + 0.f) * 127 + 128 / 255.0f, sin(5.f * iTick + ((2.f * 3.14159265358979323846) / 3)) * 127 + 128 / 255.0f, sin(5.f * iTick + ((4.f * 3.14159265358979323846) / 3)) * 127 + 128 / 255.0f, 255 / 255.0f);

}
VOID Esp::EspThread()
{
	VECTOR3 Screen;
	INT Distance = 0;
	INT EnemyCount = 0;




	VECTOR3 HeadPos;
	VECTOR2 Head;
	VECTOR2 Chest;
	VECTOR2 Pelvis;
	VECTOR2 lSholder;
	VECTOR2 rSholder;
	VECTOR2 lElbow;
	VECTOR2 rElbow;
	VECTOR2 lWrist;
	VECTOR2 rWrist;
	VECTOR2 lThigh;
	VECTOR2 rThigh;
	VECTOR2 lKnee;
	VECTOR2 rKnee;
	VECTOR2 lAnkle;
	VECTOR2 rAnkle;
	std::string temp = "";
	std::string dist = "";
	string Text = "ssssssss";
	LoadTextureFromFile(L"C://icons//Logo.jpg", &my_texture, &my_image_width, &my_image_height);


	vector<AActor> TempAActorList = {};
	vector<Deadbox> TempBoxesList = {};
	vector<Vehicle> TempVehicalList = {};
	vector<Item> TempItemList = {};
	vector<BombAlert> TempBombAlertList = {};

	while (true)
	{
		try
		{
			//	auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			RECT Rect;
			GetWindowRect(Game::hWindow, &Rect);
			DX11Window::Left = Rect.left;
			DX11Window::Top = Rect.top;
			DX11Window::Width = Rect.right - Rect.left;
			DX11Window::Height = Rect.bottom - Rect.top;
			MoveWindow(DX11Window::hWindow, DX11Window::Left, DX11Window::Top, DX11Window::Width, DX11Window::Height, true);

			// cout << "Height Of window "<< DX11Window::Height << endl;
			// cout << "Width Of window " << DX11Window::Width <<endl;

			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();


			{
				if (Setting::ShowMenu)
				{
					DrawMenux();
				}
				if (Setting::ShowSideMenu)
				{
					DrawSideMenu();
				}
				if (login)
				{

					ViewMatrix = Utility::ReadMemoryEx<D3DMATRIX>(Utility::ReadMemoryEx<DWORD>(Utility::ReadMemoryEx<DWORD>(Data::ViewMatrixBase) + 0x20) + 0x200);
					Data::CameraCache = Utility::ReadMemoryEx<CameraCacheEntry>(Data::PlayerCameraManager + Offset::PlayerCameraManager1::CameraCache);
					TempAActorList.clear();
					TempAActorList = Data::AActorList;
					DWORD MeshAddv1 = Utility::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::Mesh);
					DWORD BodyAddv1 = MeshAddv1 + Offset::BodyAddv;
					DWORD BoneAddv1 = Utility::ReadMemoryEx<DWORD>(MeshAddv1 + Offset::MinLOD) + 48;


					Data::lOCALPLAYERHEAD = Algorithm::GetBoneWorldPosition(BodyAddv1, BoneAddv1 + 5 * 48);
					Data::lOCALPLAYERPosotion = Utility::ReadMemoryEx<VECTOR3>(Utility::ReadMemoryEx<DWORD>(Data::LocalPlayerAddr + Offset::RootComponent) + Offset::Position);
					if (Data::AActorList.size() != 0)
					{

						for (AActor& AActor : Data::AActorList)
						{
							int _dist;
							AActor.Position = Utility::ReadMemoryEx<VECTOR3>(Utility::ReadMemoryEx<DWORD>(AActor.Address + Offset::RootComponent) + Offset::Position);

							teamids = AActor.TeamId;
							col = ImColor(teamids, teamids, teamids, 255);



							linescolors = ImVec4(sin(5.f * teamids + 0.f) * 127 + 128 / 255.0f, sin(5.f * teamids + ((2.f * 3.14159265358979323846) / 3)) * 127 + 128 / 255.0f, sin(5.f * teamids + ((4.f * 3.14159265358979323846) / 3)) * 127 + 128 / 255.0f, 255 / 255.0f);
							bonescolors = Colors::playerbone;
							fullboxcolor = Colors::playerbox;
						
							if (Setting::dots)
							{
								float S_height = DX11Window::Height;
								float S_width = DX11Window::Width;
								bool shit = false;
								VECTOR3 EntityPos = WorldToRadar(Data::CameraCache.POV.Rotation.Yaw, AActor.Position, Data::CameraCache.POV.Location, NULL, NULL, ToVECTOR3(S_width, S_height, 0), shit);
								int radar_range = 25;//
								int x, y;
								x = EntityPos.X;
								y = EntityPos.Y;

								VECTOR3 angle{};
								VECTOR3 temmp = ToVECTOR3((float)(S_width / 2) - x, (float)(S_height / 2) - y, 0.f);

								VectorAnglesRadar(temmp, angle);

								const auto angle_yaw_rad = DEG2RAD(angle.Y + 180.f);
								const auto new_point_x = (S_width / 2) + (radar_range) / 2 * 8 * cosf(angle_yaw_rad);
								const auto new_point_y = (S_height / 2) + (radar_range) / 2 * 8 * sinf(angle_yaw_rad);

								std::array<VECTOR3, 3> points
								{
									ToVECTOR3(new_point_x - ((90) / 4 + 3.5f) / 2, new_point_y - ((radar_range) / 4 + 3.5f) / 2, 0.f),
									ToVECTOR3(new_point_x + ((90) / 4 + 3.5f) / 4, new_point_y, 0.f),
									ToVECTOR3(new_point_x - ((90) / 4 + 3.5f) / 2, new_point_y + ((radar_range) / 4 + 3.5f) / 2, 0.f)
								};
								RotateTriangle(points, angle.Y + 180.f);
					
								if (AActor.IsBot) {
									DX11::ImGui_DX11::DrawTriangle(points.at(0).X, points.at(0).Y, points.at(1).X, points.at(1).Y, points.at(2).X, points.at(2).Y, 2, Colors::bot);
								}
								else {
									DX11::ImGui_DX11::DrawTriangle(points.at(0).X, points.at(0).Y, points.at(1).X, points.at(1).Y, points.at(2).X, points.at(2).Y, 2, linescolors);
								}
								if (Setting::radar)
								{

									float S_height = DX11Window::Height;
									float S_width = DX11Window::Width;
									DrawRadarHUD(Data::CameraCache.POV, AActor, Distance, 20, 50, 100, 200, linescolors);
								}



								if (!Algorithm::WorldToScreenPlayer(Data::lOCALPLAYERPosotion, AActor.Position, Screen, &_dist, ViewMatrix)) continue;

								temp = AActor.Name.c_str();
								std::string lol1;
								lol1 = to_string(_dist) + "M";
								if (Screen.X > DX11Window::Width && Screen.Y > 0 && Screen.Y < DX11Window::Height)//Right
								{
									DX11::ImGui_DX11::DrawBorderText(DX11::ImGui_DX11::pRegularFont, 20, lol1, DX11Window::Width - 20, Screen.Y + Screen.Z, linescolors, true);
									if (Setting::enemyoffscreen)
									{
										if (Setting::pline)
										{
											DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, linescolors, Setting::plinesize);
										}
									}

								}
								if (Screen.X < 0 && Screen.Y  >0 && Screen.Y < DX11Window::Height)//Left
								{

									if (Setting::enemyoffscreen)
									{
										if (Setting::pline)
										{
											DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, linescolors, Setting::plinesize);
										}
									}

									DX11::ImGui_DX11::DrawBorderText(DX11::ImGui_DX11::pRegularFont, 20, lol1, 20, Screen.Y + Screen.Z, linescolors, true);

								}
								if (Screen.Y < 0 && Screen.X>0 && Screen.X < DX11Window::Width)//Top
								{
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 20, lol1, Screen.X, 0, linescolors, true);
									if (Setting::enemyoffscreen)
									{
										if (Setting::pline)
										{
											DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, linescolors, Setting::plinesize);
										}
									}

								}
								if (Screen.Y > DX11Window::Height && Screen.X > 0 && Screen.X < DX11Window::Width)//Bottom
								{
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 20, lol1, Screen.X, DX11Window::Height - 20, linescolors, true);
									if (Setting::enemyoffscreen)
									{
										if (Setting::pline)
										{
											DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, linescolors, Setting::plinesize);
										}
									}

								}
								if (Screen.X < 0 && Screen.Y < 0)//top left
								{
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 20, lol1, 0, 0, linescolors, true);
									if (Setting::enemyoffscreen)
									{
										if (Setting::pline)
										{
											DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, linescolors, Setting::plinesize);
										}
									}

								}
								if (Screen.X > DX11Window::Width && Screen.Y > DX11Window::Height)//bottom right
								{
									// DX11::ImGui_DX11::DrawCircle(DX11Window::Width - 20, DX11Window::Height - 20, 7, linescolors, 4.0f);
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 20, lol1, DX11Window::Width - 40, DX11Window::Height - 20, linescolors, true);
									if (Setting::enemyoffscreen)
									{
										if (Setting::pline)
										{
											DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, linescolors, Setting::plinesize);
										}
									}

								}
								if (Screen.X > DX11Window::Width && Screen.Y < 0)//top right
								{
									// DX11::ImGui_DX11::DrawCircle(DX11Window::Width - 20, 20, 7, linescolors, 4.0f);
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 20, lol1, DX11Window::Width - 40, 0, linescolors, true);
									if (Setting::enemyoffscreen)
									{
										if (Setting::pline)
										{
											DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, linescolors, Setting::plinesize);
										}
									}

								}
								if (Screen.X<0 && Screen.Y >DX11Window::Width)//bottom left
								{
									// DX11::ImGui_DX11::DrawCircle(20, DX11Window::Height - 20, 7, linescolors, 4.0f);
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 20, lol1, 0, DX11Window::Height - 20, linescolors, true);
									if (Setting::enemyoffscreen)
									{
										if (Setting::pline)
										{
											DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, linescolors, Setting::plinesize);
										}
									}

								}

							}

							DWORD MeshAddv;
							DWORD BodyAddv;
							DWORD BoneAddv;
							if (Setting::Bone || Setting::MagicBullet)
							{
								MeshAddv = Utility::ReadMemoryEx<DWORD>(AActor.Address + Offset::Mesh);
								BodyAddv = MeshAddv + Offset::BodyAddv;
								BoneAddv = Utility::ReadMemoryEx<DWORD>(MeshAddv + Offset::MinLOD) + 48;
								AActor.HeadPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 5 * 48);



							}
							if (Setting::Bone)
							{
								AActor.ChestPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 4 * 48);
								AActor.PelvisPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 1 * 48);
								AActor.lSholderPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 11 * 48);
								AActor.rSholderPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 32 * 48);
								AActor.lElbowPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 12 * 48);
								AActor.rElbowPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 33 * 48);
								AActor.lWristPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 63 * 48);
								AActor.rWristPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 62 * 48);
								AActor.lThighPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 52 * 48);
								if (AActor.rWristPos == AActor.lThighPos)continue;
								if (AActor.rElbowPos == AActor.lSholderPos)continue;
								AActor.rThighPos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 56 * 48);
								AActor.lKneePos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 53 * 48);
								AActor.rKneePos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 57 * 48);
								AActor.lAnklePos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 54 * 48);
								AActor.rAnklePos = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 58 * 48);
							}
							HeadPos = AActor.HeadPos;
							HeadPos.Z += 7;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, HeadPos, Head, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.ChestPos, Chest, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.PelvisPos, Pelvis, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lSholderPos, lSholder, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rSholderPos, rSholder, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lElbowPos, lElbow, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rElbowPos, rElbow, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lWristPos, lWrist, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rWristPos, rWrist, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lThighPos, lThigh, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rThighPos, rThigh, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lKneePos, lKnee, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rKneePos, rKnee, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lAnklePos, lAnkle, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rAnklePos, rAnkle, &Distance)) continue;
							//if (Distance < Setting::PlayerMAxDistance)
							if (Distance < Setting::PlayerMAxDistance)
							{

								
								if (AActor.IsBot)
								{
									linescolors = Colors::bot;
									temp = "[BOT]";
								}
								if (!Setting::enemyoffscreen)
								{
									if (Setting::pline)
									{
										DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, linescolors, Setting::plinesize);
									}
								}
								if (Setting::EnemyLineOfSight)
								{
									VECTOR3 hed = AActor.HeadPos;
									hed.Z += 7.0f;
									VECTOR3 SightAngle = FRotatorToVector(AActor.RelativeRotation);
									VECTOR3 end = ADDVECTORS(hed, MULTIPLYVECT(SightAngle, Setting::enemyLineofSightSize));

									VECTOR3 screen_start, screen_end;
									int dis;
									if (Algorithm::WorldToScreen(Data::lOCALPLAYERPosotion, hed, screen_start, &dis, ViewMatrix) && Algorithm::WorldToScreen(Data::lOCALPLAYERPosotion, end, screen_end, &dis, ViewMatrix)) {
										DX11::ImGui_DX11::DrawLine(screen_start.X, screen_start.Y, screen_end.X, screen_end.Y, Colors::enemyLineofSight, 2);
										DX11::ImGui_DX11::DrawCircle(screen_end.X, screen_end.Y, 1.f, linescolors, 1.0f);

									}
								}
								//	string TemID = "[" + std::to_string(teamids) + "]";
								string TemID = std::to_string(teamids) + ". " + AActor.Nation;
								std::string dist = std::to_string(Distance) + "M";
								if (Setting::pname)
								{

									if (AActor.Health <= 0)
									{
										if (AActor.IsBot) {
											const char* BOT = ("%d ", ICON_FA_USER);
											DX11::ImGui_DX11::DrawStringchar(DX11::ImGui_DX11::pRegularFont, 15, BOT, Screen.X-2, Screen.Y - 29, DX11::ImGui_DX11::Color::Red, true);
										}
										else
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, nsize, TemID, Screen.X - 50, Screen.Y - 28, linescolors, false);
											DX11::ImGui_DX11::DrawStrokeText(DX11::ImGui_DX11::pRegularFont, Screen.X - 10, Screen.Y - 28, DX11::ImGui_DX11::Color::Red, temp.c_str(), 18, false);
										}

									}
									else
									{


										if (AActor.IsBot) {
											const char* BOT = ("%d ", ICON_FA_USER);
											DX11::ImGui_DX11::DrawStringchar(DX11::ImGui_DX11::pRegularFont, 15, BOT, Screen.X-2 , Screen.Y - 29, DX11::ImGui_DX11::Color::Green, true);
										}
										else {
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, nsize, TemID, Screen.X - 50, Screen.Y - 28, linescolors, false);
											DX11::ImGui_DX11::DrawStrokeText(DX11::ImGui_DX11::pRegularFont, Screen.X - 10, Screen.Y - 28, Colors::nam, temp.c_str(), 18, false);
										}


									}

								}
								if (Setting::pflag)
								{
									if (!AActor.IsBot) {
										NationFlag(Screen, AActor, 50, 40, 20, 10);
									}
									
								}

								if (Setting::pfullbox)
								{
									if (!Setting::plyrbox)
									{
										fullboxcolor = linescolors;
									}
									else
									{
										fullboxcolor = Colors::playerbox;
									}


									DX11::ImGui_DX11::DrawRectangle(Screen.X - (Screen.Z / 4) - 3, Screen.Y - 5, (Screen.Z / 2) + 3, Screen.Z + 5, fullboxcolor, Setting::pfullboxsize);

								}
								else if (Setting::pcorner)
								{
									if (!Setting::plyrbox)
									{
										cornerboxcolor = linescolors;
									}
									else
									{
										cornerboxcolor = Colors::playerbox;
									}

									DX11::ImGui_DX11::CornerBox(Screen.X - Screen.Z / 4 - 3, Screen.Y - 5, (Screen.Z / 2) + 3, Screen.Z + 5, Setting::pcornersize, popcorn / 2, cornerboxcolor);

								}

								if (Setting::puid)
								{
								
									DX11::ImGui_DX11::DrawBorderText(DX11::ImGui_DX11::pRegularFont, dissize, AActor.UID, Screen.X+17, (Screen.Y + Screen.Z) + 30, Colors::plyerdistance, true);
								}
								if (Setting::phealth)
								{

									if (AActor.Health > 70.0)
									{
										DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 4, (Screen.Y - 5) + (Screen.Z + 5), 2, (Screen.Z + 5) * AActor.Health / AActor.HealthMax, DX11::ImGui_DX11::Color::Green);
									}
									else if (AActor.Health > 30.0 && AActor.Health <= 70.0)
									{
										DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 4, (Screen.Y - 5) + (Screen.Z + 5), 2, (Screen.Z + 5) * AActor.Health / AActor.HealthMax, DX11::ImGui_DX11::Color::Yellow);
									}
									else if (AActor.Health > 0.0 && AActor.Health <= 30.0)
									{
										DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 4, (Screen.Y - 5) + (Screen.Z + 5), 2, (Screen.Z + 5) * AActor.Health / AActor.HealthMax, DX11::ImGui_DX11::Color::Red);

									}
									else  if (AActor.Health <= 0)
									{
										DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 4, (Screen.Y - 5) + (Screen.Z + 5), 2, (Screen.Z + 5) * AActor.KnockedHealth / AActor.HealthMax, DX11::ImGui_DX11::Color::Red);
									}
									DX11::ImGui_DX11::DrawUnFilledRectangle(Screen.X - (Screen.Z / 4) - 4, (Screen.Y - 5) + (Screen.Z + 5), 2, (Screen.Z + 5), DX11::ImGui_DX11::Color::Black);


									//DX11::ImGui_DX11::DrawBlood(Screen.X - 30, (Screen.Y + 15 + Screen.Z), 70, 4, AActor.Health);
								}
								if (Setting::playerBone)
								{
									if (AActor.Address == Setting::CurrentTargetAddress) {



										bonescolors = Colors::targetenemybone;



									}
									else {



										bonescolors = Colors::playerbone;
									}

									if (Setting::playerBone)
									{
										DX11::ImGui_DX11::DrawCircle(Head.X, Head.Y, Screen.Z / 12, DX11::ImGui_DX11::Color::Yellow, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(Chest.X, Chest.Y, Pelvis.X, Pelvis.Y, bonescolors, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(Chest.X, Chest.Y, lSholder.X, lSholder.Y, bonescolors, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(Chest.X, Chest.Y, rSholder.X, rSholder.Y, bonescolors, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(lSholder.X, lSholder.Y, lElbow.X, lElbow.Y, bonescolors, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(rSholder.X, rSholder.Y, rElbow.X, rElbow.Y, bonescolors, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(lElbow.X, lElbow.Y, lWrist.X, lWrist.Y, bonescolors, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(rElbow.X, rElbow.Y, rWrist.X, rWrist.Y, bonescolors, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(Pelvis.X, Pelvis.Y, lThigh.X, lThigh.Y, bonescolors, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(Pelvis.X, Pelvis.Y, rThigh.X, rThigh.Y, bonescolors, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(lThigh.X, lThigh.Y, lKnee.X, lKnee.Y, bonescolors, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(rThigh.X, rThigh.Y, rKnee.X, rKnee.Y, bonescolors, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(lKnee.X, lKnee.Y, lAnkle.X, lAnkle.Y, bonescolors, Setting::pbonesize);
										DX11::ImGui_DX11::DrawLine(rKnee.X, rKnee.Y, rAnkle.X, rAnkle.Y, bonescolors, Setting::pbonesize);
									}

								}
								if (Setting::playerweapon || Setting::plyrdistance)
								{
									string wep = AActor.Weapon;
									string dista = dist;

									if (wep == "Fist")
									{

										if (Setting::playerweapon && Setting::plyrdistance)
										{
											wep.append(" | ");
											wep.append(dista);
											//DX11::ImGui_DX11::DrawStrokeText(DX11::ImGui_DX11::pRegularFont,  Screen.X, (Screen.Y + Screen.Z) + 10, Colors::ammo5, wep.c_str(), dissize, true);
											DX11::ImGui_DX11::DrawBorderText(DX11::ImGui_DX11::pRegularFont, dissize, wep, Screen.X + 4, (Screen.Y + Screen.Z), Colors::ammo5, true);

										}
									}
									else
									{


										if (Setting::plyrdistance)
										{
	
											DX11::ImGui_DX11::DrawBorderText(DX11::ImGui_DX11::pRegularFont, dissize, dist, Screen.X + 4, (Screen.Y + Screen.Z) + 12, Colors::plyerdistance, true);
											//	DX11::ImGui_DX11::DrawStrokeText(DX11::ImGui_DX11::pRegularFont, Screen.X, (Screen.Y + Screen.Z) + 25, Colors::plyerdistance, dist.c_str(), dissize, true);
										}
										if (Setting::playerweapon)
										{

											//	printf_s(temptext, xorstr_("%s (%d/%d)"), wep, AActor.Ammo, AActor.AmmoMax);

											/*string weapon; = wep AActor.Ammo, AActor.AmmoMax
												wep.append(" | ");
											wep.append(dista);*/

											wep.append(" | ");
											wep.append(to_string(AActor.Ammo) + ":");

											wep.append(to_string(AActor.AmmoMax));
											wep.append(AActor.ScopeFov);
											if (AActor.Ammo <= 200 && AActor.AmmoMax > 0)
											{
												DX11::ImGui_DX11::DrawBorderText(DX11::ImGui_DX11::pRegularFont, dissize, wep, Screen.X + 5, (Screen.Y + Screen.Z) - 1, Colors::plyrweapon, true);
											}
											else
											{
												DX11::ImGui_DX11::DrawCharBorderText(DX11::ImGui_DX11::pRegularFont, dissize, AActor.Weapon.c_str(), Screen.X + 5, (Screen.Y + Screen.Z) - 1, Colors::plyrweapon, true);
											}



											//		DX11::ImGui_DX11::DrawCharBorderText(DX11::ImGui_DX11::pRegularFont, dissize, AActor.Weapon.c_str(), Screen.X, (Screen.Y + Screen.Z), Colors::plyrweapon, true);

											//	DX11::ImGui_DX11::DrawBorderText(DX11::ImGui_DX11::pRegularFont, dissize, AActor.Weapon, Screen.X, (Screen.Y + Screen.Z), Colors::plyrweapon, true);

											//	DX11::ImGui_DX11::DrawStrokeText(DX11::ImGui_DX11::pRegularFont, Screen.X, (Screen.Y + Screen.Z) + 10, Colors::plyrweapon, AActor.Weapon.c_str(), dissize, true);
										}

									}

								}

							

								if (Setting::AimLineBottm)
								{
									if (AActor.Address == Setting::CurrentTargetAddress)
									{

										//DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, DX11Window::Height, Screen.X, Screen.Y + 30, Colors::magicline, 0.5f);
										DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, DX11Window::Height, Screen.X + 5, (Screen.Y + 15 + Screen.Z) - 10, Colors::magicline, 0.5f);

									}


								}
								else if (Setting::AimLineCross)
								{
									if (AActor.Address == Setting::CurrentTargetAddress)
									{
										if (Setting::curraim == 0)
										{
											DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, DX11Window::Height / 2, Head.X, Head.Y, Colors::magicline, 0.7f);
										}
										else if (Setting::curraim == 1)
										{
											DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, DX11Window::Height / 2, Chest.X, Chest.Y, Colors::magicline, 0.7f);
										}
										else if (Setting::curraim == 2)
										{
											DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, DX11Window::Height / 2, Pelvis.X, Pelvis.Y, Colors::magicline, 0.7f);
										}
										else if (Setting::curraim == 3)
										{
											DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, DX11Window::Height / 2, Pelvis.X, Pelvis.Y, Colors::magicline, 0.7f);
										}
									}
								}

							}
						}
					}

					if (Setting::IsimingAtYou) {

						if (!Data::AimingAtMePlayersList.empty()) {
							const char* Aim = ("\xef\x81\xb1  !! AIM ALERT !! \xef\x81\xb1  ");


							ImColor warncolor;
							int randomNum = (rand() % 2) + 1;
							if (randomNum == 1)
							{
								warncolor = DX11::ImGui_DX11::Color::Red;
							}

							if (randomNum == 2)
							{
								warncolor = DX11::ImGui_DX11::Color::Yellow;
							}
							DX11::ImGui_DX11::DrawStringchar(DX11::ImGui_DX11::pRegularFont, 40, Aim, (DX11Window::Width / 2) - 180, (DX11Window::Height / 9), warncolor, 0);
							for (AActor Aming : Data::AimingAtMePlayersList) {
								Aming.Position = Utility::ReadMemoryEx<VECTOR3>(Utility::ReadMemoryEx<DWORD>(Aming.Address + Offset::RootComponent) + Offset::Position);

								VECTOR2 Screen;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, Aming.Position, Screen, &Distance)) continue;
								if (Aming.isAimingAtMe)
								{
									string SIMI = "AIMING";
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, nsize, SIMI, Screen.X + 5, (Screen.Y + 25) - 10, DX11::ImGui_DX11::Color::Red, false);

								}
							}
						}

					}
					if (Setting::MyLineOfSight)
					{
						CameraCacheEntry CameraCache = Data::CameraCache;
						VECTOR3 currentViewLocation = Data::CameraCache.POV.Location;//Data::lOCALPLAYERHEAD;
						VECTOR3 currentViewRotation = FRotatorToVector(Data::CameraCache.POV.Rotation);
						VECTOR3 end = ADDVECTORS(currentViewLocation, MULTIPLYVECT(currentViewRotation, Setting::enemyLineofSightSize));

						VECTOR3 screen_start, screen_end;
						int dis;
						if (Algorithm::WorldToScreen(Data::lOCALPLAYERPosotion, currentViewLocation, screen_start, &dis, ViewMatrix) && Algorithm::WorldToScreen(Data::lOCALPLAYERPosotion, end, screen_end, &dis, ViewMatrix)) {
							DX11::ImGui_DX11::DrawLine(screen_start.X, screen_start.Y, screen_end.X, screen_end.Y, Colors::enemyLineofSight, 0.001);
							DX11::ImGui_DX11::DrawCircle(screen_end.X, screen_end.Y, 1.f, linescolors, 1.0f);

						}

					}
					if (Setting::MagicBulletticked)
					{
						if (Data::NetDriver > 0) {


							/*if (Setting::MagicBulletd) {
								if (Data::AActorList.size() != 0)
								{
									Setting::MagicBullet = true;
									Text = "  Tracking Bullet [ON]";
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 15, Text, DX11Window::Width / 2.2, DX11Window::Height / 2 + 220, DX11::ImGui_DX11::Color::Green, true);
								}
								else
								{
									Setting::MagicBullet = false;
									Text = "  Tracking Bullet [OFF]";
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 15, Text, DX11Window::Width / 2.2, DX11Window::Height / 2 + 220, DX11::ImGui_DX11::Color::Red, true);
								}
							}*/

							if (Setting::Legitrack)
							{
								srand(time(0));
								int random = rand() % 3;
								Setting::curraim = random;
							}

							if (Setting::MagicBulletd) {
								if (Data::AActorList.size() != 0)
								{
									const char* aimb[] = { "HEAD", "BODY", "PELVIS", "AUTO" };
									const char* combo_label = aimb[Setting::curraim];

									

									std::string Aim = combo_label;

									Setting::MagicBullet = true;

									if (Setting::Legitrack)
									{
										Text = "  Tracking ON [ Legitrack ]";
									}
									else
									{
										Text = "  Tracking ON [ " + Aim + "] [" + to_string(Setting::magicrange) + "]M";
									}
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 15, Text, DX11Window::Width / 2.2, DX11Window::Height / 2 + 220, DX11::ImGui_DX11::Color::Green, true);
								}
								else
								{
									Setting::MagicBullet = false;
									Text = "  Tracking Bullet [OFF]";
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 15, Text, DX11Window::Width / 2.2, DX11Window::Height / 2 + 220, DX11::ImGui_DX11::Color::Red, true);
								}
							}
						}
					}
					if (Setting::TotalEnemy)
					{
						DrawTotalEnemies();

					}
					if (Setting::gameinfo)
					{
						Drawgameinfo();
					}
					if (Setting::fovcircle)
					{
							DX11::ImGui_DX11::DrawCircle(DX11Window::Width / 2, DX11Window::Height / 2, Setting::fovcircleredus, Colors::fovcirclecolor);
					}
					if (Setting::allitemss)
					{
						if (Setting::impitems || Setting::healthitem || Setting::scope || Setting::allitemss && !Setting::fightmode)
						{
							if (Data::ItemList.size() != 0)
							{
								TempItemList.clear();
								TempItemList = Data::ItemList;
								for (Item& Item : Data::ItemList)
								{
									if (!Algorithm::WorldToScreen(Data::lOCALPLAYERPosotion, Item.Position, Screen, &Distance, ViewMatrix)) continue;

									std::string	Textt = Item.Name;
									Text = Item.Name;
									std::string air = Item.Name + " " + to_string(Distance) + "M";

									if (Setting::UselessShow)
									{
										DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Textt, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Bag1_Color[0], Setting::Esp_Item_Bag1_Color[1], Setting::Esp_Item_Bag1_Color[2], Setting::Esp_Item_Bag1_Color[3]), true);

									}
									if (Setting::impitems)
									{
										if (Setting::Esp_Item_AKM && Item.Name == "AKM")
										{
											if (Setting::Esp_Item_AKM_Icon)
											{
												DX11::ImGui_DX11::DrawImage(DX11::AKM, Screen.X - 50, Screen.Y - 25, 100, 50);
												continue;
											}
											else
											{
												DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, weapon::AKM, true);
												continue;
											}
										}
										if (Setting::Esp_Item_SCARL && Item.Name == "SCAR-L")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, weapon::scarl, true);
											continue;
										}

										if (Setting::Esp_Item_M416 && Item.Name == "M416")
										{
											if (Setting::Esp_Item_M416_Icon)
											{
												DX11::ImGui_DX11::DrawImage(DX11::M416, Screen.X - 50, Screen.Y - 25, 100, 50);
												continue;
											}
											else
											{

												DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, weapon::m16, true);
												continue;
											}
										}
										if (Setting::Esp_Item_M24 && Item.Name == "M24")
										{
											if (Setting::Esp_Item_M24_Icon)
											{
												DX11::ImGui_DX11::DrawImage(DX11::M24, Screen.X - 50, Screen.Y - 25, 100, 50);
												continue;
											}
											else
											{

												DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, weapon::M24, true);
												continue;
											}
										}






										if (Setting::token && Item.Name == "FalierInAir")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::Normalfontsize, air, Screen.X, Screen.Y + 15, ImColor(Esp_Item_Tokenf_Color[0], Esp_Item_Tokenf_Color[1], Esp_Item_Tokenf_Color[2], Esp_Item_Tokenf_Color[3]), true);
										}
										if (Setting::BP_QK_Choke_Pickup_C_1 && Item.Name == "Choke") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QK_Choke_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QK_Choke_Pickup_C_1[0], BP_QK_Choke_Pickup_C_1[1], BP_QK_Choke_Pickup_C_1[2], BP_QK_Choke_Pickup_C_1[3]), true); }
										if (Setting::BP_QK_Mid_Compensator_Pickup_C_1 && Item.Name == "Compensator (SMG)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QK_Mid_Compensator_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QK_Mid_Compensator_Pickup_C_1[0], BP_QK_Mid_Compensator_Pickup_C_1[1], BP_QK_Mid_Compensator_Pickup_C_1[2], BP_QK_Mid_Compensator_Pickup_C_1[3]), true); }
										if (Setting::BP_QK_Sniper_Compensator_Pickup_C_1 && Item.Name == "Compensator (Snipers)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QK_Sniper_Compensator_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QK_Sniper_Compensator_Pickup_C_1[0], BP_QK_Sniper_Compensator_Pickup_C_1[1], BP_QK_Sniper_Compensator_Pickup_C_1[2], BP_QK_Sniper_Compensator_Pickup_C_1[3]), true); }
										if (Setting::BP_QK_Mid_FlashHider_Pickup_C_1 && Item.Name == "Flash Hider (SMG)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QK_Mid_FlashHider_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QK_Mid_FlashHider_Pickup_C_1[0], BP_QK_Mid_FlashHider_Pickup_C_1[1], BP_QK_Mid_FlashHider_Pickup_C_1[2], BP_QK_Mid_FlashHider_Pickup_C_1[3]), true); }
										if (Setting::BP_QK_Sniper_FlashHider_Pickup_C_1 && Item.Name == "Flash Hider (Snipers)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QK_Sniper_FlashHider_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QK_Sniper_FlashHider_Pickup_C_1[0], BP_QK_Sniper_FlashHider_Pickup_C_1[1], BP_QK_Sniper_FlashHider_Pickup_C_1[2], BP_QK_Sniper_FlashHider_Pickup_C_1[3]), true); }
										if (Setting::BP_QK_Mid_Suppressor_Pickup_C_1 && Item.Name == "Suppressor (SMG)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QK_Mid_Suppressor_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QK_Mid_Suppressor_Pickup_C_1[0], BP_QK_Mid_Suppressor_Pickup_C_1[1], BP_QK_Mid_Suppressor_Pickup_C_1[2], BP_QK_Mid_Suppressor_Pickup_C_1[3]), true); }
										if (Setting::BP_QK_Sniper_Suppressor_Pickup_C_1 && Item.Name == "Suppressor (Snipers)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QK_Sniper_Suppressor_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QK_Sniper_Suppressor_Pickup_C_1[0], BP_QK_Sniper_Suppressor_Pickup_C_1[1], BP_QK_Sniper_Suppressor_Pickup_C_1[2], BP_QK_Sniper_Suppressor_Pickup_C_1[3]), true); }
										if (Setting::BP_QK_Large_Compensator_Pickup_C_1 && Item.Name == "Compensator (AR)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QK_Large_Compensator_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QK_Large_Compensator_Pickup_C_1[0], BP_QK_Large_Compensator_Pickup_C_1[1], BP_QK_Large_Compensator_Pickup_C_1[2], BP_QK_Large_Compensator_Pickup_C_1[3]), true); }
										if (Setting::BP_QK_Large_FlashHider_Pickup_C_1 && Item.Name == "Flash Hider (AR)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QK_Large_FlashHider_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QK_Large_FlashHider_Pickup_C_1[0], BP_QK_Large_FlashHider_Pickup_C_1[1], BP_QK_Large_FlashHider_Pickup_C_1[2], BP_QK_Large_FlashHider_Pickup_C_1[3]), true); }
										if (Setting::BP_QK_Large_Suppressor_Pickup_C_1 && Item.Name == "Suppressor (AR)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QK_Large_Suppressor_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QK_Large_Suppressor_Pickup_C_1[0], BP_QK_Large_Suppressor_Pickup_C_1[1], BP_QK_Large_Suppressor_Pickup_C_1[2], BP_QK_Large_Suppressor_Pickup_C_1[3]), true); }
										if (Setting::BP_QK_DuckBill_Pickup_C_1 && Item.Name == "Duckbill (Shotguns)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QK_DuckBill_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QK_DuckBill_Pickup_C_1[0], BP_QK_DuckBill_Pickup_C_1[1], BP_QK_DuckBill_Pickup_C_1[2], BP_QK_DuckBill_Pickup_C_1[3]), true); }
										if (Setting::BP_WB_Angled_Pickup_C_1 && Item.Name == "Angled Foregrip") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_WB_Angled_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_WB_Angled_Pickup_C_1[0], BP_WB_Angled_Pickup_C_1[1], BP_WB_Angled_Pickup_C_1[2], BP_WB_Angled_Pickup_C_1[3]), true); }
										if (Setting::BP_WB_Vertical_Pickup_C_1 && Item.Name == "Vertical Foregrip") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_WB_Vertical_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_WB_Vertical_Pickup_C_1[0], BP_WB_Vertical_Pickup_C_1[1], BP_WB_Vertical_Pickup_C_1[2], BP_WB_Vertical_Pickup_C_1[3]), true); }
										if (Setting::BP_WB_LightGrip_Pickup_C_1 && Item.Name == "Light Grip") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_WB_LightGrip_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_WB_LightGrip_Pickup_C_1[0], BP_WB_LightGrip_Pickup_C_1[1], BP_WB_LightGrip_Pickup_C_1[2], BP_WB_LightGrip_Pickup_C_1[3]), true); }
										if (Setting::BP_WB_HalfGrip_Pickup_C_1 && Item.Name == "Half Grip") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_WB_HalfGrip_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_WB_HalfGrip_Pickup_C_1[0], BP_WB_HalfGrip_Pickup_C_1[1], BP_WB_HalfGrip_Pickup_C_1[2], BP_WB_HalfGrip_Pickup_C_1[3]), true); }
										if (Setting::BP_WB_ThumbGrip_Pickup_C_1 && Item.Name == "Thumb Grip") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_WB_ThumbGrip_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_WB_ThumbGrip_Pickup_C_1[0], BP_WB_ThumbGrip_Pickup_C_1[1], BP_WB_ThumbGrip_Pickup_C_1[2], BP_WB_ThumbGrip_Pickup_C_1[3]), true); }
										if (Setting::BP_WB_Lasersight_Pickup_C_1 && Item.Name == "Laser Sight") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_WB_Lasersight_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_WB_Lasersight_Pickup_C_1[0], BP_WB_Lasersight_Pickup_C_1[1], BP_WB_Lasersight_Pickup_C_1[2], BP_WB_Lasersight_Pickup_C_1[3]), true); }
										if (Setting::BP_MZJ_HD_Pickup_C_1 && Item.Name == "Red Dot Sight") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_MZJ_HD_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_MZJ_HD_Pickup_C_1[0], BP_MZJ_HD_Pickup_C_1[1], BP_MZJ_HD_Pickup_C_1[2], BP_MZJ_HD_Pickup_C_1[3]), true); }
										if (Setting::BP_MZJ_QX_Pickup_C_1 && Item.Name == "Holographic Sight") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_MZJ_QX_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_MZJ_QX_Pickup_C_1[0], BP_MZJ_QX_Pickup_C_1[1], BP_MZJ_QX_Pickup_C_1[2], BP_MZJ_QX_Pickup_C_1[3]), true); }
										if (Setting::BP_MZJ_SideRMR_Pickup_C_1 && Item.Name == "Canted Sight") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_MZJ_SideRMR_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_MZJ_SideRMR_Pickup_C_1[0], BP_MZJ_SideRMR_Pickup_C_1[1], BP_MZJ_SideRMR_Pickup_C_1[2], BP_MZJ_SideRMR_Pickup_C_1[3]), true); }
										if (Setting::BP_ZDD_Sniper_Pickup_C_1 && Item.Name == "Bullet Loop (Shotguns, Sniper Rifles)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_ZDD_Sniper_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_ZDD_Sniper_Pickup_C_1[0], BP_ZDD_Sniper_Pickup_C_1[1], BP_ZDD_Sniper_Pickup_C_1[2], BP_ZDD_Sniper_Pickup_C_1[3]), true); }
										if (Setting::BP_QT_UZI_Pickup_C_1 && Item.Name == "Stock (Micro UZI)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QT_UZI_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QT_UZI_Pickup_C_1[0], BP_QT_UZI_Pickup_C_1[1], BP_QT_UZI_Pickup_C_1[2], BP_QT_UZI_Pickup_C_1[3]), true); }
										if (Setting::BP_QT_A_Pickup_C_1 && Item.Name == "Tactical Stock (Rifles, SMG)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QT_A_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QT_A_Pickup_C_1[0], BP_QT_A_Pickup_C_1[1], BP_QT_A_Pickup_C_1[2], BP_QT_A_Pickup_C_1[3]), true); }
										if (Setting::BP_QT_Sniper_Pickup_C_1 && Item.Name == "Cheek Pad (Snipers)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_QT_Sniper_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_QT_Sniper_Pickup_C_1[0], BP_QT_Sniper_Pickup_C_1[1], BP_QT_Sniper_Pickup_C_1[2], BP_QT_Sniper_Pickup_C_1[3]), true); }
										if (Setting::BP_ZDD_Crossbow_Q_Pickup_C_1 && Item.Name == "Quiver (Crossbow)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_ZDD_Crossbow_Q_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_ZDD_Crossbow_Q_Pickup_C_1[0], BP_ZDD_Crossbow_Q_Pickup_C_1[1], BP_ZDD_Crossbow_Q_Pickup_C_1[2], BP_ZDD_Crossbow_Q_Pickup_C_1[3]), true); }
										if (Setting::BP_DJ_Mid_E_Pickup_C_1 && Item.Name == "Extended Mag (SMG, Pistols)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_DJ_Mid_E_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_DJ_Mid_E_Pickup_C_1[0], BP_DJ_Mid_E_Pickup_C_1[1], BP_DJ_Mid_E_Pickup_C_1[2], BP_DJ_Mid_E_Pickup_C_1[3]), true); }
										if (Setting::BP_DJ_Mid_Q_Pickup_C_1 && Item.Name == "Quickdraw Mag (SMG, Pistols)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_DJ_Mid_Q_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_DJ_Mid_Q_Pickup_C_1[0], BP_DJ_Mid_Q_Pickup_C_1[1], BP_DJ_Mid_Q_Pickup_C_1[2], BP_DJ_Mid_Q_Pickup_C_1[3]), true); }
										if (Setting::BP_DJ_Mid_EQ_Pickup_C_1 && Item.Name == "Extended Quickdraw Mag (SMG, Pistols)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_DJ_Mid_EQ_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_DJ_Mid_EQ_Pickup_C_1[0], BP_DJ_Mid_EQ_Pickup_C_1[1], BP_DJ_Mid_EQ_Pickup_C_1[2], BP_DJ_Mid_EQ_Pickup_C_1[3]), true); }
										if (Setting::BP_DJ_Sniper_E_Pickup_C_1 && Item.Name == "Extended Mag (Snipers)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_DJ_Sniper_E_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_DJ_Sniper_E_Pickup_C_1[0], BP_DJ_Sniper_E_Pickup_C_1[1], BP_DJ_Sniper_E_Pickup_C_1[2], BP_DJ_Sniper_E_Pickup_C_1[3]), true); }
										if (Setting::BP_DJ_Sniper_Q_Pickup_C_1 && Item.Name == "Quickdraw Mag (Snipers)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_DJ_Sniper_Q_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_DJ_Sniper_Q_Pickup_C_1[0], BP_DJ_Sniper_Q_Pickup_C_1[1], BP_DJ_Sniper_Q_Pickup_C_1[2], BP_DJ_Sniper_Q_Pickup_C_1[3]), true); }
										if (Setting::BP_DJ_Sniper_EQ_Pickup_C_1 && Item.Name == "Extended Quickdraw Mag (Snipers)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_DJ_Sniper_EQ_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_DJ_Sniper_EQ_Pickup_C_1[0], BP_DJ_Sniper_EQ_Pickup_C_1[1], BP_DJ_Sniper_EQ_Pickup_C_1[2], BP_DJ_Sniper_EQ_Pickup_C_1[3]), true); }
										if (Setting::BP_DJ_Large_E_Pickup_C_1 && Item.Name == "Extended Quickdraw Mag (AR)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_DJ_Large_E_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_DJ_Large_E_Pickup_C_1[0], BP_DJ_Large_E_Pickup_C_1[1], BP_DJ_Large_E_Pickup_C_1[2], BP_DJ_Large_E_Pickup_C_1[3]), true); }
										if (Setting::BP_DJ_Large_Q_Pickup_C_1 && Item.Name == "Quickdraw Mag (AR)") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_DJ_Large_Q_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_DJ_Large_Q_Pickup_C_1[0], BP_DJ_Large_Q_Pickup_C_1[1], BP_DJ_Large_Q_Pickup_C_1[2], BP_DJ_Large_Q_Pickup_C_1[3]), true); }
										if (Setting::BP_DJ_Large_EQ_Pickup_C_1 && Item.Name == "Extended Quickdraw Mag") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_DJ_Large_EQ_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_DJ_Large_EQ_Pickup_C_1[0], BP_DJ_Large_EQ_Pickup_C_1[1], BP_DJ_Large_EQ_Pickup_C_1[2], BP_DJ_Large_EQ_Pickup_C_1[3]), true); }
										//-------------//
										// PISTOLS
										if (Setting::BP_Pistol_P92_Wrapper_C_1 && Item.Name == "P92") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_Pistol_P92_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_Pistol_P92_Wrapper_C_1[0], BP_Pistol_P92_Wrapper_C_1[1], BP_Pistol_P92_Wrapper_C_1[2], BP_Pistol_P92_Wrapper_C_1[3]), true); }
										if (Setting::BP_Pistol_P1911_Wrapper_C_1 && Item.Name == "P1911") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_Pistol_P1911_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_Pistol_P1911_Wrapper_C_1[0], BP_Pistol_P1911_Wrapper_C_1[1], BP_Pistol_P1911_Wrapper_C_1[2], BP_Pistol_P1911_Wrapper_C_1[3]), true); }
										if (Setting::BP_Pistol_R1895_Wrapper_C_1 && Item.Name == "R1895") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_Pistol_R1895_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_Pistol_R1895_Wrapper_C_1[0], BP_Pistol_R1895_Wrapper_C_1[1], BP_Pistol_R1895_Wrapper_C_1[2], BP_Pistol_R1895_Wrapper_C_1[3]), true); }
										if (Setting::BP_Pistol_P18C_Wrapper_C_1 && Item.Name == "P18C") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_Pistol_P18C_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_Pistol_P18C_Wrapper_C_1[0], BP_Pistol_P18C_Wrapper_C_1[1], BP_Pistol_P18C_Wrapper_C_1[2], BP_Pistol_P18C_Wrapper_C_1[3]), true); }
										if (Setting::BP_Pistol_R45_Wrapper_C_1 && Item.Name == "R45") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_Pistol_R45_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_Pistol_R45_Wrapper_C_1[0], BP_Pistol_R45_Wrapper_C_1[1], BP_Pistol_R45_Wrapper_C_1[2], BP_Pistol_R45_Wrapper_C_1[3]), true); }
										if (Setting::BP_Pistol_Vz61_Wrapper_C_1 && Item.Name == "Vz61") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_Pistol_Vz61_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_Pistol_Vz61_Wrapper_C_1[0], BP_Pistol_Vz61_Wrapper_C_1[1], BP_Pistol_Vz61_Wrapper_C_1[2], BP_Pistol_Vz61_Wrapper_C_1[3]), true); }
										if (Setting::BP_Pistol_DesertEagle_Wrapper_C_1 && Item.Name == "Desert Eagle") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_Pistol_DesertEagle_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_Pistol_DesertEagle_Wrapper_C_1[0], BP_Pistol_DesertEagle_Wrapper_C_1[1], BP_Pistol_DesertEagle_Wrapper_C_1[2], BP_Pistol_DesertEagle_Wrapper_C_1[3]), true); }
										if (Setting::BP_ShotGun_SawedOff_Wrapper_C_1 && Item.Name == "Sawed-off") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_ShotGun_SawedOff_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_ShotGun_SawedOff_Wrapper_C_1[0], BP_ShotGun_SawedOff_Wrapper_C_1[1], BP_ShotGun_SawedOff_Wrapper_C_1[2], BP_ShotGun_SawedOff_Wrapper_C_1[3]), true); }
										//////////////////MALE////////////////////////////////
										if (Setting::BP_WEP_Machete_Pickup_C_1 && Item.Name == "Machete") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_WEP_Machete_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_WEP_Machete_Pickup_C_1[0], BP_WEP_Machete_Pickup_C_1[1], BP_WEP_Machete_Pickup_C_1[2], BP_WEP_Machete_Pickup_C_1[3]), true); }
										if (Setting::BP_WEP_Cowbar_Pickup_C_1 && Item.Name == "Crowbar") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_WEP_Cowbar_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_WEP_Cowbar_Pickup_C_1[0], BP_WEP_Cowbar_Pickup_C_1[1], BP_WEP_Cowbar_Pickup_C_1[2], BP_WEP_Cowbar_Pickup_C_1[3]), true); }
										if (Setting::BP_WEP_Sickle_Pickup_C_1 && Item.Name == "Sickle") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_WEP_Sickle_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_WEP_Sickle_Pickup_C_1[0], BP_WEP_Sickle_Pickup_C_1[1], BP_WEP_Sickle_Pickup_C_1[2], BP_WEP_Sickle_Pickup_C_1[3]), true); }
										if (Setting::BP_WEP_Pan_Pickup_C_1 && Item.Name == "Pan") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_WEP_Pan_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_WEP_Pan_Pickup_C_1[0], BP_WEP_Pan_Pickup_C_1[1], BP_WEP_Pan_Pickup_C_1[2], BP_WEP_Pan_Pickup_C_1[3]), true); }
										//////////////////SHOTGANS////////////////////////////////
										if (Setting::BP_WEP_Pan_Pickup_C_1 && Item.Name == "S686") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_ShotGun_S686_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_ShotGun_S686_Wrapper_C_1[0], BP_ShotGun_S686_Wrapper_C_1[1], BP_ShotGun_S686_Wrapper_C_1[2], BP_ShotGun_S686_Wrapper_C_1[3]), true); }
										if (Setting::BP_WEP_Pan_Pickup_C_1 && Item.Name == "S1897") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_ShotGun_S1897_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_ShotGun_S1897_Wrapper_C_1[0], BP_ShotGun_S1897_Wrapper_C_1[1], BP_ShotGun_S1897_Wrapper_C_1[2], BP_ShotGun_S1897_Wrapper_C_1[3]), true); }
										if (Setting::BP_WEP_Pan_Pickup_C_1 && Item.Name == "S12K") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_ShotGun_S12K_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_ShotGun_S12K_Wrapper_C_1[0], BP_ShotGun_S12K_Wrapper_C_1[1], BP_ShotGun_S12K_Wrapper_C_1[2], BP_ShotGun_S12K_Wrapper_C_1[3]), true); }
										if (Setting::BP_WEP_Pan_Pickup_C_1 && Item.Name == "DP12") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_ShotGun_DP12_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_ShotGun_DP12_Wrapper_C_1[0], BP_ShotGun_DP12_Wrapper_C_1[1], BP_ShotGun_DP12_Wrapper_C_1[2], BP_ShotGun_DP12_Wrapper_C_1[3]), true); }
										if (Setting::BP_WEP_Pan_Pickup_C_1 && Item.Name == "M1014 Shotgun") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_ShotGun_M1014_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_ShotGun_M1014_Wrapper_C_1[0], BP_ShotGun_M1014_Wrapper_C_1[1], BP_ShotGun_M1014_Wrapper_C_1[2], BP_ShotGun_M1014_Wrapper_C_1[3]), true); }
										///////////////////////////////

										if (Setting::BP_Sniper_MK12_Wrapper_C_1 && Item.Name == "MK12") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_Sniper_VSS_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_Sniper_VSS_Wrapper_C_1[0], BP_Sniper_VSS_Wrapper_C_1[1], BP_Sniper_VSS_Wrapper_C_1[2], BP_Sniper_VSS_Wrapper_C_1[3]), true); }
										if (Setting::BP_Sniper_QBU_Wrapper_C_1 && Item.Name == "QBU") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_WEP_Mk14_Pickup_C_1s, air, Screen.X, Screen.Y, ImColor(BP_WEP_Mk14_Pickup_C_1[0], BP_WEP_Mk14_Pickup_C_1[1], BP_WEP_Mk14_Pickup_C_1[2], BP_WEP_Mk14_Pickup_C_1[3]), true); }
										if (Setting::BP_Sniper_Win94_Wrapper_C_1 && Item.Name == "Win94") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_Sniper_Win94_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_Sniper_Win94_Wrapper_C_1[0], BP_Sniper_Win94_Wrapper_C_1[1], BP_Sniper_Win94_Wrapper_C_1[2], BP_Sniper_Win94_Wrapper_C_1[3]), true); }
										if (Setting::BP_Sniper_VSS_Wrapper_C_1 && Item.Name == "VSS") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_Sniper_QBU_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_Sniper_QBU_Wrapper_C_1[0], BP_Sniper_QBU_Wrapper_C_1[1], BP_Sniper_QBU_Wrapper_C_1[2], BP_Sniper_QBU_Wrapper_C_1[3]), true); }
										if (Setting::BP_Sniper_Mosin_Wrapper_C_1 && Item.Name == "MosinNagant") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_Sniper_Mosin_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_Sniper_Mosin_Wrapper_C_1[0], BP_Sniper_Mosin_Wrapper_C_1[1], BP_Sniper_Mosin_Wrapper_C_1[2], BP_Sniper_Mosin_Wrapper_C_1[3]), true); }
										if (Setting::BP_DJ_Large_EQ_Pickup_C_1 && Item.Name == "Mk14") { DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, BP_Sniper_MK12_Wrapper_C_1s, air, Screen.X, Screen.Y, ImColor(BP_Sniper_MK12_Wrapper_C_1[0], BP_Sniper_MK12_Wrapper_C_1[1], BP_Sniper_MK12_Wrapper_C_1[2], BP_Sniper_MK12_Wrapper_C_1[3]), true); }


										if (Setting::Esp_Item_AKM && Item.Name == "AKM")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, AKMS, air, Screen.X, Screen.Y, ImColor(AKM[0], AKM[1], AKM[2], AKM[3]), true);
										}
										if (Setting::Esp_Item_SCARL && Item.Name == "SCAR-L")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, SCARS, air, Screen.X, Screen.Y, ImColor(scarl[0], scarl[1], scarl[2], scarl[3]), true);
										}
										if (Setting::Esp_Item_M416 && Item.Name == "M416")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, M416S, air, Screen.X, Screen.Y, ImColor(m16[0], m16[1], m16[2], m16[3]), true);
										}
										if (Setting::Esp_Item_HoneyBadger && Item.Name == "Honey Badger")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, Text, Screen.X, Screen.Y, Setting::plancolor, true);
										}
										if (Setting::Esp_Item_M762 && Item.Name == "M762")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, M762S, air, Screen.X, Screen.Y, ImColor(Esp_Item_M762_Color[0], Esp_Item_M762_Color[1], Esp_Item_M762_Color[2], Esp_Item_M762_Color[3]), true);
										}
										if (Setting::Esp_Item_FlareGun && Item.Name == "Groza")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, FLAREGS, air, Screen.X, Screen.Y, ImColor(Flaregun[0], Flaregun[1], Flaregun[2], Flaregun[3]), true);
										}

										if (Setting::Esp_Item_DP28 && Item.Name == "DP28")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, DPS, air, Screen.X, Screen.Y, ImColor(Esp_Item_DP28_Color[0], Esp_Item_DP28_Color[1], Esp_Item_DP28_Color[2], Esp_Item_DP28_Color[3]), true);
										}

										if (Setting::Esp_Item_M249 && Item.Name == "M249")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, M249S, Text, Screen.X, Screen.Y, ImColor(M249[0], M249[1], M249[2], M249[3]), true);
										}

										if (Setting::Esp_Item_Kar98k && Item.Name == "Kar98k")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, KARS, air, Screen.X, Screen.Y, ImColor(kar98[0], kar98[1], kar98[2], kar98[3]), true);
										}
										if (Setting::Esp_Item_M24 && Item.Name == "M24")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, M24S, air, Screen.X, Screen.Y, ImColor(M24[0], M24[1], M24[2], M24[3]), true);
										}
										if (Setting::Esp_Item_Awm && Item.Name == "AWM")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, AWMS, air, Screen.X, Screen.Y, ImColor(AWM[0], AWM[1], AWM[2], AWM[3]), true);
										}
										if (Setting::plan && Item.Name == "Plan")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Setting::fontsize, air, Screen.X, Screen.Y, ImColor(plancolor[0], plancolor[1], plancolor[2], plancolor[3]), true);
										}
										if (Setting::Esp_Item_FlareGun && Item.Name == "Flare Gun")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, FLAREGS, air, Screen.X, Screen.Y, ImColor(Flaregun[0], Flaregun[1], Flaregun[2], Flaregun[3]), true);
										}

										if (Setting::Esp_Item_Flare && Item.Name == "Flare")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, FLARES, air, Screen.X, Screen.Y, ImColor(Flare[0], Flare[1], Flare[2], Flare[3]), true);
										}
										if (Setting::Esp_Item_Armor3 && Item.Name == "Armor L.3")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Armor3S, air, Screen.X, Screen.Y, ImColor(Esp_Item_Armor3_Color[0], Esp_Item_Armor3_Color[1], Esp_Item_Armor3_Color[2], Esp_Item_Armor3_Color[3]), true);
										}
										if (Setting::Esp_Item_Bag3 && Item.Name == "Bag L.3")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Bag3S, air, Screen.X, Screen.Y, ImColor(Esp_Item_Bag3_Color[0], Esp_Item_Bag3_Color[1], Esp_Item_Bag3_Color[2], Esp_Item_Bag3_Color[3]), true);
										}
										if (Setting::Esp_Item_Helmet3 && Item.Name == "Helmet L.3")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Helmet3S, air, Screen.X, Screen.Y, ImColor(Esp_Item_Helmet3_Color[0], Esp_Item_Helmet3_Color[1], Esp_Item_Helmet3_Color[2], Esp_Item_Helmet3_Color[3]), true);
										}
										if (Setting::Esp_Item_Helmet3 && Item.Name == "300Magnum")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, AMO300S, air, Screen.X, Screen.Y, ImColor(Esp_Item_Helmet3_Color[0], Esp_Item_Helmet3_Color[1], Esp_Item_Helmet3_Color[2], Esp_Item_Helmet3_Color[3]), true);
										}
										if (Setting::Esp_Item_Bag1 && Item.Name == "Bag L.1")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Bag1S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_Bag1_Color[0], Esp_Item_Bag1_Color[1], Esp_Item_Bag1_Color[2], Esp_Item_Bag1_Color[3]), true);
										}

										if (Setting::Esp_Item_Bag2 && Item.Name == "Bag L.2")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Bag2S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_Bag2_Color[0], Esp_Item_Bag2_Color[1], Esp_Item_Bag2_Color[2], Esp_Item_Bag2_Color[3]), true);
										}

										if (Setting::Esp_Item_Helmet1 && Item.Name == "Helmet L.1")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Helmet1S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_Helmet1_Color[0], Esp_Item_Helmet1_Color[1], Esp_Item_Helmet1_Color[2], Esp_Item_Helmet1_Color[3]), true);
										}

										if (Setting::Esp_Item_Helmet2 && Item.Name == "Helmet L.2")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Helmet2S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_Helmet2_Color[0], Esp_Item_Helmet2_Color[1], Esp_Item_Helmet2_Color[2], Esp_Item_Helmet2_Color[3]), true);
										}

										if (Setting::Esp_Item_Armor1 && Item.Name == "Armor L.1")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Armor1S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_Armor1_Color[0], Esp_Item_Armor1_Color[1], Esp_Item_Armor1_Color[2], Esp_Item_Armor1_Color[3]), true);
										}

										if (Setting::Esp_Item_Armor2 && Item.Name == "Armor L.2")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Armor2S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_Armor2_Color[0], Esp_Item_Armor2_Color[1], Esp_Item_Armor2_Color[2], Esp_Item_Armor2_Color[3]), true);
										}


										if (Setting::Esp_Item_Mk47Mutant && Item.Name == "Mk47 Mutant")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, MK47S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_Mk47Mutant_Color[0], Esp_Item_Mk47Mutant_Color[1], Esp_Item_Mk47Mutant_Color[2], Esp_Item_Mk47Mutant_Color[3]), true);
										}

										if (Setting::Esp_Item_M16A4 && Item.Name == "M16A4")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, M16A4S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_M16A4_Color[0], Esp_Item_M16A4_Color[1], Esp_Item_M16A4_Color[2], Esp_Item_M16A4_Color[3]), true);
										}

										if (Setting::Esp_Item_G36C && Item.Name == "G36C")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, G36CS, Text, Screen.X, Screen.Y, ImColor(Esp_Item_G36C_Color[0], Esp_Item_G36C_Color[1], Esp_Item_G36C_Color[2], Esp_Item_G36C_Color[3]), true);
										}

										if (Setting::Esp_Item_QBZ && Item.Name == "QBZ")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, QBZS, Text, Screen.X, Screen.Y, ImColor(Esp_Item_QBZ_Color[0], Esp_Item_QBZ_Color[1], Esp_Item_QBZ_Color[2], Esp_Item_QBZ_Color[3]), true);
										}

										if (Setting::Esp_Item_QBU && Item.Name == "QBU")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, QBUS, Text, Screen.X, Screen.Y, ImColor(Esp_Item_QBU_Color[0], Esp_Item_QBU_Color[1], Esp_Item_QBU_Color[2], Esp_Item_QBU_Color[3]), true);
										}

										if (Setting::Esp_Item_SLR && Item.Name == "SLR")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, SLRS, Text, Screen.X, Screen.Y, ImColor(Esp_Item_SLR_Color[0], Esp_Item_SLR_Color[1], Esp_Item_SLR_Color[2], Esp_Item_SLR_Color[3]), true);
										}

										if (Setting::Esp_Item_Mini14 && Item.Name == "Mini-14")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, MINIS, Text, Screen.X, Screen.Y, ImColor(Esp_Item_Mini14_Color[0], Esp_Item_Mini14_Color[1], Esp_Item_Mini14_Color[2], Esp_Item_Mini14_Color[3]), true);
										}

										if (Setting::Esp_Item_PP19 && Item.Name == "PP19")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, PPS, Text, Screen.X, Screen.Y, ImColor(Esp_Item_PP19_Color[0], Esp_Item_PP19_Color[1], Esp_Item_PP19_Color[2], Esp_Item_PP19_Color[3]), true);
										}

										if (Setting::Esp_Item_TommyGun && Item.Name == "Tommy Gun")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, TOMMYS, Text, Screen.X, Screen.Y, ImColor(Esp_Item_TommyGun_Color[0], Esp_Item_TommyGun_Color[1], Esp_Item_TommyGun_Color[2], Esp_Item_TommyGun_Color[3]), true);
										}

										if (Setting::Esp_Item_MP5K && Item.Name == "MP5K")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, MP5KS, Text, Screen.X, Screen.Y, ImColor(Esp_Item_MP5K_Color[0], Esp_Item_MP5K_Color[1], Esp_Item_MP5K_Color[2], Esp_Item_MP5K_Color[3]), true);
										}

										if (Setting::Esp_Item_UMP9 && Item.Name == "UMP9")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, UMP9S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_UMP9_Color[0], Esp_Item_UMP9_Color[1], Esp_Item_UMP9_Color[2], Esp_Item_UMP9_Color[3]), true);
										}

										if (Setting::Esp_Item_Vector && Item.Name == "Vector")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, VECTORS, Text, Screen.X, Screen.Y, ImColor(Esp_Item_Vector_Color[0], Esp_Item_Vector_Color[1], Esp_Item_Vector_Color[2], Esp_Item_Vector_Color[3]), true);
										}

										if (Setting::Esp_Item_Uzi && Item.Name == "Uzi")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, UZIS, Text, Screen.X, Screen.Y, ImColor(Esp_Item_Uzi_Color[0], Esp_Item_Uzi_Color[1], Esp_Item_Uzi_Color[2], Esp_Item_Uzi_Color[3]), true);
										}

										if (Setting::Esp_Item_762mm && Item.Name == "7.62mm")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, AMO7S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_762mm_Color[0], Esp_Item_762mm_Color[1], Esp_Item_762mm_Color[2], Esp_Item_762mm_Color[3]), true);
										}

										if (Setting::Esp_Item_556mm && Item.Name == "5.56mm")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, AMO5S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_556mm_Color[0], Esp_Item_556mm_Color[1], Esp_Item_556mm_Color[2], Esp_Item_556mm_Color[3]), true);
										}

										if (Setting::Esp_Item_9mm && Item.Name == "9mm")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, AMO9S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_9mm_Color[0], Esp_Item_9mm_Color[1], Esp_Item_9mm_Color[2], Esp_Item_9mm_Color[3]), true);
										}

										if (Setting::Esp_Item_45ACP && Item.Name == "45ACP")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, AMO45S, Text, Screen.X, Screen.Y, ImColor(Esp_Item_45ACP_Color[0], Esp_Item_45ACP_Color[1], Esp_Item_45ACP_Color[2], Esp_Item_45ACP_Color[3]), true);
										}

										if (Setting::Esp_Item_Holo && Item.Name == "Holo")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, HOLOS, Text, Screen.X, Screen.Y, ImColor(Esp_Item_Holo_Color[0], Esp_Item_Holo_Color[1], Esp_Item_Holo_Color[2], Esp_Item_Holo_Color[3]), true);
										}

										if (Setting::Esp_Item_Mk12 && Item.Name == "MK12")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, MK12S, Text, Screen.X, Screen.Y, ImColor(MK12[0], MK12[1], MK12[2], MK12[3]), true);
										}

										if (Setting::token && Item.Name == "Shop Token")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X - 10, Screen.Y, DX11::ImGui_DX11::Color::enem2, true);
											continue;
										}

										if (Setting::Esp_Item_Kar98k && Item.Name == "Kar98k")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, weapon::kar98, true);
											continue;
										}

										if (Setting::plan && Item.Name == "[AIR-PLANE]")
										{
											string  Text = Item.Name + " " + to_string(Distance) + "M";
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, Setting::plancolor, true);
											continue;
										}

										if (Item.Name == "[MVP-STATUE]")
										{
											string  statue1 = Item.Name + " " + to_string(Distance) + "M";
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, statue1, Screen.X, Screen.Y, ImColor(255, 255, 0, 255), true);
											continue;
										}

										if (Setting::Esp_Item_DP28 && Item.Name == "DP28")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_DP28_Color[0], Setting::Esp_Item_DP28_Color[1], Setting::Esp_Item_DP28_Color[2], Setting::Esp_Item_DP28_Color[3]), true);
											continue;
										}
										if (Setting::Esp_Item_M762 && Item.Name == "M762")
										{
											if (Setting::Esp_Item_M762_Icon)
											{
												DX11::ImGui_DX11::DrawImage(DX11::M762, Screen.X - 50, Screen.Y - 25, 100, 50);
												continue;
											}
											else
											{

												DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_M762_Color[0], Setting::Esp_Item_M762_Color[1], Setting::Esp_Item_M762_Color[2], Setting::Esp_Item_M762_Color[3]), true);
												continue;
											}
										}
										if (Setting::Esp_Item_Awm && Item.Name == "AWM")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, air, Screen.X, Screen.Y, weapon::AWM, true);
											continue;
										}

										if (Setting::Esp_Item_FlareGun && Item.Name == "Flare Gun")
										{
											if (Setting::Esp_Item_FlareGun_Icon)
											{
												DX11::ImGui_DX11::DrawImage(DX11::FLAREGUN, Screen.X - 50, Screen.Y - 25, 100, 50);
												continue;
											}
											else
											{

												DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, air, Screen.X, Screen.Y, weapon::Flaregun, true);
												continue;
											}
										}
										if (Setting::Esp_Item_Flare && Item.Name == "Flare")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, air, Screen.X, Screen.Y, weapon::Flare, true);
											continue;
										}

										if (Setting::Esp_Item_AirDrop && Item.Name == "Air Drop")
										{
											//DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, air, Screen.X, Screen.Y, weapon::Airdrop, true);
											continue;
										}
										if (Setting::Esp_Item_Armor3 && Item.Name == "Armor L.3")
										{
											DX11::ImGui_DX11::DrawImage(DX11::Armor3, Screen.X - 15, Screen.Y - 15, 30, 30);
											//continue;
											//DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Armor3_Color[0], Setting::Esp_Item_Armor3_Color[1], Setting::Esp_Item_Armor3_Color[2], Setting::Esp_Item_Armor3_Color[3]), true);
											continue;
										}
										if (Setting::Esp_Item_Bag3 && Item.Name == "Bag L.3")
										{

											DX11::ImGui_DX11::DrawImage(DX11::Bag3, Screen.X - 15, Screen.Y - 15, 30, 30);
											continue;
											//DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Bag3_Color[0], Setting::Esp_Item_Bag3_Color[1], Setting::Esp_Item_Bag3_Color[2], Setting::Esp_Item_Bag3_Color[3]), true);
											continue;
										}
										if (Setting::Esp_Item_Helmet3 && Item.Name == "Helmet L.3")
										{


											DX11::ImGui_DX11::DrawImage(DX11::Helmet3, Screen.X - 15, Screen.Y - 15, 30, 30);
											continue;
											/*
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Helmet3_Color[0], Setting::Esp_Item_Helmet3_Color[1], Setting::Esp_Item_Helmet3_Color[2], Setting::Esp_Item_Helmet3_Color[3]), true);
											continue;*/
										}
										if (Setting::Esp_Item_Helmet3 && Item.Name == "300Magnum")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, air, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Helmet3_Color[0], Setting::Esp_Item_Helmet3_Color[1], Setting::Esp_Item_Helmet3_Color[2], Setting::Esp_Item_Helmet3_Color[3]), true);
											continue;
										}
										if (Setting::Esp_Item_exquic && Item.Name == "Ex QuickDraw")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, weapon::QuickDraw, true);
											//DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, air, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_exquic_Color[0], Setting::Esp_Item_exquic_Color[1], Setting::Esp_Item_exquic_Color[2], Setting::Esp_Item_exquic_Color[3]), true);
											continue;
										}
									}
									if (Setting::healthitem) {
										if (Setting::Esp_Item_MedKit && Item.Name == "Med Kit")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_MedKit_Color[0], Setting::Esp_Item_MedKit_Color[1], Setting::Esp_Item_MedKit_Color[2], Setting::Esp_Item_MedKit_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_FirstAidKit && Item.Name == "First Aid Kit")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_FirstAidKit_Color[0], Setting::Esp_Item_FirstAidKit_Color[1], Setting::Esp_Item_FirstAidKit_Color[2], Setting::Esp_Item_FirstAidKit_Color[3]), true);
											continue;
										}
										if (Setting::Esp_Item_Painkiller && Item.Name == "Painkiller")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Painkiller_Color[0], Setting::Esp_Item_Painkiller_Color[1], Setting::Esp_Item_Painkiller_Color[2], Setting::Esp_Item_Painkiller_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_EnergyDrink && Item.Name == "Energy Drink")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_EnergyDrink_Color[0], Setting::Esp_Item_EnergyDrink_Color[1], Setting::Esp_Item_EnergyDrink_Color[2], Setting::Esp_Item_EnergyDrink_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_AdrenalineSyringe && Item.Name == "Adrenaline Syringe")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_AdrenalineSyringe_Color[0], Setting::Esp_Item_AdrenalineSyringe_Color[1], Setting::Esp_Item_AdrenalineSyringe_Color[2], Setting::Esp_Item_AdrenalineSyringe_Color[3]), true);
											continue;
										}
									}
									if (Setting::scope) {
										if (Setting::Esp_Item_x2 && Item.Name == "2x")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_x2_Color[0], Setting::Esp_Item_x2_Color[1], Setting::Esp_Item_x2_Color[2], Setting::Esp_Item_x2_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_x3 && Item.Name == "3x")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_x3_Color[0], Setting::Esp_Item_x3_Color[1], Setting::Esp_Item_x3_Color[2], Setting::Esp_Item_x3_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_x4 && Item.Name == "4x")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_x4_Color[0], Setting::Esp_Item_x4_Color[1], Setting::Esp_Item_x4_Color[2], Setting::Esp_Item_x4_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_x6 && Item.Name == "6x")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_x6_Color[0], Setting::Esp_Item_x6_Color[1], Setting::Esp_Item_x6_Color[2], Setting::Esp_Item_x6_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_x8 && Item.Name == "8x")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_x8_Color[0], Setting::Esp_Item_x8_Color[1], Setting::Esp_Item_x8_Color[2], Setting::Esp_Item_x8_Color[3]), true);
											continue;
										}
									}
									if (Setting::allitemss) {
										if (Setting::Esp_Item_Bag1 && Item.Name == "Bag L.1")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Bag1_Color[0], Setting::Esp_Item_Bag1_Color[1], Setting::Esp_Item_Bag1_Color[2], Setting::Esp_Item_Bag1_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_Bag2 && Item.Name == "Bag L.2")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Bag2_Color[0], Setting::Esp_Item_Bag2_Color[1], Setting::Esp_Item_Bag2_Color[2], Setting::Esp_Item_Bag2_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_Helmet1 && Item.Name == "Helmet L.1")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Helmet1_Color[0], Setting::Esp_Item_Helmet1_Color[1], Setting::Esp_Item_Helmet1_Color[2], Setting::Esp_Item_Helmet1_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_Helmet2 && Item.Name == "Helmet L.2")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Helmet2_Color[0], Setting::Esp_Item_Helmet2_Color[1], Setting::Esp_Item_Helmet2_Color[2], Setting::Esp_Item_Helmet2_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_Armor1 && Item.Name == "Armor L.1")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Armor1_Color[0], Setting::Esp_Item_Armor1_Color[1], Setting::Esp_Item_Armor1_Color[2], Setting::Esp_Item_Armor1_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_Armor2 && Item.Name == "Armor L.2")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Armor2_Color[0], Setting::Esp_Item_Armor2_Color[1], Setting::Esp_Item_Armor2_Color[2], Setting::Esp_Item_Armor2_Color[3]), true);
											continue;
										}


										if (Setting::Esp_Item_Mk47Mutant && Item.Name == "Mk47 Mutant")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Mk47Mutant_Color[0], Setting::Esp_Item_Mk47Mutant_Color[1], Setting::Esp_Item_Mk47Mutant_Color[2], Setting::Esp_Item_Mk47Mutant_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_M16A4 && Item.Name == "M16A4")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_M16A4_Color[0], Setting::Esp_Item_M16A4_Color[1], Setting::Esp_Item_M16A4_Color[2], Setting::Esp_Item_M16A4_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_G36C && Item.Name == "G36C")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_G36C_Color[0], Setting::Esp_Item_G36C_Color[1], Setting::Esp_Item_G36C_Color[2], Setting::Esp_Item_G36C_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_QBZ && Item.Name == "QBZ")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_QBZ_Color[0], Setting::Esp_Item_QBZ_Color[1], Setting::Esp_Item_QBZ_Color[2], Setting::Esp_Item_QBZ_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_QBU && Item.Name == "QBU")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_QBU_Color[0], Setting::Esp_Item_QBU_Color[1], Setting::Esp_Item_QBU_Color[2], Setting::Esp_Item_QBU_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_SLR && Item.Name == "SLR")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_SLR_Color[0], Setting::Esp_Item_SLR_Color[1], Setting::Esp_Item_SLR_Color[2], Setting::Esp_Item_SLR_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_Mini14 && Item.Name == "Mini-14")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Mini14_Color[0], Setting::Esp_Item_Mini14_Color[1], Setting::Esp_Item_Mini14_Color[2], Setting::Esp_Item_Mini14_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_SKS && Item.Name == "SKS")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_SKS_Color[0], Setting::Esp_Item_SKS_Color[1], Setting::Esp_Item_SKS_Color[2], Setting::Esp_Item_SKS_Color[3]), true);
											continue;
										}


										if (Setting::Esp_Item_PP19 && Item.Name == "PP19")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_PP19_Color[0], Setting::Esp_Item_PP19_Color[1], Setting::Esp_Item_PP19_Color[2], Setting::Esp_Item_PP19_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_TommyGun && Item.Name == "Tommy Gun")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_TommyGun_Color[0], Setting::Esp_Item_TommyGun_Color[1], Setting::Esp_Item_TommyGun_Color[2], Setting::Esp_Item_TommyGun_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_MP5K && Item.Name == "MP5K")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_MP5K_Color[0], Setting::Esp_Item_MP5K_Color[1], Setting::Esp_Item_MP5K_Color[2], Setting::Esp_Item_MP5K_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_UMP9 && Item.Name == "UMP9")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_UMP9_Color[0], Setting::Esp_Item_UMP9_Color[1], Setting::Esp_Item_UMP9_Color[2], Setting::Esp_Item_UMP9_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_Vector && Item.Name == "Vector")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Vector_Color[0], Setting::Esp_Item_Vector_Color[1], Setting::Esp_Item_Vector_Color[2], Setting::Esp_Item_Vector_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_Uzi && Item.Name == "Uzi")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Uzi_Color[0], Setting::Esp_Item_Uzi_Color[1], Setting::Esp_Item_Uzi_Color[2], Setting::Esp_Item_Uzi_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_762mm && Item.Name == "7.62mm")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_762mm_Color[0], Setting::Esp_Item_762mm_Color[1], Setting::Esp_Item_762mm_Color[2], Setting::Esp_Item_762mm_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_556mm && Item.Name == "5.56mm")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_556mm_Color[0], Setting::Esp_Item_556mm_Color[1], Setting::Esp_Item_556mm_Color[2], Setting::Esp_Item_556mm_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_9mm && Item.Name == "9mm")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_9mm_Color[0], Setting::Esp_Item_9mm_Color[1], Setting::Esp_Item_9mm_Color[2], Setting::Esp_Item_9mm_Color[3]), true);
											continue;
										}
										if (Setting::Esp_Item_45ACP && Item.Name == "45ACP")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_45ACP_Color[0], Setting::Esp_Item_45ACP_Color[1], Setting::Esp_Item_45ACP_Color[2], Setting::Esp_Item_45ACP_Color[3]), true);
											continue;
										}

										if (Setting::Esp_Item_Holo && Item.Name == "Holo")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_Holo_Color[0], Setting::Esp_Item_Holo_Color[1], Setting::Esp_Item_Holo_Color[2], Setting::Esp_Item_Holo_Color[3]), true);
											continue;
										}
										if (Setting::Esp_Item_M249 && Item.Name == "M249")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, Colors::M249, true);
											continue;
										}

										if (Setting::Esp_Item_Mk12 && Item.Name == "MK12")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, Colors::MK12, true);
											continue;
										}
										if (Setting::Esp_Item_SniperAMR && Item.Name == "Sniper-AMR")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_SniperAMR_Color[0], Setting::Esp_Item_SniperAMR_Color[1], Setting::Esp_Item_SniperAMR_Color[2], Setting::Esp_Item_SniperAMR_Color[3]), true);
											continue;
										}
										if (Setting::Esp_Item_BulletAMR && Item.Name == "Ammo-50BMG")
										{
											DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::Normalfontsize, Text, Screen.X, Screen.Y, ImColor(Setting::Esp_Item_BulletAMR_Color[0], Setting::Esp_Item_BulletAMR_Color[1], Setting::Esp_Item_BulletAMR_Color[2], Setting::Esp_Item_BulletAMR_Color[3]), true);
											continue;
										}

									}
								}
							}
						}
					}
					if (Setting::deadbox)
					{
						ImColor color;
						if (Data::BoxesList.size() != 0)
						{
							TempBoxesList.clear();
							TempBoxesList = Data::BoxesList;
						}
						for (Deadbox Box : TempBoxesList)
						{
							if (!Algorithm::WorldToScreen(Data::lOCALPLAYERPosotion, Box.Position, Screen, &Distance, ViewMatrix)) continue;
							if (Distance < 8)
							{
								continue;
							}
							std::string dead = (Box.Name) + to_string(Distance) + "M";
							if (Box.IsDeadBox)
							{
								if (Distance > 100)
								{
									continue;
								}
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, dead, Screen.X, Screen.Y + 13, Colors::deadbox, false);

							}
							else if (Box.isAirDrop)
							{
								DX11::ImGui_DX11::DrawImage(DX11::AirDrop, Screen.X, Screen.Y - 20, 30, 30);
								string Dist = to_string(Distance) + "M";
								DX11::ImGui_DX11::DrawBorderText(DX11::ImGui_DX11::pRegularFont, 15, Dist, Screen.X, Screen.Y + 15, DX11::ImGui_DX11::Color::enem2, false);
							}
							if (Setting::playerdeadbox)
							{
								float yOffset{ -18.0f };
								for (int k = 0; k < Box.boxitem.size(); k++)
								{
									color = Box.boxitem[k].colorcod;
									std::string text = Box.boxitem[k].Displayname;
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, text, Screen.X + 16, Screen.Y + 15 + (yOffset), Box.boxitem[k].colorcod, false);
									yOffset -= 18.0f;

								}

							}

						}


					}

					if (Setting::Vehicle)
					{
						if (Data::VehicleList.size() != 0)
						{
							TempVehicalList.clear();
							TempVehicalList = Data::VehicleList;

							for (Vehicle& Vehicle : Data::VehicleList)
							{
								Vehicle.Position = Utility::ReadMemoryEx<VECTOR3>(Utility::ReadMemoryEx<DWORD>(Vehicle.Address + Offset::RootComponent) + Offset::Position);
								if (!Algorithm::WorldToScreen(Data::lOCALPLAYERPosotion, Vehicle.Position, Screen, &Distance, ViewMatrix)) continue;
								if (Distance < 5 || Distance > 700) {
									continue;
								}
								Text = Vehicle.Name + " | " + to_string(Distance) + "m";
								std::string hp;
								ImVec4 color;
								if (Vehicle.driving)
								{
									color = DX11::ImGui_DX11::Color::Red;
								}
								else {
									color = Colors::vehicle;
								}
								ImVec2 TextSize = DX11::ImGui_DX11::pRegularFont->CalcTextSizeA(vehisize, FLT_MAX, 0.0f, Text.c_str());

								if (Setting::hp)
								{
									const char* Fuel = ("%d ", ICON_FA_BATTERY_FULL);
									if (Vehicle.oil == 100.0) {
										Fuel = ("%d ", ICON_FA_BATTERY_FULL);
									}
									else if (Vehicle.oil > 75.0) {
										Fuel = ("%d ", ICON_FA_BATTERY_THREE_QUARTERS);
									}
									else if (Vehicle.oil > 50.0 && Vehicle.oil <= 75.0) {
										Fuel = ("%d ", ICON_FA_BATTERY_HALF);
									}
									else 	if (Vehicle.oil > 25.0 && Vehicle.oil <= 50.0)
									{
										Fuel = ("%d ", ICON_FA_BATTERY_QUARTER);

									}
									else if (Vehicle.oil <= 0) {
										Fuel = ("%d ", ICON_FA_BATTERY_EMPTY);
									}
									else {
										continue;
									}
									string OIL = std::to_string((int)(Vehicle.oil));







									// hp.append("%d :-", ICON_FA_HEART).append(std::to_string((int)(Vehicle.oil)).append(" ♡:-").append(std::to_string((int)(Vehicle.hp)).append("")));


									// DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - 5, Screen.Y + 23, Vehicle.hp, 2.0f, Colors::vehicle);
								//	 DX11::ImGui_DX11::DrawUnFilledRectangle2(Screen.X - 2, Screen.Y + 13, TextSize.x, 2.0f, DX11::ImGui_DX11::Color::Cyan);
									// DX11::ImGui_DX11::DrawUnFilledRectangle2(Screen.X - 5, Screen.Y + 23, Vehicle.oil, 2.0f, DX11::ImGui_DX11::Color::Olive);

									DX11::ImGui_DX11::DrawStringchar(DX11::ImGui_DX11::pRegularFont, 12, Fuel, Screen.X + 48, Screen.Y + 23, DX11::ImGui_DX11::Color::Yellow, true);
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 12, OIL, Screen.X + 58, Screen.Y + 23, DX11::ImGui_DX11::Color::enem2, true);
									//	 DX11::ImGui_DX11::DrawBlood(Screen.X - 5, Screen.Y + 23, 2, 4.0f, Vehicle.hp);
										//DX11::ImGui_DX11::DrawBlood(Screen.X - 5, Screen.Y + 31, 80.0f, 4.0f, Vehicle.oil);
										// DX11::ImGui_DX11::DrawImage(DX11::Heart, Screen.X  -5, Screen.Y + 20, 15, 15);

										//DX11::ImGui_DX11::DrawLine(Screen.X - 5, Screen.Y + 23, screen_end.X, screen_end.Y, Colors::enemyLineofSight, 2);
								}

								if (Setting::feul)
								{
									const char* Heart = ("%d ", ICON_FA_HEARTBEAT);
									string HPP = std::to_string((int)(Vehicle.hp));
									DX11::ImGui_DX11::DrawStringchar(DX11::ImGui_DX11::pRegularFont, 12, Heart, Screen.X + 10, Screen.Y + 23, DX11::ImGui_DX11::Color::Green, true);
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, 12, HPP, Screen.X + 18, Screen.Y + 23, DX11::ImGui_DX11::Color::enem2, true);
								}

								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, vehisize, Text, Screen.X, Screen.Y, color, true);
								continue;

							}
						}
					}
					if (Setting::BombAlert)
					{
						TempBombAlertList.clear();
						TempBombAlertList = Data::BombAlertList;
						for (BombAlert& bomb : TempBombAlertList) {
							bomb.Position = Utility::ReadMemoryEx<VECTOR3>(Utility::ReadMemoryEx<DWORD>(bomb.Address + Offset::RootComponent) + Offset::Position);
							//bomb.Position = Utility::ReadMemoryEx<VECTOR3>(Data::RootComponent + Offset::Position);
							if (!Algorithm::WorldToScreen(Data::lOCALPLAYERPosotion, bomb.Position, Screen, &Distance, ViewMatrix)) continue;
							if (Distance > 210)continue;
							string  Name = bomb.Name + " [" + to_string(Distance) + "m]";
							const char* Aim;
						//	string time = to_string(bomb.timeLeft);
							if (bomb.Name == "Smoke" || bomb.Name == "[ALERT] !Flash Granade")
							{
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, Setting::fontsize, Name, Screen.X, Screen.Y - 5, DX11::ImGui_DX11::Color::Red, true);
							}
							if (bomb.Name == "Frag")
							{
								Aim = ("\xef\x87\xa2 ");
								DX11::ImGui_DX11::DrawStringchar(DX11::ImGui_DX11::pRegularFont, 16, Aim, Screen.X, Screen.Y - 4, DX11::ImGui_DX11::Color::Red, true);
								Algorithm::Draw3Dcircle(ViewMatrix, Data::lOCALPLAYERPosotion, bomb.Position, 32, 550.0f, 1.0f, DX11::ImGui_DX11::Color::Green);
							}
							if (bomb.Name == "Air Bomb !")
							{
								Aim = ("\xef\x84\xb5 ");
								DX11::ImGui_DX11::DrawStringchar(DX11::ImGui_DX11::pRegularFont, 16, Aim, Screen.X, Screen.Y - 4, DX11::ImGui_DX11::Color::Red, true);
								Algorithm::Draw3Dcircle(ViewMatrix, Data::lOCALPLAYERPosotion, bomb.Position, 32, 550.0f, 1.0f, DX11::ImGui_DX11::Color::Green);
							}


							if (bomb.Name == "Burn")
							{
								Aim = ("\xef\x81\xad ");
								DX11::ImGui_DX11::DrawStringchar(DX11::ImGui_DX11::pRegularFont, 16, Aim, Screen.X , Screen.Y - 4, DX11::ImGui_DX11::Color::Red, true);
								Algorithm::Draw3Dcircle(ViewMatrix, Data::lOCALPLAYERPosotion, bomb.Position, 32, 550.0f, 1.0f, DX11::ImGui_DX11::Color::Green);


							}
							continue;
						}

					}
				}
			}

			ImGui::EndFrame();

			DX11::BeginDraw();
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			DX11::EndDraw();

			DX11Window::IsDrawing = false;

			DX11Window::IsDrawing = true;
		}
		catch (int e)
		{
			//std::cout << e << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}


}