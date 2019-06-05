#pragma once

#include "MyUIControllerSaveLoadEvents.generated.h"

class IUIControllerSaveLoad;
class UUIControllerSaveLoadEvents;

USTRUCT(BlueprintType)
struct FUIControllerSaveLoadParamsBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	TScriptInterface<IUIControllerSaveLoad> Sender;

	FUIControllerSaveLoadParamsBase() = default;
	FUIControllerSaveLoadParamsBase(TScriptInterface<IUIControllerSaveLoad> InSender) 
	{
		Sender = InSender;
	}
};

//USTRUCT(BlueprintType)
//struct FUIControllerSaveLoad_XParams : public FUIControllerSaveLoadParamsBase
//{
//	GENERATED_BODY()
//
//	FUIControllerGameplay_XParams() = default;
//	FUIControllerGameplay_XParams(TScriptInterface<IUIControllerSaveLoad> InSender) :
//		FUIControllerSaveLoadParamsBase(InSender) {}
//};
//
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIControllerSaveLoad_XSignature, const FUIControllerSaveLoad_XParams&, InParams);

UCLASS()
class UUIControllerSaveLoadEvents : public UObject
{
	GENERATED_BODY()

public:
	UUIControllerSaveLoadEvents();

	/**
	* X
	*/ 
	//UPROPERTY(BlueprintAssignable, Category = Events)
	//FUIControllerSaveLoad_XSignature X;
};