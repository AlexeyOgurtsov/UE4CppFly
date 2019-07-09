#pragma once

/**
* Base class of all UI Controller components.
*/

#include "Components/ActorComponent.h"
#include "Util/Component/IMyComponent.h"
#include "UIControllerComponentConfigLib.h"
#include "UIControllerComponentDebugConfigLib.h"

#include "Blueprint/UserWidget.h"

#include "UIControllerComponentBase.generated.h"


class APlayerController;

class UUIControllerComponentEnvBase;

UCLASS()
class UUIControllerComponentBase : 
	public UActorComponent
,	public IMyComponent
{
	GENERATED_BODY()

public:
	UUIControllerComponentBase();

	// ~ UObject Begin
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type InReason) override;
	// ~ UObject End

	// ~ UActorComponent Begin
	virtual void InitializeComponent() override;
	virtual void Activate(bool bReset) override;
	virtual void Deactivate() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
	// ~ UActorComponent End

	// ~IMyComponent Begin
	virtual void BindOwner_Implementation(AActor* InOwner) override;
	virtual void OwnerReady_Implementation(AActor* InOwner) override;
	// ~IMyComponent End

	// ~ Helper accessors Begin
	UFUNCTION(BlueprintPure, Category = Accessor)
	APlayerController* GetPC() const;
	// ~ Helper accessors End

	// ~Editable properties getters Begin
	UFUNCTION(BlueprintPure, Category = Params)
	const FUIControllerComponentConfig& GetParams() const { return Params; }

	UFUNCTION(BlueprintPure, Category = DebugParams)
	const FUIControllerComponentDebugConfig& GetDebugParams() const { return DebugParams; }
	// ~Editable properties getters End

protected:
	// ~ Initialization Begin
	UFUNCTION(BlueprintCallable, Category = Initialization)
	virtual void InitPlayerController(APlayerController* InPC);
	// ~ Initialization End

	// ~ Helper accessors Begin
	UFUNCTION(BlueprintPure, Category = Accessor)
	APlayerController* GetController() const;

	// Returns true, if we should create/show/hide game widgets in this world
	UFUNCTION(BlueprintPure, Category = Widgets)
	bool AreGameWidgetsRelevant() const;
	// ~ Helper accessors End

	/**
	* Creates widget of the given class and adds it to the array of all widgets.
	*/
	UFUNCTION(BlueprintCallable, Category = Widgets)
	UUserWidget* CreateAndRegisterWidget(TSubclassOf<UUserWidget> InWidgetClass, const FString& InWidgetName);

	/**
	* Registers the given widget in the array of all widgets.
	* To be called for every widget.
	*
	* NOTE: Consider using CreateAndRegisterWidget instead by default.
	*/
	UFUNCTION(BlueprintCallable, Category = Widgets)
	void RegisterWidget(UUserWidget* InWidget);

	/**
	* Marks the given widget as visible, and really shows it if it's necessary.
	*/
	UFUNCTION(BlueprintCallable, Category = Widgets)
	void ShowWidget(UUserWidget* InWidget);

	/**
	* Marks the given widget as invisible, and really hides it if it's necessary.
	*/
	UFUNCTION(BlueprintCallable, Category = Widgets)
	void HideWidget(UUserWidget* InWidget);

	/**
	* Checks whether the given widget should be visible if component is active.
	*/
	UFUNCTION(BlueprintPure, Category = Widgets)
	bool IsWidgetVisible(UUserWidget* InWidget) const;

	/**
	* Environment.
	*/
	UFUNCTION(BlueprintPure)
	UUIControllerComponentEnvBase* GetEnvBase() const { return Env; }

protected:
	// ~Editable properties Begin
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Params, Meta = (AllowPrivateAccess = true))
	FUIControllerComponentConfig Params;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DebugParams, Meta = (AllowPrivateAccess = true))
	FUIControllerComponentDebugConfig DebugParams;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Environment, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UUIControllerComponentEnvBase> EnvClass = nullptr;
	// ~Editable properties End

private:
	UPROPERTY()
	UUIControllerComponentEnvBase* Env = nullptr;

	void InitializeEnvironment();

	// ~ Widget Helpers Begin
	void DoShowWidget(UUserWidget* InWidget);
	void DoHideWidget(UUserWidget* InWidget);

	/**
	* Show all widgets that are in the visible state
	*/
	void ShowWidgetCanvas();

	/**
	* Hide all widgets
	*/
	void HideWidgetCanvas();
	// ~ Widget Helpers End

	// ~ Widgets Begin
	UPROPERTY()
	TArray<UUserWidget*> AllWidgets;
	// ~ Widgets End

	// ~ Player controller Begin
	APlayerController* PC = nullptr;
	// ~ Player controller End
};
