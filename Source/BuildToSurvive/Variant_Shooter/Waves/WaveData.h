#pragma once

#include "CoreMinimal.h"
#include "AI/ShooterNPC.h"
#include "WaveData.generated.h"

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AShooterNPC> EnemyClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 EnemyCount { 5 };
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SpawnInterval { 1.0f };
	
};
