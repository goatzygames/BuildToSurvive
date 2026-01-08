// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFuncLib.h"


FVector UBPFuncLib::SnapToGrid(const FVector& Location, float GridSize)
{
	const float Half = GridSize * 0.5f;

	return FVector(
		FMath::FloorToFloat(Location.X / GridSize) * GridSize + Half,
		FMath::FloorToFloat(Location.Y / GridSize) * GridSize + Half,
		FMath::FloorToFloat(Location.Z / GridSize) * GridSize + Half
	);
}
