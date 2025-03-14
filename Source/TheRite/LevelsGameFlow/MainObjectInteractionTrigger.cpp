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
	UGameplayStatics::OpenLevel(GetWorld(), Clock->GetObjectData());
}

//----------------------------------------------------------------------------------------------------------------------
void AMainObjectInteractionTrigger::MainObjectGrabbed(AInteractor* interactable)
{
	auto Player = Cast<AAlex>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Player->ForceDisableInput();

	for (auto Element : MainObjctGrabbedSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), Element, 3.0f);
	}

	if(!GetWorld()->GetTimerManager().IsTimerActive(WaitTimer))
		GetWorld()->GetTimerManager().SetTimer(WaitTimer,this, &AMainObjectInteractionTrigger::OpenLevel,7.5f, false);
}