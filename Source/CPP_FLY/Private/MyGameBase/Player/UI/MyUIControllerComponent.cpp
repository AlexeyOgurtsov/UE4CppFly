#include "MyUIControllerComponent.h"
#include "MySys/HelperLib.h"

#include "MyGameBase/UI/I/UIControllerEvents.h"
#include "Gameplay/MyUIControllerGameplay.h"
#include "Menu/MyUIControllerMenu.h"
#include "SaveLoad/MyUIControllerSaveLoad.h"
#include "MyUIControllerComponentEnv.h"

UMyUIControllerComponent::UMyUIControllerComponent()
{
	EnvClass = UMyUIControllerComponentEnv::StaticClass();

	Events = CreateDefaultSubobject<UUIControllerEvents>(TEXT("Events"));
}

void UMyUIControllerComponent::InitPlayerController(APlayerController* InPC)
{
	UE_LOG(MyLog, Log, TEXT("UMyUIControllerComponent::InitPlayerController..."));
	Super::InitPlayerController(InPC);

	InitializeGameplay();
	InitializeMenu();
	InitializeSaveLoad();
}

void UMyUIControllerComponent::InitializeGameplay()
{
	FMyUIControllerGameplayInitializer Initializer { GetEnv() };
	Gameplay = UMyUIControllerGameplay::NewInitializedObject(TEXT("Gameplay"), Initializer);
}

void UMyUIControllerComponent::InitializeMenu()
{
	if(MainMenuClass)
	{
		UE_LOG(MyLog, Log, TEXT("UMyUIControllerComponent: Creating main menu object"));
		Menu = UMyUIControllerMenu::NewInitializedObject(TEXT("Menu"), GetEnv(), MainMenuClass);
		checkf(Menu, TEXT("UMyUIControllerMenu::CreateInitializedDefaultSubobject: returned nullptr - means that menu controller is NOT initialized"));
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("MainManuClass is nullptr, skipping creating main menu object"));
	}
}

void UMyUIControllerComponent::InitializeSaveLoad()
{
	FMyUIControllerSaveLoadInitializer Initializer { GetEnv() };
	SaveLoad = UMyUIControllerSaveLoad::NewInitializedObject(TEXT("SaveLoad"), Initializer);
}

UMyUIControllerComponentEnv* UMyUIControllerComponent::GetEnv() const
{
	return CastChecked<UMyUIControllerComponentEnv>(GetEnvBase());
}

void UMyUIControllerComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UMyUIControllerComponent::BeginPlay()
{
	UE_LOG(MyLog, Log, TEXT("UMyUIControllerComponent::BeginPlay"));

	Super::BeginPlay();

	// Stop!!! Rather consider adding code to OwnerReady
}

void UMyUIControllerComponent::OwnerReady_Implementation(AActor* InOwner)
{
	UE_LOG(MyLog, Log, TEXT("OwnerReady..."));

	Super::OwnerReady_Implementation(InOwner);

	// Registering widget
	if(HUDWidget = CreateAndRegisterWidget(HUDWidgetClass, FString(TEXT("HUDWidget"))))
	{
		ShowWidget(HUDWidget);
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("HUD Widget is nullptr"));
	}

	// When player controller is ready, the UI Controller is ready
	UE_LOG(MyLog, Log, TEXT("At this point UI Controller component is ready"));
	Events->Ready.Broadcast(FUIControllerReadyParams{this});

	UE_LOG(MyLog, Log, TEXT("OwnerReady DONE"));
}

void UMyUIControllerComponent::PlayerPawnReady_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("UMyUIControllerComponent::PlayerPawnReady"));
	
	if(Gameplay)
	{
		UE_LOG(MyLog, Log, TEXT("UMyUIControllerComponent: Sending Player Pawn Ready to Gameplay"));
		Gameplay->PlayerPawn_Ready();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("UMyUIControllerComponent: Gameplay is nullptr, skipping sender Player Pawn Ready"));
	}
}

void UMyUIControllerComponent::ToggleMenu_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("UMyUIControllerComponent::ToggleMenu"));
	if(Menu)
	{
		Menu->Toggle();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("Menu is nullptr, skip toggling"));
	}
}

void UMyUIControllerComponent::ToggleDebugMenu_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("UMyUIControllerComponent::ToggleDebugMenu"));
	// @TODO
	UE_LOG(MyLog, Log, TEXT("NOT YET IMPL"));
}

UUIControllerEvents* UMyUIControllerComponent::GetEvents_Implementation() const
{
	return Events;
}

TScriptInterface<IUIControllerGameplay> UMyUIControllerComponent::GetGameplay_Implementation() const
{
	return TScriptInterface<IUIControllerGameplay>(Gameplay);
}

TScriptInterface<IUIControllerMenu> UMyUIControllerComponent::GetMenu_Implementation() const
{
	return TScriptInterface<IUIControllerMenu>(Menu);
}

TScriptInterface<IUIControllerSaveLoad> UMyUIControllerComponent::GetSaveLoad_Implementation() const
{
	return TScriptInterface<IUIControllerSaveLoad>(SaveLoad);
}

TScriptInterface<IUIControllerLevels> UMyUIControllerComponent::GetLevels_Implementation() const
{
	return nullptr; // @TODO
}

void UMyUIControllerComponent::CloseCurrentUI_Implementation(UUserWidget* InSender)
{
	UE_LOG(MyLog, Log, TEXT("UMyUIControllerComponent::CloseCurrentUI"));
	if(Menu)
	{
		Menu->Toggle();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("Menu is nullptr, skipping closing"));
	}
}