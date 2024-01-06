#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "LevelSequence.h"
#include "GameFramework/Actor.h"
#include "Rite.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClockGain);

UCLASS()
class THERITE_API ARite : public AInteractor
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(EditAnywhere, Category= "Voice Audio")
	bool bClockReady = false;

	
	UPROPERTY(EditAnywhere, Category= "Voice Audio")
	FName NextLevel;
	
	UPROPERTY(EditAnywhere, Category= "Voice Audio")
	USoundBase* AudioClockReady;
	
	UPROPERTY(EditAnywhere, Category= "Voice Audio")
	USoundBase* AudioClockNotReady;
	
	UPROPERTY(EditAnywhere, Category= "Audio")
	USoundBase* PortalAudio;

	UPROPERTY(EditAnywhere, Category= "Mesh")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, Category= "Sequence")
	ULevelSequence* SequenceFade;

	UFUNCTION()
	void CheckAudio();

	UFUNCTION()
	void ChangeLevel();
	
protected:
	virtual void BeginPlay() override;

public:	
	ARite();
	
	virtual void Interaction() override;

	void SetClockReady();
	
	UPROPERTY(BlueprintAssignable, Category = "Clock")
	FClockGain OnClockGain;
};