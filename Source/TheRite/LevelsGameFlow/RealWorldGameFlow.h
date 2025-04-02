//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RealWorldGameFlow.generated.h"

class ATriggerVolume;
class AAlex;

UCLASS()
class THERITE_API ARealWorldGameFlow : public AActor
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ARealWorldGameFlow();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	//-------- Collider
	UPROPERTY(EditAnywhere, Category= "Objects")
	ATriggerVolume* KnockTrigger;
	
	//-------- Audio
	UPROPERTY(EditAnywhere, Category= "Audios")
	USoundBase* FirstTalkAudio;
	
	UPROPERTY(EditAnywhere, Category = "Audios")
	USoundBase* SFX_Knocking;
	AAlex* Player;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	
	void PlayerMethods();
	
//---------------- Widgets Methods
	void ShowingFirstTutorialWidget();
	void HidingFirstTutorialWidget();
	void ShowingSecondTutorialWidget();
	void HidingSecondTutorialWidget();
	
	
	UFUNCTION()
	void OnOverlapBeginKnock(AActor* OverlappedActor, AActor* OtherActor);
};