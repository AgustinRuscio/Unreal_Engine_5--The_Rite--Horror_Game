//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.3						//
//----------------------------------------------//

#include "HospitalEndGmae.h"
#include "Engine/TriggerBox.h"
#include <TheRite/AlexPlayerController.h>
#include <TheRite/Characters/Alex.h>
#include "TheRite/Interactuables/Door.h"
#include "TheRite/Interactuables/Emblem/EmblemsPlace.h"

//----------------------------------------------------------------------------------------------------------------------

AHospitalEndGmae::AHospitalEndGmae()
{
	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AHospitalEndGmae::BeginPlay()
{
	Super::BeginPlay();
	
	EmblemPlace->OnEndGame.AddDynamic(this, &AHospitalEndGmae::OnAllEmblesPlaced);
	EndGameBox->OnActorBeginOverlap.AddDynamic(this, &AHospitalEndGmae::BeginOverlap);
}

//----------------------------------------------------------------------------------------------------------------------
void AHospitalEndGmae::OnAllEmblesPlaced()
{
	LastDoor->SetLockedState(false);
}

//----------------------------------------------------------------------------------------------------------------------
void AHospitalEndGmae::BeginOverlap(AActor* OverlapedActor, AActor* OtherActor)
{	
	if (auto player = Cast<AAlex>(OtherActor))
	{
		LastDoor->HardClosing();

		auto playerController = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController());
		playerController->DisableInput(playerController);
	}
}