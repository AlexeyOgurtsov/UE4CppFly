#include "TestControllerComponentBase.h"
#include "Kismet/GameplayStatics.h"

UTestControllerComponentBase::UTestControllerComponentBase()
{
	bAutoActivate = true;
	bAutoRegister = true;
}

APCBase* UTestControllerComponentBase::GetPCBase() const
{
	return Cast<APCBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}