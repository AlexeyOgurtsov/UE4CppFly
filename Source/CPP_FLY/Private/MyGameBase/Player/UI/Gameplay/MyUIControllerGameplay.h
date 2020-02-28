#pragma once

#include "MyGameBase/UI/I/Gameplay/IUIControllerGameplay.h"
#include "MyUIControllerGameplay.generated.h"

class UMyUIControllerComponentEnv;

USTRUCT(BlueprintType)
struct FMyUIControllerGameplayInitializer 
{
	GENERATED_BODY()

	UPROPERTY()
	UMyUIControllerComponentEnv* Env = nullptr;

	FMyUIControllerGameplayInitializer() = default;
	FMyUIControllerGameplayInitializer(UMyUIControllerComponentEnv* InEnv) :
		Env(InEnv) {}
};

UCLASS()
class UMyUIControllerGameplay : 
	public UObject
,	public IUIControllerGameplay
{
	GENERATED_BODY()

public:
	UMyUIControllerGameplay();

	UFUNCTION(BlueprintCallable, Category = Creation)
	static UMyUIControllerGameplay* CreateInitializedDefaultSubobject
	(
		const FName& InName, 
		const FMyUIControllerGameplayInitializer& InInitializer
	);

	UFUNCTION(BlueprintCallable, Category = Creation)
	static UMyUIControllerGameplay* NewInitializedObject
	(
		const FName& InName, 
		const FMyUIControllerGameplayInitializer& InInitializer
	);

	// ~IUIControllerGameplay Begin
	virtual UUIControllerGameplayEvents* GetEvents_Implementation() const override;
	// ~IUIControllerGameplay End

	// ~ Notifications Begin
	UFUNCTION(BlueprintCallable)
	void PlayerPawn_Ready();
	// ~ Notifications End;

protected:
	UFUNCTION(BlueprintPure, Category = Environment)
	UMyUIControllerComponentEnv* GetEnv() const { return Env; }

private:
	// ~Environment Begin
	UPROPERTY()
	UMyUIControllerComponentEnv* Env = nullptr;
	// ~Environment End

	UPROPERTY()
	UUIControllerGameplayEvents* Events = nullptr;
};