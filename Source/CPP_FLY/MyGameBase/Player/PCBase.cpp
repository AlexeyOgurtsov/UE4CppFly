#include "PCBase.h"
#include "MyEngine/MyEngineHelperLib.h"
#include "MyGameBase/Pawn/I/ITrackPawnMovement.h"
#include "MyGameBase/I/IWeaponInventory.h"
#include "MyGameBase/I/IWeaponInventoryHolder.h"
#include "MyGameBase/Damage/I/DamageableHelperLib.h"
#include "MyGameBase/Player/UI/MyUIControllerComponent.h"
#include "MyGameBase/Player/Test/I/ITestController.h"

#include "Util/Component/MyComponentLib.h"

#include "GameFramework/Pawn.h"

/**
* Internal utils for PC implementation
*/
class PCHelpers
{
public:
	static FName PLAYER_PAWN_TAG;

	static void TagAsPlayerPawn(APawn* InPawn)
	{
		check(InPawn);
		InPawn->Tags.AddUnique(PLAYER_PAWN_TAG);
	}

	static void UntagAsPlayerPawn(APawn* InPawn)
	{
		check(InPawn);
		InPawn->Tags.RemoveSingleSwap(PLAYER_PAWN_TAG, /*bAllowShrinking=*/false);
	}
};
FName PCHelpers::PLAYER_PAWN_TAG { TEXT("PlayerPawn") };

APCBase::APCBase()
{
	if(IsLocalController())
	{
		UIControllerComponent = CreateDefaultSubobject<UMyUIControllerComponent>(TEXT("UIControllerComponent"));
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("Not a local controller, so we skipping creation of the UIControllerComponent"));
		UIControllerComponent = nullptr;
	}
}

void APCBase::BeginPlay()
{
	UE_LOG(MyLog, Log, TEXT("PCBase::BeginPlay; IsLocalController=%s"), (IsLocalController() ? TEXT("YES") : TEXT("no")));
	bBeginPlayAlreadyCalled = true;
	Super::BeginPlay();

	// ATTENTION: As GetComponents() does NOT return BP-added components inside the PreRegisterAllComponents,
	// we're doing it here (temporary workaround)
	ChooseComponents();

	// Binding components
	UMyComponentLib::BindAllComponentsToOwner(this);

	// At this moment the controller state is fully initialized:
	DoWhenReady();

	bool const bShouldPostponePlayerPawnReady = bPlayerPawnBegunPlay || bSetPawnAlreadyCalled;
	if(bShouldPostponePlayerPawnReady)
	{
		UE_LOG(MyLog, Log, TEXT("APCBase::BeginPlay: Player pawn was ready before the PC, so we perform initialization here"));
		PlayerPawnReady();
	}
}

void APCBase::DoWhenReady_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("PlayerController is READY"));
	UE_LOG(MyLog, Log, TEXT("Notifying components that Controller is Ready..."));
	if(auto MyComp = Cast<IMyComponent>(UIControllerComponent))
	{
		IMyComponent::Execute_OwnerReady(UIControllerComponent, this);
	}

	// Warning!!! Typically here ALL components to be notified.
	//UMyComponentLib::NotifyOwnerReady(this);
	UE_LOG(MyLog, Log, TEXT("Notifying components that Controller is Ready DONE"));
}

void APCBase::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();
}

void APCBase::ChooseComponents()
{
	// Getting all components (we need to find a component that supports a given interface)
	TArray<UActorComponent*> ChildComponents;
	GetComponents(ChildComponents);

	UE_LOG(MyLog, Log, TEXT("%d child components found"), ChildComponents.Num());
	int32 CompIndex = 0;
	for(UActorComponent* Comp : ChildComponents)
	{
		UE_LOG(MyLog, Log, TEXT("Component %d: \"%s\" of \"%s\" class found"), CompIndex , *Comp->GetName(), *Comp->GetClass()->GetName());
		CompIndex++;
	}

	// Checking which components to use
	ChooseComponent_UIControllerComponent(ChildComponents);
	ChooseComponent_TestComponent(ChildComponents);
}

void APCBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APCBase::ChooseComponent_TestComponent(const TArray<UActorComponent*>& InComponents)
{
	if(TestControllerComponent == nullptr)
	{
		UE_LOG(MyLog, Log, TEXT("TestControllerComponent is nullptr, trying to find withing array of components"));

		for(UActorComponent* Comp : InComponents)
		{
			if(auto TC = Cast<ITestController>(Comp))
			{
				if(TestControllerComponent == nullptr)
				{
			
					TestControllerComponent = Comp;
					UE_LOG(MyLog, Log, TEXT("Test component named \"%s\" of \"%s\" class found"), *Comp->GetName(), *Comp->GetClass()->GetName());
					check(TestControllerComponent);
				}
				else
				{
					check(TestControllerComponent);
					UE_LOG(MyLog, Warning, TEXT("More than one interface that implements ITestController found! The first is to be used!"));
					break;
				}
			}
			
		}
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("TestComponent is already set"));
	}

	if(TestControllerComponent == nullptr)
	{
		UE_LOG(MyLog, Warning, TEXT("TestControllerComponent NOT found"));
	}
}

void APCBase::ChooseComponent_UIControllerComponent(const TArray<UActorComponent*>& InComponents)
{
	// Finding UI Controller Component
	UIControllerComponent = nullptr;
	for(UActorComponent* Comp : InComponents)
	{
		if(UIControllerComponent == nullptr)
		{
			if(Cast<IUIControllerComponent>(Comp))
			{
				UIControllerComponent = Comp;
				UE_LOG(MyLog, Log, TEXT("UI Controller component named \"%s\" of \"%s\" class found"), *Comp->GetName(), *Comp->GetClass()->GetName());
			}
		}
		else
		{
			UE_LOG(MyLog, Warning, TEXT("More than one interface that implements IUIControllerComponent found! The first is to be used!"));
			break;
		}
	}

	// Removing the UI Controller Component if NOT locally controlled:
	if(false == IsLocalController())
	{
		if(UIControllerComponent)
		{
			UE_LOG(MyLog, Log, TEXT("Destroying UIControllerComponent: PlayerController is not local"));
			UIControllerComponent->DestroyComponent(/*bPromoteChildren*/true);
			UIControllerComponent = nullptr;
		}
	}
	else
	{
		if(UIControllerComponent == nullptr)
		{
			UE_LOG(MyLog, Warning, TEXT("Warning! No UIControllerComponent found on local player controller"));
		}
	}


	if(UIControllerComponent)
	{
		UIControllerComponent->AddTickPrerequisiteActor(this);
	}
}

void APCBase::DoSetPawn(APawn* InNewPawn, APawn* InOldPawn)
{
	const FString FuncPrefix { TEXT("DoSetPawn on PC") };

	UE_LOG(MyLog, Log, TEXT("BeginPlay: already called, so we performing the initialization here"));
	if(InOldPawn)
	{	
		MyUnsetPawn(InOldPawn);
	}

	if(InNewPawn)
	{
		const FString& PawnClassName = InNewPawn->GetClass()->GetName();
		UE_LOG(MyLog, Log, TEXT("%s: pawn to set is of class \"%s\""), *FuncPrefix, *PawnClassName);
		MySetPawn(InNewPawn);
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("%s: pawn to set is nullptr"), *FuncPrefix);
		// Nothing is to do here yet
	}	
}

void APCBase::SetPawn(APawn* InPawn) 
{
	bSetPawnAlreadyCalled = true;
	const FString FuncPrefix { TEXT("SetPawn on PC") };
	FString const PawnName = AActor::GetDebugName(InPawn);
	APawn* const OldPawn = GetPawn();
	FString const OldPawnName = AActor::GetDebugName(OldPawn);
	FString OldPawnClassName = GetPawn() ? (OldPawn->GetClass()->GetName()) : (FString(TEXT("nullptr")));
	FString NetworkString = FString::Printf
	(
		TEXT("IsLocalController=%s; HasAuthority=%s"), 
		IsLocalController() ? TEXT("YES") : TEXT("no"), 
		HasAuthority() ? TEXT("YES") : TEXT("no")
	);

	UE_LOG(MyLog, Log, TEXT("%s called with pawn \"%s\" (%s)"), *FuncPrefix, *PawnName, *NetworkString);
	UE_LOG(MyLog, Log, TEXT("%s: Old Pawn is \"%s\" of class \"%s\""), *FuncPrefix, *OldPawnName, *OldPawnClassName);

	MyOldPawn = OldPawn;
	MyNewPawn = InPawn;

	Super::SetPawn(InPawn);

	DoSetPawn(InPawn, OldPawn);	
}

void APCBase::MyUnsetPawn_Implementation(APawn* InPawn)
{
	PCHelpers::UntagAsPlayerPawn(InPawn);
}

void APCBase::MySetPawn_Implementation(APawn* InPawn)
{
	PCHelpers::TagAsPlayerPawn(InPawn);
	if(bBeginPlayAlreadyCalled)
	{
		UE_LOG(MyLog, Log, TEXT("MySetPawn: Calling PlayerPawnReady (PC's BeginPlay already called)"));
		PlayerPawnReady();
	}
}

