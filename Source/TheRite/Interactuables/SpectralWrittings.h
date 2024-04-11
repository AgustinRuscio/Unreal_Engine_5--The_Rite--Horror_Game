//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Components/PostProcessComponent.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "SpectralWrittings.generated.h"


UCLASS()
class THERITE_API ASpectralWrittings : public AInteractor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, Category= "Audio")
	UAudioComponent* IdleAudio;
	UPROPERTY(EditAnywhere, Category= "Audio")
	USoundBase* SpectralSound;
	
	
	UPROPERTY(EditAnywhere, Category= "Collidion")
	UBoxComponent* CollisionBox;
	
	bool bDiscovered = false;
	
	UMaterialInterface* Material;
	UMaterialInstanceDynamic* DynamicMaterial;

	
	UPROPERTY(EditAnywhere, Category= "Settings")
	USphereComponent* Sphere;
	
	bool bPlayerInside;
	bool bReady = false;

	AActor* InsideActor;

	UPROPERTY(EditAnywhere, Category = "Post process event")
	UMaterialInterface* PostProcesVHSdMaterial;
	UMaterialInstanceDynamic* DynamicMaterialPostProcess;

	UPROPERTY(EditAnywhere, Category = "Post process event")
	UPostProcessComponent* PostProcessComponent;
	
	
public:
	ASpectralWrittings();
	~ASpectralWrittings();

	virtual void BeginDestroy() override;
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnActorOverapFinished(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
	bool GetDiscoverdStatus() const;
	void Activate() const;
	void Deactivate() const;

	void EnableInteraction();
	void SetMaterialAlpha(float alpha);

	void Discovered();

	virtual void Interaction() override;
};