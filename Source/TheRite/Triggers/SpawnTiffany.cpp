//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "SpawnTiffany.h"
#include "Components/BoxComponent.h"
#include "Components/LightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/Characters/Tiffany.h"
#include "Engine/PointLight.h"
#include "Engine/TargetPoint.h"
#include "TheRite/Characters/Alex.h"

//*****************************Public*********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
ASpawnTiffany::ASpawnTiffany()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	Box = CreateDefaultSubobject<UBoxComponent>("Box collision");
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ASpawnTiffany::OnOverlapBegin);
}

//*****************************Private*********************************************
//*********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ASpawnTiffany::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<AAlex>(OtherActor)) return;
	
	FVector Position = SpawnPoint->GetActorLocation();
	FRotator Rotation = SpawnPoint->GetActorRotation();
	TSubclassOf<ATiffany> ActorClass = ATiffany::StaticClass();
	
	auto spawnedTiffany = GetWorld()->SpawnActor<AActor>(ActorClass,Position, Rotation);
	
	ATiffany* CastedTiffany = Cast<ATiffany>(spawnedTiffany);
	
	CastedTiffany->SetData(false,true,false, false);
	CastedTiffany->SetWaypoints(Waypoints);
	
	tif->GetMesh()->SetVisibility(true);
	
	Light->GetLightComponent()->SetIntensity(0.2f);
	
	UGameplayStatics::PlaySoundAtLocation(this,Sound, Light->GetActorLocation());
	
	Destroy();
}