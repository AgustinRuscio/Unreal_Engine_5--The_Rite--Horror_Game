//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "FadeObjectComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "MathUtil.h"

//*****************************Public********************************************
//*******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
UFadeObjectComponent::UFadeObjectComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Action Methods
void UFadeObjectComponent::SetMaterialAlpha(float alpha) const
{
	if(bFading || bPermanentTurnedOn) return;
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),alpha);
}

//----------------------------------------------------------------------------------------------------------------------
void UFadeObjectComponent::ActivateFade()
{
	if(bPermanentTurnedOn) return;
	
	bFading = true;
	FadeTimeLine.Stop();
	FadeTimeLine.PlayFromStart();
}

//----------------------------------------------------------------------------------------------------------------------
void UFadeObjectComponent::DeActivateFade()
{
	if(bPermanentTurnedOn) return;
	
	bFading = true;
	FadeTimeLine.Stop();

	FadeTimeLine.ReverseFromEnd();
}

//----------------------------------------------------------------------------------------------------------------------
void UFadeObjectComponent::PermanentActivation()
{
	bPermanentTurnedOn = true;
	
	FadeTimeLine.Stop();
	FadeTimeLine.PlayFromStart();
}
#pragma endregion

//*****************************Private********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void UFadeObjectComponent::BeginPlay()
{
	Super::BeginPlay();
	BindTimeLine();

	ObtainOwnerMaterial();
}

//----------------------------------------------------------------------------------------------------------------------
void UFadeObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FadeTimeLine.TickTimeline(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
void UFadeObjectComponent::ObtainOwnerMaterial()
{
	GetOwner()->GetComponents<UMeshComponent>(OwnerMesh);
	Material = OwnerMesh[0]->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	OwnerMesh[0]->SetMaterial(0, DynamicMaterial);
	
	DeActivateFade();
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region TimeLine Methods
void UFadeObjectComponent::BindTimeLine()
{
	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("FadeTick"));
	FadeTimeLine.AddInterpFloat(FadeCurve, CameraTargetTick);
	
	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("FadeFinished"));
	FadeTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

//----------------------------------------------------------------------------------------------------------------------
void UFadeObjectComponent::FadeTick(float deltaSeconds)
{
	float value = FMathf::Lerp(0,1.f,deltaSeconds);
	
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),value);
}

//----------------------------------------------------------------------------------------------------------------------
void UFadeObjectComponent::FadeFinished()
{
	bFading = false;
	
	if(!bPermanentTurnedOn) return;
	
	DynamicMaterial->SetScalarParameterValue(TEXT("Alpha"),1);
}
#pragma endregion 