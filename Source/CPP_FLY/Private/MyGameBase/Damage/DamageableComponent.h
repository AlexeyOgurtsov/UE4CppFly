#pragma once

/**
* Any actor that can be damaged must include this component.
*/

#include "Components/ActorComponent.h"
#include "I/IDamageable.h"
#include "DamageableComponent.generated.h"

UCLASS()
class UDamageableComponent : 
	public UActorComponent
,	public IDamageable
{
	GENERATED_BODY()

public:
	UDamageableComponent();

	virtual void Activate(bool bReset) override;
	virtual void Deactivate() override;

	// ~IDamageable Begin
	virtual UDamageableEvents* GetEvents_Implementation() const override;
	virtual FDamageableState GetDamageState_Implementation() const override;
	virtual float MakeDamage_Implementation(const UDamageType* InDamage, float InAmount) override;
	// ~IDamageable End

protected:
	// ~State helpers Begin
	UFUNCTION(BlueprintPure)
	bool IsFatallyDamaged() const;
	// ~State helpers End

	// ~Events implementation Begin
	UFUNCTION(BlueprintCallable)
	void Broadcast_DamageStateChangedEvent(bool bInFromActivateReset);
	// ~Events implementation End

protected:
	// ~State setters Begin
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetStateAndNotify(const FDamageableState& InState, bool bFromActivateReset = false);
	// ~State setters End

private:
	// ~State Begin
	UPROPERTY()
	FDamageableState State;

	UPROPERTY(EditDefaultsOnly, Category = Defaults)
	FDamageableState DefaultState;
	// ~State End

	// ~Events implementation Begin
	UDamageableEvents* MyEvents = nullptr;
	// ~Events implementation End
};
