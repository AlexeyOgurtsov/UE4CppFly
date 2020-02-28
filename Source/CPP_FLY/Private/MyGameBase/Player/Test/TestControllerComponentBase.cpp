#include "TestControllerComponentBase.h"
#include "MyGameBase/Player/PCBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UTestControllerComponentBase::UTestControllerComponentBase()
{
	bAutoActivate = true;
	bAutoRegister = true;
}

APCBase* UTestControllerComponentBase::GetPCBase() const
{
	return Cast<APCBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}
