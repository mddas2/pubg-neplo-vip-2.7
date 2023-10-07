#pragma once

#include "Includes.h"
#include"imgui-docking/imgui.h"
#include "imgui-docking/imgui_impl_win32.h"
#include "imgui-docking/imgui_impl_dx11.h"
#include "imgui-docking/imgui_internal.h"

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;

namespace weapon {


	extern ImVec4 m16;
	extern ImVec4 AKM;
	extern ImVec4 AWM;
	extern ImVec4 AWMimmo;
	extern ImVec4 scarl;
	extern ImVec4 m762;
	extern ImVec4 M24;
	extern ImVec4  GROZZA;
	extern ImVec4 scope8x;
	extern ImVec4 kar98;
	extern ImVec4  Airdrop;
	extern ImVec4 Flare;
	extern ImVec4 Flaregun;
	extern ImVec4 QuickDraw;
}

namespace Colors {

	extern ImVec4  dp;
	extern ImVec4  enemyLineofSight;
	extern ImVec4  Granadeswarn;
	extern ImVec4  mg3;
	extern ImVec4  scope4x;
	extern ImVec4  scope3x;
	extern	ImVec4  bag;
	extern	ImVec4  armer;
	extern	ImVec4  helmat;
	extern	ImVec4  mosin;
	extern ImVec4  aug;
	extern ImVec4  g36;
	extern ImVec4  assm;
	extern	ImVec4  Grandes;
	extern	ImVec4  ammo7;
	extern	ImVec4  ammo5;
	extern ImVec4  madkit;

	/////////////////////////
	extern ImVec4 itemcolors;
	// ARGB playr
	extern	ImVec4  playerline;
	extern	ImVec4  playercorner;
	extern	ImVec4  playerbox;
	extern	ImVec4  lotbox;
	// ARGB
	extern ImVec4  helthbar;
	extern ImVec4  boxColor;
	extern ImVec4  cornerColor;
	extern ImVec4  crosshairColor;
	extern	ImVec4  bot;
	extern	ImVec4  botbone;
	extern	ImVec4  skelec;
	extern	ImVec4  playerbone;
	extern	ImVec4  player;
	extern ImVec4  vehicle;
	//RGB
	extern ImVec4  botcorner;
	extern ImVec4  botline;
	extern	ImVec4 circle;
	extern	ImVec4  enemy;
	extern	ImVec4  botbox;
	extern	ImVec4  bone;
	extern	 ImVec4  fillrect;
	extern	 ImVec4  nam;
	extern	 ImVec4  nambar;
	extern	 ImVec4  bothealth;
	extern	ImVec4  botname;
	extern	ImVec4  playerhealth;
	extern	ImVec4  textcolor;
	extern	ImVec4  plyerdistance;
	extern	ImVec4  plyrweapon;
	extern	ImVec4  targetenemybone;
	extern	ImVec4 Granades;
	extern	ImVec4 health;
	extern	ImVec4 deadbox;
	extern	ImVec4 deadboxitem;
	extern	ImVec4 airdrop;
	extern	ImVec4 airdropitem;
	extern	ImVec4 scopetextcolor;
	extern	ImVec4  allitem;
	extern	ImVec4  scope6x;
	extern	ImVec4  magicline;
	extern	ImVec4  magiclinevvisile;
	extern	ImVec4  bgcorner;
	extern	ImVec4  fovcirclecolor;
	extern	ImVec4 M249;
	extern	ImVec4 MK12;
	extern	ImVec4 hpt;
}

namespace Setting
{
	extern bool puid;
	extern bool pflag; 
	extern bool knocked;
	extern bool gameinfo;
	extern bool enemyoffscreen;
	extern DWORD CurrentTargetAddress;
	extern bool SkipBots;
	extern bool SkipKnocked;
	extern bool AimLineCross;
	extern bool IsimingAtYou;
	extern bool AimLineBottm;
	extern bool MyLineOfSight;
	extern bool EnemyLineOfSight;
	extern int EnableKey;
	extern int AimbotKey;
	extern int FastCarKeys;
	extern int CamerAimbotKey;
	extern int fastrunkey;
	extern int GodViewKey;
	extern int PositionKey;
	extern	bool radar;
	extern	bool dots;
	extern	bool bg;
	extern int  redioption;
	extern int  RadarLength;
	extern int  RadarWidth;
	extern bool  redioption2;
	extern	bool IsMagicInitialize;
	extern FLOAT Aimspeed;
	extern float fovcircleredus;
	extern float enemyLineofSightSize;
	extern float CurrentBulletFireSpeed;
	extern bool aimbotposition;
	extern bool fovcircle;
	extern bool PREDICTION;
	extern bool Legitrack;









