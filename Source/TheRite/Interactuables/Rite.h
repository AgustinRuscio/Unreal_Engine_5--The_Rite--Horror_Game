//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "GameFramework/Actor.h"
#include "Rite.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClockGain);

class ULevelSequence;
class UAudioComponent;
class USphereComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class UPostProcessComponent;
class AClock;

UCLASS()
class THERITE_API ARite : public AInteractor
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(EditAnywhere, Category= "Voice Audio")
	bool bObjectReady = false;

	
	//UPROPERTY(EditAnywhere, Category= "Level to Open")
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
	
	UPROPERTY(EditAnywhere, Category= "Audio")
	UAudioComponent* IdleAudio;

	UPROPERTY(EditAnywhere, Category= "Settings")
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, Category= "Settings")
	LevelObjectType LevelType;
	
	UFUNCTION()
	void CheckAudio();

	UFUNCTION()
	void ChangeLevel();

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);
	UFUNCTION()
	void OnActorOverapFinished(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I);
	
	bool bPlayerInside;
	bool bReady = false;

	AActor* InsideActor;

	UPROPERTY(EditAnywhere, Category = "Post process event")
	UMaterialInterface* PostProcesRealWorldMaterial;
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, Category = "Post process event")
	UPostProcessComponent* PostProcessComponent;
	
	FPostProcessVolumeProperties OriginalPostProcessValues;

	UPROPERTY(EditAnywhere, Category="Settings")
	AClock* CurrentMainObject;
	
protected:
	virtual void BeginPlay() override;

public:
	ARite();

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void Interaction() override;

	UFUNCTION()
	void SetClockReady(AInteractor* obj);
	
	UPROPERTY(BlueprintAssignable, Category = "Clock")
	FClockGain OnClockGain;
};