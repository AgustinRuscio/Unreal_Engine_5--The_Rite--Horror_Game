//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Fader.generated.h"

class UFadeObjectComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActivation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeactivation);

UINTERFACE(MinimalAPI)
class UFader : public UInterface
{
	GENERATED_BODY()
};

class THERITE_API IFader
{
	GENERATED_BODY()

public:
	//*****************************************************************************//
	//								PUBLIC VARIABLES							   //
	//*****************************************************************************//
	FOnActivation OnActivate;
	FOnDeactivation OnDeactivate;

	//*****************************************************************************//
	//								PUBLIC METHODS								   //
	//*****************************************************************************//
	AActor* GetActor() const;
	
	void OnFadeActivate() const;
	void OnFadeDeActivate() const;
	
	void SetAlpha(float alpha) const;

protected:
	//*****************************************************************************//
	//								PROTECTED METHODS							   //
	//*****************************************************************************//
	void SetFaderComponent(UFadeObjectComponent* FaderComponent);
	void SetActor(AActor* Parent);

private:
	//*****************************************************************************//
	//								PRIVATE VARIABLES							   //
	//*****************************************************************************//
	AActor* Parentactor;
	UFadeObjectComponent* FadeComponent;
};