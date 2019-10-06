#include "MyPawnBase.h"
#include "MyEngine/MyEngineHelperLib.h"
#include "MyGameBase/Controller/I/IMyController.h"
#include "MyGameBase/Damage/DamageableComponent.h"

#include "Engine/EngineTypes.h"
#include "GameFramework/DamageType.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

AMyPawnBase::AMyPawnBase()
{
	// Setting up the root scene component
	RootComponent = RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	check(RootSceneComponent);

	// ~ Camera initialization Begin
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = SpringArm->bInheritYaw = SpringArm->bInheritRoll = false;
	SpringArm->SetRelativeLocation(FVector{-400.F, 0, 500.F});
	SpringArm->TargetArmLength = 400.F;
	SpringArm->SetupAttachment(RootSceneComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	DamageableComponent = CreateDefaultSubobject<UDamageableComponent>(TEXT("Damageable"));
	// ~ Camera initialization End
}

TScriptInterface<IDamageable> AMyPawnBase::GetDamageable_Implementation() const
{
	return DamageableComponent;
}

void AMyPawnBase::SetupProximityComponentAttachment(UPrimitiveComponent* InProxComponent)
{
	checkf(RootSceneComponent, TEXT("AMyPawnBase::AttachProximityComponent: root scene component must be set before calling AttachProximityComponent"));
	checkf(nullptr == ProximityComponent, TEXT("AMyPawnBase::AttachProximityComponent: proximity component is already attached"));
	ProximityComponent = InProxComponent;
	ProximityComponent->SetupAttachment(RootSceneComponent);
}

void AMyPawnBase::BeginPlay()
{
	Super::BeginPlay();
	if(TScriptInterface<IMyController> PC = GetPC())
	{
		IMyController::Execute_Pawn_BeginPlay(PC.GetObject());
	}
}

void AMyPawnBase::EndPlay(const EEndPlayReason::Type InReason)
{
	Super::EndPlay(InReason);
	if(TScriptInterface<IMyController> PC = GetPC())
	{
		IMyController::Execute_Pawn_EndPlay(PC.GetObject(), InReason);
	}
}

float AMyPawnBase::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if(DamageableComponent)
	{
		return IDamageable::Execute_MakeDamage(DamageableComponent, NewObject<UDamageType>(DamageEvent.DamageTypeClass), DamageAmount);
	}
	return 0.0F;
}

void AMyPawnBase::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();

	DamageableComponent = FindComponentByClass<UDamageableComponent>();
	if(DamageableComponent == nullptr)
	{
		UE_LOG(MyLog, Warning, TEXT("No damageable component found for pawn \"%s\""), *GetName());
	}
}

void AMyPawnBase::PostInitializeComponents()
{
	UE_LOG(MyLog, Log, TEXT("AMyPawnBase::PostInitializeComponents"));
	Super::PostInitializeComponents();

	if(DamageableComponent)
	{
		PostInitialize_DamageableComponent(DamageableComponent);
	}

	// Here we should NOT initialize the proximity component with the first found primitive component,
	// because not necessarily any primitive component is proximity component;
	if(ProximityComponent)
	{
		PostInitialize_ProximityComponent(ProximityComponent);
	}
}

TScriptInterface<IMyController> AMyPawnBase::GetPC() const
{
	return TScriptInterface<IMyController>(Controller);
}

void AMyPawnBase::PostInitialize_DamageableComponent(UDamageableComponent* InComponent)
{
	if(UDamageableEvents* TheEvents = IDamageable::Execute_GetEvents(InComponent))
	{
		TheEvents->StateChanged.AddDynamic(this, &AMyPawnBase::OnDamageableComponent_DamageStateChanged);
	}
	else
	{
		UE_LOG(MyLog, Warning, TEXT("GetEvents returned nullptr for the given damageable component"));
	}
}

void AMyPawnBase::PostInitialize_ProximityComponent(UPrimitiveComponent* InComponent)
{
	InComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyPawnBase::OnProximityComponent_BeginOverlap);
	InComponent->OnComponentEndOverlap.AddDynamic(this, &AMyPawnBase::OnProximityComponent_EndOverlap);
}

void AMyPawnBase::OnProximityComponent_BeginOverlap
(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
)
{
	// @TODO: Notify controller about pickups;
}

void AMyPawnBase::OnProximityComponent_EndOverlap
(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent, 
	int32 OtherBodyIndex
)
{
	// @TODO: Notify controller about pickups;
}

void AMyPawnBase::OnDamageableComponent_DamageStateChanged(const FDamageableStateChangedParams& InParams)
{
	if(TScriptInterface<IMyController> PC = GetPC())
	{
		IMyController::Execute_Pawn_CharsUpdated(PC.GetObject());

		if(InParams.bFatallyDamaged)	
		{
			IMyController::Execute_Pawn_DestructionStarted(PC.GetObject());
		}
	}
}