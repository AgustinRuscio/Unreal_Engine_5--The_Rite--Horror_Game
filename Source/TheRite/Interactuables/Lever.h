//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Lever.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeverUsageEnd, ALever*, caller);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeverUsageStart, ALever*, caller);

UCLASS()
class THERITE_API ALever : public AInteractor
{
	GENERATED_BODY()

public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ALever();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Visual, meta = (allowPrivateAccess = "true"))
	UStaticMeshComponent* LeverMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Visual, meta = (allowPrivateAccess = "true"))
	UStaticMeshComponent* LeverBaseMesh;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	FOnLeverUsageEnd OnLeverUsageEnd;
	FOnLeverUsageStart OnLeverUsageStart;
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	FORCEINLINE bool IsCorrect() const { return bIsCorrect; };

	virtual void Interaction() override;

	void ResetLever();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = Settings)
	bool bIsCorrect;

	bool bWasUsed;
	bool bPlayForward;

	UPROPERTY(EditAnywhere, Category = Settings)
	FRotator InitialRotation;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	FRotator UsedRotation;
	
	FTimeline Timeline;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	UCurveFloat* CurveFloat;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void LeverTimeLineTick(float delta);

	UFUNCTION()
	void LeverTimeLineFinished();
};