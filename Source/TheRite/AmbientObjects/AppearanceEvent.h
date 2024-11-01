//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AppearanceEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAppreaceEventStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAppreaceEventEndStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAppreaceEventEndEnd);

UCLASS()
class THERITE_API AAppearanceEvent : public AActor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AAppearanceEvent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Visuals, meta=(AllowPrivateAccess=true))
	USkeletalMeshComponent* SkeletalMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Visuals, meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* StaticMesh;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	FOnAppreaceEventStart OnAppearanceEventStart;
	FOnAppreaceEventEndStart OnAppearanceEventEndStart;
	FOnAppreaceEventEndEnd OnAppearanceEventEndEnd;
	
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	UFUNCTION()
	void MakeAppear();

	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bVisible;

	UPROPERTY(EditAnywhere, Category = Settings)
	float DistanceWithPlayer;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	float TimeForSecondCallback;
	UPROPERTY(EditAnywhere, Category = Settings)
	float TimeToSee;

	float counter;
	
	UPROPERTY(EditAnywhere, Category = FeedBack)
	USoundBase* Sound;
	
	class AAlex* Player;

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void ChangeMeshesVisibility(bool visibility);
	
	void MakeDisappear();
	void CalculateDistance(float DeltaSecond);
};
