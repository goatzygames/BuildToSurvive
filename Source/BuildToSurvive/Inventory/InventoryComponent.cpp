// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "BuildToSurviveCharacter.h"
#include "EngineUtils.h"
#include "Engine/DataAsset.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	HotbarItemInstances.SetNum(5);

	// Craftable items
	SortCraftableItemArray();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UInventoryComponent::RefreshInventory()
{
	OrganiseItems();
	CallFunctionByName(this, "BP_Character", "RefreshItemsOnWidget");
}

void UInventoryComponent::SetMaxSlotAmount(const int32 NewMaxSlotAmount)
{
	SlotAmount = NewMaxSlotAmount;
	ItemInstances.SetNum(NewMaxSlotAmount);
}

void UInventoryComponent::CallFunctionByName(UObject* WorldContext, FName ActorName, FName FunctionName)
{
	if (!WorldContext) return;

	UWorld* World = WorldContext->GetWorld();
	if  (!World) return;

	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor && Actor->GetName() == ActorName)
		{
			UFunction* Function = Actor->FindFunction(FunctionName);
			if (Function)
			{
				Actor->ProcessEvent(Function, nullptr);
			}
			return;
		}
	}
}

void UInventoryComponent::CallFunctionOnOwner(FName FunctionName)
{
	if (AActor* OwnerActor = GetOwner())
	{
		if (UFunction* Function = OwnerActor->FindFunction(FunctionName))
		{
			OwnerActor->ProcessEvent(Function, nullptr);
		}
	}
}


bool UInventoryComponent::AddItem(FItemInstance AddedItem, const bool bDontAdd, bool bAddInHotbar)
{
	if (!AddedItem.Definition || AddedItem.Quantity <= 0)
		return false;

	ABuildToSurviveCharacter* Character = Cast<ABuildToSurviveCharacter>(GetOwner());
	if (!Character)
		return false;

	if (!bAddInHotbar)
	{
		for (FItemInstance& Item : ItemInstances)
		{
			if (Item.Definition && Item.Definition->ItemID == AddedItem.Definition->ItemID)
			{
				if (!bDontAdd)
					Item.Quantity += AddedItem.Quantity;
				Character->RefreshHotbarFunction();
				return true;
			}
		}

		for (FItemInstance& Item : ItemInstances)
		{
			if (!Item.Definition || Item.Quantity <= 0)
			{
				if (!bDontAdd)
					Item = AddedItem;
				Character->RefreshHotbarFunction();
				return true;
			}
		}
	}

	// Hotbar time!!!

	bool bCanAddToHotbar = CanAddItemToItemArray(HotbarItemInstances);
	
		for (FItemInstance& Item : HotbarItemInstances)
		{
			if (Item.Definition && Item.Definition->ItemID == AddedItem.Definition->ItemID)
			{
				if (!bDontAdd)
					Item.Quantity += AddedItem.Quantity;
				Character->RefreshHotbarFunction();
				return true;
			}
		}

	if (bCanAddToHotbar)
	{
		for (FItemInstance& Item : HotbarItemInstances)
		{
			if (!Item.Definition || Item.Quantity <= 0)
			{
				if (!bDontAdd)
					Item = AddedItem;
				Character->RefreshHotbarFunction();
				return true;
			}
		}
	}

	return false;
}

bool UInventoryComponent::RemoveItem(const FItemInstance& RemovedItem, bool bDontRemove)
{
	if (RemovedItem.Quantity <= 0 || !RemovedItem.Definition)
		return false;

	ABuildToSurviveCharacter* Character = Cast<ABuildToSurviveCharacter>(GetOwner());
	if (!Character)
		return false;

	int32 RemainingToRemove = RemovedItem.Quantity;

	// Helper lambda to remove from a single array
	auto RemoveFromArray = [&](TArray<FItemInstance>& Array)
	{
		for (FItemInstance& Item : Array)
		{
			if (RemainingToRemove <= 0)
				break;

			if (Item.Definition && Item.Definition->ItemID == RemovedItem.Definition->ItemID)
			{
				if (Item.Quantity > RemainingToRemove)
				{
					if (!bDontRemove)
						Item.Quantity -= RemainingToRemove;
					RemainingToRemove = 0;
					break;
				}
				else
				{
					RemainingToRemove -= Item.Quantity;
					if (!bDontRemove)
						Item = FItemInstance();
				}
			}
		}
	};

	// Remove from inventory first
	RemoveFromArray(ItemInstances);

	// Then remove from hotbar if needed
	RemoveFromArray(HotbarItemInstances);
	Character->RefreshHotbarFunction();
	return RemainingToRemove <= 0;
}


