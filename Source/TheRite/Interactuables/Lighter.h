//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "SpectralWrittings.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/Widgets/TutorialWidget.h"
#include "TheRite/Interactuables/RedDoor.h"
#include "Lighter.generated.h"

UCLASS()
class THERITE_API ALighter : public AInteractor
{
	GENERATED_BODY()
	
private:
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
	ARedDoor* RedDoor;

	UPROPERTY(EditAnywhere, Category = "States")
	ASpectralWrittings* KeySpectralWritting;
	
	void TurnTutorialOff();
	
protected:
	virtual void BeginPlay() override;

public:	
	ALighter();
	virtual void Tick(float DeltaTime) override;
	virtual void Interaction() override;
};