TScriptInterface<ITrackPawnMovement> APCBase::GetPawnMovement() const
{
	return TScriptInterface<ITrackPawnMovement>(GetPawn());
}

TScriptInterface<IWeaponInventory> APCBase::GetPawnWeapons() const
{
	TScriptInterface<IWeaponInventoryHolder> PawnWeaponHolder(GetPawn());
	if(PawnWeaponHolder.GetInterface())
	{
		return PawnWeaponHolder->GetWeapons();
	}
	return nullptr;
}

TScriptInterface<IDamageableContainer> APCBase::GetPawnDamageableContainer() const
{
	return TScriptInterface<IDamageableContainer>(GetPawn());
}

TScriptInterface<IDamageable> APCBase::GetPawnDamageable() const
{
	return UDamageableHelperLib::GetDamageable(GetPawn());
}

TScriptInterface<IDamageable> APCBase::LogGetPawnDamageable() const
{
	return UDamageableHelperLib::LogGetDamageable(GetPawn());
}

TScriptInterface<IUIController> APCBase::GetUIController_Implementation() const
{
	return TScriptInterface<IUIController>(GetUIControllerComponent().GetObject());
}

TScriptInterface<IUIControllerComponent> APCBase::GetUIControllerComponent() const
{
	return TScriptInterface<IUIControllerComponent>(UIControllerComponent);
}

TScriptInterface<ITestController> APCBase::GetTestController() const
{
	return TScriptInterface<ITestController>(TestControllerComponent);
}

TScriptInterface<ITestController> APCBase::LogGetTestController() const
{
	if(nullptr == TestControllerComponent)
	{
		UE_LOG(MyLog, Warning, TEXT("TestControllerComponent is nullptr"));
		return nullptr;
	}
	auto TC = TScriptInterface<ITestController>(TestControllerComponent);
	if(nullptr == TC.GetObject())
	{
		UE_LOG(MyLog, Warning, TEXT("TScriptInterface<ITestController>(TestControllerComponent) returned nullptr"));
		return nullptr;
	}
	return TC;
}

void APCBase::Pawn_BeginPlay_Implementation() 
{
	UE_LOG(MyLog, Log, TEXT("Pawn_BeginPlay"));
	bPlayerPawnBegunPlay = true;
	if(bBeginPlayAlreadyCalled)
	{
		UE_LOG(MyLog, Log, TEXT("Calling PlayerPawnReady (PC's BeginPlay already was called)"));
		PlayerPawnReady();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("We postpone the PlayerPawn ready processing until the PC's BeginPlay is called"));
	}
}

void APCBase::PlayerPawnReady_Implementation()
{
	if(TScriptInterface<IUIControllerComponent> UIComp = GetUIControllerComponent())
	{
		IUIControllerComponent::Execute_PlayerPawnReady(UIComp.GetObject());
	}
}

void APCBase::Pawn_EndPlay_Implementation(const EEndPlayReason::Type InReason)
{
	// Nothing is to be done here yet
}

void APCBase::Pawn_DestructionStarted_Implementation()
{
	// Nothing is to be done here yet
}

void APCBase::Pawn_CharsUpdated_Implementation()
{
	// Nothing is to be done here yet
}

void APCBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	UE_LOG(MyLog, Log, TEXT("APCBase::SetupInputComponent"));
	check(InputComponent);

	InputComponent->BindAxis("LookYaw", this, &APCBase::Axis_LookYaw);
	InputComponent->BindAxis("LookPitch", this, &APCBase::Axis_LookPitch);
	InputComponent->BindAxis("LookZoom", this, &APCBase::Axis_LookZoom);

	InputComponent->BindAxis("Vertical", this, &APCBase::Axis_MoveVertical);
	InputComponent->BindAxis("Horz", this, &APCBase::Axis_MoveHorz);
	InputComponent->BindAxis("Thrust", this, &APCBase::Axis_Thrust);
	InputComponent->BindAxis("Roll", this, &APCBase::Axis_Roll);

	InputComponent->BindAction("Fire", IE_Pressed, this, &APCBase::Action_Fire);

	InputComponent->BindAction("ShowMenu", IE_Pressed, this, &APCBase::Action_ShowMenu);
	InputComponent->BindAction("ShowDebugMenu", IE_Pressed, this, &APCBase::Action_ShowDebugMenu);

	InputComponent->BindAction("Debug1", IE_Pressed, this, &APCBase::Action_Debug1);
	InputComponent->BindAction("Debug2", IE_Pressed, this, &APCBase::Action_Debug2);
	InputComponent->BindAction("Debug3", IE_Pressed, this, &APCBase::Action_Debug3);
}

