#include "MyPawnBase.h"
#include "MyEngine/MyEngineHelperLib.h"
#include "MyGameBase/Controller/I/IMyController.h"
#include "MyGameBase/Damage/DamageableComponent.h"
#include "Util/Weapon/QuickWeaponComponent/QuickWeaponComponent.h"

#include "Engine/EngineTypes.h"
#include "GameFramework/DamageType.h"
#include "Components/ShapeComponent.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

#include "Engine/World.h"

#include "Util/Core/LogUtilLib.h"

AMyPawnBase::AMyPawnBase()
{
	DamageableComponent = CreateDefaultSubobject<UDamageableComponent>(TEXT("Damageable"));
	WeaponComponent = CreateOptionalDefaultSubobject<UQuickWeaponComponent>(TEXT("QuickWeaponComponent"));
}

void AMyPawnBase::SetupDefaultComponents(UPrimitiveComponent* InProxComponent, class UMeshComponent* InRootMeshComponent)
{
	checkf(InProxComponent, TEXT("Assigned proximity component must always be valid"));
	checkf(nullptr == ProximityComponent, TEXT("Proximity component is already attached"));
	checkf(InRootMeshComponent, TEXT("Root mesh component should never be nullptr"));

	RootComponent = InRootMeshComponent;
	SetupDefaultRootSceneAndComponents(InRootMeshComponent);
	InProxComponent->SetupAttachment(InRootMeshComponent);
}

void AMyPawnBase::SetupDefaultRootSceneAndComponents(USceneComponent* const AttachTo)
{
	checkf(AttachTo, TEXT("Component to attach to must be set"));

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));

	// WRONG solution!
	// Set so that root scene component is never transformed
	// when the root collision mesh is transformed
	// (transform is to be relative to mesh, rather than relative to parent component).
	//RootSceneComponent->SetAbsolute(true, true, true);

	RootSceneComponent->SetupAttachment(AttachTo);

	SetupDefaultCameraComponents(RootSceneComponent);
}

void AMyPawnBase::SetupDefaultCameraComponents(USceneComponent* const AttachTo)
{
	checkf(AttachTo, TEXT("Component to attach to must be set"));

	// ~ Camera initialization Begin
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = SpringArm->bInheritYaw = SpringArm->bInheritRoll = true;
	SpringArm->SetRelativeLocation(FVector{ -400.F, 0, 500.F });
	SpringArm->TargetArmLength = 400.F;
	SpringArm->SetupAttachment(AttachTo);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	// ~ Camera initialization End
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
	if(GetWorld()->IsGameWorld())
	{
		if(DamageableComponent)
		{
			return IDamageable::Execute_MakeDamage(DamageableComponent, NewObject<UDamageType>(DamageEvent.DamageTypeClass), DamageAmount);
		}
	}
	return 0.0F;
}

void AMyPawnBase::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();

	FindComponents();
}

void AMyPawnBase::FindComponents()
{
	FindDamageableComponent();
	FindWeaponComponent();
	FindProximityComponent();
}

void AMyPawnBase::FindDamageableComponent()
{
	DamageableComponent = FindComponentByClass<UDamageableComponent>();
	if (DamageableComponent == nullptr)
	{
		UE_LOG(MyLog, Warning, TEXT("No damageable component found for pawn \"%s\""), *GetName());
	}
}

void AMyPawnBase::FindWeaponComponent()
{
	WeaponComponent = FindComponentByClass<UWeaponComponent>();
	if (WeaponComponent == nullptr)
	{
		UE_LOG(MyLog, Warning, TEXT("No weapon component found for pawn \"%s\""), *GetName());
	}
}

void AMyPawnBase::FindProximityComponent()
{
	ProximityComponent = FindComponentByClass<UShapeComponent>();
	if (ProximityComponent == nullptr)
	{
		UE_LOG(MyLog, Warning, TEXT("No proximity component found for pawn \"%s\""), *GetName());
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

void AMyPawnBase::PostInitialize_DamageableComponent(UDamageableComponent* InComponent)
{
	if(GetWorld()->IsGameWorld())
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
}

void AMyPawnBase::PostInitialize_ProximityComponent(UShapeComponent* InComponent)
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
	checkf(GetWorld()->IsGameWorld(), TEXT("This function should only be called in Game-type worlds!"));
	if(TScriptInterface<IMyController> PC = GetPC())
	{
		IMyController::Execute_Pawn_CharsUpdated(PC.GetObject());

		if(InParams.bFatallyDamaged)	
		{
			IMyController::Execute_Pawn_DestructionStarted(PC.GetObject());
		}
	}
}

TScriptInterface<IWeaponInventory> AMyPawnBase::GetWeapons_Implementation() const
{
	return TScriptInterface<IWeaponInventory>(WeaponComponent);
}

UQuickWeaponComponent* AMyPawnBase::GetQuickWeaponComponent() const
{
	return Cast<UQuickWeaponComponent>(WeaponComponent);
}

UQuickWeaponComponent* AMyPawnBase::GetQuickWeaponComponentChecked() const
{
	return CastChecked<UQuickWeaponComponent>(WeaponComponent);
}


TScriptInterface<IDamageable> AMyPawnBase::GetDamageable_Implementation() const
{
	return DamageableComponent;
}

TScriptInterface<IMyController> AMyPawnBase::GetPC() const
{
	return TScriptInterface<IMyController>(Controller);
}