//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "RealWorldGameFlow.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TriggerVolume.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Widgets/TutorialWidget.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Interactuables/Clock.h"

//----------------------------------------------------------------------------------------------------------------------
ARealWorldGameFlow::ARealWorldGameFlow()
{
 	PrimaryActorTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldGameFlow::BeginPlay()
{
	Super::BeginPlay();

	PlayerMethods();
	
	KnockTrigger->OnActorBeginOverlap.AddDynamic(this, &ARealWorldGameFlow::OnOverlapBeginKnock);
}

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldGameFlow::PlayerMethods()
{
	Player = CastChecked<AAlex>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlex::StaticClass()));
	Player->ForceTalk(FirstTalkAudio);
	Player->SetPlayerOptions(true, false, false);
}

//----------------------------------------------------------------------------------------------------------------------
void ARealWorldGameFlow::OnOverlapBeginKnock(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!Cast<AAlex>(OtherActor))return;

	UGameplayStatics::SpawnSound2D(GetWorld(), SFX_Knocking);
	KnockTrigger->Destroy();
}