#include "MyWidgetBase.h"
#include "MySys/HelperLib.h"

bool UMyWidgetBase::Initialize()
{
	PrefixString = FString::Printf(TEXT("UMyWidgetBase \"%s\" of class \"%s\":"), *GetName(), *GetClass()->GetName());

	UE_LOG(MyLog, Log, TEXT("%s UMyWidgetBase::Initialize: "), *PrefixString);

	if(false == Super::Initialize())
	{
		return false;
	}
	return true;
}

void UMyWidgetBase::NativeConstruct()
{
	UE_LOG(MyLog, Log, TEXT("%s UMyEnvBase::NativeConstruct..."), *PrefixString);
	UE_LOG(MyLog, Log, TEXT("%s NumWidgetsInViewport=%d"), *PrefixString, NumWidgetsInViewport);

	Super::NativeConstruct();
	
	if(0 == NumWidgetsInViewport)
	{
		UE_LOG(MyLog, Log, TEXT("%s Binding delegetes (No widget is added to the viewport)"), *PrefixString);
		MyBindDelegates();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("%s Skipping binding delegates- must be already binded (More than one widget already in viewport)"), *PrefixString);
	}	

	NumWidgetsInViewport++;
}

void UMyWidgetBase::NativeDestruct()
{
	UE_LOG(MyLog, Log, TEXT("%s UMyEnvBase::NativeDestruct..."), *PrefixString);
	UE_LOG(MyLog, Log, TEXT("%s NumWidgetsInViewport=%d"), *PrefixString, NumWidgetsInViewport);

	Super::NativeDestruct();

	checkf(NumWidgetsInViewport > 0, TEXT("As we destructing a widget, at least one widget must already be in the viewport!"));
	if(1 == NumWidgetsInViewport)
	{
		check(1 == NumWidgetsInViewport);
	
		UE_LOG(MyLog, Log, TEXT("%s Unbinding delegates: exactly one widget is binded to the viewport"), *PrefixString);
		MyUnbindDelegates();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("%s Skipping unbinding delegates: more than one widget is binded to viewport, we still need the delegates"), *PrefixString);
	}

	NumWidgetsInViewport--;
}

void UMyWidgetBase::MyUnbindDelegates_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("%s UMyWidgetBase::MyUnbindDelegates..."), *PrefixString);
}

void UMyWidgetBase::MyBindDelegates_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("%s UMyWidgetBase::MyBindDelegates..."), *PrefixString);
}