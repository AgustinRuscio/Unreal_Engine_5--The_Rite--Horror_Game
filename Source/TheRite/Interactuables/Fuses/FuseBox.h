//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "EnumsContainer.generated.h"
#include "GameFramework/Actor.h"
#include "TheRite/Interactuables/Interactor.h"
#include "FuseBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFuseBoxCompleted);

class UArrowComponent;
class ALightSwitch;
class UNiagaraSystem;

UCLASS()
class THERITE_API AFuseBox : public AInteractor
{
	GENERATED_BODY()
	
public:	
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AFuseBox();
	
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FFuseBoxCompleted OnFuseBoxComplete;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	virtual void Interaction() override;

	void GrabFusible(FString FuseName, PickableItemsID FuseId);
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	bool bHastFusibleToPut;
	bool bBothFusesSameTime;

	UPROPERTY(EditAnywhere, Category="Settings")
	int MaxFusesQuantity = 0;
	int FusesQuantity = 0;

	TArray<FString> FusesNames;
	TArray<PickableItemsID> FusesId;
	
	
//-------- Meshes Collider
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* FusibleBoxMesh;
	
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* FirstFusible;
	
	UPROPERTY(EditAnywhere, Category = "Mesh", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* SecondsFusible;
	
//-------- Niagara System
	UPROPERTY(EditAnywhere, Category = "Niagara", meta=(AllowPrivateAccess = true))
	UNiagaraSystem* NiagaraSytem_Sparks;
	
//-------- Arrow
	UPROPERTY(EditAnywhere, Category = "Arrow", meta=(AllowPrivateAccess = true))
	UArrowComponent* InitialPosition;
	
	UPROPERTY(EditAnywhere, Category = "Arrow", meta=(AllowPrivateAccess = true))
	UArrowComponent* EndFirstPosition;
	
	UPROPERTY(EditAnywhere, Category = "Arrow", meta=(AllowPrivateAccess = true))
	UArrowComponent* EndSecondPosition;
	
//-------- Audio
	UPROPERTY(EditAnywhere, Category = "Feed back", meta=(AllowPrivateAccess = true))
	USoundBase* SFX_Sparking;

//-------- Time line
	FTimeline LocateFusibleTimeLine;
	
	UPROPERTY(EditAnywhere, Category = "Timeline", meta=(AllowPrivateAccess = true))
	UCurveFloat* LocateFusibleCurve;

	UPROPERTY(EditAnywhere, Category = "Timeline", meta=(AllowPrivateAccess = true))
	ALightSwitch* ThermalSwitch;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
//--------------------- TimeLine methods
	UFUNCTION()
	void LocateFusibleTick(float deltaSeconds);
	
	UFUNCTION()
	void LocateFusibleFinished();
};