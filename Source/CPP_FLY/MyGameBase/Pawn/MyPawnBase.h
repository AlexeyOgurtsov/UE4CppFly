#pragma once
/**
* Base class of all pawns in the game.
*/

#include "GameFramework/Pawn.h"
#include "MyGameBase/Damage/I/IDamageableContainer.h"
#include "MyGameBase/Damage/I/DamageableEvents.h"
#include "MyPawnBase.generated.h"

class IMyController;

class USceneComponent;
class UPrimitiveComponent;
class USpringArmComponent;
class UCameraComponent;
class UDamageableComponent;

struct FDamageableStateChangedParams;

UCLASS(Blueprintable)
class AMyPawnBase : 
	public APawn
,	public IDamageableContainer
{
	GENERATED_BODY()

public:
	AMyPawnBase();

	virtual void PreRegisterAllComponents() override;
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type InReason) override;

	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// ~ IDamageableContainer Begin
	virtual TScriptInterface<IDamageable> GetDamageable_Implementation() const override;
	// ~ IDamageableContainer End

	// Player controller helper getters Begin
	UFUNCTION(BlueprintPure)
	TScriptInterface<IMyController> GetPC() const;
	// Player controller helper getters End

protected:
	// ~Actor components Begin
	/**
	* Damageable component or nullptr.
	*/
	UFUNCTION(BlueprintPure, Category = Damage)
	UDamageableComponent* GetDamageableComponent() const { return DamageableComponent; }
	// ~Actor components End

	// ~Scene components Begin
	/**
	* The root scene component that all other scene components to be attached to.
	*/
	UFUNCTION(BlueprintPure, Category = Components)
	USceneComponent* GetRootSceneComponent() const { return RootSceneComponent; }

	/**
	* Primitive component to be used for proximity collisions (e.g. pickups).
	*/
	UFUNCTION(BlueprintPure, Category = Collision)
	UPrimitiveComponent* GetProximityComponent() const { return ProximityComponent; }

	/**
	* Setup primitive component to be used for proximity collisions (e.g. pickups).
	* Call only when you use dynamic components or C++, should NOT be called for static blueprint components.
	*
	* Calls SetupAttachment;
	*/
	UFUNCTION(BlueprintCallable, Category = Collision)
	void SetupProximityComponentAttachment(UPrimitiveComponent* InProxComponent);
	// ~Scene components End

	// ~Camera Begin
	UFUNCTION(BlueprintPure, Category = Camera)
	UCameraComponent* GetCameraComponent() const { return Camera; }
	// ~Camera End

private:
	// ~Actor components Begin
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = true), Category = Damage)
	UDamageableComponent* DamageableComponent = nullptr;

	/**
	* Helper: Performs post-actions that should be done after the damageable component is set.
	* Setups event handlers.
	* Does NOT sets the damageable component variable itself.
	*/
	UFUNCTION(BlueprintCallable, Category = Damage)
	void PostInitialize_DamageableComponent(UDamageableComponent* InComponent);

	UFUNCTION(BlueprintCallable, Category = Damage)
	void OnDamageableComponent_DamageStateChanged(const FDamageableStateChangedParams& InParams);
	// ~Actor components End

	// ~Scene components Begin
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = true), Category = Components)
	USceneComponent* RootSceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = true), Category = Collision)
	UPrimitiveComponent* ProximityComponent = nullptr;

	/**
	* Helper: Performs post-actions that should be done after the proximity component is set.
	* Setups event handlers.
	* Does NOT set the proximity component variable itself.
	*/
	UFUNCTION(BlueprintCallable, Category = Collision)
	void PostInitialize_ProximityComponent(UPrimitiveComponent* InComponent);

	UFUNCTION(BlueprintCallable, Category = Collision)
	void OnProximityComponent_BeginOverlap
	(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
	);

	UFUNCTION(BlueprintCallable, Category = Collision)
	void OnProximityComponent_EndOverlap
	(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComponent, 
		int32 OtherBodyIndex
	);
	// ~Scene components End	

	// ~Camera Begin
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = true), Category = Camera)
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = true), Category = Camera)
	UCameraComponent* Camera = nullptr;
	// ~Camera End
};