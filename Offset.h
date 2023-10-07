#pragma once

#include "Includes.h"

namespace Offset
{

	//https://raw.githubusercontent.com/FiZZ-Op/SDK-PUBGM-BGMI/2.8-PUBGM/PUBG_SDK_2.8.txt

	const DWORD GWorld = 0x7B28F74 + 0x3C;// 0x759F77C;
	const DWORD GName = 0x7827A58 + 0x88;//0x06F5AB00 + 0x14;//IF NOT 0742D880
	const DWORD IPADVIEWOFFSET = 0x3CB57A4;//0x06F5AB00 + 0x14;//IF NOT 0742D880
	const DWORD GameState = 0x13c;//0x138;
	const DWORD ElapsedTime = 0x348; //GameState.GameStateBase.Info.Actor.Object
	const DWORD NoneAIGameTime = 0x7fc;
	const DWORD AlivePlayerNum = 0x7f4;//0x7e4;//[Offset: 0x79c, Size: 4]
	const DWORD PlayerNum = 0x554;//0x548;//[Offset: 0x79c, Size: 4]
	const DWORD AliveTeamNum = 0x7f8;//0x7e8;//[Offset: 0x7a0, Size: 4]
	const DWORD bNoAliveHumanPlayer = 0x738;//[Offset: 0x7a0, Size: 4]
	const DWORD PlayerNumPerTeam = 0x108c;//0xaa0;//[Offset: 0x7a0, Size: 4]
	const DWORD PlayerAddonCount = 0xe3c;//[Offset: 0x7a0, Size: 4]
	const DWORD CircleLessenTo = 0x76c;//[Offset: 0x7a0, Size: 4]
	const DWORD BlueCircle = 0x478;//[Offset: 0x7a0, Size: 4]
	const DWORD WhiteCircle = 0x484;//[Offset: 0x7a0, Size: 4]
	const DWORD AirAttackArea = 0x498;//[Offset: 0x7a0, Size: 4]
	const DWORD GameModeID = 0xbf8;//[Offset: 0x7a0, Size: 4]
	const DWORD CurCircleWave = 0x734;//[Offset: 0x7a0, Size: 4]
	const DWORD CirclePain = 0x490;//[Offset: 0x7a0, Size: 4]
	const DWORD MarkMgr = 0xe58;//[Offset: 0x7a0, Size: 4]
	const DWORD bIsTrainingMode = 0x439;//[Offset: 0x7a0, Size: 4]
	const DWORD bIsOutsideBlueCircle = 0x7a4;//[Offset: 0x7a0, Size: 4]
	const DWORD GameReplayType = 0x700;//[Offset: 0x7a0, Size: 4]

	const DWORD PersistentLevel = 0x20;

	const DWORD NetDriver = 0x24;
	const DWORD ServerConnection = 0x60;
	const DWORD PlayerController = 0x20;//10292;
	const DWORD AcknowledgedPawn = 0x360;//0x330;
	const DWORD STExtraBaseCharacter = 0x1c64;//0x1c74;//0x1c28;//my team ids //STExtraBaseCharacter* STExtraBaseCharacter
	const DWORD EncryptedActors_Offset = 0x334;
	const DWORD EntityList = 0x70; //m
	const DWORD EntityCount = EntityList + 4; //m

	const DWORD RootComponent = 0x150; //324;
	const DWORD CurrentStates = 0xb48;//0xb20 for 2.7;//0xb18;

	// AActor/////////CharacterMovementComponent* CharacterMovement;//[Offset: 0x31c, Size: 4]
	const DWORD TeamId = 0x6b4;//1648;Class: UAECharacter.Character.Pawn.Actor.Object
	const DWORD PlayerUID = 0x69c;//1648;
	const DWORD PoseState = 0x1034;//0x100c;//0xea0;
	const DWORD IsBot = 0x74d;//0x734;//0x9A9; //bool bIsAI
	const DWORD IsDead = 0x9f4;//0x9c4;///STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object   , bDead  //m
	const DWORD Name = 0x680;//1608;
	const DWORD Nation = 0x68c;//1608;
	const DWORD Health = 0xa04;// 0x9dc;//0x9d0;				// float Health;//[Offset:
	const DWORD HealthMax = 0xa08;// 0x9e0;//0x9d4;
	const DWORD NearDeathBreath = 0x1234;
	const DWORD NearDeatchComponent = 0x1200;
	const DWORD BreathMax = 0x104;

