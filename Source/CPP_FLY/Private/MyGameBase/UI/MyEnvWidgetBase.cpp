#include "MyEnvWidgetBase.h"

#include "I/IUIController.h"
#include "MyGameBase/Player/I/IPCInterface.h"
#include "MyGameBase/UI/I/SaveLoad/IUIControllerSaveLoad.h"
#include "MyGameBase/UI/I/Menu/IUIControllerMenu.h"
#include "MyGameBase/UI/I/Levels/IUIControllerLevels.h"

#include "MySys/HelperLib.h"

UMyEnvWidgetBase::UMyEnvWidgetBase()
{
}

bool UMyEnvWidgetBase::Initialize()
{
	if(false == Super::Initialize())
	{
		return false;
	}

	return true;
}

void UMyEnvWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	RegisterEventHelpers();
}

void UMyEnvWidgetBase::RegisterEventHelpers_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("Registering event helpers..."));
	
	TScriptInterface<IUIController> UICont = GetUIController();
	if( nullptr == UICont.GetObject() )
	{
		UE_LOG(MyLog, Warning, TEXT("GetUIController() returned nullptr, skipping registering event helpers"));
		return;
	}

	UUIControllerEvents* UIContEvents = IUIController::Execute_GetEvents(UICont.GetObject());
	if( nullptr == UIContEvents )
	{
		UE_LOG(MyLog, Warning, TEXT("GetUIController()->GetEvents() returned nullptr"));
		return;
	}

	// ~Actual Events Begin
	UIContEvents->Ready.AddDynamic(this, &UMyEnvWidgetBase::UIControllerReady);
	// ~Actual Events End

	UE_LOG(MyLog, Log, TEXT("Registering event helpers DONE"));
}

void UMyEnvWidgetBase::UIControllerReady_Implementation(const FUIControllerReadyParams& InParams)
{
	// Nothing is to be done here yet
}

TScriptInterface<IUIControllerLevels> UMyEnvWidgetBase::GetControllerLevels() const
{
	if(auto Controller = UMyEnvWidgetBase::GetUIController())
	{
		return IUIController::Execute_GetLevels(Controller.GetObject());
	}
	return nullptr;
}

TScriptInterface<IUIControllerMenu> UMyEnvWidgetBase::GetControllerMenu() const
{
	if(auto Controller = UMyEnvWidgetBase::GetUIController())
	{
		return IUIController::Execute_GetMenu(Controller.GetObject());
	}
	return nullptr;
}

UUIControllerMenuEvents* UMyEnvWidgetBase::GetMenuEvents() const
{
	TScriptInterface<IUIControllerMenu> UIContMenu = GetControllerMenu();
	if(nullptr == UIContMenu.GetObject())
	{
		return nullptr;
	}
	else
	{
		return IUIControllerMenu::Execute_GetEvents(UIContMenu.GetObject());
	}
}

TScriptInterface<IUIControllerSaveLoad> UMyEnvWidgetBase::GetControllerSaveLoad() const
{
	if(auto Controller = UMyEnvWidgetBase::GetUIController())
	{
		return IUIController::Execute_GetSaveLoad(Controller.GetObject());
	}
	return nullptr;
}

UUIControllerSaveLoadEvents* UMyEnvWidgetBase::GetSaveLoadEvents() const
{
	TScriptInterface<IUIControllerSaveLoad> UIContSaveLoad = GetControllerSaveLoad();
	if(nullptr == UIContSaveLoad.GetObject())
	{
		return nullptr;
	}
	else
	{
		return IUIControllerSaveLoad::Execute_GetEvents(UIContSaveLoad.GetObject());
	}
}

TScriptInterface<IUIController> UMyEnvWidgetBase::GetUIController() const
{
	if(auto PC = TScriptInterface<IPCInterface>(GetOwningPlayer()))
	{
		return IPCInterface::Execute_GetUIController(PC.GetObject());
	}
	else
	{
		return nullptr;
	}
}

UUIControllerEvents* UMyEnvWidgetBase::GetUIControllerEvents() const
{
	TScriptInterface<IUIController> UICont = GetUIController();
	if(nullptr == UICont.GetObject())
	{
		return nullptr;
	}
	else
	{
		return IUIController::Execute_GetEvents(UICont.GetObject());
	}
}