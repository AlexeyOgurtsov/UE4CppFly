#pragma once

/**
* Common helpers for accessing engine singleton and its subobjects.
* Typically to be included in the gameplay code .cpp files.
*/

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MySys/HelperLib.h"
#include "GlobSingletonHelperLib.generated.h"

UCLASS()
class UGlobSingletonHelperLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* The main access point for accessing the global singleton.
	*/
	UFUNCTION(BlueprintPure, Category = "Engine")
	static class TScriptInterface<IGlobSingletonInterface> Get();
};
