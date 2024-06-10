//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "BasePlayerSettingsSetter.h"
#include "TheRite/Characters/Alex.h"
#include "Kismet/GameplayStatics.h"

ABasePlayerSettingsSetter::ABasePlayerSettingsSetter()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ABasePlayerSettingsSetter::BeginPlay()
{
	Super::BeginPlay();

	Player = CastChecked<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Player->SetPlayerOptions(bWillRun, bWilUseLighter, bWilShowLighterReminder);
}

void ABasePlayerSettingsSetter::SetUseLighter(bool WillUseLighter)
{
	bWilUseLighter = WillUseLighter;
	Player->SetPlayerOptions(bWillRun, bWilUseLighter, bWilShowLighterReminder);
}

void ABasePlayerSettingsSetter::SetCanRun(bool WillRun)
{
	bWillRun = WillRun;
	Player->SetPlayerOptions(bWillRun, bWilUseLighter, bWilShowLighterReminder);
}