	extern RGBA	BP_QK_Choke_Pickup_C_1c;
	extern RGBA	BP_QK_Mid_Compensator_Pickup_C_1c;
	extern RGBA	BP_QK_Sniper_Compensator_Pickup_C_1c;
	extern RGBA	BP_QK_Mid_FlashHider_Pickup_C_1c;
	extern RGBA	BP_QK_Sniper_FlashHider_Pickup_C_1c;
	extern RGBA	BP_QK_Mid_Suppressor_Pickup_C_1c;
	extern RGBA	BP_QK_Sniper_Suppressor_Pickup_C_1c;
	extern RGBA	BP_QK_Large_Compensator_Pickup_C_1c;
	extern RGBA	BP_QK_Large_FlashHider_Pickup_C_1c;
	extern RGBA	BP_QK_Large_Suppressor_Pickup_C_1c;
	extern RGBA	BP_QK_DuckBill_Pickup_C_1c;
	extern RGBA	BP_WB_Angled_Pickup_C_1c;
	extern RGBA	BP_WB_Vertical_Pickup_C_1c;
	extern RGBA	BP_WB_LightGrip_Pickup_C_1c;
	extern RGBA	BP_WB_HalfGrip_Pickup_C_1c;
	extern RGBA	BP_WB_ThumbGrip_Pickup_C_1c;
	extern RGBA	BP_WB_Lasersight_Pickup_C_1c;
	extern RGBA	BP_MZJ_HD_Pickup_C_1c;
	extern RGBA	BP_MZJ_QX_Pickup_C_1c;
	extern RGBA	BP_MZJ_SideRMR_Pickup_C_1c;
	extern RGBA	BP_ZDD_Sniper_Pickup_C_1c;
	extern RGBA	BP_QT_UZI_Pickup_C_1c;
	extern RGBA	BP_QT_A_Pickup_C_1c;
	extern RGBA	BP_QT_Sniper_Pickup_C_1c;
	extern RGBA	BP_ZDD_Crossbow_Q_Pickup_C_1c;
	extern RGBA	BP_DJ_Mid_E_Pickup_C_1c;
	extern RGBA	BP_DJ_Mid_Q_Pickup_C_1c;
	extern RGBA	BP_DJ_Mid_EQ_Pickup_C_1c;
	extern RGBA	BP_DJ_Sniper_E_Pickup_C_1c;
	extern RGBA	BP_DJ_Sniper_Q_Pickup_C_1c;
	extern RGBA	BP_DJ_Sniper_EQ_Pickup_C_1c;
	extern RGBA	BP_DJ_Large_E_Pickup_C_1c;
	extern RGBA	BP_DJ_Large_Q_Pickup_C_1c;
	extern RGBA	BP_DJ_Large_EQ_Pickup_C_1c;
	extern RGBA	BP_Pistol_P92_Wrapper_C_1c;
	extern RGBA	BP_Pistol_P1911_Wrapper_C_1c;
	extern RGBA	BP_Pistol_R1895_Wrapper_C_1c;
	extern RGBA	BP_Pistol_P18C_Wrapper_C_1c;
	extern RGBA	BP_Pistol_R45_Wrapper_C_1c;
	extern RGBA	BP_Pistol_Vz61_Wrapper_C_1c;
	extern RGBA	BP_Pistol_DesertEagle_Wrapper_C_1c;
	extern RGBA	BP_ShotGun_SawedOff_Wrapper_C_1c;

	extern RGBA BP_ShotGun_S686_Wrapper_C_1c;
	extern RGBA BP_ShotGun_S1897_Wrapper_C_1c;
	extern RGBA BP_ShotGun_S12K_Wrapper_C_1c;
	extern RGBA BP_ShotGun_DP12_Wrapper_C_1c;
	extern RGBA BP_ShotGun_M1014_Wrapper_C_1c;


	extern RGBA	BP_WEP_Machete_Pickup_C_1c;
	extern RGBA	BP_WEP_Cowbar_Pickup_C_1c;
	extern RGBA	BP_WEP_Sickle_Pickup_C_1c;
	extern RGBA	BP_WEP_Pan_Pickup_C_1c;
	extern RGBA BP_Sniper_VSS_Wrapper_C_1c;
	extern RGBA BP_WEP_Mk14_Pickup_C_1c;
	extern RGBA BP_Sniper_Win94_Wrapper_C_1c;
	extern RGBA BP_Sniper_QBU_Wrapper_C_1c;
	extern RGBA BP_Sniper_Mosin_Wrapper_C_1c;
	extern RGBA BP_Sniper_MK12_Wrapper_C_1c;



