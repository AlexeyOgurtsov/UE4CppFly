#include "ITestController.h"
#include "MySys/HelperLib.h"

void ITestController::DoTest(UObject* InObject, int32 InIndex)
{
	switch(InIndex)
	{
	case 1:
		Execute_DoTest_1(InObject);	
		break;

	case 2:
		Execute_DoTest_2(InObject);	
		break;

	case 3:
		Execute_DoTest_3(InObject);	
		break;

	case 4:
		Execute_DoTest_4(InObject);	
		break;

	case 5:
		Execute_DoTest_5(InObject);	
		break;

	case 6:
		Execute_DoTest_6(InObject);	
		break;

	case 7:
		Execute_DoTest_7(InObject);	
		break;

	default:
		UE_LOG(MyLog, Warning, TEXT("Unknown test index: %d"), InIndex);
	};
}
