#include "MyUIControllerSaveLoad.h"
#include "MySys/HelperLib.h"
#include "MyGameBase/UI/I/SaveLoad/MyUIControllerSaveLoadEvents.h"
#include "MyGameBase/Player/UI/MyUIControllerComponentEnv.h"
#include "MyGameBase/Player/UI/MyUIControllerComponent.h"

#include "MyGameBase/Save/SaveLoadServiceLib.h"

UMyUIControllerSaveLoad::UMyUIControllerSaveLoad()
{
	Events = CreateDefaultSubobject<UUIControllerSaveLoadEvents>(TEXT("Events"));
}

UUIControllerSaveLoadEvents* UMyUIControllerSaveLoad::GetEvents_Implementation() const
{
	return Events;
}

UMyUIControllerSaveLoad* UMyUIControllerSaveLoad::CreateInitializedDefaultSubobject(const FName& InName, const FMyUIControllerSaveLoadInitializer& InInitializer)
{
	check(InInitializer.Env);

	UMyUIControllerSaveLoad* const pObj = InInitializer.Env->GetUIControllerComponent()->CreateDefaultSubobject<UMyUIControllerSaveLoad>(InName);
	pObj->Env = InInitializer.Env;
	return pObj;
}


UMyUIControllerSaveLoad* UMyUIControllerSaveLoad::NewInitializedObject(const FName& InName, const FMyUIControllerSaveLoadInitializer& InInitializer)
{
	check(InInitializer.Env);

	UMyUIControllerSaveLoad* const pObj = NewObject<UMyUIControllerSaveLoad>(InInitializer.Env->GetUIControllerComponent(), UMyUIControllerSaveLoad::StaticClass(), InName);
	pObj->Env = InInitializer.Env;
	return pObj;
}

void UMyUIControllerSaveLoad::QuickSave_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("UI Controller Save Load: QuickSave..."));
	USaveLoadServiceLib::QuickSave();
}

void UMyUIControllerSaveLoad::QuickLoad_Implementation()
{
	UE_LOG(MyLog, Log, TEXT("UI Controller Save Load: QuickLoad..."));
	USaveLoadServiceLib::QuickLoad();
}