	extern RGBA M416; //(m16); //{ 1.000f, 0.647f, 0.000f, 1.000f };
	extern RGBA LAKM; //(AKM); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LAWM; //(AWM); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LAWMimmo; //(AWMimmo); //{ 0.942f, 0.300f, 0.073f, L.000f };
	extern RGBA LAirAttack; //(AirAttack); //{ L.000f, 0.000f, 0.000f, L.000f };
	extern RGBA Lscarl; //(scarl); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA Lm762; //(m762); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LM24; //(M24); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LGROZZA; //(GROZZA); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA Lscope8x; //(scope8x); //{ 0.866f, 0.128f, 0.081f, L.000f };
	extern RGBA Lkar98; //(kar98); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LAirdrop; //(Airdrop); //{ 0.279f, 0.990f, 0.812f, L.000f };
	extern RGBA LFlare; //(Flare); //{ 0.866f, 0.128f, 0.081f, L.000f };
	extern RGBA LFlaregun; //(Flaregun); //{ L.0f, 0.60f,0.05f, L.0f };
	extern RGBA Ldp; //(dp); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA Lmg3; //(mg3); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA Lscope4x; //(scope4x); //{ 0.937f, 0.063f, 0.937f, L.000f };
	extern RGBA Lscope3x; //(scope3x); //{ 0.874f, 0.484f, 0.106f, L.000f };
	extern RGBA Lbag; //(bag); //{ 0.529f, 0.127f, 0.903f, L.000f };
	extern RGBA Larmer; //(armer); //{ 0.591f, L.000f, 0.237f, L.000f };
	extern RGBA Lhelmat; //(helmat); //{ 0.726f, 0.070f, 0.908f, L.000f };
	extern RGBA Lmosin; //(mosin); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA Laug; //(aug); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA Lg36; //(g36); //{ 0.671f, 0.217f, L.000f, L.000f };
	extern RGBA Lassm; //(assm); //{ L.000f, 0.217f, 0.762f, L.000f };
	extern RGBA LGrandes; //(Grandes); //{ L.000f, 0.396f, 0.357f, L.000f };
	extern RGBA Lammo7; //(ammo7); //{ 0.984f, 0.871f, 0.043f, L.000f };
	extern RGBA Lammo5; //(ammo5); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA Lmadkit; //(madkit); //{ 0.952f, 0.558f, 0.129f, L.000f };
	extern RGBA Litemcolors;//; //(itemcolors); //{ L.000f, 0.100f, 0.401f, L.000f };
	extern RGBA Lplayerline; //(playerline); //{ 0.591f, L.000f, 0.237f, L.000f };
	extern RGBA Lplayercorner; //(playercorner); //{ L.0f, 0.70f,0.30f, L.0f };
	extern RGBA Lplayerbox; //(playerbox); //{ L.0f, L.0f,0.0f, L.0f };
	extern RGBA Llotbox; //(lotbox); //{ L.0f, L.0f,0.0f, L.0f };
	extern RGBA Lhelthbar; //(helthbar); //{ 0.950f, 0.125f, 0.125f, L.0f };
	extern RGBA LboxColor; //(boxColor); //{ 0.950f, 0.125f, 0.125f, L.0f };
	extern RGBA LcornerColor; //(cornerColor); //{ 0.950f, 0.125f, 0.125f, L.0f };
	extern RGBA LcrosshairColor; //(crosshairColor); //{ 0.950f, 0.125f, 0.125f, L.0f };
	extern RGBA Lbot; //(bot); //{ 0.016f, 0.725f, 0.929f, L.0f };
	extern RGBA Lplayer; //(player); //{ 0.950f, 0.125f, 0.125f, L.0f };
	extern RGBA Lvehicle; //(vehicle); //{ L.000f, L.000f, 0.000f, L.000f };
	extern RGBA Lbotcorner; //(botcorner); //{ 0.050f, 0.125f, 0.925f, L.0f };
	extern RGBA Lbotline; //(botline); //{ 0.050f, 0.025f, 0.925f, L.0f };
	extern RGBA Lcircle; //(circle); //{ 0.950f, 0.125f, 0.125f, L.0f };
	extern RGBA Lenemy; //(enemy); //{ 255, 255, 255, 255 };
	extern RGBA Lbotbox; //(botbox); //{ 0.950f, 0.125f, 0.925f, L.0f };
	extern RGBA Lbone; //(bone); //{ 0.950f, 0.125f, 0.125f, L.0f };
	extern RGBA Lfillrect; //(fillrect); //{ 0.950f, 0.125f, 0.125f, L.0f };
	extern RGBA Lnam; //(nam); //{ L.000f, L.000f, 0.000f, L.000f };
	extern RGBA Lnambar; //(nambar); //{ 0.880f, 0.185f, 0.25f, L.0f };
	extern RGBA Lbothealth; //(bothealth); //{ 0.95f, 0.125f, 0.825f, L.0f };
	extern RGBA Lbotname; //(botname); //{ 0.050f, 0.825f, 0.185f, L.0f };
	extern RGBA Lplayerhealth; //(playerhealth); //{ 0.50f, 0.725f, 0.105f, L.0f };
	extern RGBA Ltextcolor; //(textcolor); //{ 0.500f, 0.150f, 0.125f, L.0f };
	extern RGBA LGranades; //(Granades); //{ 0.990f, 0.995f, 0.995f, L.0f };
	extern RGBA Lhealth; //(health); //{ 0.108f, L.000f, L.000f, L.000f };
	extern RGBA Ldeadbox; //(deadbox); //{ 0.737f, L.000f, 0.000f, L.000f };
	extern RGBA Ldeadboxitem; //(deadboxitem); //{ L.000f, 0.100f, 0.401f, L.000f };
	extern RGBA Lairdrop; //(airdrop); //{ L.000f, 0.695f, 0.323f, L.000f };
	extern RGBA Lairdropitem; //(airdropitem); //{ 0.300f, 0.695f, 0.323f, L.000f };
	extern RGBA Lscopetextcolor; //(scopetextcolor); //{ 0.000f, 0.995f, 0.995f, L.000f };
	extern RGBA Lallitem; //(allitem); //{ 0.034f, L.000f, 0.040f, L.000f };
	extern RGBA Lscope6x; //(scope6x); //{ 0.120f, 0.955f, 0.125f, L.0f };
	extern RGBA Lbotbone; //(botbone); //{ 0.050f, 0.025f, 0.925f, L.0f };
	extern RGBA Lplayerbone; //(playerbone); //{ 0.986f, 0.952f, 0.209f, L.000f };
	extern RGBA Lmagicline; //(magicline); //{ 255, 0, 0, 255 };
	extern RGBA Lbgcorner; //(bgcorner); //{ 0.000f, L.000f, 0.964f, L.000f };
	extern RGBA Lfovcirclecolor; //(fovcirclecolor); //{ 255, 0, 0, 255 };
	extern RGBA Lweapont; //(weapont); //{ 255,255,0,255 };
	extern RGBA Lskelec; //(skelec); //{ 255, 255, 255, 255 };
	extern RGBA Lhpt; //(hpt); //{ 255, 255, 255, 255 };
	extern RGBA Lplancolor; //(plancolor); //{ 0.737f, L.000f, 0.000f, L.000f };
	extern RGBA Ldotss; //(dotss); //{ 0.950f, 0.125f, 0.925f, L.0f };
	extern RGBA LEsp_Item_AKM_Color; //(Esp_Item_AKM_Color); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LM249; //(M249); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LMK12; //(MK12); //{ L.00f, 0.796f, 0.715f, L.0f };
	extern RGBA LEsp_Item_M762_Color; //(Esp_Item_M762_Color); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LEsp_Item_Mk47Mutant_Color; //(Esp_Item_Mk47Mutant_Color); //{ L.00f, 0.76f, 0.15f, L.0f };
	extern RGBA LEsp_Item_DP28_Color; //(Esp_Item_DP28_Color); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LEsp_Item_SCARL_Color; //(Esp_Item_SCARL_Color); //{ 0.00f, L.0f, 0.0f, L.0f };
	extern RGBA LEsp_Item_M416_Color; //(Esp_Item_M416_Color); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LEsp_Item_M16A4_Color; //(Esp_Item_M16A4_Color); //{ 0.00f, L.0f, 0.0f, L.0f };
	extern RGBA LEsp_Item_G36C_Color; //(Esp_Item_G36C_Color); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LEsp_Item_QBZ_Color; //(Esp_Item_QBZ_Color); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LEsp_Item_QBU_Color; //(Esp_Item_QBU_Color); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LEsp_Item_SLR_Color; //(Esp_Item_SLR_Color); //{ 0.627f, 0.102f, 0.941f, L.000f };
	extern RGBA LEsp_Item_SKS_Color; //(Esp_Item_SKS_Color); //{ 0.627f, 0.102f, 0.941f, L.000f };
	extern RGBA LEsp_Item_Mini14_Color; //(Esp_Item_Mini14_Color); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LEsp_Item_M24_Color; //(Esp_Item_M24_Color); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LEsp_Item_Kar98k_Color; //(Esp_Item_Kar98k_Color); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LEsp_Item_PP19_Color; //(Esp_Item_PP19_Color); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LEsp_Item_TommyGun_Color; //(Esp_Item_TommyGun_Color); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LEsp_Item_MP5K_Color; //(Esp_Item_MP5K_Color); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LEsp_Item_UMP9_Color; //(Esp_Item_UMP9_Color); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LEsp_Item_Vector_Color; //(Esp_Item_Vector_Color); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LEsp_Item_Uzi_Color; //(Esp_Item_Uzi_Color); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LEsp_Item_762mm_Color; //(Esp_Item_762mm_Color); //{ 0.984f, 0.871f, 0.043f, L.000f };
	extern RGBA LEsp_Item_556mm_Color; //(Esp_Item_556mm_Color); //{ 0.000f, L.000f, 0.318f, L.000f };
	extern RGBA LEsp_Item_9mm_Color; //(Esp_Item_9mm_Color); //{ L.000f, 0.000f, 0.337f, L.000f };
	extern RGBA LEsp_Item_45ACP_Color; //(Esp_Item_45ACP_Color); //{ L.00f, 0.96f, 0.56f, L.0f };
	extern RGBA LEsp_Item_Holo_Color; //(Esp_Item_Holo_Color); //{ 0.000f, 0.682f, L.000f, L.000f };
	extern RGBA LEsp_Item_x2_Color; //(Esp_Item_x2_Color); //{ 0.000f, 0.682f, L.000f, L.000f };
	extern RGBA LEsp_Item_x3_Color; //(Esp_Item_x3_Color); //{ 0.000f, 0.682f, L.000f, L.000f };
	extern RGBA LEsp_Item_x4_Color; //(Esp_Item_x4_Color); //{ 0.000f, 0.682f, L.000f, L.000f };
	extern RGBA LEsp_Item_x6_Color; //(Esp_Item_x6_Color); //{ L.000f, 0.000f, 0.000f, L.000f };
	extern RGBA LEsp_Item_x8_Color; //(Esp_Item_x8_Color); //{ L.000f, 0.000f, 0.000f, L.000f };
	extern RGBA LEsp_Item_Bag1_Color; //(Esp_Item_Bag1_Color); //{ 0.000f, 0.682f, L.000f, L.000f };
	extern RGBA LEsp_Item_Bag2_Color; //(Esp_Item_Bag2_Color); //{ 0.627f, 0.102f, 0.941f, L.000f };
	extern RGBA LEsp_Item_Bag3_Color; //(Esp_Item_Bag3_Color); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LEsp_Item_Armor1_Color; //(Esp_Item_Armor1_Color); //{ 0.000f, 0.682f, L.000f, L.000f };
	extern RGBA LEsp_Item_Armor2_Color; //(Esp_Item_Armor1_Color); //{ 0.627f, 0.102f, 0.941f, L.000f };
	extern RGBA LEsp_Item_Armor3_Color; //(Esp_Item_Armor3_Color); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LEsp_Item_Helmet1_Color; //(Esp_Item_Helmet1_Color); //{ 0.000f, 0.682f, L.000f, L.000f };
	extern RGBA LEsp_Item_Helmet2_Color; //(Esp_Item_Helmet2_Color); //{ 0.627f, 0.102f, 0.941f, L.000f };
	extern RGBA LEsp_Item_Helmet3_Color; //(Esp_Item_Helmet3_Color); //{ L.000f, 0.647f, 0.000f, L.000f };
	extern RGBA LEsp_Item_Frag_Color; //(Esp_Item_Frag_Color); //{ L.000f, L.000f, 0.000f, L.000f };
	extern RGBA LEsp_Item_Smoke_Color; //(Esp_Item_Smoke_Color); //{ L.000f, L.000f, 0.000f, L.000f };
	extern RGBA LEsp_Item_Molotof_Color; //(Esp_Item_Molotof_Color); //{ L.000f, L.000f, 0.000f, L.000f };
	extern RGBA LEsp_Item_MedKit_Color; //(Esp_Item_MedKit_Color); //{ L.000f, 0.753f, 0.796f, L.000f };
	extern RGBA LEsp_Item_FirstAidKit_Color; //(Esp_Item_FirstAidKit_Color); //{ L.000f, 0.753f, 0.796f, L.000f };
	extern RGBA LEsp_Item_Painkiller_Color; //(Esp_Item_Painkiller_Color); //{ L.000f, 0.753f, 0.796f, L.000f };
	extern RGBA LEsp_Item_EnergyDrink_Color; //(Esp_Item_EnergyDrink_Color); //{ L.000f, 0.753f, 0.796f, L.000f };
	extern RGBA LEsp_Item_AdrenalineSyringe_Color; //(Esp_Item_AdrenalineSyringe_Color); //{ L.000f, 0.753f, 0.796f, L.000f };
	extern RGBA LEsp_Item_FlareGun_Color; //(Esp_Item_FlareGun_Color); //{ L.000f, 0.000f, 0.000f, L.000f };
	extern RGBA LEsp_Item_Flare_Color; //(Esp_Item_Flare_Color); //{ L.000f, 0.000f, 0.000f, L.000f };
	extern RGBA LEsp_Item_AirDrop_Color; //(Esp_Item_AirDrop_Color); //{ L.000f, 0.647f, 0.000f, L.000f };	extern bool MagicX;








