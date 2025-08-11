//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//
#pragma once

#include "CoreMinimal.h"

class AchievementContainer
{
public:
	static void UnlockAchievemetns(UWorld* World, FName AchievementID);
};

namespace Achievements
{
	inline FName ACH_WIN_ONE_GAME = TEXT("ACH_WIN_ONE_GAME"); //Done
	inline FName ACH_BEGIN_FIRST_GAME = TEXT("ACH_BEGIN_FIRST_GAME"); //Done
	inline FName ACH_COMPLETE_THE_HOUSE = TEXT("ACH_COMPLETE_THE_HOUSE"); //Done
	inline FName ACH_DISCOVER_THE_TRUTH = TEXT("ACH_DISCOVER_THE_TRUTH"); //Done

	inline FName ACH_CLOCK_PUZZLE_COMPLETED = TEXT("ACH_CLOCK_PUZZLE_COMPLETED"); //Done
	inline FName ACH_STATUETE_PUZZLE_COMPLETED = TEXT("ACH_STATUETE_PUZZLE_COMPLETED"); //Done
	inline FName ACH_LUCY_PUZZLE_COMPLETED = TEXT("ACH_LUCY_PUZZLE_COMPLETED"); //Done

	inline FName ACH_USE_FIVE_SWITCHER = TEXT("ACH_USE_FIVE_SWITCHER");
	inline FName ACH_FIND_ALL_WRITTING = TEXT("ACH_FIND_ALL_WRITTING");
}