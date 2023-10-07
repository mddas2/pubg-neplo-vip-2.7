#pragma once

#include "Includes.h"
#include "Utility.h"
#include "Setting.h"
#include "Algorithm.h"
#include "Offset.h"
#include "Global.h"
struct ActorsEncryption {
	uint32_t Enc_1;
	uint32_t Enc_2;
	uint32_t Enc_3;
	uint32_t Enc_4;
};
struct AActor
{
	bool IsBot;
	bool IsDead;
	bool isAimingAtMe;
	VECTOR3 Position;
	FLOAT Health;
	FLOAT KnockedHealth;
	//FLOAT ScopeFov;
	FLOAT HealthMax;
	string Name;
	string Nation;
	string Weapon;
	string ScopeFov;
	INT Ammo;
	INT AmmoMax;
	INT TeamId;
	string UID;
	DWORD Address;
	VECTOR3 Velocity;
	FRotator RelativeRotation;
	VECTOR3 RelativeLocation;

	VECTOR3 HeadPos;
	VECTOR3 ChestPos;
	VECTOR3 PelvisPos;
	VECTOR3 lSholderPos;
	VECTOR3 rSholderPos;
	VECTOR3 lElbowPos;
	VECTOR3 rElbowPos;
	VECTOR3 lWristPos;
	VECTOR3 rWristPos;
	VECTOR3 lThighPos;
	VECTOR3 rThighPos;
	VECTOR3 lKneePos;
	VECTOR3 rKneePos;
	VECTOR3 lAnklePos;
	VECTOR3 rAnklePos;
};

struct BombAlert
{
	int timeLeft;
	string Name;
	VECTOR3 Position;
	DWORD Address;
};

struct Item
{
	string Name;
	VECTOR3 Position;
};
struct impItem
{
	string Name;
	VECTOR3 Position;
};
struct Vehicle
{
	float oil;
	float hppercet;
	float hp;
	string Name;
	VECTOR3 Position;
	DWORD Address;
	bool driving;
};

struct Itemb {
	std::string Displayname;
	ImVec4 colorcod;

};
struct Airdrop
{
	std::string Displayname;
	string Name;
	VECTOR3 Position;
	std::vector<Item> boxitemm;
};
struct Deadbox
{
	bool isAirDrop;
	bool IsDeadBox;
	bool IsTreasureBox;
	int picid;
	std::vector<Itemb> boxitem;
	string Name;
	VECTOR3 Position;
};


class Espp {
public:
	std::vector<Airdrop> LootData, LootDatadatar;

	Airdrop lboxx, temploot;
	std::string airdropstring;
	std::vector<Deadbox> lootbox, lootboxr;


	Deadbox lbox;
};
extern Espp* g_pEsp;
namespace Data
{
	extern DWORD ViewMatrixBase;
	extern DWORD Ue4base;
	extern AActor TargetActor;
	extern DWORD UWorld;
	extern DWORD GName;
	extern DWORD NetDriver;
	extern DWORD GameState;
	extern DWORD GameMode;
	extern string GameType;
	extern int ElapsedTime;
	extern int NoneAIGameTime;
	extern int PlayerNumPerTeam;
	extern DWORD TimeRemind;
	extern int PlayerAddonCount;
	extern int PlayerNumGameState;
	extern int AlivePlayerNum;
	extern int AliveTeamNum;
	extern int GameModeID;
	extern int CurCircleWave;
	extern DWORD LocalPlayer;
	extern DWORD LocalPlayerAddr;
	extern DWORD LocalController;
	extern DWORD CurrentReloadWeapon;
	extern DWORD ShootWeaponEntity;
	extern DWORD PlayerController;
	extern DWORD PlayerCameraManager;
	extern CameraCacheEntry CameraCache;
	extern DWORD EntityAddress;
	extern VECTOR3 AimingCoordinates;
	extern VECTOR3 lOCALPLAYERHEAD;
	extern VECTOR3 lOCALPLAYERPosotion;
	extern FRotator lOCALPLAYERRotation;

	extern vector<AActor> AActorList;
	extern vector<AActor> AimingAtMePlayersList;
	extern vector<AActor>ABotList;
	extern vector<BombAlert> BombAlertList;
	extern vector<Item> ItemList;
	extern vector<Vehicle> VehicleList;
	extern vector<Deadbox> BoxesList;
	extern vector<impItem> impItemList;


	DWORD GetViewMatrixBase(DWORD StartAddress, DWORD EndAddress);
	DWORD GetUe4Base(DWORD StartAddress, DWORD EndAddress);

	VOID QueryThread();
	VOID ItemPicker();
	VOID KeyHandler();
};

