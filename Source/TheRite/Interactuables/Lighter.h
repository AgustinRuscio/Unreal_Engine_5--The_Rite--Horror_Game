//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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
	ALighter();
	virtual void Interaction() override;

	virtual void Deactivate() override;
	virtual void Activate() override;
	
private:
	virtual void BeginPlay() override;
	
	void CreateWidgets();
	void TurnTutorialOff();
	
private:
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
};