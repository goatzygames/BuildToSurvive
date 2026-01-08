// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveGame/SaveGameInstance.h"
#include "Block.generated.h"



UCLASS(Blueprintable)
class BUILDTOSURVIVE_API ABlock : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlock();
	
	UFUNCTION(BlueprintCallable)
	void SetBlockType(EBlockType NewType);

	UFUNCTION(BlueprintCallable)
	void SetPreview(bool bPreview);
	
	UFUNCTION(BlueprintCallable)
	bool IsPreview() const { return bIsPreview; };
	
	UFUNCTION(BlueprintCallable)
	void RemoveBlockHealth(float RemovedHealth);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BlockHealth { 1.0f };
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsPreview { false };
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterial;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
