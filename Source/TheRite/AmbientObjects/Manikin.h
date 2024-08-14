//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "Manikin.generated.h"

UCLASS()
class THERITE_API AManikin : public AActor
{
	GENERATED_BODY()
	
public:	
	AManikin();

	void Activate();
	void Deactivate();

private:
	virtual void Tick(float DeltaTime) override;
	
	void ReLocateObject();
	
private:
	UPROPERTY(EditAnywhere, Category="Settings")
	bool bStartsActive;
	bool bActive;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	float ReLocateColdDown;
	float ReLocateTimer;
	
	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="Target points")
	TArray<ATargetPoint*> PossiblesLocations;
};