int32 UInventoryComponent::GetUsedSlotsAmount()
{
	int32 UsedSlots {0};
	for (auto& CurrentInstance : ItemInstances)
	{
		if (CurrentInstance.Quantity > 0) UsedSlots++;
	}

	return UsedSlots;
}

bool UInventoryComponent::SetItemElementAtIndex(FItemInstance NewItem, int32 Index)
{
	ItemInstances[Index] = NewItem;
	return true;
}

bool UInventoryComponent::DoesElementExistByName(FString Name)
{
	for (int32 Index = 0; Index < ItemInstances.Num(); Index++)
	{
		if (ItemInstances[Index].Definition->ItemID.ToString() == Name || ItemInstances[Index].Definition->ItemID.ToString().Contains(Name))
		{
			return true;
		}
	}

	return false;
}

int32 UInventoryComponent::FindItemByNameAndIfQuantity(FString Name, int32 Quantity)
{
	for (int32 Index = 0; Index < ItemInstances.Num(); Index++)
	{
		if (ItemInstances[Index].Definition->DisplayName.ToString() == Name && ItemInstances[Index].Quantity == Quantity)
		{
			return Index;
		}
	}

	return -1;
}

bool UInventoryComponent::DoesElementExistByNameAndIfQuantity(FString Name, int32 Quantity)
{
	for (int32 Index = 0; Index < ItemInstances.Num(); Index++)
	{
		if (ItemInstances[Index].Definition->DisplayName.ToString() == Name && ItemInstances[Index].Quantity == Quantity)
		{
			return true;
		}
	}

	return false;
}

int32 UInventoryComponent::FindItemByName(FString Name)
{
	for (int32 Index = 0; Index < ItemInstances.Num(); Index++)
	{
		if (ItemInstances[Index].Definition->ItemID.ToString() == Name || ItemInstances[Index].Definition->ItemID.ToString().Contains(Name))
		{
			return Index;
		}
	}

	return -1;
}

void UInventoryComponent::OrganiseItems()
{
	TArray<FItemInstance> ItemInstancesTemp;
	for (FItemInstance& a : ItemInstances)
	{
		if (a.Definition->DisplayName.ToString() != "None") ItemInstancesTemp.Add(a);
	}

	ItemInstancesTemp.SetNum(SlotAmount);
	ItemInstances = ItemInstancesTemp;
}

FString UInventoryComponent::GetNameFromItemInstance(FItemInstance InputItemInstance)
{
	return InputItemInstance.Definition->DisplayName.ToString();
}


UItemDefinition* UInventoryComponent::GetDefinitionFromInstance(const FItemInstance& InputItemInstance)
{
	return InputItemInstance.Definition;
}



void UInventoryComponent::SortCraftableItemArray()
{
	CraftableItems.Sort([](const UCraftableItemDefinition& A, const UCraftableItemDefinition& B)
	{
		return static_cast<int32>(A.Rarity) < static_cast<int32>(B.Rarity);
	});
}


