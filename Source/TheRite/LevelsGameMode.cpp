//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "LevelsGameMode.h"
#include "TheRite/Interactuables/LightSwitch.h"
#include "TheRite/AchievementContainer.h"
#include <Kismet/GameplayStatics.h>

void ALevelsGameMode::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALightSwitch::StaticClass(), FoundEnemies);

    for (AActor* Current : FoundEnemies)
    {
        if (ALightSwitch* CurrentCast = Cast<ALightSwitch>(Current))
        {
            CurrentCast->OnInteractionTrigger.AddDynamic(this, &ALevelsGameMode::OnLightSwitchInteracted);
        }
    }
}

void ALevelsGameMode::OnLightSwitchInteracted(AInteractor* LightSwitch)
{
    switchesInteractedPerLevel++;

    if (switchesInteractedPerLevel >= 5)
    {
        UnlockAchievemetns(Achievements::ACH_USE_FIVE_SWITCHER);
    }
}