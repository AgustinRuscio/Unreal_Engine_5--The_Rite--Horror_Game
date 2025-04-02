//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateTheRite.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerValuesLoaded, APlayerStateTheRite*, PlayerState);

UCLASS()
class THERITE_API APlayerStateTheRite : public APlayerState
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FPlayerValuesLoaded OnPlayerValuesLoaded;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	UFUNCTION(BlueprintCallable)
	void SetMouseSensitivity(float NewSensitivity);
	
	UFUNCTION(BlueprintCallable)
	float GetMouseSensitivity() const;
	
private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	
	float MouseSensitivity;

	class ALevelsGameState* GameState;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;

	UFUNCTION()
	void LoadValues();
};