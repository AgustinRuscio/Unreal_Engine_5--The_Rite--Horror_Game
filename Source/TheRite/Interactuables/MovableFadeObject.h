//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "MovableFadeObject.generated.h"

UCLASS()
class THERITE_API AMovableFadeObject : public AInteractor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   // 
	//*****************************************************************************//

	//Constructor
	AMovableFadeObject();

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* NewActorLocation;
	
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

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	bool HoldFade;
	
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float  FromAlpha;
	
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float  ToAlpha;
	
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float  FadeDuration;
	
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	FLinearColor FadeColor;
};