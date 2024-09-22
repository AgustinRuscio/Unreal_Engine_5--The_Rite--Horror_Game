//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "SimonButton.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	int8 LevelQuantity;
	
	int8 CheckCountIndex;
	int8 SequenceCurrentIndex;
	int8 SequenceLevel;

	TArray<int8> CurrenSequence;
	
	UPROPERTY(EditAnywhere, Category = Buttons)
	TArray<class ASimonButton*> SimonButtons;
	
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	FVector CenterLocationToAdd;

	UPROPERTY(EditDefaultsOnly, Category = SFX)
	USoundBase* SFX_NextLevelReach;
	UPROPERTY(EditDefaultsOnly, Category = SFX)
	USoundBase* SFX_Failure;
	
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

	void CreateSequence();
	void StarSequence();
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

	void BindTimeLine();

	UFUNCTION()
	void MoveCenterTick(float deltaSeconds);
	UFUNCTION()
	void MoveCenterFinished();
};