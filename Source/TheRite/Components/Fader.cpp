//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Fader.h"
#include "FadeObjectComponent.h"

AActor* IFader::GetActor()
{
	return Parentactor;
}

void IFader::OnFadeActivate()
{
	FadeComponent->ActivateFade();
	OnActivate.Broadcast();
}

void IFader::OnFadeDeActivate()
{
	FadeComponent->DeActivateFade();
	OnDeactivate.Broadcast();
}

void IFader::SetAlpha(float alpha)
{
	FadeComponent->SetMaterialAlpha(alpha);
}

void IFader::SetFaderComponent(UFadeObjectComponent* FaderComponent)
{
	FadeComponent = FaderComponent;
}

void IFader::SetActor(AActor* Parent)
{
	Parentactor = Parent;
}
