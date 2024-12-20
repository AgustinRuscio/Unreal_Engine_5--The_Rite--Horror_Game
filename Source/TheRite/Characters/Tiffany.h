//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Tiffany.generated.h"

class UAudioComponent;
class USphereComponent;
class ATargetPoint;
class ATiffanyController;
class UBlackboardComponent;

UCLASS()
class THERITE_API ATiffany : public ACharacter
{
	GENERATED_BODY()

public:	
	ATiffany();

	UFUNCTION(BlueprintCallable)
	bool GetWalkingState() const;
	
	bool SetHasToMove(bool hasToMoveState) const;
	
	UFUNCTION()
	void StartMovement(ATargetPoint* newTarget);

	UFUNCTION()
	void SetData(bool IsVisible, bool NoCollision, bool HasToMove, bool Crawling);

	UFUNCTION()
	void SetWaypoints(TArray<ATargetPoint*> targets);

	void Activate() const;
	void MakeVisible();

	void Deactivate() const;
	void MakeInvisible();
	
private:
	virtual void BeginPlay() override;
	
//---------------- Collider Methods
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="States")
	bool bCrawling;
	
private:
	UPROPERTY(EditAnywhere, Category="States")
	bool bHasToMove;
	
	UPROPERTY(EditAnywhere, Category="States")
	bool bWalking;
	
	const FName TargetKey = "Target";
	
	const FName BooleanKey = "HasToMove";
	
	UPROPERTY(EditAnywhere)
	UAudioComponent* CryingAudio;

	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;
	
	UPROPERTY(EditAnywhere, Category="Waypoints")
	TArray<ATargetPoint*> Waypoints;
	
	UPROPERTY(EditAnywhere, Category="Waypoints")
	TSubclassOf<ATiffanyController> DefaultAIController;
	ATiffanyController* AIController;
	
	UPROPERTY()
	UBlackboardComponent* BlackBoard ;

	FTimerHandle timerHandle;
	FTimerDelegate TimerDelegate;
};