	const DWORD CharacterMovement = 0x350;//0x334;//796;
	const DWORD ControlRotation = 0x324;//0x308;//796; Class: Controller.Actor.Object
	const DWORD LastUpdateVelocity = 0x250;//592;
	const DWORD  ReplicatedMovement = 0x78;         /////////////messing 2.0
	const DWORD Velocity = 0xc8;//0xd4;
	const DWORD ComponentVelocity = 0x1a0;// Vector ComponentVelocity;//[Offset: 0x1a0, Size: 12]
	const DWORD  CurrentVehicle = 0x3c4;// 0x3c4;  0x3c4; //Class: VehicleContainer.LuaActor.Actor.Object

	const DWORD RelativeLocation = 0x118; //352; player location
	const DWORD RelativeRotation = 0x124;//0x124;
	const DWORD Position = 0x150;
	const DWORD IsVisible = 0x1bc;///SceneComponent.ActorComponent.Object , bVisible

	// Bone
	const DWORD Mesh = 0x34c;//1496; SkeletalMeshComponent* Mesh
	const DWORD BodyAddv = 0x140;
	const DWORD MinLOD = 0x63c;//792; StaticMeshComponent.MeshComponent.PrimitiveComponent.SceneComponent.ActorComponent.Object

	// Camera
	const DWORD PlayerCameraManager = 0x370;//0x340; Class: PlayerController.Controller.Actor.Object
	const DWORD CameraCache = 0x370;//0x350;
	const DWORD POV = 0x10;
	const DWORD Location = 0x0;
	const DWORD Rotation = 0x18;
	const DWORD FOV = 0x24;

	const DWORD ThirdPersonCameraComponent = 0x13dc;//0x13a4; // CameraComponent* ThirdPersonCameraComponent;//[Offset: 0x132c, Size: 4]
	const DWORD ScopeCameraComp = 0x13b4; //CameraComponent* ScopeCameraComp;//[Offset: 0x133c, Size: 4]
	//WeaponGuObjectArray
	const DWORD CurrentReloadWeapon = 0x2178;// 0x212c;  //
	const DWORD CurrentWeapon = 0x1D5C;// 0x1d18;  //0x1D5C
	const DWORD ShootWeaponComponent = 0xb18; // STExtraShootWeaponComponent* ShootWeaponComponent;//[Offset: 0xb18, Size: 4]
	const DWORD OwnerShootWeapon = 0x194; // Class: STExtraShootWeaponComponent.WeaponLogicBaseComponent.ActorComponent.Object ->STExtraShootWeapon* OwnerShootWeapon;//[Offset: 0x194, Size: 4]
	const DWORD CurBulletNumInClip = 0xb2c;
	const DWORD CurMaxBulletNumInOneClip = 0xb40;


	const DWORD ShootWeaponEntity = 0xc40;
	const DWORD ShootWeaponEffectComp = 0xbb4;

	//No Shake need  update md
	const DWORD CameraShakeInnerRadius = 0x198;
	const DWORD CameraShakeOuterRadius = 0x19c;
	const DWORD  CameraShakFalloff = 0x1a0;
	const DWORD  bDrawDebug = 0x348;
	const DWORD  CharacterOverrideAttrs = 0x2220;

	////msing///////

	// Instant hit
	const DWORD BulletFireSpeed = 0x408;
	const DWORD BulletMomentum = 0x518;
	const DWORD DamageImpulse = 0x684;
	const DWORD MaxDamageRate = 0x534;
	const DWORD RangeModifier = 0x5d0;
	const DWORD DropDuration = 0x6dc;
	const DWORD BulletRange = 0x51c;
	const DWORD BaseImpactDamage = 0x510;
	const DWORD VehicleDamageScale = 0x514;
	const DWORD ExtraHitPerformScale = 0x964;
	const DWORD  LaunchGravityScale = 0x340;
	//Rapid Fire
	const DWORD ShootInterval = 0x428;
	const DWORD bHasSingleFireMode = 0x474;
	const DWORD bHasAutoFireMode = 0x475;//	bool bHasSingleFireMode;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x474, Size: 1] 	
	const DWORD  BulletNumSingleShot = 0x49c;//bool bHasAutoFireMode;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x475, Size: 1]
	const DWORD  bHasBurstFireMode = 0x476;//bool bHasAutoFireMode;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x475, Size: 1]
	const DWORD  BurstShootInterval = 0x494; //bool bHasBurstFireMode;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x476, Size: 1]
	const DWORD ExtraShootInterval = 0x430;
	const DWORD ReloadRate = 0x6b8;
	const DWORD CrossHairBurstSpeed = 0x8c8;
	const DWORD CrossHairBurstIncreaseSpeed = 0x8cc;

