#include "GlobSingletonBase.h"

FText UGlobSingletonBase::GetSingletonDesc_Implementation() const
{	
	return FText::FromString(TEXT("GlobSingletonBase"));
}