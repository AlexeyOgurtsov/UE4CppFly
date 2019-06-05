#include "GlobSingleton.h"
#include "MySys/HelperLib.h"

UGlobSingleton::UGlobSingleton()
{
	UE_LOG(MyLog, Log, TEXT("UGlobSingleton: Constructor"));
}

FText UGlobSingleton::GetSingletonDesc_Implementation() const
{
	return FText::FromString(TEXT("Global singleton {Main object}"));
}