	//-------------------------ATTICHMENT------------


	extern bool BP_QK_Choke_Pickup_C_1;
	extern bool icons;
	extern bool token;
	extern bool BP_QK_Mid_Compensator_Pickup_C_1;
	extern bool BP_QK_Sniper_Compensator_Pickup_C_1;
	extern bool BP_QK_Mid_FlashHider_Pickup_C_1;
	extern bool BP_QK_Sniper_FlashHider_Pickup_C_1;
	extern bool BP_QK_Mid_Suppressor_Pickup_C_1;
	extern bool BP_QK_Sniper_Suppressor_Pickup_C_1;
	extern bool BP_QK_Large_Compensator_Pickup_C_1;
	extern bool BP_QK_Large_FlashHider_Pickup_C_1;
	extern bool BP_QK_Large_Suppressor_Pickup_C_1;
	extern bool BP_QK_DuckBill_Pickup_C_1;
	extern bool BP_WB_Angled_Pickup_C_1;
	extern bool BP_WB_Vertical_Pickup_C_1;
	extern bool BP_WB_LightGrip_Pickup_C_1;
	extern bool BP_WB_HalfGrip_Pickup_C_1;
	extern bool BP_WB_ThumbGrip_Pickup_C_1;
	extern bool BP_WB_Lasersight_Pickup_C_1;
	extern bool BP_MZJ_HD_Pickup_C_1;
	extern bool BP_MZJ_QX_Pickup_C_1;
	extern bool BP_MZJ_SideRMR_Pickup_C_1;
	extern bool BP_ZDD_Sniper_Pickup_C_1;
	extern bool BP_QT_UZI_Pickup_C_1;
	extern bool BP_QT_A_Pickup_C_1;
	extern bool BP_QT_Sniper_Pickup_C_1;
	extern bool BP_ZDD_Crossbow_Q_Pickup_C_1;
	extern bool BP_DJ_Mid_E_Pickup_C_1;
	extern bool BP_DJ_Mid_Q_Pickup_C_1;
	extern bool BP_DJ_Mid_EQ_Pickup_C_1;
	extern bool BP_DJ_Sniper_E_Pickup_C_1;
	extern bool BP_DJ_Sniper_Q_Pickup_C_1;
	extern bool BP_DJ_Sniper_EQ_Pickup_C_1;
	extern bool BP_DJ_Large_E_Pickup_C_1;
	extern bool BP_DJ_Large_Q_Pickup_C_1;
	extern bool BP_DJ_Large_EQ_Pickup_C_1;

