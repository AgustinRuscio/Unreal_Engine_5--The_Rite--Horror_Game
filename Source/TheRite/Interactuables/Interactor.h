//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "IInteractuable.h"
#include "GameFramework/Actor.h"
#include "Interactor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractionTrigger, AInteractor*, myself);

UCLASS()


class THERITE_API AInteractor : public AActor, public IIInteractuable
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//						CONSTRUCTOR & PUBLIC COMPONENTS						   //
	//*****************************************************************************//
	//Constructor
	AInteractor();

	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FInteractionTrigger OnInteractionTrigger;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
//---------------- Getter Methods
	virtual bool IsPickable() const override;
	virtual bool IsMainItem() const override;
	virtual bool GetCanInteract() const override;
	virtual bool IsRemovable() const override;
	
	UFUNCTION(BlueprintCallable)
	virtual FString GetItemName() const override;
	
	UFUNCTION(BlueprintCallable)
	virtual FString GetItemDescription() const override;

	UFUNCTION(BlueprintCallable)
	virtual PickableItemsID GetItemID() const override;
	
	UFUNCTION()
	virtual USoundBase* GetSound() const override;
	
	UFUNCTION()
	virtual FInventoryItemData GetItemInventoryData() const override;

	virtual TTuple<bool, FString, PickableItemsID> CheckRemove() const override;

//---------------- System Class Methods
	UFUNCTION()
	virtual void Interaction() override;

//---------------- Setter Methods
	void SetCanInteract(bool newInteractionState);
	void SetCanWillSound(bool newWillSoundState);
	void SetAudioToPlay(USoundBase* NewAudio);
	
	virtual void Deactivate() override;
	virtual void Activate() override;
	
	virtual void Dissapear();
	virtual void Appear();

	//*****************************************************************************//
	//								PROTECTED VARIABLES							   //
	//*****************************************************************************//
protected:
	UPROPERTY(EditAnywhere, Category="State")
	bool bCanInteract;
	
	UPROPERTY(EditAnywhere, Category="State")
	bool bWillSound;
	
	UPROPERTY(EditAnywhere, Category="State")
	FInventoryItemData IntemInventoryData;

	UPROPERTY(EditAnywhere, Category="State")
	USoundBase* AudioToPlay;
	
	UPROPERTY(EditAnywhere, Category= "Audio")
	USoundBase* SFX_GrabItem;
	
private:	
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	bool bIsPickeable;
	
	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	bool bIsRemovable;
	
	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	bool bIsMainItem;

	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	FString DisplayName;
	
	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	FString DisplayDescription;

	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	PickableItemsID ItemID;
};