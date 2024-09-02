//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "RealWorldGameFlow.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TriggerVolume.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Widgets/TutorialWidget.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Interactuables/Clock.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
ARealWorldGameFlow::ARealWorldGameFlow()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldGameFlow::BeginPlay()
{
	Super::BeginPlay();

	PlayerMethods();
	
	KnockTrigger->OnActorBeginOverlap.AddDynamic(this, &ARealWorldGameFlow::OnOverlapBeginKnock);
	Clock->OnInteractionTrigger.AddDynamic(this, &ARealWorldGameFlow::MainObjectGrabbed);

	Del.BindLambda([&]
	{
		UGameplayStatics::OpenLevel(GetWorld(),Clock->GetObjectData());
	});
}

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldGameFlow::PlayerMethods()
{
	Player = CastChecked<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));
	Player->ForceTalk(FirstTalkAudio);
	Player->SetPlayerOptions(true, false, false);
}

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldGameFlow::MainObjectGrabbed(AInteractor* interactable)
{
	Player->ForceDisableInput();

	for (auto Element : MainObjctGrabbedSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), Element, 3.0f);
	}

	if(!GetWorldTimerManager().IsTimerActive(WaitTimer))
		GetWorldTimerManager().SetTimer(WaitTimer,Del,7.5f, false);
}

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldGameFlow::OnOverlapBeginKnock(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor))return;

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_Knocking);
	KnockTrigger->Destroy();
}