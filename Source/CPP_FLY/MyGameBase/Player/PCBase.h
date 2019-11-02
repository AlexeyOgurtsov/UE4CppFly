#pragma once

/**
* Base class of PlayerController.
*/

#include "GameFramework/PlayerController.h"
#include "MyGameBase/Controller/I/IMyController.h"
#include "MyGameBase/Player/I/IPCInterface.h"
#include "PCBase.generated.h"

class IUIControllerComponent;

class IWeaponInventory;
class ITrackPawnMovement;
class IDamageableContainer;
class IDamageable;

class ITestController;

UCLASS()
class APCBase : 
	public APlayerController
,	public IMyController
,	public IPCInterface
{
	GENERATED_BODY()

public:
	APCBase();

	// ~ AActor Begin
	virtual void BeginPlay() override;
	// ~ AActor End

	// ~Helpers for accessing pawn Begin
	/**
	* Current pawn casted to ITrackPawnMovement.
	* Returns nullptr if track movement is not supported by pawn or no pawn is attached.
	*/
	UFUNCTION(BlueprintPure)
	TScriptInterface<ITrackPawnMovement> GetPawnMovement() const;

	/**
	* Current pawn casted to IWeaponInventory.
	* Returns nullptr if weapon inventory is not supported by pawn or no pawn is attached.
	*/
	UFUNCTION(BlueprintPure)
	TScriptInterface<IWeaponInventory> GetPawnWeapons() const;

	/**
	* Current pawn casted to IWeaponInventory.
	* Returns nullptr if weapon inventory is not supported by pawn or no pawn is attached.
	* Logs if unable to get the pawn weapons
	*
	* @see GetPawnWeapons
	*/
	UFUNCTION(BlueprintPure)
	TScriptInterface<IWeaponInventory> LogGetPawnWeapons() const;

	UFUNCTION(BlueprintPure)
	TScriptInterface<IDamageableContainer> GetPawnDamageableContainer() const;

	UFUNCTION(BlueprintPure)
	TScriptInterface<IDamageable> GetPawnDamageable() const;

	UFUNCTION(BlueprintPure)
	TScriptInterface<IDamageable> LogGetPawnDamageable() const;
	// ~Helpers for accessing pawn End

	// ~IMyController implementation Begin
	virtual void Pawn_BeginPlay_Implementation() override;
	virtual void Pawn_EndPlay_Implementation(const EEndPlayReason::Type InReason) override;
	virtual void Pawn_DestructionStarted_Implementation() override;
	virtual void Pawn_CharsUpdated_Implementation() override;
	// ~IMyController implementation End

	// ~IPCInterface Begin
	virtual TScriptInterface<IUIController> GetUIController_Implementation() const override;
	// ~IPCInterface End

protected:
	virtual void SetupInputComponent() override;

	virtual void PreRegisterAllComponents() override;

	virtual void PostInitializeComponents() override;

	virtual void SetPawn(APawn* InPawn) override;

	// ~Posession Begin
	/**
	* Called both on client and server when the given pawn released from possession.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Possession)
	void MyUnsetPawn(APawn* InPawn);

	/**
	* Called both on client and server when the given pawn is acquired for posession.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Possession)
	void MySetPawn(APawn* InPawn);

	/**
	* To be called when the player pawn is ready.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Possession)
	void PlayerPawnReady();
	// ~Posession End

	// ~UIController Component Begin
	UFUNCTION(BlueprintPure, Category = UI)
	TScriptInterface<IUIControllerComponent> GetUIControllerComponent() const;
	// ~UIController Component End

	// ~Test Controller Component Begin
	UFUNCTION(BlueprintPure, Category = Test)
	TScriptInterface<ITestController> GetTestController() const;

	UFUNCTION(BlueprintPure, Category = Test)
	TScriptInterface<ITestController> LogGetTestController() const;
	// ~Test Controller Component End

	// ~ Init Begin
	/**
	* This function is to be called when the player controller is fully initialized,
	* and its state can be shown at the UI, for example.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Init)
	void DoWhenReady();
	// ~ Init End

private:
	// ~Lifecycle Begin
	/**
	* This flags is used to Postpone the initialization that is to be done only after the BeginPlay is called.
	*/
	UPROPERTY()
	bool bBeginPlayAlreadyCalled = false;

	UPROPERTY()	
	bool bSetPawnAlreadyCalled = false;

	UPROPERTY()
	bool bPlayerPawnBegunPlay = false;

	UPROPERTY()
	APawn* MyOldPawn = nullptr;

	UPROPERTY()
	APawn* MyNewPawn = nullptr;

	/**
	* Do all the work of the SetPawn.
	* Typically used to postpone the work that would normally be done inside the SetPawn to be done after the BeginPlay.
	*/
	UFUNCTION()
	void DoSetPawn(APawn* InNewPawn, APawn* InOldPawn);
	// ~Lifecycle End

	// ~Input commands Begin
	UFUNCTION()
	void Axis_LookPitch(float InAmount);

	UFUNCTION()
	void Axis_LookYaw(float InAmount);

	UFUNCTION()
	void Axis_LookZoom(float InAmount);

	UFUNCTION()
	void Axis_MoveVertical(float InAmount);

	UFUNCTION()
	void Axis_MoveHorz(float InAmount);

	UFUNCTION()
	void Axis_Thrust(float InAmount);

	UFUNCTION()
	void Axis_Roll(float InAmount);

	UFUNCTION(Exec)
	void Action_Fire();

	UFUNCTION(Exec)
	void Action_AltFire();

	UFUNCTION(Exec)
	void Action_FireThree();

	UFUNCTION(Exec)
	void Action_Fire4();

	UFUNCTION(Exec)
	void Action_Fire5();

	void Action_FireGeneral(FName InWeaponName);

	UFUNCTION(Exec)
	void Action_ShowMenu();

	UFUNCTION(Exec)
	void Action_ShowDebugMenu();

	UFUNCTION(Exec)
	void Action_Debug1();

	UFUNCTION(Exec)
	void Action_Debug2();

	UFUNCTION(Exec)
	void Action_Debug3();
	// ~Input commands End

	// ~Components Begin
	/**
	* Chooses which components to use and setups pointers to them.
	*/
	UFUNCTION()
	void ChooseComponents();
	// ~Components End

	// ~UI Controller Component Begin
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI, Meta = (AllowPrivateAccess = true))
	UActorComponent* UIControllerComponent = nullptr;

	UFUNCTION()
	void ChooseComponent_UIControllerComponent(const TArray<UActorComponent*>& InComponents);
	// ~UI Controller Component End

	// ~Test Controller Component Begin
	void Action_DebugGeneral(int32 InIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Test, Meta = (AllowPrivateAccess = true))
	UActorComponent* TestControllerComponent = nullptr;

	UFUNCTION()
	void ChooseComponent_TestComponent(const TArray<UActorComponent*>& InComponents);
	// ~Test Controller Component End
};
