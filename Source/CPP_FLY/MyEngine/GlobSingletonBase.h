#pragma once

/**
* All method getters defaults to return nullptr.
*/

#include "IGlobSingletonInterface.h"
#include "GlobSingletonBase.generated.h"

UCLASS(Blueprintable)
class UGlobSingletonBase : 
	public UObject,
	public IGlobSingletonInterface
{
	GENERATED_BODY()

public:
	virtual FText GetSingletonDesc_Implementation() const override;
};