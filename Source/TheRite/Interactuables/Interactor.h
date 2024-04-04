//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "IInteractuable.h"
#include "GameFramework/Actor.h"
#include "TheRite/Widgets/Inventory.h"
#include "Interactor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractionTrigger);

UCLASS()


class THERITE_API AInteractor : public AActor, public IIInteractuable
{
	GENERATED_BODY()
	
private:	
	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	bool bIsPickeable;

	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	FString DisplayName;
	
	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	PickableItemsID ItemID;
	
	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	bool bIsRemovable;
	
	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	bool bIsMainItem;
	
protected:
	UPROPERTY(EditAnywhere, Category="State")
	USoundBase* AudioToPlay;

	UPROPERTY(EditAnywhere, Category="State")
	bool bCanInteract;
	
	UPROPERTY(EditAnywhere, Category="State")
	bool bWillSound;

public:
	AInteractor();
	
	UFUNCTION()
	virtual void Interaction() override;
	
	virtual bool IsPickable() const override;
	virtual bool IsMainItem() const override;
	virtual FString GetItemName() const override;
	virtual PickableItemsID GetItemID() const override;
	virtual bool IsRemovable() override;

	virtual TTuple<bool, FString, PickableItemsID> CheckRemove() override;
	
	virtual void SetPickeableSettings(bool isPickeable, FString nameToDisplay, PickableItemsID id) override;
	
	UFUNCTION()
	virtual USoundBase* GetSound() override;

	FInteractionTrigger OnInteractionTrigger;
};