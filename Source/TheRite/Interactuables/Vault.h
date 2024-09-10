//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Interactor.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Vault.generated.h"

UCLASS()
class THERITE_API AVault : public AInteractor
{
	GENERATED_BODY()
	
public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   // 
	//*****************************************************************************//

	//Constructor
	AVault();

	UPROPERTY(EditDefaultsOnly, Category = Visual, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* VaultMesh; 

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	class UArrowComponent* FrontArrow;
	
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

	bool bIsFocus;

	UPROPERTY(EditAnywhere, Category = Settings)
	FVector ExitingVector;
	
	UPROPERTY(EditAnywhere, Category = Settings)
	FRotator ExitingRotation;
	
	UPROPERTY(EditDefaultsOnly, Category = VFX)
	TSubclassOf<class UVaultWidget> VaultWidgetBase;
	
	class UVaultWidget* VaultWidget;

	UPROPERTY(EditDefaultsOnly, Category = VFX)
	UAnimSequence* OpenSequence;

	FTimerHandle OpeningTimerHandle;
	FTimerDelegate OpeningTimerDelegate;
	
	class AAlex* Player;
	
	//*****************************************************************************//
	//								PRIVATE METHODS								...// 
	//*****************************************************************************//
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
	UFUNCTION()
	void LeaveFocus();
	
	UFUNCTION()
	void OnVaultOpened();
};