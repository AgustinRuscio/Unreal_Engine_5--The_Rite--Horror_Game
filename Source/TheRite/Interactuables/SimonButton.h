//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "SimonButton.generated.h"

UENUM(BlueprintType)
enum class EButtonColor : uint8
{
	Red = 0,
	Yellow = 1,
	Blue = 2,
	Green = 3
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionStart, int8, ColorPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionFinished);

UCLASS()
class THERITE_API ASimonButton : public AInteractor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ASimonButton();

	UPROPERTY(EditDefaultsOnly,Category = Visuals, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = Visuals, meta = (AllowPrivateAccess = true))
	class UPointLightComponent* PointLightComponent;
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	FOnInteractionStart OnInteractionStart;
	FOnInteractionFinished OnInteractionFinished;
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	virtual void Interaction() override;
	virtual void Activate() override;
	virtual void Deactivate() override;
	
	void PressForced();
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditDefaultsOnly, Category = Settings, meta=(ClampMin = 0, ClampMax = 3))
	int8 Color;

	FVector PressedLocation;
	FVector NormalLocation;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	FVector LocationToSubtract;
	
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	USoundBase* PressedSounds;

	FTimeline InteractionTimeLine;
	
	UPROPERTY(EditDefaultsOnly, Category = TimeLine)
	UCurveFloat* InteractionCurveFloat;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	FLinearColor SetPointLightColor() const;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void PlayInteractionFeedBack();
	
	void BindTimeLineMethods();

	UFUNCTION()
	void InteractionTick(float deltaSeconds);
	
	UFUNCTION()
	void InteractionFinished();
};