#pragma once

/**
* Base class of all pawns that fly on the track.
*/

#include "MyPawnBase.h"
#include "TrackFlyPawn.generated.h"

UCLASS(Blueprintable)
class ATrackFlyPawn : public AMyPawnBase
{
	GENERATED_BODY()

public:
	ATrackFlyPawn();
};