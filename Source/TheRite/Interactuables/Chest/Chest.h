//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Chest.generated.h"

UCLASS()
class THERITE_API AChest : public AInteractor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   // 
	//*****************************************************************************//

	//Constructor
	AChest();

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* ChestMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* LockMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* KeyMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* ArrowFocusLocation;
	
	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* ArrowEndLocation;

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* ChestCollider;
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   // 
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   // 
	//*****************************************************************************//
	virtual void Interaction() override;

	UFUNCTION()
	void LeaveFocus();

	void UnlockChest(FString itemName, PickableItemsID id);
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   // 
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bIsUnlocked;
	
	bool bIsFocus;

	UPROPERTY(EditAnywhere, Category = Settings)
	FVector ExitingVector;

	FVector InitialKeyLocation;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	FRotator ExitingRotation;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	FRotator EndKeyRotation;
	
	UPROPERTY(EditDefaultsOnly, Category = VFX)
	UAnimSequence* OpenChestSequence;
	
	UPROPERTY(EditDefaultsOnly, Category = VFX)
	UAnimSequence* OpenLockSequence;
	
	FTimerHandle OpeningLockTimerHandle;
	FTimerDelegate OpeningLockTimerDelegate;

	FTimerHandle OpeningChestTimerHandle;
	FTimerDelegate OpeningChestTimerDelegate;
	
	FTimeline MoveKeyTimeLine;
	FTimeline RotateKeyTimeLine;

	UPROPERTY(EditDefaultsOnly, Category = VFX)
	UCurveFloat* FloatCurve;
	
	class AAlex* Player;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   // 
	//*****************************************************************************//

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnLockOpenFinished();
	
	void BindTimeLines();
	
	UFUNCTION()
	void MoveKeyTick(float DeltaSeconds);
	UFUNCTION()
	void MoveKeyFinished();
	
	UFUNCTION()
	void RotateKeyTick(float DeltaSeconds);
	UFUNCTION()
	void RotateKeyFinished();

};