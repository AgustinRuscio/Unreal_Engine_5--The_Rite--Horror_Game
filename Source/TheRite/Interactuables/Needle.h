//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactor.h"
#include "Needle.generated.h"

UCLASS()
class THERITE_API ANeedle : public AInteractor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANeedle();
	
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta =(AllowPrivateAccess = "true"))
	UStaticMeshComponent* NeedleMesh;

	virtual void Interaction() override;

private:
	UPROPERTY(EditAnywhere)
	class ABigClock* ParentClock;

};
