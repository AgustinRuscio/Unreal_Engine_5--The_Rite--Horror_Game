//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

UENUM(BlueprintType)
enum class PickableItemsID : uint8
{
	None,
	LibraryKey,
	ArtRoomKey,
	BedRoomKey,
	LucysRoom,
	LCorridorKey,
	Clock,
	TiffanysCard,
	Hours,
	Minutes,
	Diary,
	Pacifier,
	Fuse,
	ChestKey,
	PasswordVault26,
	PasswordVault47,
	SecurityCardOneToThirteen,
	SecurityCardOne,
	SecurityCardThirteen,
	EmblemLion,
	EmblemLady,
	EmblemTeddy,
};

UENUM(BlueprintType)
enum class LevelObjectType : uint8
{
	Clock,
	Diary,
	Picture
};

UENUM(BlueprintType)
enum class HouseZone : uint8
{
	ArtRoom,
	Garage,
	Library,
	TCorridor,
	Hall,
	LivingRoom,
	Kitchen,
	DiningRoom,
	LCorridor,
	BathRoom,
	BedRoom,
	ServiceRoom,
	Attic,
	UpStarirsCorridor,
	BabyRoom,
	Stairs 
};
UENUM(BlueprintType)
enum class HospitalZone : uint8
{
	Reception,
	Morgue,
	Catwalk,
	Rooms
};