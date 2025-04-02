//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "RecordPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSongPaused);

UCLASS()
class THERITE_API ARecordPlayer : public AInteractor
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	ARecordPlayer();
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(BlueprintAssignable, Category = "Song Delegate")
	FOnSongPaused OnSongPaused;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	virtual void Interaction() override;
	
//---------------- Action Methods
	UFUNCTION()
	void PlaySong();

	UFUNCTION()
	void PauseSong();

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bIsPaused;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Base;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Disc;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Latch;

	UAudioComponent* AudioComponent;
	
	UPROPERTY(EditAnywhere, Category = "Song")
	USoundBase* Song;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};