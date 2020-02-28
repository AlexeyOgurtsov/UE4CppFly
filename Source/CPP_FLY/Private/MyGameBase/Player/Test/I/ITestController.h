#pragma once

/**
* Interface for all test controllers.
*/

#include "UObject/Interface.h"
#include "ITestController.generated.h"

UINTERFACE()
class UTestController : public UInterface
{
	GENERATED_BODY()

public:
};

class ITestController 
{
	GENERATED_BODY()

public:
	static void DoTest(UObject* InObject, int32 InIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoTest_1();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoTest_2();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoTest_3();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoTest_4();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoTest_5();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoTest_6();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoTest_7();
};
