#pragma once

#include "UIControllerComponentBase.h"

#include "I/IUIControllerComponent.h"
#include "MyGameBase/UI/I/IUIController.h"
#include "MyGameBase/UI/I/Menu/IUIControllerMenu.h"
#include "MyGameBase/UI/I/SaveLoad/IUIControllerSaveLoad.h"

#include "MyUIControllerComponent.generated.h"

class UMyUIControllerGameplay;
class UMyUIControllerMenu;
class UMyUIControllerSaveLoad;

class UMyUIControllerComponentEnv;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(UI), meta=(BlueprintSpawnableComponent))
class UMyUIControllerComponent : 
	public UUIControllerComponentBase
,	public IUIControllerComponent
,	public IUIController
{
	GENERATED_BODY()

public:	
	UMyUIControllerComponent();

	// ~ Widgets Begin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widgets)
	TSubclassOf<UUserWidget> HUDWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Widgets)
	TSubclassOf<UUserWidget> MainMenuClass = nullptr;
	// ~ Widgets End

	// ~ AActor Begin
	virtual void BeginPlay() override;
	// ~ AActor End
	
	// ~ UActorComponent Begin
	virtual void InitializeComponent() override;
	// ~ UActorComponent End


	// ~IMyComponent Begin
	virtual void OwnerReady_Implementation(AActor* InOwner) override;
	// ~IMyComponent End

	// ~IUIControllerComponent Begin
	virtual void PlayerPawnReady_Implementation() override;
	virtual void ToggleMenu_Implementation() override;
	virtual void ToggleDebugMenu_Implementation() override;
	// ~IUIControllerComponent End

	// ~IUIController Begin
	virtual UUIControllerEvents* GetEvents_Implementation() const override;

	virtual TScriptInterface<IUIControllerGameplay> GetGameplay_Implementation() const override;
	virtual TScriptInterface<IUIControllerMenu> GetMenu_Implementation() const override;
	virtual TScriptInterface<IUIControllerSaveLoad> GetSaveLoad_Implementation() const override;
	virtual TScriptInterface<IUIControllerLevels> GetLevels_Implementation() const override;

	virtual void CloseCurrentUI_Implementation(UUserWidget* InSender) override;
	// ~IUIController End

	/**
	* Environment.
	*/
	UFUNCTION(BlueprintPure, Category = Environment)
	UMyUIControllerComponentEnv* GetEnv() const;

protected:
	virtual void InitPlayerController(APlayerController* InPC) override;

private:
	// ~ Widgets Begin
	UPROPERTY(BlueprintReadWrite, Category = Widgets, Meta = (AllowPrivateAccess = true))
	UUserWidget* HUDWidget = nullptr;
	// ~ Widgets End

	// ~ Subordinate controllers Begin
	void InitializeGameplay();
	void InitializeMenu();
	void InitializeSaveLoad();

	UPROPERTY(EditDefaultsOnly, Category = Controller)
	UMyUIControllerGameplay* Gameplay = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Controller)
	UMyUIControllerMenu* Menu = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Controller)
	UMyUIControllerSaveLoad* SaveLoad = nullptr;
	// ~ Subordinate controllers End

	// ~ Events Begin
	UPROPERTY()
	UUIControllerEvents* Events = nullptr;
	// ~ Events End
};