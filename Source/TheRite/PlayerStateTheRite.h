//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateTheRite.generated.h"

UCLASS()
class THERITE_API APlayerStateTheRite : public APlayerState
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//

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
	class AAlexPlayerController* PlayerController;

	//*****************************************************************************//
	//								PRIVATE METHODS								   //
	//*****************************************************************************//
	virtual void BeginPlay() override;
virtual void Tick(float DeltaSeconds) override;
	UFUNCTION()
	void LoadValues();
};