	//---------------PISTOLS------------

	extern bool BP_Pistol_P92_Wrapper_C_1;
	extern bool	BP_Pistol_P1911_Wrapper_C_1;
	extern bool	BP_Pistol_R1895_Wrapper_C_1;
	extern bool	BP_Pistol_P18C_Wrapper_C_1;
	extern bool	BP_Pistol_R45_Wrapper_C_1;
	extern bool	BP_Pistol_Vz61_Wrapper_C_1;
	extern bool	BP_Pistol_DesertEagle_Wrapper_C_1;
	extern bool	BP_ShotGun_SawedOff_Wrapper_C_1;
	/////////////////////////////////////
	extern bool BP_WEP_Machete_Pickup_C_1;
	extern bool BP_WEP_Cowbar_Pickup_C_1;
	extern bool BP_WEP_Sickle_Pickup_C_1;
	extern bool BP_WEP_Pan_Pickup_C_1;
	//-------------------------------
	extern bool sEsp_Item_762mm;
	extern bool sEsp_Item_556mm;
	extern bool sEsp_Item_9mm;
	extern bool sEsp_Item_45ACP;
	extern bool sEsp_Item_12Guagemm;
	extern bool sEsp_Item_Awmimo;

	//////////////////////////////
	extern bool BP_ShotGun_S686_Wrapper_C_1;
	extern bool BP_ShotGun_S1897_Wrapper_C_1;
	extern bool BP_ShotGun_S12K_Wrapper_C_1;
	extern bool BP_ShotGun_DP12_Wrapper_C_1;
	extern bool BP_ShotGun_M1014_Wrapper_C_1;
	/////////////////////////////////////

