//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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
	AInteractor();

//---------------- Getter Methods
	virtual bool IsPickable() const override;
	virtual bool IsMainItem() const override;
	virtual bool IsRemovable() override;
	virtual bool GetCanInteract() override;
	
	virtual FString GetItemName() const override;
	virtual PickableItemsID GetItemID() const override;
	
	virtual TTuple<bool, FString, PickableItemsID> CheckRemove() override;
	
	UFUNCTION()
	virtual USoundBase* GetSound() override;

//---------------- System Class Methods
	UFUNCTION()
	virtual void Interaction() override;

//---------------- Setter Methods
	void SetCanInteract(bool newInteractionState);
	void SetCanWillSound(bool newWillSoundState);
	void SetAudioToPlay(USoundBase* NewAudio);
	
	virtual void SetPickeableSettings(bool isPickeable, FString nameToDisplay, PickableItemsID id) override;

	virtual void Deactivate() override;
	virtual void Activate() override;
public:
	FInteractionTrigger OnInteractionTrigger;
	
protected:
	UPROPERTY(EditAnywhere, Category="State")
	bool bCanInteract;
	
	UPROPERTY(EditAnywhere, Category="State")
	bool bWillSound;
	
	UPROPERTY(EditAnywhere, Category="State")
	USoundBase* AudioToPlay;
	
	UPROPERTY(EditAnywhere, Category= "Audio")
	USoundBase* SFX_GrabItem;
	
private:	
	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	bool bIsPickeable;
	
	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	bool bIsRemovable;
	
	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	bool bIsMainItem;

	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	FString DisplayName;
	
	UPROPERTY(EditAnywhere, Category = "Interactor Settings")
	PickableItemsID ItemID;
};