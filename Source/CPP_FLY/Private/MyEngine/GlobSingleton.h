#pragma once

#include "GlobSingletonBase.h"
#include "GlobSingleton.generated.h"

UCLASS()
class UGlobSingleton : public UGlobSingletonBase
{
	GENERATED_BODY()

public:
	UGlobSingleton();

	virtual FText GetSingletonDesc_Implementation() const override;
};