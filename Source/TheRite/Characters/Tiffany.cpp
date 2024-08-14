//--------------------------------------------
//			Made by	Agustin Ruscio
//--------------------------------------------


#include "Tiffany.h"

#include "Components/AudioComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TheRite/AI/TiffanyController.h"
#include "AIController.h"
#include "Components/SphereComponent.h"
#include "Engine/TargetPoint.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TheRite/AmbientObjects/LightsTheRite.h"

//*****************************Public********************************************
//*******************************************************************************

//----------------------------------------------------------------------------------------------------------------------
ATiffany::ATiffany()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->InitSphereRadius(305.0f);
	Sphere->SetupAttachment(GetMesh());
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ATiffany::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ATiffany::OnOverlapEnd);

	GetMesh()->SetMobility(EComponentMobility::Movable);
	
	CryingAudio = CreateDefaultSubobject<UAudioComponent>("Crying");
	CryingAudio->SetupAttachment(GetMesh());
}

//----------------------------------------------------------------------------------------------------------------------
bool ATiffany::GetWalkingState() const
{
	return bWalking;
}

//----------------------------------------------------------------------------------------------------------------------
bool ATiffany::SetHasToMove(bool hasToMoveState) const
{
	return bHasToMove;
}

//----------------------------------------------------------------------------------------------------------------------
void ATiffany::StartMovement(ATargetPoint* newTarget)
{
	bWalking = true;
	
	BlackBoard->SetValueAsObject(TargetKey, newTarget);
	BlackBoard->SetValueAsBool(BooleanKey, true);
}

//----------------------------------------------------------------------------------------------------------------------
void ATiffany::SetData(bool IsVisible, bool NoCollision, bool HasToMove)
{
	GetMesh()->SetVisibility(IsVisible);

	if(NoCollision)
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bHasToMove = HasToMove;
}

//----------------------------------------------------------------------------------------------------------------------
void ATiffany::SetWaypoints(TArray<ATargetPoint*> targets)
{
	Waypoints = targets;
}

//----------------------------------------------------------------------------------------------------------------------
void ATiffany::Activate() const
{
	GetMesh()->SetVisibility(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
}

//----------------------------------------------------------------------------------------------------------------------
void ATiffany::Deactivate() const
{
	GetMesh()->SetVisibility(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

//*****************************Private********************************************
//********************************************************************************

//----------------------------------------------------------------------------------------------------------------------
void ATiffany::BeginPlay()
{
	Super::BeginPlay();
	auto AIController = CastChecked<ATiffanyController>(GetController());
	
	BlackBoard = AIController->GetBlackboardComponent();
}

//----------------------------------------------------------------------------------------------------------------------
#pragma region Collider Methods
void ATiffany::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(static_cast<EObjectTypeQuery>(ECollisionChannel::ECC_WorldDynamic));
	
	TArray<AActor*> IgnoredTargtes;

	IgnoredTargtes.Add(this);
	
	TArray<AActor*> OutTragtes;

	FVector StartPosition = GetActorLocation();
	
	bool overlaped = UKismetSystemLibrary::SphereOverlapActors(this, StartPosition, 500.0f,
		ObjectTypes,ALightsTheRite::StaticClass(),IgnoredTargtes, OutTragtes);

	if(overlaped)
	{
		for (auto ObjectType : OutTragtes)
		{
			auto light = CastChecked<ALightsTheRite>(ObjectType);
			light->SetAggressiveMaterial();
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ATiffany::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(static_cast<EObjectTypeQuery>(ECollisionChannel::ECC_WorldDynamic));
	
	TArray<AActor*> IgnoredTargtes;

	IgnoredTargtes.Add(this);
	
	TArray<AActor*> OutTragtes;

	FVector StartPosition = GetActorLocation();
	
	bool overlaped = UKismetSystemLibrary::SphereOverlapActors(this, StartPosition, 500.0f,
		ObjectTypes,ALightsTheRite::StaticClass(),IgnoredTargtes, OutTragtes);

	if(overlaped)
	{
		for (auto ObjectType : OutTragtes)
		{
			auto light = Cast<ALightsTheRite>(ObjectType);
			light->SetNormalMaterial();
		}
	}
}
#pragma endregion 