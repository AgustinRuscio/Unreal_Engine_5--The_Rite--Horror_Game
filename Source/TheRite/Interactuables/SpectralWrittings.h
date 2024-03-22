
#pragma once

#include "CoreMinimal.h"
#include "TheRite/Interactuables/Interactor.h"
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
	UBoxComponent* CollisionBox;
	
	bool bDiscovered = false;
	
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material;
	UMaterialInstanceDynamic* DynamicMaterial;

public:
	ASpectralWrittings();
	virtual void BeginPlay() override;
	
	bool GetDiscoverdStatus() const;
	void Activate() const;
	void Deactivate() const;

	void SetMaterialAlpha(float alpha);


	virtual void Interaction() override;
};