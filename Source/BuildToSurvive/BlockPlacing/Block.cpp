// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

#include "SaveGame/SaveGameInstance.h"


// Sets default values
ABlock::ABlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
	
	Mesh->SetStaticMesh(CubeMesh.Object);
	Mesh->SetWorldScale3D(FVector(1.0f));
	Mesh->SetCollisionProfileName("BlockAll");
	
	SetReplicates(false);
	SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlock::SetBlockType(EBlockType NewType)
{
	USaveGameInstance* GameInst = Cast<USaveGameInstance>(GetGameInstance());
	if (!GameInst)
		return;

	UMaterialInterface* BaseMat = nullptr;

	switch (NewType)
	{
	case EBlockType::Dirt:
		BaseMat = GameInst->DirtMat;
		BlockHealth = 2.0f;
		break;
	case EBlockType::Grass:
		BaseMat = GameInst->GrassMat;
		BlockHealth = 2.0f;
		break;
	case EBlockType::Stone:
		BaseMat = GameInst->StoneMat;
		BlockHealth = 5.0f;
		break;
	}

	if (BaseMat)
	{
		// Create a dynamic material instance from the UMaterialInterface
		DynMaterial = UMaterialInstanceDynamic::Create(BaseMat, this);
		Mesh->SetMaterial(0, DynMaterial);
		
		DynMaterial->SetScalarParameterValue("Opacity", bIsPreview ? 0.5f : 1.0f);
	}
}


void ABlock::SetPreview(bool bPreview)
{
	bIsPreview = bPreview;

	if (bIsPreview)
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetCollisionProfileName("NoCollision");
		
		Mesh->SetRenderCustomDepth(true);
		Mesh->SetCustomDepthStencilValue(1);
		
		if (DynMaterial)
		{
			DynMaterial->SetScalarParameterValue("Opacity", 0.5f); // or 0.6
		}
	}
	else
	{
		Mesh->SetCollisionProfileName("BlockAll");
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		Mesh->SetRenderCustomDepth(false);
		
		if (DynMaterial)
		{
			DynMaterial->SetScalarParameterValue("Opacity", 1.0f);
		}
	}
}

void ABlock::RemoveBlockHealth(float RemovedHealth)
{
	BlockHealth -= RemovedHealth;
	
	if (BlockHealth <= 0.0f)
		Destroy();
}








