//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Components/TimelineComponent.h"
#include "SpectralWrittings.generated.h"

class UBoxComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class AProsProcessModifier;
class USphereComponent;

UCLASS()
class THERITE_API ASpectralWrittings : public AInteractor
{
	GENERATED_BODY()
private:
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	FName PostProcessToModifyParameterName;
	
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
	bool bFading = false;

	float LastAlphaValue;
	float AlphaValue;
	
	AActor* InsideActor;

	UPROPERTY(EditAnywhere, Category= "Settings")
	AProsProcessModifier* Gameflow;

	FTimeline FadeTimeLine;
	UPROPERTY(EditAnywhere, Category="Settings")
	UCurveFloat* FadeCurve;

UFUNCTION()
	void FadeTick(float deltaSeconds);
UFUNCTION()
	void FadeFinished();
	
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
	void Activate();
	void Deactivate();

	void EnableInteraction();
	void SetMaterialAlpha(float alpha);

	void Discovered();
	virtual void Interaction() override;
};