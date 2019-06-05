#include "StringUtilLib.h"

FString UStringUtilLib::YesNo(bool bYes)
{
	return BoolString(bYes, FString("YES"), FString("no"));
}

FString UStringUtilLib::BoolString(bool bTrue, const FString& InTrueString, const FString& InFalseString)
{
	return bTrue ? InTrueString : InFalseString;
}