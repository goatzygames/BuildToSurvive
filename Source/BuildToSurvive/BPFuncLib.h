// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFuncLib.generated.h"

/**
 * 
 */
UCLASS()
class BUILDTOSURVIVE_API UBPFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	static FVector SnapToGrid(const FVector& Location, float GridSize);
};
