#include "Letter.h"

ALetter::ALetter()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	LetterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Letter mesh");
	Writing = CreateDefaultSubobject<UStaticMeshComponent>("Write mesh");
	
	RootComponent = LetterMesh;
	Writing->SetupAttachment(LetterMesh);

	PointLight = CreateDefaultSubobject<UPointLightComponent>("Point Light");
	PointLight->SetupAttachment(LetterMesh);
}

void ALetter::Interaction()
{
	OnAction.Broadcast();
	Destroy();
}