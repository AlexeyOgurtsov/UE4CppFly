#include "DamageableHelperLib.h"
#include "MySys/HelperLib.h"

UDamageableHelperLib::UDamageableHelperLib()
{
}

void UDamageableHelperLib::LogActorDamageState(AActor* InActor)
{
	TScriptInterface<IDamageable> Damageable = GetDamageable(InActor);
	LogDamageState(Damageable);	
}

void UDamageableHelperLib::LogDamageState(TScriptInterface<IDamageable> InDamageable)
{
	FDamageableState State = IDamageable::Execute_GetDamageState(InDamageable.GetObject());

	UE_LOG(MyLog, Log, TEXT("Hits: \"%f\""), State.HitPoints);
	UE_LOG(MyLog, Log, TEXT("MaxHits: \"%f\""), State.MaxHitPoints);
}

TScriptInterface<IDamageable> UDamageableHelperLib::GetDamageable(AActor* InActor)
{
	auto Cont = TScriptInterface<IDamageableContainer>(InActor);
	if(nullptr == Cont.GetInterface())
	{
		return nullptr;
	}
	else
	{
		TScriptInterface<IDamageable> Damageable = IDamageableContainer::Execute_GetDamageable(Cont.GetObject());
		if(nullptr == Damageable.GetInterface())	
		{
			return nullptr;
		}	
		else
		{
			return Damageable;
		}
	}
}

TScriptInterface<IDamageable> UDamageableHelperLib::LogGetDamageable(AActor* InActor)
{
	if(InActor == nullptr)
	{
		return nullptr;
	}

	const FString FuncName = "LogGetDamageable";
	const FString& ActorName = InActor->GetName();

	auto Cont = TScriptInterface<IDamageableContainer>(InActor);
	if(nullptr == Cont.GetInterface())
	{
		UE_LOG(MyLog, Warning, TEXT("%s: Actor \"%s\" is NOT IDamageableContainer"), *FuncName, *ActorName);
		return nullptr;
	}

	TScriptInterface<IDamageable> Damageable = IDamageableContainer::Execute_GetDamageable(Cont.GetObject());
	if(nullptr == Damageable.GetInterface())
	{
		UE_LOG(MyLog, Warning, TEXT("%s: GetDamageable() for Actor \"%s\" returned nullptr"), *FuncName, *ActorName);
	}

	return TScriptInterface<IDamageable>(Damageable);
}