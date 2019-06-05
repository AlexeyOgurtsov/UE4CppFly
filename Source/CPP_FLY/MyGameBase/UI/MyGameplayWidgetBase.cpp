#include "MyGameplayWidgetBase.h"

#include "I/IUIController.h"

#include "MyGameBase/Damage/I/IDamageableContainer.h"
#include "MyGameBase/Damage/I/IDamageable.h"
#include "MyGameBase/Pawn/I/ITrackPawnMovement.h"
#include "MyGameBase/I/IWeaponInventory.h"

#include "MySys/HelperLib.h"

UMyGameplayWidgetBase::UMyGameplayWidgetBase()
{
}

bool UMyGameplayWidgetBase::Initialize()
{
	if(false == Super::Initialize())
	{
		return false;
	}
	return true;
}

void UMyGameplayWidgetBase::RegisterEventHelpers_Implementation()
{
	Super::RegisterEventHelpers_Implementation();
	// Warning!!! The gameplay events must be registered inside the RegisterGameplayEventHelpers!
}

void UMyGameplayWidgetBase::RegisterGameplayEventHelpers_Implementation()
{	
	UE_LOG(MyLog, Log, TEXT("Registering Gameplay event helpers"));
	
	TScriptInterface<IUIControllerGameplay> UICont = GetUIControllerGameplay();
	if(nullptr == UICont.GetObject())
	{
		UE_LOG(MyLog, Warning, TEXT("GetUIControllerGameplay() returned nullptr"));
	}
	else
	{
		UUIControllerGameplayEvents* GameplayEvents = IUIControllerGameplay::Execute_GetEvents(UICont.GetObject());
		if(nullptr == GameplayEvents)
		{
			UE_LOG(MyLog, Warning, TEXT("IUIControllerGameplay::GetEvents() returned nullptr"));
		}
		else
		{
			GameplayEvents->PlayerPawnReady.AddDynamic(this, &UMyGameplayWidgetBase::PlayerPawnReady);
		}
	}

	// ~ Events Begin
	if(UDamageableEvents* DamageableEvents = GetPawnDamageableEvents())
	{
		DamageableEvents->StateChanged.AddDynamic(this, &UMyGameplayWidgetBase::PlayerPawn_DamageStateChanged);	
	}
	else
	{
		UE_LOG(MyLog, Warning, TEXT("IDamageable::GetEvents() returned nullptr for PlayerPawn"));
	}
	// ~ Events End
}

void UMyGameplayWidgetBase::UIControllerReady_Implementation(const FUIControllerReadyParams& InParams)
{
	RegisterGameplayEventHelpers();
}

TScriptInterface<IUIControllerGameplay> UMyGameplayWidgetBase::GetUIControllerGameplay() const
{
	if(TScriptInterface<IUIController> UIController = GetUIController())
	{
		return IUIController::Execute_GetGameplay(UIController.GetObject());
	}
	else
	{
		return nullptr;
	}
}

UUIControllerGameplayEvents* UMyGameplayWidgetBase::GetUIControllerGameplayEvents() const
{
	TScriptInterface<IUIControllerGameplay> UICont = GetUIControllerGameplay();
	if(nullptr == UICont.GetObject())
	{
		return nullptr;
	}
	else
	{
		return IUIControllerGameplay::Execute_GetEvents(UICont.GetObject());
	}
}

TScriptInterface<IDamageable> UMyGameplayWidgetBase::GetPawnDamageable() const
{
	if(APawn* P = GetOwningPlayerPawn())
	{
		if(auto DamageableContainer = Cast<IDamageableContainer>(P))	
		{
			return TScriptInterface<IDamageable>(IDamageableContainer::Execute_GetDamageable(P));
		}
	}
	return nullptr;
}

UDamageableEvents* UMyGameplayWidgetBase::GetPawnDamageableEvents() const
{
	TScriptInterface<IDamageable> PawnDamageable = GetPawnDamageable();
	if(nullptr == PawnDamageable.GetObject())
	{
		return nullptr;
	}
	else
	{
		return IDamageable::Execute_GetEvents(PawnDamageable.GetObject());
	}
}

TScriptInterface<IWeaponInventory> UMyGameplayWidgetBase::GetPawnWeapons() const
{
	if(APawn* P = GetOwningPlayerPawn())
	{
		return TScriptInterface<IWeaponInventory>(P);
	}
	return nullptr;
}

TScriptInterface<ITrackPawnMovement> UMyGameplayWidgetBase::GetPawnMovement() const
{
	if(APawn* P = GetOwningPlayerPawn())
	{
		return TScriptInterface<ITrackPawnMovement>(P);
	}
	return nullptr;
}