//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Letter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAction);

UCLASS()
class THERITE_API ALetter : public AInteractor
{
	GENERATED_BODY()
	
private:	
	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* LetterMesh;
	
public:	
	ALetter();

	virtual void Interaction() override;
	
	UPROPERTY(BlueprintAssignable, Category = "Action")
	FAction OnAction;
};