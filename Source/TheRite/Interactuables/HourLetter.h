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
	
private:
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* LetterMesh;

public:	
	AHourLetter();
	
	virtual void Interaction() override;

	UPROPERTY(BlueprintAssignable, Category = "Action")
	FActioning OnAction;
};