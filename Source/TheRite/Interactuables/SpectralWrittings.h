//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "TheRite/Interactuables/Interactor.h"
#include "Components/TimelineComponent.h"
#include "TheRite/Components/Fader.h"
#include "SpectralWrittings.generated.h"

class UBoxComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class AProsProcessModifier;
class USphereComponent;
class UFadeObjectComponent;

UCLASS()
class THERITE_API ASpectralWrittings : public AInteractor, public IFader
{
	GENERATED_BODY()

public:
	ASpectralWrittings();
	~ASpectralWrittings();
	
//---------------- Getter Methods
	bool GetDiscoverdStatus() const;
	
//---------------- System Class Methods
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Interaction() override;
	
//---------------- Actions Methods
	//void Activate();
	//void Deactivate();
	void Discovered();

	void EnableInteraction();
	void SetMaterialAlpha(float alpha);

private:
	void SetFaderValues();
	
	UFUNCTION()
	void OnFadeActivated();
	
	UFUNCTION()
	void OnFadeDeactivate();
	
	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnActorOverapFinished(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
//---------------- TimeLine Methods
	void BindTimeLine();
	
	UFUNCTION()
	void FadeTick(float deltaSeconds);
	UFUNCTION()
	void FadeFinished();
	
private:
	bool bReady = false;
	bool bPlayerInside;
	bool bFading = false;
	bool bDiscovered = false;

	float LastAlphaValue;
	float AlphaValue;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	FName PostProcessToModifyParameterName;
	//-------- Mesh / Colliders
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, Category= "Collidion")
	UBoxComponent* CollisionBox;
	
	UPROPERTY(EditAnywhere, Category= "Settings")
	USphereComponent* Sphere;
	
	//-------- Audio
	UPROPERTY(EditAnywhere, Category= "Audio")
	UAudioComponent* IdleAudio;
	UPROPERTY(EditAnywhere, Category= "Audio")
	USoundBase* SpectralSound;
	
	//-------- FeedBack
	UMaterialInterface* Material;
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, Category= "Settings")
	AProsProcessModifier* PostProcesModifierClass;

	FTimeline FadeTimeLine;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	UCurveFloat* FadeCurve;

	
	UPROPERTY(EditAnywhere, Category = "Component")
	UFadeObjectComponent* FadeComponent;
	
	AActor* InsideActor;
};