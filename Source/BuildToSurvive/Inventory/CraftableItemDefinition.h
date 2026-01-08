// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDefinition.h"
#include "CraftableItemDefinition.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FCraftingIngredient
{
	GENERATED_BODY()

	FCraftingIngredient()
		: IngredientItem(nullptr)
		, Quantity(1)
	{}

	// What item this ingredient is
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UItemDefinition* IngredientItem;

	// How many units needed
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Quantity;
};



UCLASS(BlueprintType)
class BUILDTOSURVIVE_API UCraftableItemDefinition : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Craftable Item")
	UItemDefinition* ResultItem;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Craftable Item")
	ERarity Rarity { ERarity::Basic };

	// Category (building, resource, consumable, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Craftable Item")
	FName Category;

	// Crafting requirements
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Craftable Crafting")
	TArray<FCraftingIngredient> CraftingIngredients;

	// Crafting time (seconds)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Craftable Crafting")
	float CraftingTime { 1.0f };
	
};
