#include "MyHUDWidgetBase.h"

bool UMyHUDWidgetBase::Initialize()
{
	if(false == Super::Initialize())
	{
		return false;
	}
	return true;
}