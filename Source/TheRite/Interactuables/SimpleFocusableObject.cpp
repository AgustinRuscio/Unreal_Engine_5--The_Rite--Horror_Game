//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "SimpleFocusableObject.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Characters/Alex.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"
#include "CommonActivatableWidget.h"
#include "Kismet/GameplayStatics.h"

namespace 
{
	FVector InitialPlayerLocation;
}

//----------------------------------------------------------------------------------------------------------------------
ASimpleFocusableObject::ASimpleFocusableObject()
{
	PrimaryActorTick.bCanEverTick = false;

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>("Object Mesh");
	RootComponent = ObjectMesh;
	
	CameraLocation = CreateDefaultSubobject<UArrowComponent>("Camera Arrow");
	CameraLocation->SetupAttachment(ObjectMesh);
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleFocusableObject::BeginPlay()
{
	Super::BeginPlay();

	Player = CastChecked<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleFocusableObject::Interaction()
{
	if (bIsFocus || !bCanInteract) return;

	Player->OnFocusMode(CameraLocation->GetComponentTransform(), ExittingRotation, bShowDefaultWidgets, false);

	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetFocusInput();

	controller->OnLeaveFocus.AddDynamic(this, &ASimpleFocusableObject::LeaveFocus);

	bIsFocus = true;

	if (DisplayedWidgetBase != nullptr)
	{
		DisplatedWidget = controller->PushWidget(DisplayedWidgetBase);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleFocusableObject::LeaveFocus()
{
	if (!bCanInteract || Player->GetFocusingState()) return;

	bIsFocus = false;

	Player->BackToNormalView(CameraLocation->GetComponentTransform(), ExittingVector,ExittingRotation);

	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetNormalInput();

	if (DisplatedWidget != nullptr)
		controller->RemoveWidget(DisplatedWidget);

	controller->OnLeaveFocus.RemoveDynamic(this, &ASimpleFocusableObject::LeaveFocus);
}