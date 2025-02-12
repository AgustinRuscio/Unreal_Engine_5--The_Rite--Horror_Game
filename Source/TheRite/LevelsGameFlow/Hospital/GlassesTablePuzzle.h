//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Interactor.h"
#include "GlassesTablePuzzle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGlassReady, int8, GlasIndex);

UCLASS()
class THERITE_API AGlassesTablePuzzle : public AInteractor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AGlassesTablePuzzle();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TableMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FirstGlassMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))

	class UStaticMeshComponent* SecondGlassMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))

	class UStaticMeshComponent* ThirdGlassMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))

	class UArrowComponent* FirstGlassCorrectLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* SecondGlassCorrectLocation;

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

	FGlassReady GlassReady;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//

	void ObtainGlass();

private:

	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//

	bool bGlassReady;
	bool bSecondGlassReady;
	bool bBothReady;

	FTimeline GlassMovementTimeLine;

	UPROPERTY(EditDefaultsOnly, Category = "TimeLine")
	class UCurveFloat* TimeLineCurveFloat;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Interaction() override;

	void GlassObetain(int8 GlassIndex);

	UFUNCTION()
	void TimeLineTick(float tick);

	UFUNCTION()
	void TimeLineFinished();
};