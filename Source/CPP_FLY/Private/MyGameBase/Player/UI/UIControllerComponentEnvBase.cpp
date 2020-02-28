#include "UIControllerComponentEnvBase.h"
#include "UIControllerComponentBase.h"
#include "UIControllerComponentEnvBaseLib.h"
#include "Util/UI/ShowMouseStack.h"
#include "Util/UI/InputModeStack.h"
#include "MySys/HelperLib.h"

UUIControllerComponentEnvBase::UUIControllerComponentEnvBase()
{
}

void UUIControllerComponentEnvBase::MyBeginPlay()
{
	UE_LOG(MyLog, Log, TEXT("UUIControllerComponentEnvBase::MyBeginPlay..."));

	InitializeInput();
}

void UUIControllerComponentEnvBase::InitializeInput()
{
	UE_LOG(MyLog, Log, TEXT("UUIControllerComponentEnvBase::Initialize input..."));

	UUIControllerComponentEnvBaseLib::PushInputAndCursor_GameOnly(this);

	ShowMouseStack->Activate();
	InputModeStack->Activate();

	UE_LOG(MyLog, Log, TEXT("UUIControllerComponentEnvBase::Initialize input DONE"));
}

void UUIControllerComponentEnvBase::BindController(UUIControllerComponentBase* InUIControllerComponent)
{
	UE_LOG(MyLog, Log, TEXT("UUIControllerComponentEnvBase::BindController..."));

	check(InUIControllerComponent);

	UIControllerComponent = InUIControllerComponent;

	// Initializing objects
	UE_LOG(MyLog, Log, TEXT("Creating ShowMouseStack"));
	ShowMouseStack = UShowMouseStack::NewInitializedObject(TEXT("ShowMouseStack"), InUIControllerComponent->GetPC());

	UE_LOG(MyLog, Warning, TEXT("@TODO: Now the bEnableMouseStack parameter is ignored"));
	//ShowMouseStack->SetEnableState(GetDebugParams().bEnableMouseStack);	

	UE_LOG(MyLog, Log, TEXT("Creating InputModeStack"));
	InputModeStack = UInputModeStack::NewInitializedObject(TEXT("InputModeStack"), InUIControllerComponent->GetPC());
	InputModeStack->SetEnableState(GetDebugParams().bEnableInputModeStack);

	UE_LOG(MyLog, Log, TEXT("UUIControllerComponentEnvBase::BindController DONE"));
}

const FUIControllerComponentConfig& UUIControllerComponentEnvBase::GetParams() const
{
	return UIControllerComponent->GetParams();
}

const FUIControllerComponentDebugConfig& UUIControllerComponentEnvBase::GetDebugParams() const
{
	return UIControllerComponent->GetDebugParams();
}

APlayerController* UUIControllerComponentEnvBase::GetPC() const
{
	return GetUIControllerComponentBase()->GetPC();
}