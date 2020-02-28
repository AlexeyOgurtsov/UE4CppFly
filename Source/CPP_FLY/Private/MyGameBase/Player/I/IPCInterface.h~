#pragma once

#include "IPCInterface.generated.h"

class IUIController;

UINTERFACE()
class UPCInterface : public UInterface
{
	GENERATED_BODY()

public:
};

class IPCInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IUIController> GetUIController() const;
};