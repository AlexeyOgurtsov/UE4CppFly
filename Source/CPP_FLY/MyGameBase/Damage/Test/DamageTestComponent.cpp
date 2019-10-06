#include "DamageTestComponent.h"

#include "MyGameBase/Damage/I/DamageableHelperLib.h"
#include "MySys/HelperLib.h"

#include "GameFramework/DamageType.h"
#include "GameFramework/Actor.h"

UDamageTestComponent::UDamageTestComponent()
{	
}

void UDamageTestComponent::LogMyActorDamageState()
{
	TScriptInterface<IDamageable> Damageable = LogGetDamageable();
	if(Damageable)
	{
		UE_LOG(MyLog, Log, TEXT("IDamageable is supported"));
		UDamageableHelperLib::LogDamageState(Damageable);
	}
}

void UDamageTestComponent::DoTest_1_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("Logging Damage state..."));

	LogMyActorDamageState();
}

void UDamageTestComponent::DoTest_2_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("Making Damage using IDamageable..."));
	LogMyActorDamageState();

	float const DamageAmount = GetDamageAmount();
	TSubclassOf<UDamageType> const DamageTypeClass = GetDamageTypeClass();

	if(nullptr == DamageTypeClass)
	{
		UE_LOG(MyLog, Warning, TEXT("Skipping: DamageTypeClass is nullptr"));
		return;
	}

	UDamageType* const DamageType = NewObject<UDamageType>(this, DamageTypeClass);
	check(DamageType);

	LogDamageConfig();

	TScriptInterface<IDamageable> Damageable = LogGetDamageable();
	if(nullptr == Damageable.GetObject()) 
	{
		return;
	}


	float const DamageReallyTaken = IDamageable::Execute_MakeDamage(Damageable.GetObject(), DamageType, DamageAmount);
	UE_LOG(MyLog, Log, TEXT("MakeDamage returned %f (damage really taken)"), DamageReallyTaken);

	LogMyActorDamageState();
}

void UDamageTestComponent::LogDamageConfig()
{
	float const DamageAmount = GetDamageAmount();
	TSubclassOf<UDamageType> const DamageTypeClass = GetDamageTypeClass();

	UE_LOG(MyLog, Log, TEXT("DamageAmount=%d"), DamageAmount);

	if(nullptr == DamageTypeClass)
	{
		UE_LOG(MyLog, Log, TEXT("Damage type class is nullptr"));
		return;
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("Damage type class is\"%s\""), *DamageTypeClass->GetName());
	}
}

void UDamageTestComponent::DoTest_3_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("Making Damage using AActor::TakeDamage..."));

	float const DamageAmount = GetDamageAmount();
	TSubclassOf<UDamageType> const DamageTypeClass = GetDamageTypeClass();
	if(nullptr == DamageTypeClass)
	{
		UE_LOG(MyLog, Warning, TEXT("Skipping: DamageTypeClass is nullptr"));
		return;
	}

	LogDamageConfig();

	AActor* A = GetMyActor();
	if(A)
	{
		FDamageEvent DamageEvent;
		DamageEvent.DamageTypeClass = DamageTypeClass;		

		A->TakeDamage(DamageAmount, DamageEvent, /*DamageInstigator=*/nullptr, /*DamageCauser=*/nullptr);
	}
}

void UDamageTestComponent::DoTest_4_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("NO Test Yet"));
}

void UDamageTestComponent::DoTest_5_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("NO Test Yet"));
}

void UDamageTestComponent::DoTest_6_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("NO Test Yet"));
}

void UDamageTestComponent::DoTest_7_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("NO Test Yet"));
}

TScriptInterface<IDamageable> UDamageTestComponent::GetDamageable() const
{
	return UDamageableHelperLib::GetDamageable(GetMyActor());
}

TScriptInterface<IDamageable> UDamageTestComponent::LogGetDamageable() const
{
	return UDamageableHelperLib::LogGetDamageable(GetMyActor());
}

TSubclassOf<UDamageType> UDamageTestComponent::GetDamageTypeClass() const
{
	return DamageTypeClass;
}

float UDamageTestComponent::GetDamageAmount() const
{
	return DamageAmount;
}