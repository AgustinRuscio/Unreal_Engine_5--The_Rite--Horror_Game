//----------------------------------------------//
// *Author		: github.com/AgustinRuscio		//
// *UE version	: UE 5.5.4						//
//----------------------------------------------//

#include "LoreInteractuable.h"
#include "Kismet/GameplayStatics.h"
#include <TheRite/AlexPlayerController.h>
#include <TheRite/Widgets/ChangingdWidget.h>

//----------------------------------------------------------------------------------------------------------------------
ALoreInteractuable::ALoreInteractuable()
{
 	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Object mesh");
	bCanInteract = true;
	bWillSound = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ALoreInteractuable::Interaction()
{
	Super::Interaction();
	
	UGameplayStatics::SpawnSound2D(GetWorld(), AudioToPlay);

	if(!LoreWidgetClass) return;

	if (auto controller = Cast<AAlexPlayerController>(GetWorld()->GetFirstPlayerController()))
		controller->PushWidget(LoreWidgetClass, true);
}