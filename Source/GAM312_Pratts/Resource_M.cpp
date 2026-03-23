// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource_M.h" // Include resource header file

// Sets default values
AResource_M::AResource_M()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // Allow actor to tick

	ResourceNameTxt = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render")); // Create text display component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); // Create static mesh component

	RootComponent = Mesh; // Set mesh as root

	ResourceNameTxt->SetupAttachment(Mesh); // Attach text to mesh
}

// Called when the game starts or when spawned
void AResource_M::BeginPlay()
{
	Super::BeginPlay(); // Call base begin play

	tempText = tempText.FromString(resourceName); // Convert string to FText

	ResourceNameTxt->SetText(tempText); // Update world text display
}

// Called every frame
void AResource_M::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call base tick function
}