// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlockPlacing/Block.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SaveGame/SaveGameInstance.h"
#include "BuildToSurviveCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A basic first person character
 */
UCLASS(abstract)
class ABuildToSurviveCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* EquipmentChildActor;
	
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Building")
	TSubclassOf<ABlock> BlockClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Building")
	bool bBlockPlacingActive { false };
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Building")
	EBlockType CurrentBlockType;

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* MouseLookAction;
	
public:
	ABuildToSurviveCharacter();
	
	virtual void Tick(float DeltaTime) override;

public:

	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();
	
	
	// Build stuff
	
	UFUNCTION(BlueprintCallable, Category="Building")
	bool TraceBlock(FHitResult& OutHit) const;
	
	UFUNCTION(BlueprintCallable, Category="Building")
	void PlaceBlock(EBlockType NewBlockType);
	
	UFUNCTION(BlueprintCallable, Category="Building")
	void RemoveBlock();
	
	UFUNCTION(BlueprintCallable, Category="Building")
	void ToggleBlockPlacing();
	
	
	// Inventory stuff
	
	UFUNCTION(BlueprintNativeEvent, Category="Inventory")
	void RefreshHotbarFunction();
	
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void SetEquipmentChildActor(TSoftClassPtr<AActor> Actor);
	
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void CallFunctionByNameOnObject(UObject* Object, const FName FunctionName);

protected:

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
	UPROPERTY()
	ABlock* PreviewBlock;
	
	UFUNCTION()
	void UpdateBlockPlacement();
	

public:

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

