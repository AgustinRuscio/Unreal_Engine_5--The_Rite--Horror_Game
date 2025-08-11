//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "AchievementContainer.h"
#include "TheRite/LevelsGameMode.h"

void AchievementContainer::UnlockAchievemetns(UWorld* World, FName AchievementID)
{
	if(!World) return;

	if(auto GameMode = Cast<ALevelsGameMode>(World->GetAuthGameMode()))
		GameMode->UnlockAchievemetns(AchievementID);
}