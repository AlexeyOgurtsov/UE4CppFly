#pragma once

#include "MyGameBase/UI/I/SaveLoad/IUIControllerSaveLoad.h"
#include "MyUIControllerSaveLoad.generated.h"

class UMyUIControllerComponentEnv;

class UUIControllerSaveLoadEvents;

USTRUCT(BlueprintType)
struct FMyUIControllerSaveLoadInitializer 
{
	GENERATED_BODY()

	UPROPERTY()
	UMyUIControllerComponentEnv* Env = nullptr;

	FMyUIControllerSaveLoadInitializer() = default;
	FMyUIControllerSaveLoadInitializer(UMyUIControllerComponentEnv* InEnv) :
		Env(InEnv) {}
};

UCLASS()
class UMyUIControllerSaveLoad : 
	public UObject
,	public IUIControllerSaveLoad
{
	GENERATED_BODY()

public:
	UMyUIControllerSaveLoad();

	UFUNCTION(BlueprintCallable, Category = Creation)
	static UMyUIControllerSaveLoad* CreateInitializedDefaultSubobject(const FName& InName, const FMyUIControllerSaveLoadInitializer& InInitializer);

	UFUNCTION(BlueprintCallable, Category = Creation)
	static UMyUIControllerSaveLoad* NewInitializedObject(const FName& InName, const FMyUIControllerSaveLoadInitializer& InInitializer);

	// ~IUIControllerSaveLoad Begin
	virtual UUIControllerSaveLoadEvents* GetEvents_Implementation() const;

	virtual void QuickSave_Implementation() override;
	virtual void QuickLoad_Implementation() override;
	// ~IUIControllerSaveLoad End

protected:
	UFUNCTION(BlueprintPure, Category = Environment)
	UMyUIControllerComponentEnv* GetEnv() const { return Env; }

private:
	// ~Environment Begin
	UPROPERTY()
	UMyUIControllerComponentEnv* Env = nullptr;
	// ~Environment End

	UPROPERTY()
	UUIControllerSaveLoadEvents* Events = nullptr;
};