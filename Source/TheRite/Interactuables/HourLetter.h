//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "HourLetter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActioning);

UCLASS()
class THERITE_API AHourLetter : public AInteractor
{
	GENERATED_BODY()

public:
	AHourLetter();
	
	virtual void Interaction() override;
	
public:	
	UPROPERTY(BlueprintAssignable, Category = "Action")
	FActioning OnAction;
	
private:
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* LetterMesh;
};