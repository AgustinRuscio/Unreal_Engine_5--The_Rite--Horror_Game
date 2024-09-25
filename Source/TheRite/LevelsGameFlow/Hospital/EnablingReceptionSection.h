//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnablingReceptionSection.generated.h"

UCLASS()
class THERITE_API AEnablingReceptionSection : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AEnablingReceptionSection();
	
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
	float IntensityToAddToReceptionLight;

	UPROPERTY(EditDefaultsOnly, Category = SFX)
	USoundBase* ReceptionLightChanged;
	
	UPROPERTY(EditAnywhere, Category = Puzzle)
	TArray<class ALightsTheRite*> Lights;
	
	UPROPERTY(EditAnywhere, Category = Puzzle)
	class AEmblemsPlace* EmblemsPlace;

	UPROPERTY(EditAnywhere, Category = Puzzle)
	class ADoor* OfficeDoor;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnFirstInteractionWithEmblemsPlace(class AInteractor* Interactable);

	void ChangeReceptionLightsSettings();
};