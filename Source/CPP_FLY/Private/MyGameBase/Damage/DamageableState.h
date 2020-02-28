#pragma once

#include "DamageableState.generated.h"

USTRUCT(Blueprintable)
struct FDamageableState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HitPoints = 100.F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHitPoints = 100.F;

	FDamageableState() = default;
	FDamageableState(float InHitPoints) :
		HitPoints(InHitPoints)
	,	MaxHitPoints(InHitPoints) {}
};