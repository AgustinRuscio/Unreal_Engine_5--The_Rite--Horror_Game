//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "BasePlayerSettingsSetter.h"
#include "TheRite/Characters/Alex.h"
#include "Kismet/GameplayStatics.h"

//*****************************Public********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
ABasePlayerSettingsSetter::ABasePlayerSettingsSetter()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Setter Methods
void ABasePlayerSettingsSetter::SetUseLighter(bool WillUseLighter)
{
	bWilUseLighter = WillUseLighter;
	Player->SetPlayerOptions(bWillRun, bWilUseLighter, bWilShowLighterReminder);
}

//----------------------------------------------------------------------------------------------------------------------
void ABasePlayerSettingsSetter::SetCanRun(bool WillRun)
{
	bWillRun = WillRun;
	Player->SetPlayerOptions(bWillRun, bWilUseLighter, bWilShowLighterReminder);
}
#pragma endregion

//*****************************Private********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ABasePlayerSettingsSetter::BeginPlay()
{
	Super::BeginPlay();

	Player = CastChecked<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Player->SetPlayerOptions(bWillRun, bWilUseLighter, bWilShowLighterReminder);
}