	///Smal Cross Hair
	const DWORD CrossHairInitialSize = 0x8c4;
	const DWORD WeaponOverrideAttrs = 0x2208;

	// NoRecoil
	const DWORD AccessoriesVRecoilFactor = 0x858;
	const DWORD AccessoriesHRecoilFactor = 0x85c;
	const DWORD AccessoriesRecoveryFactor = 0x860;
	const DWORD ShotGunCenterPerc = 0x8a8;
	const DWORD ShotGunVerticalSpread = 0x8ac;
	const DWORD  ShotGunHorizontalSpread = 0x8b0;
	const DWORD  GameDeviationFactor = 0x8b4;
	const DWORD   GameDeviationAccuracy = 0x8b8;
	const DWORD   AccessoriesDeviationFactor = 0x8bc;
	const DWORD   VehicleWeaponDeviationAngle = 0x8d0;
	const DWORD   RecoilKickADS = 0x960;
	const DWORD   TraceDistance = 0x584;
	//Vehicle

	const DWORD VehicleCommon = 0x77c;//0x75c;
	const DWORD lastForwardSpeed = 0x7e8;
	// Class: VehicleCommonComponent.VehicleComponent.ActorComponent.Object
	class VehicleCommonComponent
	{
	public:
		unsigned char Padding00[0x1e0];
		float HPMax;//[Offset: 0x1a4, Size: 4]
		float HP;//[Offset: 0x1a8, Size: 4] //0X1AC

		unsigned char Padding01[0x10];
		float FuelMax;//[Offset: 0x1bc, Size: 4]
		float Fuel;//[Offset: 0x1c0, Size: 4]
		float DelayDestroySeconds;//[Offset: 0x1c4, Size: 4]
		float FuelConsumeFactor;//[Offset: 0x1c8, Size: 4]
	};

	const DWORD HP = 0x1e4;
	const DWORD IsEngineStarted = 0x719; //m

	const  DWORD HPMax = 0x1e0;					//Class: VehicleCommonComponent.VehicleComponent.LuaActorComponent.ActorComponent.Object
	const  DWORD FuelMax = 0x23c;//0x200;//0x1fc;				// Class: VehicleCommonComponent.VehicleComponent.ActorComponent.Object -> float FuelMax;//[Offset: 0x130,
	const  DWORD Fuel = 0x240;//0x200;


	const  DWORD VehicleMovement = 0x1078;  //STExtraVehicleMovementComponent4W* VehicleMovement;//[Offset: 0x1078, Size: 4]
	//loot box
	const DWORD PickUpDataList = 0x680;
	const DWORD boxItemsCount = 0x69c;


	namespace STExtraPlayerCharacter {
		constexpr auto STPlayerController = 0x2d2c;
	}
	namespace PlayerController1 {
		constexpr auto PlayerCameraManager = 0x370;
		constexpr auto MyHUD = 0x34c;

	}
	const DWORD HitPerform = 0x3f4;

	namespace PlayerCameraManager1 {
		constexpr auto CameraCache = 0x360;
	}

	//From Local  Player
	const DWORD CharacterMovementComponent = 0x334;//	CharacterMovementComponent* CharacterMovement;//[Offset: 0x344, Size: 4]  
	const DWORD  MoveAntiCheatComponent = 0xf70;//float SpeedValue;//[Offset: 0xb58, Size: 4]
	const DWORD  ParachuteComponent = 0xf80;//float SpeedValue;//[Offset: 0xb58, Size: 4]

	const DWORD bShouldDrowningHurt = 0x1ae0;//bool (ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x1a40, Size: 1]
	const DWORD HealthPredict = 0x1ad8;
	const DWORD MaxCrouchSpeed = 0x1ac4;
	const DWORD MaxProneSpeed = 0x1ac8;
	const DWORD MaxSprintSpeed = 0x1acc;
	const DWORD MaxSprintCrouchSpeed = 0x1ad0;
	const DWORD MaxSwimSpeed = 0x1ad4;
	const DWORD SpeedDynamicScale = 0x1af4;
	const DWORD SpeedRate = 0x1b4c;
	const DWORD BreathAmount = 0x1adc;
	const DWORD HighWalkSpeed = 0x1ab8;
	const DWORD WalkSpeedChangeRate = 0x1abc;
	const DWORD  DefaultSpeedValue = 0x1b58;
	const DWORD  EnergySpeedScale = 0x1b50;
	const DWORD  RecoveryScale = 0x1b54;
	const DWORD  SwimUpRate = 0x161c;//float SwimUpRate;//[Offset: 0x1584, Size: 4]
	const DWORD  SpeedScale = 0xbac;//float SpeedScale;//[Offset: 0xb54, Size: 4]
	const DWORD  SpeedValue = 0xbb0;//float SpeedValue;//[Offset: 0xb58, Size: 4]
	const DWORD  SwimSpeedDynamicScale = 0x9dc;//float SpeedValue;//[Offset: 0xb58, Size: 4]