	extern bool BP_Sniper_VSS_Wrapper_C_1;
	extern bool BP_WEP_Mk14_Pickup_C_1;
	extern bool BP_Sniper_Win94_Wrapper_C_1;
	extern bool BP_Sniper_QBU_Wrapper_C_1;
	extern bool BP_Sniper_Mosin_Wrapper_C_1;
	extern bool BP_Sniper_MK12_Wrapper_C_1;


	/////////////////////////////
	extern ImVec4 colorcode;
	extern bool Magntic;
	extern int	curraim;
	extern int autocurraim;
	extern bool	engine;
	extern bool	skele;
	extern bool watermark;
	extern bool MAgicline;
	extern char filename[];
	extern float Normalfontsize;
	extern float fontsize;
	extern float plinesize;
	extern float pfullboxsize;
	extern float pcornersize;
	extern float pbonesize;

	extern float blinesize;
	extern float bfullboxsize;
	extern float bcornersize;
	extern float bbonesize;
	extern bool silent;
	extern bool bortext;
	extern bool pcorner;
	extern bool plyrdistance;
	extern bool botdistance;
	extern bool botweapon;
	extern bool playerweapon;

	extern float PlayerMAxDistance;
	extern float VehicalMexDistance;
	extern float ItemMaxDistance;
	extern int UpdateThreadDelay;
	extern int AdreessGetterDelay;
	extern int EspThreadDelay;
	extern int dotsize;
	extern bool style1;
	extern bool style2;
	extern bool ShowMenu;
	extern bool ShowSideMenu;
	extern bool AntiScreenShot;
	extern bool CRPTPressed;
	extern bool profree;
	extern	bool botname, bothealth, botline, botfullbox, botblood, botcorner;
	//playr
	extern	bool pline, phealth, pfullbox, pname, pblood, plyrbox, plyrwep, boxitems;
	extern bool fightmode;
	extern bool Name;
	extern bool Distance;
	extern bool Distancee;
	extern bool TotalEnemy;
	extern bool Line;
	extern bool Box;
	extern bool botBone;
	extern bool playerBone;
	extern bool  Bone;
	extern bool Health;
	extern bool BombAlert;
	extern bool Item;
	extern bool PlayerESP;
	extern bool Vehicle;
	extern bool UselessShow;
	extern bool hp;
	extern bool feul;

	extern bool impitems;
	extern bool granedwarn;
	extern bool healthitem;
	extern bool scope;
	extern bool allitemss;

	extern bool instanthit;
	extern bool XEffect;
	extern bool XEffectRandomBody;
	extern bool XEffectRandomHead;
	extern bool fastrun;
	extern bool ScopeZoom;
	extern bool FastWeponSwith;
	extern bool fastShoot;
	extern bool ShowDaamge;
	extern bool GodView;
	extern bool IpadView;
	extern bool fly;
	extern bool carfly;
	extern bool speedcar;
	extern bool recoil;
	extern bool ForceTPP;
	extern bool deadboxloot;

	extern bool airdrop;
	extern bool airdropitem;
	extern bool deadbox;
	extern bool playerdeadbox;
	extern bool itemrect;
	extern bool Bags;
	extern bool Helmat;
	extern bool Armer;

	extern	bool Esp_Item_M249;

	extern	bool Esp_Item_Mk12;

