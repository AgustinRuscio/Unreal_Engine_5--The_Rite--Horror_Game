//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelStreamLoader.generated.h"

UCLASS()
class THERITE_API ALevelStreamLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	ALevelStreamLoader();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	UPROPERTY(EditAnywhere, Category = "Settings")
	TArray<FName> LevelsToLoad;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TArray<FName> LevelsToUnload;


public:
	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

private:
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void LoadLevels();
	void UnloadLevels();

	UFUNCTION()
	void OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};