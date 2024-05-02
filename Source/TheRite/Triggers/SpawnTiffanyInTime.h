//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnTiffanyInTime.generated.h"

class UBoxComponent;

UCLASS()
class THERITE_API ASpawnTiffanyInTime : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnTiffanyInTime();
	virtual void Tick(float DeltaTime) override;

private:
	bool SetTimer(float DeltaTime);
	
//---------------- Bind Colliders Methods
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex);
	
private:
	UPROPERTY(EditAnywhere, Category="State")
	bool bAlexInsede;
	
	UPROPERTY(EditAnywhere, Category="State")
	float TimerCD = 7;
	float Timer;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;
	
	UPROPERTY(EditAnywhere, Category="SFX")
	USoundBase* TiffanyTalk;
};