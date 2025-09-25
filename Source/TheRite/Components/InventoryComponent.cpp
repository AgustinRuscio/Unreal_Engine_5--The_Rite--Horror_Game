//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "InventoryComponent.h"
#include "Components/WidgetComponent.h"
#include "TheRite/Widgets/Inventory.h"
#include "TheRite/Widgets/WidgetsElements/InspectItem.h"
#include <Kismet/GameplayStatics.h>

namespace {
	AInspectItem* InspectedActor;
	UUserWidget* InspectWidget;
}
namespace {

	float MyPitch = 0.f;
	float MyYaw = 0.f;
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

	MyYaw = InspectedActor->GetActorRotation().Yaw;
	MyPitch = InspectedActor->GetActorRotation().Pitch;

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

	MyYaw += Vector.X * InspectSpeed;
	MyPitch += Vector.Y * InspectSpeed;

	FRotator NewRotation = FRotator(MyPitch, MyYaw, 0.f);

	InspectedActor->SetActorRotation(NewRotation);
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