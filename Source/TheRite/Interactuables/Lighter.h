//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Lighter.generated.h"


class ASpectralWrittings;
class UPointLightComponent;
class UTutorialWidget;

UCLASS()
class THERITE_API ALighter : public AInteractor
{
	GENERATED_BODY()

public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ALighter();

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	virtual void Interaction() override;

	virtual void Deactivate() override;
	virtual void Activate() override;
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bWillPlayerRun;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bWillShowReminder;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* LighterBody;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* LighterWheel;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* LighterTop;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UPointLightComponent* PointLight;
	
	FTimerHandle TutorialTimerHanlde;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UTutorialWidget> TutorialMenu;
	
	UTutorialWidget* TutorialWidget;
	
	UPROPERTY(EditAnywhere, Category = "States")
	ASpectralWrittings* KeySpectralWritting;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	void PushWidget();
	
	void TurnTutorialOff();
};