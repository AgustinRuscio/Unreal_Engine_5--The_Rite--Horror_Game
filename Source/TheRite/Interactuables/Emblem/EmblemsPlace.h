//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Interactor.h"
#include "EmblemsPlace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndGame);

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

	UStaticMeshComponent* CurrentEmblem;
	
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

	FOnEndGame OnEndGame;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	bool GetIsFirstInteraction();
	
	virtual void Interaction() override;
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bFistInteraction;
	
	int8 EmblemsPicked;
	
	FVector StartLocation;
	FVector EndLocation;
	UPROPERTY(EditAnyWhere, Category = Settings)
	FVector LocationToAdd;

	FString CurrentEmblemName;
	PickableItemsID CurrentEmblemId;
	
	UPROPERTY(EditAnyWhere, Category = Settings)
	USoundBase* MovingSound;

	TArray< TPair<UStaticMeshComponent*, UArrowComponent*> > MapEmblem;
	
	UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowPrivateAccess = "true"));
	TArray<class ASimpleGrabbableActor*> NeededEmblems;
	
	FTimeline PlaceEmblemTimeLine;
	FTimeline PlaceEmblemTimeLineEndPuzzle;

	UPROPERTY(EditDefaultsOnly, Category = TimeLine)
	UCurveFloat* PlaceEmblemCurveFloat;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetUpComponents();
	void SetUpEmblems();
	void SetUpArrows();
	void SetUpPairs();
	
	UFUNCTION()
	void EmblemObtained(AInteractor* Interactable);

	void BindTimeline();

	UFUNCTION()
	void PlaceEmblemTick(float deltaSeconds);
	
	UFUNCTION()
	void PlaceEmblemFinished();

	UFUNCTION()
	void PlaceEmblemEndGameTick(float deltaSeconds);
	
	UFUNCTION()
	void PlaceEmblemEndGameFinished();
};
