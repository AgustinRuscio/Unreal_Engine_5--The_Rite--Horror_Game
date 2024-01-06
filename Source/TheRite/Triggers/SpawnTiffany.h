#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/PointLight.h"
#include "TheRite/Characters/Tiffany.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "SpawnTiffany.generated.h"

UCLASS()
class THERITE_API ASpawnTiffany : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category="Spawnning")
	ATargetPoint* SpawnPoint;

	UPROPERTY(EditAnywhere, Category="New states for Tiffany")
	TArray<ATargetPoint*> Waypoints;

	UPROPERTY(EditAnywhere, Category="New states for Tiffany")
	ATiffany* tif;

	UPROPERTY(EditAnywhere, Category="Ambient")
	APointLight* Light;

	UPROPERTY(EditAnywhere, Category="Ambient")
	USoundBase* Sound;
protected:
	virtual void BeginPlay() override;

public:	
	ASpawnTiffany();
};
