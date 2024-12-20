//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


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
	AActor* GetActor() const;
	
	void OnFadeActivate() const;
	void OnFadeDeActivate() const;
	
	void SetAlpha(float alpha) const;

protected:
	void SetFaderComponent(UFadeObjectComponent* FaderComponent);
	void SetActor(AActor* Parent);

public:
	FOnActivation OnActivate;
	FOnDeactivation OnDeactivate;

private:
	AActor* Parentactor;
	UFadeObjectComponent* FadeComponent;
};