	const DWORD  StandHalfHeight = 0x1bd8;//float SpeedValue;//[Offset: 0xb58, Size: 4]
	const DWORD  CrouchHalfHeight = 0x1bdc;//float SpeedValue;//[Offset: 0xb58, Size: 4]
	const DWORD  ProneHalfHeight = 0x1be0;//float SpeedValue;//[Offset: 0xb58, Size: 4]
	const DWORD  StandRadius = 0x1be8;//float SpeedValue;//[Offset: 0xb58, Size: 4]

	const DWORD  HearRadius = 0x11b8;//float HearRadius;//[Offset: 0x117c, Size: 4]
	const DWORD  PickUpRadius = 0x13b8;//	float PickUpRadius;//[Offset: 0x1348, Size: 4]

	//Force TPP
	const DWORD  bIsFPPOnVehicle = 0xf20;// = 0x1a24;	bool bIsFPPOnVehicle;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0xeb0, Size: 1]
	const DWORD  IsNetFPP = 0x1480;// = 0x1a24;	bool IsNetFPP;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x13f0, Size: 1]
	const DWORD  IsFPP = 0x1481;// = 0x1a24;bool IsFPP;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x13f1, Size: 1]
	const DWORD  ScopeFov = 0x130c;// = 0x1a24;bool IsFPP;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x13f1, Size: 1]
	const DWORD  IsGameModeFpp = 0x618;
	const DWORD  GameModeState = 0x740;
	const DWORD  IsFPPGameMode = 0x688;
	const DWORD  IsCanSwitchFPP = 0x681;


	// From CharacterMovementComponent.PawnMovementComponent.NavMovementComponent.MovementComponent.ActorComponent 
	const DWORD GravityScale = 0x134;//float GravityScale;//[Offset: 0x134, Size: 4]
	const DWORD MaxStepHeight = 0x138;//float GravityScale;//[Offset: 0x134, Size: 4]
	const DWORD JumpZVelocity = 0x13c; //float GravityScale;//[Offset: 0x134, Size: 4]
	const DWORD JumpOffJumpZFactor = 0x140;//float GravityScale;//[Offset: 0x134, Size: 4]
	const DWORD GroundFriction = 0x170;//float GravityScale;//[Offset: 0x134, Size: 4] //set to 1 
	const DWORD MaxWalkSpeedCharcterMovmnet = 0x174;
	const DWORD MaxWalkSpeedCrouchedCharcterMovmnet = 0x178;
	const DWORD MaxSwimSpeedCharcterMovmnet = 0x180;
	const DWORD MaxFlySpeedCharcterMovmnet = 0x17c;
	const DWORD MaxCustomMovementSpeedCharcterMovmnet = 0x184;
	const DWORD MaxAccelerationCharcterMovmnet = 0x188;




	//From Parachute Compnent
	const DWORD  CurrentFallSpeed = 0x2c0;//float SpeedValue;//[Offset: 0xb58, Size: 4]
	const DWORD  AllowMaxDiatanceSqAtServer = 0x17c;//float SpeedValue;//[Offset: 0xb58, Size: 4]
	const DWORD  AllowMaxDistanceSqInParachuteOpen = 0x2c8;//float SpeedValue;//[Offset: 0xb58, Size: 4]
	const DWORD  MaxZAllowDistance = 0x2cc;//float SpeedValue;//[Offset: 0xb58, Size: 4]
	//Will Check
	const DWORD  PawnBackpackCapacity = 0x1b5c;
	const DWORD  IsInWater = 0x1554;//	bool IsInWater;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x14bc, Size: 1]
	const DWORD  OutofWaterZ = 0x1e4;//CharacterMovementComponent.PawnMovementComponent.NavMovementComponent.MovementComponent.ActorComponent

	//Fast Weapon Swithch
	const DWORD  SwitchWeaponSpeedScale = 0x1d24;// = 0x1a24;


	const DWORD  bIsGunADS = 0xb7d;// = 0x1a24;




}
