// Copyright Epic Games, Inc. All Rights Reserved.

#include "BuildToSurviveCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BPFuncLib.h"
#include "BuildToSurvive.h"
#include "BlockPlacing/Block.h"

ABuildToSurviveCharacter::ABuildToSurviveCharacter()
{
	
	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void ABuildToSurviveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABuildToSurviveCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABuildToSurviveCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABuildToSurviveCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABuildToSurviveCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ABuildToSurviveCharacter::LookInput);
	}
	else
	{
		UE_LOG(LogBuildToSurvive, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABuildToSurviveCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateBlockPlacement();
}


void ABuildToSurviveCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ABuildToSurviveCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ABuildToSurviveCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ABuildToSurviveCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ABuildToSurviveCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ABuildToSurviveCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

bool ABuildToSurviveCharacter::TraceBlock(FHitResult& OutHit) const
{
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + FirstPersonCameraComponent->GetForwardVector() * 500.0f;

	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.bTraceComplex = false;
	
	return GetWorld()->LineTraceSingleByChannel(
		OutHit,
		Start,
		End,
		ECC_Visibility,
		Params
		);
}

void ABuildToSurviveCharacter::PlaceBlock(EBlockType NewBlockType)
{
	if (!bBlockPlacingActive || !PreviewBlock || PreviewBlock->IsHidden())
		return;
	
	PreviewBlock->SetPreview(false);
	PreviewBlock->SetBlockType(CurrentBlockType);
	
	PreviewBlock = GetWorld()->SpawnActor<ABlock>(
		BlockClass,
		FVector::ZeroVector,
		FRotator::ZeroRotator
		);
	
	if (PreviewBlock)
	{
		PreviewBlock->SetPreview(true);
		PreviewBlock->SetBlockType(CurrentBlockType);
	}
	
	PreviewBlock = nullptr;
}

void ABuildToSurviveCharacter::RemoveBlock()
{
	if (!bBlockPlacingActive)
		return;
	
	FHitResult Hit;
	if (!TraceBlock(Hit))
		return;
	
	if (ABlock* Block = Cast<ABlock>(Hit.GetActor()))
	{
		if (!Block->IsPreview())
		{
			Block->Destroy();
		}
	}
}

void ABuildToSurviveCharacter::CallFunctionByNameOnObject(UObject* Object, const FName FunctionName)
{
	if (!Object)
		return;
	
	if (UFunction* Func = Object->FindFunction(FunctionName))
		Object->ProcessEvent(Func, nullptr); 
}

void ABuildToSurviveCharacter::RefreshHotbarFunction()
{
	
}

void ABuildToSurviveCharacter::SetEquipmentChildActor(TSoftClassPtr<AActor> Actor)
{
	
}

void ABuildToSurviveCharacter::ToggleBlockPlacing()
{
	bBlockPlacingActive = !bBlockPlacingActive;
	
	if (bBlockPlacingActive)
	{
		PreviewBlock = GetWorld()->SpawnActor<ABlock>(
			BlockClass,
			FVector::ZeroVector,
			FRotator::ZeroRotator
			);
		
		PreviewBlock->SetPreview(true);
		PreviewBlock->SetBlockType(CurrentBlockType);
	}
	else
	{
		if (PreviewBlock)
		{
			PreviewBlock->Destroy();
			PreviewBlock = nullptr;
		}
	}
}


void ABuildToSurviveCharacter::UpdateBlockPlacement()
{
	if (!bBlockPlacingActive || !PreviewBlock)
		return;
	
	FHitResult Hit;
	if (!TraceBlock(Hit))
	{
		PreviewBlock->SetActorHiddenInGame(true);
		return;
	}
	
	const FVector RawLoc = Hit.ImpactPoint + Hit.ImpactNormal * 50.0f;
	const FVector SnapLoc = UBPFuncLib::SnapToGrid(RawLoc, 100.0f);
	
	PreviewBlock->SetActorHiddenInGame(false);
	PreviewBlock->SetActorLocation(SnapLoc);
}







