//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "MinutesLetter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAction);

UCLASS()
class THERITE_API AMinutesLetter : public AInteractor
{
	GENERATED_BODY()

public:
	AMinutesLetter();

	virtual void Interaction() override;
	
public:	
	UPROPERTY(BlueprintAssignable, Category = "Action")
	FOnAction OnAction;
	
private:
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* LetterMesh;
};