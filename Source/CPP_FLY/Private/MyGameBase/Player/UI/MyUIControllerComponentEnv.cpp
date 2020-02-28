#include "MyUIControllerComponentEnv.h"
#include "MyUIControllerComponent.h"

UMyUIControllerComponentEnv::UMyUIControllerComponentEnv()
{
}

void UMyUIControllerComponentEnv::BindController(UUIControllerComponentBase* InUIControllerComponent)
{
	Super::BindController(InUIControllerComponent);
}

UMyUIControllerComponent* UMyUIControllerComponentEnv::GetUIControllerComponent() const
{
	return CastChecked<UMyUIControllerComponent>(GetUIControllerComponentBase());
}
