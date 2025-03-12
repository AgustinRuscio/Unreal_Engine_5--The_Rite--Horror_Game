//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.3						//
//----------------------------------------------//
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HospitalEndGmae.generated.h"

UCLASS()
class THERITE_API AHospitalEndGmae : public AActor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AHospitalEndGmae();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnyWhere, Category = Settings)
	FName NextLevelName;

	UPROPERTY(EditAnywhere, Category= Settings)
	class ULevelSequence* SequenceHospitalEnd;
	
	UPROPERTY(EditAnywhere, Category= Settings)
	USoundBase* EndGameSound;

	UPROPERTY(EditAnyWhere, Category = InGame)
	class AEmblemsPlace* EmblemPlace;

	UPROPERTY(EditAnyWhere, Category = InGame)
	class ADoor* LastDoor;

	UPROPERTY(EditAnyWhere, Category = InGame)
	TArray<class ADoor*> NearDoors;

	UPROPERTY(EditAnyWhere, Category = InGame)
	TArray<class ACustomLight*> NearLights;

	UPROPERTY(EditAnyWhere, Category = InGame)
	class ATriggerBox* EndGameBox;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnAllEmblesPlaced();

	UFUNCTION()
	void BeginOverlap(AActor* OverlapedActor, AActor* OtherActor);

	UFUNCTION()
	void ChangeLevel();
};