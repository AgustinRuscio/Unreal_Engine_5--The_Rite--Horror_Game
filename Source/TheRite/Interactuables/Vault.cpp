//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.2.1						//
//----------------------------------------------//

#include "Vault.h"

#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TheRite/AlexPlayerController.h"
#include "TheRite/Characters/Alex.h"
#include "TheRite/Widgets/VaultWidget.h"

//----------------------------------------------------------------------------------------------------------------------
AVault::AVault()
{
	PrimaryActorTick.bCanEverTick = true;

	VaultMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Vault Mesh");

	FrontArrow = CreateDefaultSubobject<UArrowComponent>("Front Arrow");
	FrontArrow->SetupAttachment(VaultMesh);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	WidgetComponent->SetupAttachment(VaultMesh);
}

//----------------------------------------------------------------------------------------------------------------------
void AVault::Interaction()
{
	if(bIsFocus || !bCanInteract) return;

	Player->OnFocusMode(FrontArrow->GetComponentTransform(), GetActorRotation(), false);
	
	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetFocusInput();
	controller->SetNewCursorVisibilityState(true);
	controller->OnLeaveFocus.AddDynamic	(this, &AVault::LeaveFocus);
	
	bIsFocus = true;
	
	VaultMesh->PlayAnimation(OpenSequence, false);

	if(!GetWorld()->GetTimerManager().IsTimerActive(OpeningTimerHandle))
	{
		OpeningTimerDelegate.BindLambda([&]
		{
			VaultMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
			bCanInteract = false;
			LeaveFocus();
		});
		
		GetWorld()->GetTimerManager().SetTimer(OpeningTimerHandle, OpeningTimerDelegate,OpenSequence->GetPlayLength(),false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AVault::BeginPlay()
{
	Super::BeginPlay();

	VaultWidget = Cast<UVaultWidget>(WidgetComponent->GetUserWidgetObject());
	VaultWidget->OnCodeCorrect.AddDynamic(this, &AVault::OnVaultOpened);
	
	Player = CastChecked<AAlex>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

//----------------------------------------------------------------------------------------------------------------------
void AVault::BeginDestroy()
{
	Super::BeginDestroy();

	if(GetWorld())
	{
		if(GetWorld()->GetTimerManager().IsTimerActive(OpeningTimerHandle))
			GetWorld()->GetTimerManager().ClearTimer(OpeningTimerHandle);
	}

	if(OpeningTimerDelegate.IsBound())
	{
		OpeningTimerDelegate.Unbind();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AVault::LeaveFocus()
{
	bIsFocus = false;
	Player->BackToNormalView(FrontArrow->GetComponentTransform(), ExitingVector, ExitingRotation);
	
	auto controller = Cast<AAlexPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetNormalInput();
	controller->SetNewCursorVisibilityState(false);
	
	controller->OnLeaveFocus.RemoveDynamic(this, &AVault::LeaveFocus);
}

//----------------------------------------------------------------------------------------------------------------------
void AVault::OnVaultOpened()
{
	VaultWidget->OnCodeCorrect.RemoveDynamic(this, &AVault::OnVaultOpened);
	WidgetComponent->DestroyComponent();

	bCanInteract = true;
}