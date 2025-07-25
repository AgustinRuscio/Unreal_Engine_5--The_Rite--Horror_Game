//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "LevelStreamLoader.h"
#include "Components/BoxComponent.h" 
#include "TheRite/Characters/Alex.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
ALevelStreamLoader::ALevelStreamLoader()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALevelStreamLoader::OverlapBegins);
}

//----------------------------------------------------------------------------------------------------------------------
void ALevelStreamLoader::OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!Cast<AAlex>(OtherActor)) return;

	LoadLevels();
	UnloadLevels();
}

//----------------------------------------------------------------------------------------------------------------------
void ALevelStreamLoader::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	BoxComponent->OnComponentBeginOverlap.RemoveDynamic(this, &ALevelStreamLoader::OverlapBegins);
}

//----------------------------------------------------------------------------------------------------------------------
void ALevelStreamLoader::LoadLevels()
{
	for(const auto& levelName : LevelsToLoad)
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(GetWorld(), levelName, true, true, LatentInfo);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ALevelStreamLoader::UnloadLevels()
{
	for (const auto& levelName : LevelsToUnload)
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::UnloadStreamLevel(GetWorld(), levelName, LatentInfo, true);
	}
}