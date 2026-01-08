// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CraftableItemDefinition.h"
#include "BuildToSurvive/Inventory/ItemInstance.h"
#include "ItemInstance.h"
#include "ItemDefinition.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUILDTOSURVIVE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UInventoryComponent();
	
	// UPROPERTIES

	// New
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FItemInstance> ItemInstances;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TArray<UItemDefinition*> AvailableItemDefinitions;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TArray<UItemDefinition*> AllAvailableItemDefinitions;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TArray<UCraftableItemDefinition*> CraftableItems;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	UItemDefinition* CurrentEquippedItem = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TArray<FItemInstance> HotbarItemInstances;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	int32 CurrentHotbarIndex { -1 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 SlotAmount { 25 };

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	int32 HotbarSlotAmount { 9 };

	// UFUNCTIONS

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(FItemInstance AddedItem, const bool bDontAdd, bool bAddInHotbar = true);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(const FItemInstance& RemovedItem, bool bDontRemove);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RefreshInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory Helper Functions")
	void SetMaxSlotAmount(const int32 NewMaxSlotAmount);

	UFUNCTION(BlueprintPure, Category = "Inventory Helper Functions")
	int32 GetUsedSlotsAmount();

	UFUNCTION(BlueprintCallable, Category = "Inventory Helper Functions")
	bool SetItemElementAtIndex(FItemInstance NewItem, int32 Index);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool DoesElementExistByName(FString Name);

	UFUNCTION(BlueprintPure, Category = "Inventory Helper Functions")
	bool DoesElementExistByNameAndIfQuantity(FString Name, int32 Quantity);

	UFUNCTION(BlueprintPure, Category = "Inventory Helper Functions")
	int32 FindItemByName(FString Name);

	UFUNCTION(BlueprintPure, Category = "Inventory Helper Functions")
	int32 FindItemByNameAndIfQuantity(FString Name, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void OrganiseItems();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory Helper Functions")
	static void CallFunctionByName(UObject* WorldContext, FName ActorName, FName FunctionName);

	UFUNCTION(BlueprintCallable, Category = "Inventory Helper Functions")
	void CallFunctionOnOwner(FName FunctionName);

	UFUNCTION(BlueprintPure, Category = "Inventory Helper Functions")
	FString GetNameFromItemInstance(FItemInstance InputItemInstance);

	UFUNCTION(BlueprintPure, Category = "Inventory Helper Functions")
	UItemDefinition* GetDefinitionFromInstance(const FItemInstance& InputItemInstance);

	UFUNCTION(BlueprintCallable, Category = "Inventory Helper Functions")
	void SortCraftableItemArray();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CanCraftItem(UCraftableItemDefinition* ItemDef, bool bDontRemove = false);

	UFUNCTION(BlueprintCallable, Category = "Inventory Helper Functions")
	int32 GetAmountOfItem(UItemDefinition* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UItemDefinition* GetItemDefinition(FString Name);

	UFUNCTION(BlueprintCallable, Category = "Inventory Helper Functions")
	UItemDefinition* GetItemDefinitionByItemID(FName ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AssignInventorySlotToHotbar(int32 InventoryIndex, int32 HotbarIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool EquipFromHotbar(int32 HotbarIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CanAddItemToItemArray(TArray<FItemInstance> InArray);

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void RefreshHotbar();

	virtual void RefreshHotbar_Implementation();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
