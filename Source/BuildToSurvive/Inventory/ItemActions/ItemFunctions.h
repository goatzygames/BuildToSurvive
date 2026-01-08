// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterWeapon.h"
#include "Components/ActorComponent.h"
#include "ItemFunctions.generated.h"

USTRUCT(BlueprintType)
struct FWeapons
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftClassPtr<AShooterWeapon> Rifle;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftClassPtr<AShooterWeapon> GrenadeLauncher;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftClassPtr<AShooterWeapon> Pistol;
	
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUILDTOSURVIVE_API UItemFunctions : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemFunctions();


	// Item functions referenced by name in Item Definitions
	
	UFUNCTION(BlueprintCallable)
	void UseRifle();
	
	UFUNCTION(BlueprintCallable)
	void UseGrenadeLauncher();
	
	UFUNCTION(BLueprintCallable)
	void UsePistol();
	
	UFUNCTION(BlueprintCallable)
	void StopPlacingBlock();
	
	UFUNCTION(BlueprintCallable)
	void UseDirtBlock();
	
	UFUNCTION(BlueprintCallable)
	void UseGrassBlock();
	
	UFUNCTION(BlueprintCallable)
	void UseStoneBlock();
	
	UFUNCTION(BlueprintCallable)
	void PlaceCurrentBlock();
	
	
	// Necessary variables to use
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FWeapons Weapons;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
};
