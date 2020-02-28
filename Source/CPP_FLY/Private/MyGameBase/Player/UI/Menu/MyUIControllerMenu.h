#pragma once

/**
* Controller of any menu.
*/

#include "MyGameBase/UI/I/Menu/IUIControllerMenu.h"
#include "MyUIControllerMenu.generated.h"

class UMyUIControllerComponentEnv;
class UMyUIControllerComponent;
class UWidgetClassStack;
class UUIControllerMenuEvents;

class UUserWidget;
class APlayerController;

UCLASS()
class UMyUIControllerMenu :
	public UObject
,	public IUIControllerMenu
{
	GENERATED_BODY()

public:
	UMyUIControllerMenu();

	/**
	* Create object using CreateDefaultSubobject
	*/
	static UMyUIControllerMenu* CreateInitializedDefaultSubobject(const FName& InName, UMyUIControllerComponentEnv* InEnv, TSubclassOf<UUserWidget> InStartWidgetClass);

	/**
	* Create object using NewObject
	*/
	static UMyUIControllerMenu* NewInitializedObject(const FName& InName, UMyUIControllerComponentEnv* InEnv, TSubclassOf<UUserWidget> InStartWidgetClass);

	// ~IUIControllerMenu Begin
	virtual UUIControllerMenuEvents* GetEvents_Implementation() const override { return Events; }

	virtual void OpenMenu_Implementation(TSubclassOf<UUserWidget> InWidgetClass) override;
	virtual void Return_Implementation() override;
	virtual bool CanReturn_Implementation() const override;
	virtual void ReturnToStart_Implementation() override;
	virtual bool CanReturnToStart_Implementation() const override;
	// ~IUIControllerMenu End

	// ~Menu interface Begin
	bool IsOpened() const;
	void Open();
	void Close();
	void Toggle();
	bool IsWidgetOnTop(UUserWidget* InWidget);
	bool IsWidgetClassOnTop(TSubclassOf<UUserWidget> InWidgetClass);
	// ~Menu interface End

protected:
	// ~Initialization Begin
	/**
	* Function that is called after each construction.
	*/
	UFUNCTION(BlueprintCallable, Category = Initialization)
	virtual void PostConstruct(UMyUIControllerComponentEnv* InEnv, TSubclassOf<UUserWidget> InStartWidgetClass);
	// ~Initialization End

	UFUNCTION(BlueprintPure, Category = Environment)
	UMyUIControllerComponentEnv* GetEnv() const { return Env; }

	// ~Helper getters Begin
	UFUNCTION(BlueprintPure, Category = Environment)
	APlayerController* GetPC() const;

	UFUNCTION(BlueprintPure)
	UMyUIControllerComponent* GetUIControllerComponent() const;
	// ~Helper getters End

private:
	UPROPERTY()
	FString LogPrefix;

	UPROPERTY()
	UUIControllerMenuEvents* Events = nullptr;

	UPROPERTY()
	UMyUIControllerComponentEnv* Env = nullptr;

	/**
	* Widget that is to be opened when menu is opened.
	*/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> StartWidgetClass = nullptr;

	/**
	* Pops back to start element.
	*/
	void DoReturnToStart();

	UPROPERTY()
	APlayerController* PC = nullptr;

	UPROPERTY()
	bool bOpened = false;

	UPROPERTY()
	UWidgetClassStack* WidgetStack = nullptr;
};