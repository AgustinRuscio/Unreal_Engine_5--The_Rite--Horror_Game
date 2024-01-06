#include "Letter.h"

ALetter::ALetter()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	LetterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Letter mesh");
	Writing = CreateDefaultSubobject<UStaticMeshComponent>("Write mesh");
	
	RootComponent = LetterMesh;
	Writing->SetupAttachment(LetterMesh);

	PointLight = CreateDefaultSubobject<UPointLightComponent>("Point Light");
}

void ALetter::Interaction()
{
	OnAction.Broadcast();
	Destroy();
}