void APCBase::Axis_LookPitch(float InAmount)
{
	if(InAmount)
	{
		UE_LOG(MyLog, Display, TEXT("Axis_LookPitch: not yet IMPL"));
	}
}

void APCBase::Axis_LookYaw(float InAmount)
{
	if(InAmount)
	{
		UE_LOG(MyLog, Display, TEXT("Axis_LookYaw: not yet IMPL"));
	}
}

void APCBase::Axis_LookZoom(float InAmount)
{
	if(InAmount)
	{
		UE_LOG(MyLog, Display, TEXT("Axis_LookZoom: not yet IMPL"));
	}
}

void APCBase::Axis_MoveVertical(float InAmount)
{
	if(InAmount)
	{
		if(TScriptInterface<ITrackPawnMovement> Mov = GetPawnMovement())
		{
			ITrackPawnMovement::Execute_StrafeVertical(Mov.GetObject(), InAmount);
		}
		else
		{
			UE_LOG(MyLog, Display, TEXT("ITrackPawnMovement is not supported"));
		}
	}
}

void APCBase::Axis_MoveHorz(float InAmount)
{
	if(InAmount)
	{
		if(TScriptInterface<ITrackPawnMovement> Mov = GetPawnMovement())
		{
			ITrackPawnMovement::Execute_StrafeHorz(Mov.GetObject(), InAmount);
		}
		else
		{
			UE_LOG(MyLog, Display, TEXT("ITrackPawnMovement is not supported"));
		}
	}
}

void APCBase::Axis_Thrust(float InAmount)
{
	if(InAmount)
	{
		if(TScriptInterface<ITrackPawnMovement> Mov = GetPawnMovement())
		{
			ITrackPawnMovement::Execute_Thrust(Mov.GetObject(), InAmount);
		}
		else
		{
			UE_LOG(MyLog, Display, TEXT("ITrackPawnMovement is not supported"));
		}
	}
}

void APCBase::Axis_Roll(float InAmount)
{
	if(InAmount)
	{
		if(TScriptInterface<ITrackPawnMovement> Mov = GetPawnMovement())
		{
			ITrackPawnMovement::Execute_RotateRoll(Mov.GetObject(), InAmount);
		}
		else
		{
			UE_LOG(MyLog, Display, TEXT("ITrackPawnMovement is not supported"));
		}
	}
}

void APCBase::Action_Fire()
{
	UE_LOG(MyLog, Log, TEXT("Action: Fire"));
	if(TScriptInterface<IWeaponInventory> Weapons = GetPawnWeapons())
	{
		IWeaponInventory::Execute_Fire(Weapons.GetObject(), /*WeaponIndex*/0);
	}
	else
	{
		UE_LOG(MyLog, Display, TEXT("IWeaponInventory is not supported"));
	}
}

void APCBase::Action_ShowMenu()
{
	UE_LOG(MyLog, Log, TEXT("Action: ToggleMenu"));
	if(TScriptInterface<IUIControllerComponent> UIComp = GetUIControllerComponent())
	{
		IUIControllerComponent::Execute_ToggleMenu(UIComp.GetObject());
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("Action: ToggleMenu: UIControllerComponent is nullptr"));
	}
}

void APCBase::Action_ShowDebugMenu()
{
	UE_LOG(MyLog, Log, TEXT("Action: ToggleDebugMenu"));
	if(TScriptInterface<IUIControllerComponent> UIComp = GetUIControllerComponent())
	{
		IUIControllerComponent::Execute_ToggleDebugMenu(UIComp.GetObject());
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("Action: ToggleDebugMenu: UIControllerComponent is nullptr"));
	}
}

void APCBase::Action_DebugGeneral(int32 InIndex)
{
	UE_LOG(MyLog, Log, TEXT("Action: Debug%d"), InIndex);
	if(TScriptInterface<ITestController> TC = LogGetTestController())
	{
		UE_LOG(MyLog, Warning, TEXT("Delegating test %d to TestController"), InIndex);
		ITestController::DoTest(TC.GetObject(), InIndex);
	}
}

void APCBase::Action_Debug1()
{
	Action_DebugGeneral(1);
}

void APCBase::Action_Debug2()
{
	Action_DebugGeneral(2);
}

void APCBase::Action_Debug3()
{
	Action_DebugGeneral(3);
}
