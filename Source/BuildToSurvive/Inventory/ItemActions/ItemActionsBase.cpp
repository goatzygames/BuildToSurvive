// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActionsBase.h"

#include "BuildToSurviveCharacter.h"
#include "BuildToSurvive/Inventory/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"


void UItemActionsBase::EquipItem_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("EQUIPPED"));
}

void UItemActionsBase::UnequipItem_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("UNEQUIPPED"));
}

void UItemActionsBase::SetMeshEquippedOnCharacter_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("SET MESH EQUIPPED ON CHAR"));
}








