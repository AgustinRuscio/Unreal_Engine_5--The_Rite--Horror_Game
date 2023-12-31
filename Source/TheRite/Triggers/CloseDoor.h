#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"
#include "TheRite/Interactuables/Door.h"
#include "Components/BoxComponent.h"
#include "TheRite/AI/TiffanyController.h"
#include "CloseDoor.generated.h"

UCLASS()
class THERITE_API ACloseDoor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, Category = "Closing Door")
	ADoor* Door;

	UPROPERTY(EditAnywhere, Category = "Ambient")
	TArray<ALightsTheRite*> Lights;
	
	UPROPERTY(EditAnywhere, Category = "Ambient")
	ALightsTheRite* DestroyableLight;

	UPROPERTY(EditAnywhere, Category = "Ambient")
	USoundBase* SFXLightBReak;
	
	UPROPERTY(EditAnywhere, Category = "Ambient")
	bool bAggresiveLight;
	
public:	
	ACloseDoor();

};