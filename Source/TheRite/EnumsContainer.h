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
	Fuse
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
	
};