#include "DamageableComponent.h"
#include "I/DamageableEvents.h"

#include "Engine/World.h"

UDamageableComponent::UDamageableComponent()
{
	MyEvents = CreateDefaultSubobject<UDamageableEvents>(TEXT("DamageableEvents"));

	bAutoActivate = true;
	bAutoRegister = true;
}

void UDamageableComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	if(GetWorld()->IsGameWorld())
	{
		if(bReset)
		{
			SetStateAndNotify(DefaultState, /*bFromActivateReset=*/true);
		}
	}
}

void UDamageableComponent::Deactivate()
{
	Super::Deactivate();
}

UDamageableEvents* UDamageableComponent::GetEvents_Implementation() const
{
	checkf(GetWorld()->IsGameWorld(), TEXT("This function should only be called in Game-type worlds!"));
	return MyEvents;
}

FDamageableState UDamageableComponent::GetDamageState_Implementation() const
{
	checkf(GetWorld()->IsGameWorld(), TEXT("This function should only be called in Game-type worlds!"));
	return State;
}

float UDamageableComponent::MakeDamage_Implementation(const UDamageType* InDamage, float InAmount)
{
	checkf(GetWorld()->IsGameWorld(), TEXT("This function should only be called in Game-type worlds!"));

	if(IsActive())
	{
		FDamageableState NewState = State;
		NewState.HitPoints -= InAmount;
		SetStateAndNotify(NewState, /*bFromActivateReset=*/false);
	}

	return InAmount;
}

void UDamageableComponent::SetStateAndNotify_Implementation(const FDamageableState& InState, bool bFromActivateReset)
{
	checkf(GetWorld()->IsGameWorld(), TEXT("This function should only be called in Game-type worlds!"));
	State = InState;
	Broadcast_DamageStateChangedEvent(bFromActivateReset);
}

bool UDamageableComponent::IsFatallyDamaged() const
{
	checkf(GetWorld()->IsGameWorld(), TEXT("This function should only be called in Game-type worlds!"));
	return State.HitPoints <= 0;
}

void UDamageableComponent::Broadcast_DamageStateChangedEvent(bool bInFromActivateReset)
{
	check(MyEvents);
	checkf(GetWorld()->IsGameWorld(), TEXT("This function should only be called in Game-type worlds!"));

	FDamageableStateChangedParams EvParams;
	EvParams.Sender = TScriptInterface<IDamageable>(this);
	EvParams.bFatallyDamaged = IsFatallyDamaged();
	EvParams.bFromActivateReset = bInFromActivateReset;
	MyEvents->StateChanged.Broadcast(EvParams);
}
