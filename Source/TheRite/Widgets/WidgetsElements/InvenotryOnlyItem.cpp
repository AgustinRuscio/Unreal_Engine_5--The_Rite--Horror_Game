//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "InvenotryOnlyItem.h"

//----------------------------------------------------------------------------------------------------------------------
AInvenotryOnlyItem::AInvenotryOnlyItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

//----------------------------------------------------------------------------------------------------------------------
void AInvenotryOnlyItem::BeginPlay()
{
	Super::BeginPlay();
	OnItemAddedToInventory.Broadcast();
}