#include "MyUIControllerMenu.h"
#include "Util/UI/WidgetClassStack.h"
#include "Util/UI/UIUtilLib.h"
#include "MyGameBase/UI/I/Menu/UIControllerMenuEvents.h"
#include "MyGameBase/Player/UI/UIControllerComponentBase.h"
#include "MyGameBase/Player/UI/MyUIControllerComponentEnv.h"
#include "MyGameBase/Player/UI/UIControllerComponentEnvBaseLib.h"
#include "MySys/HelperLib.h"

#include "Blueprint/UserWidget.h"

UMyUIControllerMenu::UMyUIControllerMenu()
{
	LogPrefix = FString::Printf(TEXT("UMyUIControllerMenu \"%s\" of class \"%s\":"), *GetName(), *GetClass()->GetName());

	Events = CreateDefaultSubobject<UUIControllerMenuEvents>(TEXT("Events"));
}

UMyUIControllerMenu* UMyUIControllerMenu::CreateInitializedDefaultSubobject(const FName& InName, UMyUIControllerComponentEnv* InEnv, TSubclassOf<UUserWidget> InStartWidgetClass)
{
	UE_LOG(MyLog, Log, TEXT("UMyUIControllerMenu::CreateInitializedDefaultSubobject, Name=\"%s\"..."), *InName.ToString());

	check(InEnv);
	check(InStartWidgetClass);
	check(InEnv->GetPC());

	// Creating object and initializing fields
	UMyUIControllerMenu* pMenu = InEnv->GetUIControllerComponent()->CreateDefaultSubobject<UMyUIControllerMenu>(InName);
	pMenu->WidgetStack = UWidgetClassStack::CreateInitializedDefaultSubobject(InEnv->GetPC(), pMenu, TEXT("WidgetStack"));
	check(pMenu);

	pMenu->PostConstruct(InEnv, InStartWidgetClass);

	return pMenu;
}

UMyUIControllerMenu* UMyUIControllerMenu::NewInitializedObject(const FName& InName, UMyUIControllerComponentEnv* InEnv, TSubclassOf<UUserWidget> InStartWidgetClass)
{
	UE_LOG(MyLog, Log, TEXT("UMyUIControllerMenu::NewInitializedObject..."));

	check(InEnv);
	check(InStartWidgetClass);
	check(InEnv->GetPC());

	// Creating object and initializing fields
	UMyUIControllerMenu* pMenu = NewObject<UMyUIControllerMenu>(InEnv->GetUIControllerComponent(), UMyUIControllerMenu::StaticClass(), InName);
	pMenu->WidgetStack = UWidgetClassStack::NewInitializedObject(InEnv->GetPC(), pMenu);	
	check(pMenu);

	pMenu->PostConstruct(InEnv, InStartWidgetClass);

	return pMenu;
}

void UMyUIControllerMenu::PostConstruct(UMyUIControllerComponentEnv* InEnv, TSubclassOf<UUserWidget> InStartWidgetClass)
{
	struct SEntryExitHelper
	{
		SEntryExitHelper(const FString& InLogPrefix) :
			LogPrefix{InLogPrefix}
		{
			UE_LOG(MyLog, Log, TEXT("%s UMyUIControllerMenu::PostConstruct..."), *LogPrefix);
		}
		~SEntryExitHelper()
		{
			UE_LOG(MyLog, Log, TEXT("%s UMyUIControllerMenu::PostConstruct DONE"), *LogPrefix);
		}

	private:
		FString LogPrefix;
	} EntryExitHelper { *LogPrefix };

	Env = InEnv;
	StartWidgetClass = InStartWidgetClass;

	// Creating start widget
	if(StartWidgetClass)
	{	
		DoReturnToStart();		
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("%s StartWidgetClass is nullptr"), *LogPrefix);
	}
}

void UMyUIControllerMenu::OpenMenu_Implementation(TSubclassOf<UUserWidget> InWidgetClass)
{
	check(InWidgetClass);
	UE_LOG(MyLog, Log, TEXT("%s UI Controller Menu: Open menu widget of class \"%s\"..."), *LogPrefix, *InWidgetClass->GetName());
	WidgetStack->Push(FWidgetClassStackElement{InWidgetClass});
}

void UMyUIControllerMenu::Return_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("%s UI Controller Menu: Return from menu..."), *LogPrefix);
	if(Execute_CanReturn(this))
	{
		WidgetStack->Pop();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("%s UI Controller Menu: Cannot return: CanReturn() returned false"), *LogPrefix);
	}
}

bool UMyUIControllerMenu::CanReturn_Implementation() const 
{
	return WidgetStack->Num() > 1;
}

void UMyUIControllerMenu::ReturnToStart_Implementation()
{
	if(Execute_CanReturnToStart(this))
	{
		DoReturnToStart();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("%s UI Controller Menu: Cannot return to start: CanReturnToStart() returned false"), *LogPrefix);
	}
}

bool UMyUIControllerMenu::CanReturnToStart_Implementation() const
{
	return true;
}

bool UMyUIControllerMenu::IsOpened() const
{
	return bOpened;
}

void UMyUIControllerMenu::Open()
{
	UE_LOG(MyLog, Log, TEXT("%s Opening menu..."), *LogPrefix);

	DoReturnToStart();
	WidgetStack->Activate();
	check(WidgetStack->TopWidget());
	UUIControllerComponentEnvBaseLib::PushInputAndCursor_UIOnly(GetEnv(), WidgetStack->TopWidget());
	bOpened = true;
}

void UMyUIControllerMenu::Close()
{
	UE_LOG(MyLog, Log, TEXT("%s Closing menu..."), *LogPrefix);


	UUIControllerComponentEnvBaseLib::PopInputAndCursor(GetEnv());
	if(GetEnv()->GetDebugParams().ShouldSetInputModeManually())
	{
		UE_LOG(MyLog, Warning, TEXT("%s Setting up input mode manually to GameOnly for testing reasons due to Controller's Debug Params (Should Set input Mode Manually)"), *LogPrefix);
		UUIUtilLib::SetInputMode_GameOnly(GetEnv()->GetPC());
	}

	WidgetStack->Deactivate();
	bOpened = false;
}

void UMyUIControllerMenu::Toggle()
{
	if(IsOpened())
	{
		Close();
	}
	else
	{
		Open();
	}
}

bool UMyUIControllerMenu::IsWidgetOnTop(UUserWidget* InWidget)
{
	return WidgetStack->TopWidget() == InWidget;
}

bool UMyUIControllerMenu::IsWidgetClassOnTop(TSubclassOf<UUserWidget> InWidgetClass)
{
	if(WidgetStack->IsEmpty())
	{
		return false;
	}
	else
	{
		return WidgetStack->TopCreatorElement().WidgetClass;
	}
}

void UMyUIControllerMenu::DoReturnToStart()
{
	UE_LOG(MyLog, Log, TEXT("%s Returning to start widget..."), *LogPrefix);
	
	check(StartWidgetClass);
	check(WidgetStack);

	WidgetStack->Clear();
	WidgetStack->Push(FWidgetClassStackElement{StartWidgetClass});
}

APlayerController* UMyUIControllerMenu::GetPC() const
{
	return GetUIControllerComponent()->GetPC();
}

UMyUIControllerComponent* UMyUIControllerMenu::GetUIControllerComponent() const
{
	return GetEnv()->GetUIControllerComponent();
}