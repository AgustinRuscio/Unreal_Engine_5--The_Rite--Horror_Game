
#pragma once

#include "CoreMinimal.h"
#include "TheRite/Interactuables/Interactor.h"
#include "SpectralWrittings.generated.h"


UCLASS()
class THERITE_API ASpectralWrittings : public AInteractor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
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