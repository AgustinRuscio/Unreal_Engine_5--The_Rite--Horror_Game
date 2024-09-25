//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "SimonButton.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Simon.generated.h"

UCLASS()
class THERITE_API ASimon : public AInteractor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
    //						CONSTRUCTOR & PUBLIC COMPONENTS						   //
    //*****************************************************************************//
	//Constructor
	ASimon();

	UPROPERTY(EditDefaultsOnly, Category = Visual, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SimonMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = Visual, meta= (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CenterMesh;
	
    //*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	virtual void Interaction() override;
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	bool bIsShowingCurrentSequence;
	bool bReEnableButtons;
	bool bSimonCompleted;

	float ShowSequenceTimerRate;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	int8 LevelQuantity = 2;
	
	int8 CheckCountIndex;
	int8 SequenceCurrentIndex;
	int8 SequenceLevel;

	TArray<int8> CurrenSequence;

	UPROPERTY(EditAnywhere, Category = Settings)
	FVector CenterLocationToAdd;
	
	UPROPERTY(EditAnywhere, Category = Buttons)
	TArray<class ASimonButton*> SimonButtons;
	
	UPROPERTY(EditDefaultsOnly, Category = SFX)
	USoundBase* SFX_NextLevelReach;

	UPROPERTY(EditDefaultsOnly, Category = SFX)
	USoundBase* SFX_SimonCompleted;
	
	UPROPERTY(EditDefaultsOnly, Category = SFX)
	USoundBase* SFX_Failure;

	FTimerHandle RePlaySequenceTimerHandle;
	FTimerDelegate RePlaySequenceTimerDelegate;
	
	FTimeline MoveCenterTimeline;
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	UCurveFloat* MoveCenterCurve; 
	
	//*****************************************************************************//
    //								PRIVATE METHODS								   //
    //*****************************************************************************//

	bool HasSequenceFinish();
	bool CheckCompleteSequence();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Deactivate() override;

	void CreateSequence();
	void StartSequence();
	void PlaySequence(int8 PlayedIndex);
	void ShowNextSequence();
	void ChangeSequenceLevel();

	void ClearGameVariables();
	
	void ChangeButtonsInteractionState(bool NewState);
	
	UFUNCTION()
	void OnButtonPressed(int8 ColorPressed);
	
	UFUNCTION()
	void OnButtonPressedFinished();
	
	UFUNCTION()
	void SimonCompleted();

	void Failure();

	void PlayShowSequenceTimerHandle();
	
	void BindTimeLine();

	UFUNCTION()
	void MoveCenterTick(float deltaSeconds);
	UFUNCTION()
	void MoveCenterFinished();
};