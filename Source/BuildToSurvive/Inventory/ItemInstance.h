
#pragma once

#include "ItemDefinition.h"
#include "ItemInstance.generated.h"

USTRUCT(BlueprintType)
struct FItemInstance
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Item Instance")
	UItemDefinition* Definition;

	UPROPERTY(BlueprintReadWrite, Category = "Item Instance")
	int32 Quantity;

	UPROPERTY()
	FTransform Transform;

	FItemInstance()
	: Definition(nullptr), Quantity(0)
	{}

	// Convenience constructor
	FItemInstance(UItemDefinition* InDefinition, int32 InQuantity)
		: Definition(InDefinition), Quantity(InQuantity), Transform()
	{}
};
