//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Emblem.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Interactor.h"
#include "EmblemsPlace.generated.h"

UCLASS()
class THERITE_API AEmblemsPlace : public AInteractor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AEmblemsPlace();

	UPROPERTY(EditDefaultsOnly, Category = Visuals, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	//------------Emblems Meshes
	UPROPERTY(EditDefaultsOnly, Category = Visuals, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* EmblemA;

	UPROPERTY(EditDefaultsOnly, Category = Visuals, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* EmblemB;

	UPROPERTY(EditDefaultsOnly, Category = Visuals, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* EmblemC;

	//------------Arrows
	UPROPERTY(EditDefaultsOnly, Category = Visuals, meta=(AllowPrivateAccess = "true"))
	class UArrowComponent* EmblemAEndLocation;
	
	UPROPERTY(EditDefaultsOnly, Category = Visuals, meta=(AllowPrivateAccess = "true"))
	class UArrowComponent* EmblemBEndLocation;
	
	UPROPERTY(EditDefaultsOnly, Category = Visuals, meta=(AllowPrivateAccess = "true"))
	class UArrowComponent* EmblemCEndLocation;
	
	TArray<class UArrowComponent*> AllEndsLocation;
	
	class UArrowComponent* CurrentEndLocation;
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	virtual void Interaction() override;
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	TArray< TPair<UStaticMeshComponent*, UArrowComponent*> > MapEmblem;
	
	UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowPrivateAccess = "true"));
	TArray<class AEmblem*> NeededEmblems;

	TArray<AInteractor*> EmblemsPickedType;
	UStaticMeshComponent* CurrentEmblem;
	
	FTimeline PlaceEmblemTimeLine;

	UPROPERTY(EditDefaultsOnly, Category = TimeLine)
	UCurveFloat* PlaceEmblemCurveFloat;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetLocationData();
	
	UFUNCTION()
	void EmblemObtained(AInteractor* Interactor);

	void BindTimeline();

	UFUNCTION()
	void PlaceEmblemTick(float deltaSeconds);
	
	UFUNCTION()
	void PlaceEmblemFinished();
};
