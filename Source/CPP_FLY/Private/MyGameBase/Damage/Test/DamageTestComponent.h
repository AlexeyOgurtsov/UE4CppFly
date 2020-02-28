#pragma once

#include "MyGameBase/Player/Test/ActorTestComponentBase.h"
#include "DamageTestComponent.generated.h"

class IDamageable;
class UDamageType;

UCLASS(ClassGroup=(Test), BlueprintType, Blueprintable, EditInlineNew, Meta=(BlueprintSpawnableComponent))
class UDamageTestComponent : public UActorTestComponentBase
{
	GENERATED_BODY()

public:
	UDamageTestComponent();

	// ~ ITestController Begin
	virtual void DoTest_1_Implementation() override;
	virtual void DoTest_2_Implementation() override;
	virtual void DoTest_3_Implementation() override;
	virtual void DoTest_4_Implementation() override;
	virtual void DoTest_5_Implementation() override;
	virtual void DoTest_6_Implementation() override;
	virtual void DoTest_7_Implementation() override;
	// ~ ITestController End

protected:
	UFUNCTION(BlueprintCallable, Category = IDamageable)
	void LogMyActorDamageState();

	UFUNCTION(BlueprintCallable, Category = IDamageable)
	void LogDamageConfig();

	UFUNCTION(BlueprintPure, Category = IDamageable)
	TScriptInterface<IDamageable> GetDamageable() const;

	UFUNCTION(BlueprintPure, Category = IDamageable)
	TScriptInterface<IDamageable> LogGetDamageable() const;

	UFUNCTION(BlueprintPure, Category = Props)
	TSubclassOf<UDamageType> GetDamageTypeClass() const;

	UFUNCTION(BlueprintPure, Category = Props)
	float GetDamageAmount() const;	

private:
	UPROPERTY(EditDefaultsOnly, Category = Props)
	TSubclassOf<UDamageType> DamageTypeClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Props)
	float DamageAmount = 10.0F;
};