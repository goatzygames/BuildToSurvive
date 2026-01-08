// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveGameInstance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EBlockType : uint8
{
	Dirt,
	Stone,
	Grass
};

UCLASS(Blueprintable)
class BUILDTOSURVIVE_API USaveGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* DirtMat;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* StoneMat;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* GrassMat;
	
};