	extern bool MagicX;
	extern bool plan;
	extern ImVec4 plancolor;
	extern ImVec4 dotss;
	extern bool vahicle_item;
	extern bool Esp_Item_AKM_Icon;
	extern bool Esp_Item_AKM;
	extern float Esp_Item_AKM_Color[4];
	extern float Esp_Item_AKM_TextSize;


		extern float fovcirclecolor[4];
	extern bool Esp_Item_M762_Icon;
	extern bool Esp_Item_M762;
	extern bool Esp_Item_HoneyBadger;
	extern float Esp_Item_M762_Color[4];
	extern float Esp_Item_M762_TextSize;

	extern bool Esp_Item_FAMAS;
	extern float Esp_Item_FAMAS_Color[4];
	extern float Esp_Item_FAMAS_TextSize;

	extern bool Esp_Item_Mk47Mutant;
	extern float Esp_Item_Mk47Mutant_Color[4];
	extern float Esp_Item_Mk47Mutant_TextSize;

	extern bool Esp_Item_DP28;
	extern float Esp_Item_DP28_Color[4];
	extern float Esp_Item_DP28_TextSize;

	extern bool Esp_Item_SCARL;
	extern float Esp_Item_SCARL_Color[4];
	extern float Esp_Item_SCARL_TextSize;

	extern bool Esp_Item_M416_Icon;
	extern bool Esp_Item_M416;
	extern float Esp_Item_M416_Color[4];
	extern float Esp_Item_M416_TextSize;

	extern bool Esp_Item_M16A4;
	extern float Esp_Item_M16A4_Color[4];
	extern float Esp_Item_M16A4_TextSize;

	extern bool Esp_Item_G36C;
	extern float Esp_Item_G36C_Color[4];
	extern float Esp_Item_G36C_TextSize;

	extern bool Esp_Item_Mk14;
	extern float Esp_Item_Mk14_Color[4];
	extern float Esp_Item_Mk14_TextSize;

	extern bool Esp_Item_QBZ;
	extern float Esp_Item_QBZ_Color[4];
	extern float Esp_Item_QBZ_TextSize;

	extern bool Esp_Item_QBU;
	extern float Esp_Item_QBU_Color[4];
	extern float Esp_Item_QBU_TextSize;

	extern bool Esp_Item_SLR;
	extern float Esp_Item_SLR_Color[4];
	extern float Esp_Item_SLR_TextSize;

	extern bool Esp_Item_SniperAMR;
	extern float Esp_Item_SniperAMR_Color[4];
	extern float Esp_Item_SniperAMR_TextSize;

	extern bool Esp_Item_BulletAMR;
	extern float Esp_Item_BulletAMR_Color[4];
	extern float Esp_Item_BulletAMR_TextSize;


	extern bool Esp_Item_SKS;
	extern float Esp_Item_SKS_Color[4];
	extern float Esp_Item_SKS_TextSize;

	extern bool Esp_Item_Mini14;
	extern float Esp_Item_Mini14_Color[4];
	extern float Esp_Item_Mini14_TextSize;

	extern bool Esp_Item_M24_Icon;
	extern bool Esp_Item_M24;
	extern float Esp_Item_M24_Color[4];
	extern float Esp_Item_M24_TextSize;
	extern bool Esp_Item_Awm;
	extern bool Esp_Item_Awmimo;
	extern bool Esp_Item_Kar98k;
	extern float Esp_Item_Kar98k_Color[4];
	extern float Esp_Item_Kar98k_TextSize;

	extern bool Esp_Item_PP19;
	extern float Esp_Item_PP19_Color[4];
	extern float Esp_Item_PP19_TextSize;

	extern bool Esp_Item_TommyGun;
	extern float Esp_Item_TommyGun_Color[4];
	extern float Esp_Item_TommyGun_TextSize;

	extern bool Esp_Item_MP5K;
	extern float Esp_Item_MP5K_Color[4];
	extern float Esp_Item_MP5K_TextSize;

	extern bool Esp_Item_UMP9;
	extern float Esp_Item_UMP9_Color[4];
	extern float Esp_Item_UMP9_TextSize;

	extern bool Esp_Item_Vector;
	extern float Esp_Item_Vector_Color[4];
	extern float Esp_Item_Vector_TextSize;

	extern bool Esp_Item_Uzi;
	extern float Esp_Item_Uzi_Color[4];
	extern float Esp_Item_Uzi_TextSize;

	extern bool Esp_Item_762mm;
	extern float Esp_Item_762mm_Color[4];
	extern float Esp_Item_762mm_TextSize;

	extern bool Esp_Item_556mm;
	extern float Esp_Item_556mm_Color[4];
	extern float Esp_Item_556mm_TextSize;

	extern bool Esp_Item_9mm;
	extern float Esp_Item_9mm_Color[4];
	extern float Esp_Item_9mm_TextSize;

	extern bool Esp_Item_45ACP;
	extern float Esp_Item_45ACP_Color[4];
	extern float Esp_Item_45ACP_TextSize;

	extern bool Esp_Item_Holo;
	extern float Esp_Item_Holo_Color[4];
	extern float Esp_Item_Holo_TextSize;

