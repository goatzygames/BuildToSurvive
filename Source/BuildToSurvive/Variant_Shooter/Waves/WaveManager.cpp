// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogWaveManager, Log, All);

// Sets default values
AWaveManager::AWaveManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogWaveManager, Log, TEXT("WaveManager BeginPlay"));

	GetSpawnPoints();

	UE_LOG(LogWaveManager, Log, TEXT("Found %d spawn points"), CachedSpawnPoints.Num());

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 5.f, FColor::Green,
			FString::Printf(TEXT("Spawn Points Found: %d"), CachedSpawnPoints.Num())
		);
	}

	StartWave();
}


// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWaveManager::StartWave()
{
	if (!Waves.IsValidIndex(CurrentWaveIndex))
	{
		UE_LOG(LogWaveManager, Warning, TEXT("Invalid wave index: %d"), CurrentWaveIndex);
		return;
	}

	EnemiesSpawned = 0;
	EnemiesAlive = 0;

	UE_LOG(LogWaveManager, Log, TEXT("Starting Wave %d (Enemies: %d)"),
		CurrentWaveIndex,
		Waves[CurrentWaveIndex].EnemyCount
	);

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimer,
		this,
		&AWaveManager::SpawnEnemy,
		Waves[CurrentWaveIndex].SpawnInterval,
		true
	);
}


void AWaveManager::SpawnEnemy()
{
	if (!Waves.IsValidIndex(CurrentWaveIndex))
	{
		UE_LOG(LogWaveManager, Error, TEXT("SpawnEnemy called with invalid wave index"));
		return;
	}

	const FWaveData& Wave = Waves[CurrentWaveIndex];

	UE_LOG(LogWaveManager, Verbose,
		TEXT("SpawnEnemy: Spawned=%d Alive=%d"),
		EnemiesSpawned,
		EnemiesAlive
	);

	if (EnemiesSpawned >= Wave.EnemyCount)
	{
		UE_LOG(LogWaveManager, Log, TEXT("Finished spawning wave %d"), CurrentWaveIndex);
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
		return;
	}

	if (CachedSpawnPoints.Num() == 0)
	{
		UE_LOG(LogWaveManager, Error, TEXT("No cached spawn points!"));
		return;
	}

	AActor* SpawnPoint =
		CachedSpawnPoints[FMath::RandRange(0, CachedSpawnPoints.Num() - 1)];

	if (!SpawnPoint)
	{
		UE_LOG(LogWaveManager, Error, TEXT("Chosen spawn point was null"));
		return;
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	AShooterNPC* Enemy = GetWorld()->SpawnActor<AShooterNPC>(
		Wave.EnemyClass,
		SpawnPoint->GetActorTransform()
	);

	if (!Enemy)
	{
		UE_LOG(LogWaveManager, Error, TEXT("Failed to spawn enemy"));
		return;
	}
	
	Enemy->SpawnDefaultController();

	EnemiesSpawned++;
	EnemiesAlive++;

	UE_LOG(LogWaveManager, Log,
		TEXT("Enemy spawned. Spawned=%d Alive=%d"),
		EnemiesSpawned,
		EnemiesAlive
	);

	Enemy->OnEnemyKilled.AddDynamic(this, &AWaveManager::OnEnemyKilled);
}


void AWaveManager::OnEnemyKilled()
{
	EnemiesAlive--;
	
	if (EnemiesAlive <= 0 && EnemiesSpawned >= Waves[CurrentWaveIndex].EnemyCount)
		AdvanceWave();
}

void AWaveManager::AdvanceWave()
{
	CurrentWaveIndex++;
	
	if (Waves.IsValidIndex(CurrentWaveIndex))
	{
		StartWave();
	}
}

void AWaveManager::GetSpawnPoints()
{
	CachedSpawnPoints.Reset();
	
	if (!SpawnPointClass.IsValid())
		return;
	
	TSubclassOf<AActor> LoadedClass = SpawnPointClass.Get();
	
	if (!LoadedClass)
		return;
	
	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		LoadedClass,
		CachedSpawnPoints
		);
}







