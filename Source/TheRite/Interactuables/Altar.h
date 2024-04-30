//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Altar.generated.h"

class AAltarWhell;

UCLASS()
class THERITE_API AAltar : public AInteractor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, Category= "Obj", meta=(AllowPrivateAccess = "true"))
	TArray<AAltarWhell*> Whells;

	bool bIsFocus;

	int WhellIndex;
	
protected:
	virtual void BeginPlay() override;

public:	
	AAltar();
	virtual void Tick(float DeltaTime) override;

	virtual void Interaction() override;

	void LeaveFocus();
};