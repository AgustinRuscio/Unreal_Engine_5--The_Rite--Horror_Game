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
	
private:
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* LetterMesh;

public:	
	AMinutesLetter();

	virtual void Interaction() override;
	
	UPROPERTY(BlueprintAssignable, Category = "Action")
	FOnAction OnAction;
};