// Fill out your copyright notice in the Description page of Project Settings.

#pragma once // Prevent multiple header inclusions

#include "CoreMinimal.h" // Basic engine types/macros
#include "GameFramework/Actor.h" // Base actor class header
#include "Components/TextRenderComponent.h" // Text rendering component header
#include "Components/StaticMeshComponent.h" // Static mesh component header
#include "Resource_M.generated.h" // Unreal reflection system header

UCLASS() // Macro for Unreal classes
class GAM312_PRATTS_API AResource_M : public AActor // Define resource actor class
{
	GENERATED_BODY() // Boilerplate for engine functionality

public:
	// Sets default values for this actor's properties
	AResource_M(); // Class constructor declaration

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; // Initial setup function override

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override; // Frame update function override

	UPROPERTY(EditAnywhere) // Editable in editor details
		FString resourceName = "Wood"; // Name of this resource

	UPROPERTY(EditAnywhere) // Editable in editor details
		int resourceAmount = 5; // Amount harvested per click

	UPROPERTY(EditAnywhere) // Editable in editor details
		int totalResource = 100; // Remaining total pool amount

	UPROPERTY() // Tracked by garbage collection
		FText tempText; // Temporary text formatting variable

	UPROPERTY(EditAnywhere) // Editable in editor details
		UTextRenderComponent* ResourceNameTxt; // World space text pointer

	UPROPERTY(EditAnywhere) // Editable in editor details
		UStaticMeshComponent* Mesh; // Visual 3D model pointer

};