//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Lighter.generated.h"


class ASpectralWrittings;
class UTutorialWidget;
class UPointLightComponent;

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
	ASpectralWrittings* KeySpectralWritting;
	
	void TurnTutorialOff();
	
protected:
	virtual void BeginPlay() override;

public:	
	ALighter();
	virtual void Tick(float DeltaTime) override;
	virtual void Interaction() override;
};