#pragma once

#include "../DamageableState.h"
#include "IDamageable.generated.h"

class UDamageableEvents;

class UDamageType;

UINTERFACE(BlueprintType)
class UDamageable : public UInterface
{
	GENERATED_BODY()

public:
};

class IDamageable
{
	GENERATED_BODY()

public:
	/**
	* Use this object to bind to delegates;
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UDamageableEvents* GetEvents() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FDamageableState GetDamageState() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float MakeDamage(const UDamageType* InDamage, float InAmount);
};