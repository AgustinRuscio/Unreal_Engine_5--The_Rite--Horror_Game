﻿//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

UENUM(BlueprintType)
enum class PickableItemsID : uint8
{
	None,
	LibraryKey,
	ArtRoomKey,
	Clock,
	TiffanysCard,
	Hours,
	Minutes,
	Diary
};

UENUM(BlueprintType)
enum class LevelObjectType : uint8
{
	Clock,
	Diary,
	Picture
};