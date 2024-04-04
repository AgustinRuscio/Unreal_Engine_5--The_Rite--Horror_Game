//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "SpawnTiffanyInTime.generated.h"

UCLASS()
class THERITE_API ASpawnTiffanyInTime : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex);


	UPROPERTY(EditAnywhere, Category="SFX")
	USoundBase* TiffanyTalk;
	
	UPROPERTY(EditAnywhere, Category="State")
	bool bAlexInsede;

	float Timer;
	
	UPROPERTY(EditAnywhere, Category="State")
	float TimerCD = 7;

	bool SetTimer(float DeltaTime);
	
public:	
	ASpawnTiffanyInTime();
	
	virtual void Tick(float DeltaTime) override;
};