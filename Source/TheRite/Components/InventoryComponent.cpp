//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "InventoryComponent.h"
#include "Components/WidgetComponent.h"
#include "TheRite/Widgets/Inventory.h"
#include "TheRite/Widgets/WidgetsElements/InspectItem.h"
#include <Kismet/GameplayStatics.h>

namespace
{
	AInspectItem* InspectedActor;
	UUserWidget* InspectWidget;
}

//----------------------------------------------------------------------------------------------------------------------
UInventoryComponent::UInventoryComponent() : InventoryZOrder(2), InspectSpeed(5.f), InventoryWidgetClass(nullptr), PlayerInventory(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
bool UInventoryComponent::DoesInvetoryHasSpace() const
{
	return PlayerInventory->CanRecieveItem();
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::ToggleInventory(bool visible)
{
	visible ? PlayerInventory->AddToViewport(InventoryZOrder) : PlayerInventory->RemoveFromParent();
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::AddItem(const FInventoryItemData& ItemData)
{
	PlayerInventory->PushItemToGrid(ItemData);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::RemoveItem(const FInventoryItemData& id)
{
	PlayerInventory->RemoveItem(id);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::InspectItem(const FInventoryItemData& id)
{
	auto mesh = id.InspectMesh;

	auto cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	const FVector finalLocation = cameraManager->GetCameraLocation() + cameraManager->GetActorForwardVector() * id.CameraDistance;
	FActorSpawnParameters params;
	params.Owner = GetOwner();

	InspectedActor = GetWorld()->SpawnActor<AInspectItem>(InspecItemClass, finalLocation, FRotator::ZeroRotator, params);
	InspectedActor->SetMesh(mesh);

	PlayerInventory->SetVisibility(ESlateVisibility::Collapsed);

	InspectWidget->AddToViewport(InventoryZOrder);
	InspectWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

	OnInspectItem.Broadcast(true);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::LeaveInspection()
{
	PlayerInventory->SetVisibility(ESlateVisibility::Visible);
	InspectedActor->Destroy();

	InspectWidget->RemoveFromParent();

	OnInspectItem.Broadcast(false);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::MoveInspetedItem(FVector2D Vector)
{
	if (!InspectedActor) return;

	InspectedActor->MoveMesh(Vector, InspectSpeed);
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	CreateInventoryWidget();
}

//----------------------------------------------------------------------------------------------------------------------
void UInventoryComponent::CreateInventoryWidget()
{
	PlayerInventory = CreateWidget<UInventory>(GetWorld(), InventoryWidgetClass);
	PlayerInventory->OnItemInspected.AddDynamic(this, &UInventoryComponent::InspectItem);

	InspectWidget = CreateWidget<UUserWidget>(GetWorld(), InspectWidgetClass);
}