// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveData.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

UCLASS()
class BUILDTOSURVIVE_API AWaveManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWaveManager();
	
	// Wave functions
	
	UFUNCTION(BlueprintCallable)
	void StartWave();
	
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();
	
	UFUNCTION(BlueprintCallable)
	void OnEnemyKilled();
	
	UFUNCTION(BlueprintCallable)
	void AdvanceWave();
	
	UFUNCTION(BlueprintCallable)
	void GetSpawnPoints();	
	
	// Wave properties
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTimerHandle SpawnTimer;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentWaveIndex { 0 };
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 EnemiesSpawned { 0 };
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 EnemiesAlive { 0 };
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FWaveData> Waves;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> SpawnPoints;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> CachedSpawnPoints;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftClassPtr<AActor> SpawnPointClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
