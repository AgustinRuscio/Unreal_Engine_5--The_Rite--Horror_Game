//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VaultWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCodeCorrect);

UCLASS()
class THERITE_API UVaultWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintCallable)
	FOnCodeCorrect OnCodeCorrect;
};