	extern bool Esp_Item_x2;
	extern float Esp_Item_x2_Color[4];
	extern float CrossHairColor[4];
	extern float XeffectColor[4];
	extern float XeffectColorHead[4];
	extern float Esp_Item_x2_TextSize;

	extern bool Esp_Item_x3;
	extern float Esp_Item_x3_Color[4];
	extern float Esp_Item_x3_TextSize;

	extern bool Esp_Item_x4;
	extern float Esp_Item_x4_Color[4];
	extern float Esp_Item_x4_TextSize;

	extern bool Esp_Item_x6;
	extern float Esp_Item_x6_Color[4];
	extern float Esp_Item_x6_TextSize;

	extern bool Esp_Item_x8;
	extern float Esp_Item_x8_Color[4];
	extern float Esp_Item_x8_TextSize;

	extern bool Esp_Item_Bag1;
	extern float Esp_Item_Bag1_Color[4];
	extern float Esp_Item_Bag1_TextSize;

	extern bool Esp_Item_Bag2;
	extern float Esp_Item_Bag2_Color[4];
	extern float Esp_Item_Bag2_TextSize;

	extern bool Esp_Item_Bag3;
	extern float Esp_Item_Bag3_Color[4];
	extern float Esp_Item_Bag3_TextSize;

	extern bool Esp_Item_Armor1;
	extern float Esp_Item_Armor1_Color[4];
	extern float Esp_Item_Armor1_TextSize;

	extern bool Esp_Item_Armor2;
	extern float Esp_Item_Armor2_Color[4];
	extern float Esp_Item_Armor2_TextSize;

	extern bool Esp_Item_Armor3;
	extern float Esp_Item_Armor3_Color[4];
	extern float Esp_Item_Armor3_TextSize;

	extern bool Esp_Item_Helmet1;
	extern float Esp_Item_Helmet1_Color[4];
	extern float Esp_Item_Helmet1_TextSize;

	extern bool Esp_Item_Helmet2;
	extern float Esp_Item_Helmet2_Color[4];
	extern float Esp_Item_Helmet2_TextSize;

	extern bool Esp_Item_Helmet3;
	extern float Esp_Item_Helmet3_Color[4];
	extern float Esp_Item_Helmet3_TextSize;

	extern bool Esp_Item_Frag;
	extern float Esp_Item_Frag_Color[4];
	extern float Esp_Item_Frag_TextSize;

	extern bool Esp_Item_Smoke;
	extern float Esp_Item_Smoke_Color[4];
	extern float Esp_Item_Smoke_TextSize;

	extern bool Esp_Item_Molotof;
	extern float Esp_Item_Molotof_Color[4];
	extern float Esp_Item_Molotof_TextSize;

	extern bool Esp_Item_MedKit;
	extern float Esp_Item_MedKit_Color[4];
	extern float Esp_Item_MedKit_TextSize;

	extern bool Esp_Item_FirstAidKit;
	extern float Esp_Item_FirstAidKit_Color[4];
	extern float Esp_Item_FirstAidKit_TextSize;

	extern bool Esp_Item_Painkiller;
	extern float Esp_Item_Painkiller_Color[4];
	extern float Esp_Item_Painkiller_TextSize;

	extern bool Esp_Item_Bandage;
	extern float Esp_Item_Bandage_Color[4];
	extern float Esp_Item_Bandage_TextSize;




	extern bool Esp_Item_EnergyDrink;
	extern float Esp_Item_EnergyDrink_Color[4];
	extern float Esp_Item_EnergyDrink_TextSize;

	extern bool Esp_Item_AdrenalineSyringe;
	extern float Esp_Item_AdrenalineSyringe_Color[4];
	extern float Esp_Item_AdrenalineSyringe_TextSize;

	extern bool Esp_Item_FlareGun_Icon;
	extern bool Esp_Item_FlareGun;
	extern float Esp_Item_FlareGun_Color[4];
	extern float Esp_Item_FlareGun_TextSize;

	extern bool Esp_Item_Flare;
	extern float Esp_Item_Flare_Color[4];
	extern float Esp_Item_Flare_TextSize;

	extern bool Esp_Item_AirDrop;
	extern float Esp_Item_AirDrop_Color[4];
	extern float Esp_Item_AirDrop_TextSize;

	extern bool Esp_Item_exquic;
	extern float Esp_Item_exquic_Color[4];
	extern float Esp_Item_exquic_TextSize;

	extern bool Aimbot;

	extern bool MagicBullet;
	extern bool MagicBulletticked;
	extern bool MagicBulletd;

	extern bool borderlo;
	extern bool FlyMan;

	extern bool CameraCatch;
	extern bool CameraAimBot;
	extern bool camsmooth;

	extern bool grw;
	extern bool sm;
	extern bool molow;
	//extern float hpt;
	extern int	magicv;
	extern int	magicvy;
	extern int	flycarv;
	extern int	ttpview;
	extern int	instantv;
	extern int	carsv;
	extern int	corsshairvalue;
	extern int	scopefov;
	extern int	GodVieAndhle;
	extern int	camsmoothness;
	extern int	IpadViewValue;
	extern int	fastrv;
	extern int	FlyManHeight;
	extern int	shootinterval;
	extern bool magicb;
	extern int magicrange;
}