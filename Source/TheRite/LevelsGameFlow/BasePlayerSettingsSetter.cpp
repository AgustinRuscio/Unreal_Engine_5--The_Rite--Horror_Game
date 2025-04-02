//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "BasePlayerSettingsSetter.h"
#include "TheRite/Characters/Alex.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
ABasePlayerSettingsSetter::ABasePlayerSettingsSetter()
{
 	PrimaryActorTick.bCanEverTick = false;
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