bool UInventoryComponent::CanCraftItem(UCraftableItemDefinition* ItemDef, bool bDontRemove)
{
	if (!ItemDef) return false;

	// Check total amount (inventory + hotbar)
	for (const auto& Ingredient : ItemDef->CraftingIngredients)
	{
		int32 AmountInInventory = GetAmountOfItem(Ingredient.IngredientItem);
		int32 AmountInHotbar = 0;
		for (const FItemInstance& HotbarItem : HotbarItemInstances)
		{
			if (HotbarItem.Definition && HotbarItem.Definition->ItemID == Ingredient.IngredientItem->ItemID)
			{
				AmountInHotbar += HotbarItem.Quantity;
			}
		}

		if ((AmountInInventory + AmountInHotbar) < Ingredient.Quantity)
		{
			return false; // missing ingredient
		}
	}

	if (!bDontRemove)
	{
		for (const auto& Ingredient : ItemDef->CraftingIngredients)
		{
			RemoveItem(FItemInstance(Ingredient.IngredientItem, Ingredient.Quantity), false);
			RefreshHotbar();
		}
	}


	return true;
}



int32 UInventoryComponent::GetAmountOfItem(UItemDefinition* Item)
{
	if (!Item) return 0;

	int32 Total = 0;

	for (int32 Index = 0; Index < ItemInstances.Num(); Index++)
	{
		if (ItemInstances[Index].Definition && 
			ItemInstances[Index].Definition->ItemID == Item->ItemID)
		{
			Total += ItemInstances[Index].Quantity;
		}
	}

	return Total;
}

UItemDefinition* UInventoryComponent::GetItemDefinition(FString Name)
{
	for (UItemDefinition* Element : AvailableItemDefinitions)
	{
		if (Element->ItemID.ToString().Contains(Name) || Element->DisplayName.ToString().Contains(Name))
		{
			return Element;
		}
	}

	return nullptr;
}

UItemDefinition* UInventoryComponent::GetItemDefinitionByItemID(FName ItemID)
{
	for (UItemDefinition* Element : AllAvailableItemDefinitions)
	{
		if (Element->ItemID == ItemID || Element->DisplayName.ToString() == ItemID.ToString())
		{
			return Element;
		}
	}
	return nullptr;
}

bool UInventoryComponent::AssignInventorySlotToHotbar(int32 InventoryIndex, int32 HotbarIndex)
{
	if (!ItemInstances.IsValidIndex(InventoryIndex) || !HotbarItemInstances.IsValidIndex(HotbarIndex))
		return false;

	FItemInstance& InventoryItem = ItemInstances[InventoryIndex];
	if (!InventoryItem.Definition || InventoryItem.Quantity <= 0)
		return false;

	FItemInstance& TargetSlot = HotbarItemInstances[HotbarIndex];

	// Try stacking if same item
	if (TargetSlot.Definition && TargetSlot.Definition->ItemID == InventoryItem.Definition->ItemID)
	{
		TargetSlot.Quantity += InventoryItem.Quantity;
		RemoveItem(InventoryItem, false);
		RefreshHotbar();
		return true;
	}

	// If slot empty, assign directly
	if (!TargetSlot.Definition || TargetSlot.Quantity <= 0)
	{
		TargetSlot = InventoryItem;
		RemoveItem(InventoryItem, false);
		RefreshHotbar();
		return true;
	}

	// Try find any empty slot in hotbar
	for (FItemInstance& Slot : HotbarItemInstances)
	{
		if (!Slot.Definition || Slot.Quantity <= 0)
		{
			Slot = InventoryItem;
			RemoveItem(InventoryItem, false);
			RefreshHotbar();
			return true;
		}
	}

	return false;
}


bool UInventoryComponent::EquipFromHotbar(int32 HotbarIndex)
{
	if (!HotbarItemInstances.IsValidIndex(HotbarIndex))
		return false;

	FItemInstance& Slot = HotbarItemInstances[HotbarIndex];
	if (!Slot.Definition)
		return false;

	return true;
}

bool UInventoryComponent::CanAddItemToItemArray(TArray<FItemInstance> InArray)
{
	for (const FItemInstance& ExistingItem : InArray)
	{
		if (!ExistingItem.Definition || ExistingItem.Quantity <= 0)
		{
			return true; // Empty slot found
		}
	}
	return false;
}

void UInventoryComponent::RefreshHotbar_Implementation()
{
	
}


















