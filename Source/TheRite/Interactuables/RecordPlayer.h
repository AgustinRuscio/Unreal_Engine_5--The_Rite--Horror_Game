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
	
private:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Base;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Disc;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Latch;

	UPROPERTY(EditAnywhere, Category = "Song")
	USoundBase* Song;

	UAudioComponent* AudioComponent;

	bool bIsPaused;
	
protected:
	virtual void BeginPlay() override;

public:	
	ARecordPlayer();
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintAssignable, Category = "Song Delegate")
	FOnSongPaused OnSongPaused;

	virtual void Interaction() override;

	UFUNCTION()
	void PlaySong();

	UFUNCTION()
	void PauseSong();
};
