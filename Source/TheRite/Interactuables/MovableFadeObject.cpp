//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "MovableFadeObject.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Alex.h"

//----------------------------------------------------------------------------------------------------------------------
AMovableFadeObject::AMovableFadeObject()
{
 	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");

	NewActorLocation = CreateDefaultSubobject<UArrowComponent>("New Actor Location");
	NewActorLocation->SetupAttachment(MeshComponent);
}

//----------------------------------------------------------------------------------------------------------------------
void AMovableFadeObject::Interaction()
{
	if(!bCanInteract) return;
	
	Super::Interaction();

	AAlex* Player = Cast<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Player->MakeCameraFade(FromAlpha, ToAlpha, FadeDuration, FadeColor, HoldFade);

	SetActorLocation(NewActorLocation->GetComponentLocation());

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SFX_GrabItem, GetActorLocation());
	
	bCanInteract = false;
}