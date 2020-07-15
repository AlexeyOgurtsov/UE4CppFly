#pragma once
/**
* Base class of all pawns in the game.
*/

#include "GameFramework/Pawn.h"
#include "MyGameBase/Damage/I/IDamageableContainer.h"
#include "MyGameBase/Damage/I/DamageableEvents.h"
#include "Util/Weapon/I/IWeaponInventoryHolder.h"
#include "MyPawnBase.generated.h"

class IMyController;

class UWeaponComponent;
class UQuickWeaponComponent;
class USceneComponent;
class UPrimitiveComponent;
class USpringArmComponent;
class UCameraComponent;
class UDamageableComponent;

struct FDamageableStateChangedParams;

/**
* TODO OnComponentBeginOverlap/EndOverlap: Should be virtual?
*/

UCLASS(Blueprintable)
class AMyPawnBase : 
	public APawn
,	public IDamageableContainer
,	public IWeaponInventoryHolder
{
	GENERATED_BODY()

public:
	AMyPawnBase();

	virtual void PreRegisterAllComponents() override;
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type InReason) override;

	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// ~ IWeaponInventoryHolder Begin
	virtual TScriptInterface<IWeaponInventory> GetWeapons_Implementation() const override;

	/**
	* Returns QuickWeaponComponent or nullptr (if current weapon component is not UQuickWeaponComponent)
	*/
	UFUNCTION(BlueprintPure, Category = Weapon)
	UQuickWeaponComponent* GetQuickWeaponComponent() const;

	/**
	* Returns QuickWeaponComponent (fails if current component is not UQuickWeaponComponent)
	*/
	UFUNCTION(BlueprintPure, Category = Weapon)
	UQuickWeaponComponent* GetQuickWeaponComponentChecked() const;
	// ~ IWeaponInventoryHolder End
	
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
	* Warning! It's attached to the Root mesh component, NOT vice versa!
	*/
	UFUNCTION(BlueprintPure, Category = Components)
	USceneComponent* GetRootSceneComponent() const { return RootSceneComponent; }

	/**
	* Primitive component to be used for proximity collisions (e.g. pickups).
	* @see: GetRootSceneComponent()
	*/
	UFUNCTION(BlueprintPure, Category = Collision)
	UShapeComponent* GetProximityComponent() const { return ProximityComponent; }

	/**
	* Setups the whole set of default components, necessary for any pawn.	
	*
	* - Setups the provided mesh component as the root component;
	* - Attaches the given proximity component to the provided root mesh component;
	* - Setups RootSceneComponent and attaches it to the Proximity Component;	
	* - Setups default scene components attached to RootSceneComponent (camera etc.);	
	*
	* @warning To be called from C++ constructor only, never from blueprint!!!
	* @param InRootMeshComponent    Mesh component to be used as the root (will be assigned to root automatically)
	*/	
	void SetupDefaultComponents(UPrimitiveComponent* InProxComponent, class UMeshComponent* InRootMeshComponent);
	// ~Scene components End

	// ~Camera Begin
	UFUNCTION(BlueprintPure, Category = Camera)
	UCameraComponent* GetCameraComponent() const { return Camera; }
	// ~Camera End

private:
	void FindComponents();
	void FindDamageableComponent();
	void FindWeaponComponent();
	void FindProximityComponent();

	// ~Damageable Component Begin
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = true), Category = Damage)
	UDamageableComponent* DamageableComponent = nullptr;

	/**
	* Helper: Performs post-actions that should be done after the damageable component is set.
	* Setups event handlers.
	* Does NOT set the damageable component variable itself.
	*/
	UFUNCTION(BlueprintCallable, Category = Damage)
	void PostInitialize_DamageableComponent(UDamageableComponent* InComponent);

	UFUNCTION(BlueprintCallable, Category = Damage)
	void OnDamageableComponent_DamageStateChanged(const FDamageableStateChangedParams& InParams);
	// ~Damageable Component End
	
	// ~ Weapon Component Begin
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = true), Category = Weapon)
	UWeaponComponent* WeaponComponent = nullptr;
	// ~ Weapon Component End

	// ~Scene components Begin
	void SetupDefaultRootSceneAndComponents(USceneComponent* AttachTo);
	void SetupDefaultCameraComponents(USceneComponent* AttachTo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = true), Category = Components)
	USceneComponent* RootSceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = true), Category = Collision)
	UShapeComponent* ProximityComponent = nullptr;

	/**
	* Helper: Performs post-actions that should be done after the proximity component is set.
	* Setups event handlers.
	* Does NOT set the proximity component variable itself.
	*/
	UFUNCTION(BlueprintCallable, Category = Collision)
	void PostInitialize_ProximityComponent(UShapeComponent* InComponent);

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
