#include "UIControllerComponentEnvBaseLib.h"
#include "UIControllerComponentEnvBase.h"
#include "Util/UI/ShowMouseStack.h"
#include "Util/UI/InputModeStack.h"
#include "Util/UI/UIUtilLib.h"
#include "Util/Core/LogUtilLib.h"
#include "Util/Core/MyDebugMacros.h"
#include "GameFramework/DamageType.h"

UUIControllerComponentEnvBaseLib::UUIControllerComponentEnvBaseLib()
{
}

void UUIControllerComponentEnvBaseLib::PushInputAndCursor_GameOnly(UUIControllerComponentEnvBase* Env)
{
	check(Env);
	FInputModeStackElement const Mode = FInputModeStackElement::CreateGameOnly();
	Env->GetInputModeStack()->Push(Mode);
	if( Env->GetDebugParams().ShouldSetInputModeManually() )
	{
		M_LOG(TEXT("Setting up input mode manully..."));
		UUIUtilLib::SetInputMode_GameOnly(Env->GetPC());
	}

	Env->GetShowMouseStack()->Push(false);
}

void UUIControllerComponentEnvBaseLib::PushInputAndCursor_UIOnly(UUIControllerComponentEnvBase* Env, UUserWidget* InWidget)
{
	check(Env);
	FInputModeStackElement const Mode = FInputModeStackElement::CreateUIOnly(InWidget);
	Env->GetInputModeStack()->Push(Mode);
	if( Env->GetDebugParams().ShouldSetInputModeManually() )
	{
		M_LOG(TEXT("Setting up input mode manully..."));
		UUIUtilLib::SetInputMode_UIOnly(Env->GetPC(), InWidget);
	}
	Env->GetShowMouseStack()->Push(true);
}

void UUIControllerComponentEnvBaseLib::PushInputAndCursor_GameAndUI(UUIControllerComponentEnvBase* Env, UUserWidget* InWidget)
{
	check(Env);
	FInputModeStackElement const Mode = FInputModeStackElement::CreateGameAndUI(InWidget);
	Env->GetInputModeStack()->Push(Mode);
	if( Env->GetDebugParams().ShouldSetInputModeManually() )
	{
		M_LOG(TEXT("Setting up input mode manully..."));
		UUIUtilLib::SetInputMode_GameAndUI(Env->GetPC(), InWidget);
	}

	Env->GetShowMouseStack()->Push(true);
}

void UUIControllerComponentEnvBaseLib::PopInputAndCursor(UUIControllerComponentEnvBase* Env)
{
	check(Env);
	Env->GetInputModeStack()->Pop();
	Env->GetShowMouseStack()->Pop();
}
