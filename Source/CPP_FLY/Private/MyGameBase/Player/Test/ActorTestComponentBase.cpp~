#include "ActorTestComponentBase.h"
#include "MySys/HelperLib.h"
#include "Kismet/GameplayStatics.h"

UActorTestComponentBase::UActorTestComponentBase()
{
}

AActor* UActorTestComponentBase::GetMyActor() const
{
	if(MyActorTag == NAME_None)
	{
		UE_LOG(MyLog, Warning, TEXT("Actor tag is NONE, returning nullptr"));
		return nullptr;
	}

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), MyActorTag, Actors);

	if(Actors.Num() == 0)
	{
		UE_LOG(MyLog, Warning, TEXT("Actor with tag \"%s\" NOT found!"), *MyActorTag.ToString());
		return nullptr;
	}
	else
	{
		if(Actors.Num() > 1)
		{
			UE_LOG(MyLog, Warning, TEXT("More than one actor with tag \"%s\" FOUND, using FIRST"), *MyActorTag.ToString());
		}
		AActor* A = Actors[0];
		UE_LOG(MyLog, Log, TEXT("Actor to use is named as \"%s%\""), *A->GetName());
	
		return A;
	}
}

FName UActorTestComponentBase::GetMyActorTag() const
{
	return MyActorTag;
}