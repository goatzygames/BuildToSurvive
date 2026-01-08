// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDefinition.generated.h"


UENUM(BlueprintType)
enum class ERarity : uint8
{
	Basic UMETA(DisplayName = "Basic"),
	Processed UMETA(DisplayName = "Processed"),
	Advanced UMETA(DisplayName = "Advanced"),
	Exotic UMETA(DisplayName = "Exotic"),
	Ancient UMETA(DisplayName = "Ancient")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon UMETA(DisplayName="Weapon"),
	Block UMETA(DisplayName="Block"),
	Other UMETA(DisplayName="Other")
};

/**
 * 
 */
UCLASS(BlueprintType)
class BUILDTOSURVIVE_API UItemDefinition : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Default")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Default")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Default")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Default")
	int32 Price = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Default")
	ERarity Rarity = ERarity::Basic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Default")
	UTexture2D* Icon = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Other")
	UStaticMesh* Mesh = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item Other")
	UMaterialInterface* Material = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Item Other")
	float MeshScale { 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Other")
	float Durability = 1.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item Functions")
	FString UseFunctionName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item Functions")
	FString EquipFunctionName_OVERRIDE;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item Functions")
	FString UnequipFunctionName_OVERRIDE;

	UFUNCTION(BlueprintCallable, Category = "Item Functions")
	void UseItem(AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category = "Item Functions")
	void EquipItem(AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category = "Item Functions")
	void UnequipItem(AActor* Instigator);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item Functions")
	bool bEquippable;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item Functions")
	bool bEquipOntoHand;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item Functions")
	bool bPlacable;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Other")
	TSoftClassPtr<AActor> Actor;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Other")
	EItemType ItemType;
};












