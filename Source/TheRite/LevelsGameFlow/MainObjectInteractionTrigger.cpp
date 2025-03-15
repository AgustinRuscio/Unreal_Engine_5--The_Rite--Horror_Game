//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "MainObjectInteractionTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Interactuables/Clock.h"

//----------------------------------------------------------------------------------------------------------------------
AMainObjectInteractionTrigger::AMainObjectInteractionTrigger()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AMainObjectInteractionTrigger::BeginPlay()
{
	Super::BeginPlay();

	Clock->OnInteractionTrigger.AddDynamic(this, &AMainObjectInteractionTrigger::MainObjectGrabbed);
	GameName = Clock->GetObjectData();
}

//----------------------------------------------------------------------------------------------------------------------
void AMainObjectInteractionTrigger::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(WaitTimer);
}

//----------------------------------------------------------------------------------------------------------------------
void AMainObjectInteractionTrigger::OpenLevel()
{
	if (GameName != "")
		UGameplayStatics::OpenLevel(GetWorld(), GameName);
	else
		UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetMapName()));
}	

//----------------------------------------------------------------------------------------------------------------------
void AMainObjectInteractionTrigger::MainObjectGrabbed(AInteractor* interactable)
{
	auto Player = Cast<AAlex>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if(Player)
		Player->ForceDisableInput();

	for (auto Element : MainObjctGrabbedSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), Element, 3.0f);
	}

	if(!GetWorld()->GetTimerManager().IsTimerActive(WaitTimer))
		GetWorld()->GetTimerManager().SetTimer(WaitTimer,this, &AMainObjectInteractionTrigger::OpenLevel,7.5f, false);
}