//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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
	ARecordPlayer();
	
	virtual void Interaction() override;
	
//---------------- Action Methods
	UFUNCTION()
	void PlaySong();

	UFUNCTION()
	void PauseSong();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:	
	UPROPERTY(BlueprintAssignable, Category = "Song Delegate")
	FOnSongPaused OnSongPaused;
	
private:
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
};