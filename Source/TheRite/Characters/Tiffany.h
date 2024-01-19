#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/SphereComponent.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Character.h"
#include "TheRite/AI/TiffanyController.h"
#include "Tiffany.generated.h"

UCLASS()
class THERITE_API ATiffany : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	UAudioComponent* CryingAudio;

	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;
	
	const FName TargetKey = "Target";
	
	const FName BooleanKey = "HasToMove";

	UPROPERTY(EditAnywhere, Category="States")
	bool bHasToMove;
	
	UPROPERTY(EditAnywhere, Category="States")
	bool bWalking;

	UPROPERTY(EditAnywhere, Category="Waypoints")
	TArray<ATargetPoint*> Waypoints;

	TSubclassOf<ATiffanyController> DefaultAIController;
	
	UPROPERTY()
	UBlackboardComponent* BlackBoard ;

protected:
	virtual void BeginPlay() override;
	
public:	
	ATiffany();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	bool GetWalkingState() const;
	
	UFUNCTION()
	void StartMovement(ATargetPoint* newTarget);

	UFUNCTION()
	void SetData(bool IsVisible, bool NoCollision, bool HasToMove);

	UFUNCTION()
	void SetWaypoints(TArray<ATargetPoint*> targets);

	bool SetHasToMove(bool hasToMoveState);
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};