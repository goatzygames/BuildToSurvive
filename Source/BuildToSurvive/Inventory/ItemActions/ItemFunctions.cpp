// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemFunctions.h"

#include "BuildToSurviveCharacter.h"
#include "BuildToSurvivePlayerController.h"
#include "ShooterCharacter.h"
#include "BuildToSurvive/Inventory/InventoryComponent.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UItemFunctions::UItemFunctions()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UItemFunctions::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UItemFunctions::UseRifle()
{
	if (AShooterCharacter* Char = Cast<AShooterCharacter>(GetOwner()))
	{
		if (Weapons.Rifle.IsNull() == false)
		{
			UClass* WeaponClass = Weapons.Rifle.LoadSynchronous();
			Char->AddWeaponClass(WeaponClass);
		}
	}
}

void UItemFunctions::UseGrenadeLauncher()
{
	if (AShooterCharacter* Char = Cast<AShooterCharacter>(GetOwner()))
	{
		if (Weapons.GrenadeLauncher.IsNull() == false)
		{
			UClass* WeaponClass = Weapons.GrenadeLauncher.LoadSynchronous();
			Char->AddWeaponClass(WeaponClass);
		}
	}
}


void UItemFunctions::UsePistol()
{
	if (AShooterCharacter* Char = Cast<AShooterCharacter>(GetOwner()))
	{
		if (Weapons.Pistol.IsNull() == false)
		{
			UClass* WeaponClass = Weapons.Pistol.LoadSynchronous();
			Char->AddWeaponClass(WeaponClass);
		}
	}
}

void UItemFunctions::StopPlacingBlock()
{
	if (ABuildToSurviveCharacter* Char = Cast<ABuildToSurviveCharacter>(GetOwner()))
	{
		if (Char->bBlockPlacingActive)
		{
			Char->ToggleBlockPlacing();
		}
	}
}

void UItemFunctions::UseDirtBlock()
{
	if (ABuildToSurviveCharacter* Char = Cast<ABuildToSurviveCharacter>(GetOwner()))
	{
		if (Char->bBlockPlacingActive)
		{
			Char->ToggleBlockPlacing();
		}
		
		Char->CurrentBlockType = EBlockType::Dirt;
		Char->ToggleBlockPlacing();
	}
}

void UItemFunctions::UseGrassBlock()
{
	if (ABuildToSurviveCharacter* Char = Cast<ABuildToSurviveCharacter>(GetOwner()))
	{
		if (Char->bBlockPlacingActive)
		{
			Char->ToggleBlockPlacing();
		}
		
		Char->CurrentBlockType = EBlockType::Grass;
		Char->ToggleBlockPlacing();
	}
}

void UItemFunctions::UseStoneBlock()
{
	if (ABuildToSurviveCharacter* Char = Cast<ABuildToSurviveCharacter>(GetOwner()))
	{
		if (Char->bBlockPlacingActive)
		{
			Char->ToggleBlockPlacing();
		}
		
		Char->CurrentBlockType = EBlockType::Stone;
		Char->ToggleBlockPlacing();
	}
}

void UItemFunctions::PlaceCurrentBlock()
{
	if (ABuildToSurviveCharacter* Char = Cast<ABuildToSurviveCharacter>(GetOwner()))
	{
		if (Char->bBlockPlacingActive)
		{
			Char->PlaceBlock(Char->CurrentBlockType);
			Char->ToggleBlockPlacing();
		};
	}
}











