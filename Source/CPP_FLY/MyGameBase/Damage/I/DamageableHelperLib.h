#pragma once

/**
* Helper getters for the IDamageable and IDamageableContainer interfaces.
*/

#include "Kismet/BlueprintFunctionLibrary.h"
#include "IDamageable.h"
#include "IDamageableContainer.h"

#include "DamageableHelperLib.generated.h"

// ~Fwd Begin
class AActor;
// ~Fwd End

UCLASS()
class UDamageableHelperLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UDamageableHelperLib();

	UFUNCTION(BlueprintCallable, Category = InActor)
	static void LogActorDamageState(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = IDamageable)
	static void LogDamageState(TScriptInterface<IDamageable> InDamageable);

	UFUNCTION(BlueprintPure, Category = IDamageable)
	static TScriptInterface<IDamageable> GetDamageable(AActor* InActor);

	UFUNCTION(BlueprintPure, Category = IDamageable)
	static TScriptInterface<IDamageable> LogGetDamageable(AActor* InActor);
};
