//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "SimpleFocusableObject.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Characters/Alex.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

namespace 
{
	FVector InitialPlayerLocation;
}

//----------------------------------------------------------------------------------------------------------------------
ASimpleFocusableObject::ASimpleFocusableObject()
{
	PrimaryActorTick.bCanEverTick = true;

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>("Object Mesh");
	RootComponent = ObjectMesh;
	
	CameraLocation = CreateDefaultSubobject<UArrowComponent>("Camera Arrow");
	CameraLocation->SetupAttachment(ObjectMesh);

	PlayerLocationComp = CreateDefaultSubobject<UArrowComponent>("Player Arrow");
	PlayerLocationComp->SetupAttachment(ObjectMesh);
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

	PlayerLocationComp->SetWorldLocation(Player->GetActorLocation());

	Player->OnFocusMode(CameraLocation->GetComponentTransform(), ExittingRotation, false);


	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetFocusInput();

	controller->OnLeaveFocus.AddDynamic(this, &ASimpleFocusableObject::LeaveFocus);

	bIsFocus = true;

}

//----------------------------------------------------------------------------------------------------------------------
void ASimpleFocusableObject::LeaveFocus()
{
	if (!bCanInteract || Player->GetFocusingState()) return;

	bIsFocus = false;

	Player->BackToNormalView(PlayerLocationComp->GetComponentTransform(), ExittingVector, ExittingRotation);

	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetNormalInput();

	controller->OnLeaveFocus.RemoveDynamic(this, &ASimpleFocusableObject::LeaveFocus);
}