#pragma once

#include "CoreMinimal.h"
#include "ItemEnums.generated.h"

UENUM(BlueprintType)
enum class EItem_S_Rarity : uint8
{
	Scrap       UMETA(DisplayName = "Scrap"),
	Crafted     UMETA(DisplayName = "Crafted"),
	Engineered  UMETA(DisplayName = "Engineered"),
	Relic       UMETA(DisplayName = "Relic")
};
