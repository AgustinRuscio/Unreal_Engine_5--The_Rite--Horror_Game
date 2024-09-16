//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Simon.generated.h"

UCLASS()
class THERITE_API ASimon : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
    //						CONSTRUCTOR & PUBLIC COMPONENTS						   //
    //*****************************************************************************//
	ASimon();

	UPROPERTY(EditDefaultsOnly, Category = Visual, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SimonMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = Visual, meta= (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CenterMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = Visual, meta=(AllowPrivateAccess = "true"))
	class UWidgetComponent* WidgetComponent;

	class USimonWidget* SimonWidget;
	
    //*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	FVector CenterLocationToAdd;
	
	FTimeline MoveCenterTimeline;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	UCurveFloat* MoveCenterCurve; 
	
	//*****************************************************************************//
    //								PRIVATE METHODS								   //
    //*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SimonCompleted();

	void BindTimeLine();

	UFUNCTION()
	void MoveCenterTick(float deltaSeconds);
	UFUNCTION()
	void MoveCenterFinished();
	
};