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

	Del.BindLambda([&]
	{
		Del.Unbind();
		GetWorldTimerManager().ClearTimer(WaitTimer);
		UGameplayStatics::OpenLevel(GetWorld(),Clock->GetObjectData());
	});
}

//----------------------------------------------------------------------------------------------------------------------
void AMainObjectInteractionTrigger::MainObjectGrabbed(AInteractor* interactable)
{
	auto Player = CastChecked<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));
	Player->ForceDisableInput();

	for (auto Element : MainObjctGrabbedSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), Element, 3.0f);
	}

	if(!GetWorldTimerManager().IsTimerActive(WaitTimer))
		GetWorldTimerManager().SetTimer(WaitTimer,Del,7.5f, false);
}