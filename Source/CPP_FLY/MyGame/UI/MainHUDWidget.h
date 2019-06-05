#pragma once

/**
* The main HUD that the player normally sees.
*/

#include "MyGameBase/UI/MyHUDWidgetBase.h"
#include "MainHUDWidget.generated.h"

UCLASS()
class UMainHUDWidget : public UMyHUDWidgetBase
{
	GENERATED_BODY()

public:

protected:
	virtual bool Initialize() override;
};