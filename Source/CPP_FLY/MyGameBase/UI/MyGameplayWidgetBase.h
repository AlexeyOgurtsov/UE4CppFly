#pragma once

/**
* All UI widgets that interact with the gameplay environment
* (HUDs, Inventorys etc.).
*/

#include "MyEnvWidgetBase.h"
#include "I/Gameplay/UIControllerGameplayEvents.h"
#include "MyGameBase/Damage/I/DamageableEvents.h"
#include "MyGameplayWidgetBase.generated.h"

class IUIControllerGameplay;

UCLASS()
class UMyGameplayWidgetBase : public UMyEnvWidgetBase
{
	GENERATED_BODY()

public:
	UMyGameplayWidgetBase();

protected:
	virtual bool Initialize() override;

	// ~Helper getters Begin
	UFUNCTION(BlueprintPure, Category = "AccessHelper")
	TScriptInterface<IUIControllerGameplay> GetUIControllerGameplay() const;

	UFUNCTION(BlueprintPure, Category = "AccessHelper")
	UUIControllerGameplayEvents* GetUIControllerGameplayEvents() const;

	UFUNCTION(BlueprintPure, Category = "AccessHelper")
	TScriptInterface<IDamageable> GetPawnDamageable() const;

	UFUNCTION(BlueprintPure, Category = "EventHelper")
	UDamageableEvents* GetPawnDamageableEvents() const;

	UFUNCTION(BlueprintPure, Category = "AccessHelper")
	TScriptInterface<IWeaponInventory> GetPawnWeapons() const;

	UFUNCTION(BlueprintPure, Category = "AccessHelper")
	TScriptInterface<ITrackPawnMovement> GetPawnMovement() const;
	// ~Helper getters End

	// ~Helper system Begin
	virtual void RegisterEventHelpers_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Events")
	void RegisterGameplayEventHelpers();
	// ~Helper system End

	// ~Helper events Begin
	virtual void UIControllerReady_Implementation(const FUIControllerReadyParams& InParams) override;

	/**
	* Called when the player pawn is ready.
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "EventHelper")
	void PlayerPawnReady(const FUIControllerGameplay_PlayerPawnReadyParams& InParams);

	/**
	* Called when the player pawn is damaged.
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "EventHelper")
	void PlayerPawn_DamageStateChanged(const FDamageableStateChangedParams& InParams);
	// ~Helper events End
};