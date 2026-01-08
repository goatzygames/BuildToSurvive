// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemActionsBase.generated.h"

/**
 * 
 */
UCLASS()
class BUILDTOSURVIVE_API UItemActionsBase : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "Item Actions")
	void EquipItem();

	UFUNCTION(BlueprintNativeEvent, Category = "Item Actions")
	void UnequipItem();

	UFUNCTION(BlueprintNativeEvent, Category = "Item Actions")
	void SetMeshEquippedOnCharacter();
};
