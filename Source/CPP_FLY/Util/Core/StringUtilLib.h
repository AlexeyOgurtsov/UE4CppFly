#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "StringUtilLib.generated.h"

UCLASS()
class UStringUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = StringUtilLib)
	static FString YesNo(bool bYes);

	UFUNCTION(BlueprintPure, Category = StringUtilLib)
	static FString BoolString(bool bTrue, const FString& InTrueString, const FString& InFalseString);	
};