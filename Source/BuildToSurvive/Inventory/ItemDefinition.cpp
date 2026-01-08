// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDefinition.h"
#include "BuildToSurviveCharacter.h"
#include "BuildToSurvivePlayerController.h"
#include "InventoryComponent.h"
#include "BuildToSurvive/Inventory/ItemActions/ItemFunctions.h"
#include "ItemActions/ItemFunctions.h"
#include "Kismet/GameplayStatics.h"


void UItemDefinition::UseItem(AActor* Instigator)
{
	if (!Instigator) return;

	if (ABuildToSurviveCharacter* Character = Cast<ABuildToSurviveCharacter>(Instigator))
	{
		if (UItemFunctions* ItemFunctionsComp = Character->FindComponentByClass<UItemFunctions>())
		{
			Character->CallFunctionByNameOnObject(ItemFunctionsComp, FName(UseFunctionName));
		}
	}
}

void UItemDefinition::EquipItem(AActor* Instigator)
{
		if (ABuildToSurviveCharacter* Character = Cast<ABuildToSurviveCharacter>(Instigator))
		{
			if (UItemFunctions* Comp = Character->FindComponentByClass<UItemFunctions>())
			{
				if (EquipFunctionName_OVERRIDE.IsEmpty())
					return;
				Character->CallFunctionByNameOnObject(Comp, FName(EquipFunctionName_OVERRIDE));
				if (UInventoryComponent* Inv = Character->FindComponentByClass<UInventoryComponent>())
					Inv->CurrentEquippedItem = this;
				return;
			}
		}
	
	if (!Instigator)
		return;

	if (ABuildToSurviveCharacter* Character = Cast<ABuildToSurviveCharacter>(Instigator))
	{
		if (ItemType == EItemType::Other)
		{
			Character->SetEquipmentChildActor(Actor);
		}
		else if (ItemType == EItemType::Block)
		{
			// 
		}
	}
}

void UItemDefinition::UnequipItem(AActor* Instigator)
{
	if (!UnequipFunctionName_OVERRIDE.IsEmpty())
	{
		if (ABuildToSurviveCharacter* Character = Cast<ABuildToSurviveCharacter>(Instigator))
		{
			if (UItemFunctions* Comp = Character->FindComponentByClass<UItemFunctions>())
			{
				Character->CallFunctionByNameOnObject(Comp, FName(UnequipFunctionName_OVERRIDE));
				if (UInventoryComponent* Inv = Character->FindComponentByClass<UInventoryComponent>())
					Inv->CurrentEquippedItem = nullptr;
				return;
			}
		}
	}
	
	if (!Instigator)
		return;

	if (ABuildToSurviveCharacter* Character = Cast<ABuildToSurviveCharacter>(Instigator))
	{
		if (ItemType == EItemType::Other)
		{
			Character->SetEquipmentChildActor(nullptr);
		}
		if (ItemType == EItemType::Block)
		{
			if (ItemID.ToString().ToLower().Contains("dirt"))
				Character->CurrentBlockType = EBlockType::Dirt;
			else if (ItemID.ToString().ToLower().Contains("grass"))
				Character->CurrentBlockType = EBlockType::Grass;
			else if (ItemID.ToString().ToLower().Contains("stone"))
				Character->CurrentBlockType = EBlockType::Stone;
		}
	}
}



