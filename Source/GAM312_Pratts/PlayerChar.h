

#pragma once // Prevent multiple header inclusions

#include "CoreMinimal.h" // Basic Unreal engine types
#include "GameFramework/Character.h" // Base character class header
#include "Camera/CameraComponent.h" // Camera component functionality header
#include "Resource_M.h" // Custom resource class header
#include "Kismet/GameplayStatics.h" // Common engine utility functions
#include "Buildingpart.h"
#include "playerwidget.h"
#include "objectivewidget.h"
#include "PlayerChar.generated.h" // Unreal reflection system header

UCLASS() // Macro for Unreal classes
class GAM312_PRATTS_API APlayerChar : public ACharacter // Define player character class
{
	GENERATED_BODY() // Boilerplate for engine functionality

public:
	// Sets default values for this character's properties
	APlayerChar(); // Class constructor declaration

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; // Initial setup function override

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override; // Frame update function override

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // Input binding function override

	UFUNCTION() // Expose to reflection system
		void MoveForward(float axisValue); // Forward movement function declaration

	UFUNCTION() // Expose to reflection system
		void MoveRight(float axisValue); // Sideways movement function declaration

	UFUNCTION() // Expose to reflection system
		void StartJump(); // Jump initiation function declaration

	UFUNCTION() // Expose to reflection system
		void StopJump(); // Jump cessation function declaration

	UFUNCTION() // Expose to reflection system
		void FindObject(); // Interaction/Raycast function declaration

	UPROPERTY(VisibleAnywhere) // Show in editor details
		UCameraComponent* PlayerCamComp; // First person camera pointer

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats") // Editable health variable properties
		float Health = 100.0f; // Current health value tracker

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats") // Editable hunger variable properties
		float Hunger = 100.0f; // Current hunger value tracker

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats") // Editable stamina variable properties
		float Stamina = 100.0f; // Current stamina value tracker

	UPROPERTY(EditAnywhere, Category = "Resources") // Editable wood variable properties
		int Wood; // Wood quantity integer tracker

	UPROPERTY(EditAnywhere, Category = "Resources") // Editable stone variable properties
		int Stone; // Stone quantity integer tracker

	UPROPERTY(EditAnywhere, Category = "Resources") // Editable berry variable properties
		int Berry; // Berry quantity integer tracker

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources") // Editable resource array properties
		TArray<int> ResourcesArray; // Inventory counts dynamic array

	UPROPERTY(EditAnywhere, Category = "Resources") // Editable name array properties
		TArray<FString> ResourcesNameArray; // Inventory labels dynamic array

	UPROPERTY(EditAnywhere, Category = "HitMarker") // Editable decal material properties
		UMaterialInterface* hitDecal; // Visual feedback material pointer
//-------------------week3---------------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Supplies")
	TArray<int> BuildingArray; // Inventory for parts

	UPROPERTY()
	bool isBuilding; // Current building status

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ABuildingPart> BuildPartClass; // Building actor class

	UPROPERTY()
	ABuildingPart* spawnedPart; // Reference to instance

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerWidget* playerUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObjectiveWidget* objWidget;

	UPROPERTY()
	float objectsBuilt;

	UPROPERTY()
	float matsCollected;

	UFUNCTION(BlueprintCallable) // Callable from Unreal Blueprints
		void SetHealth(float amount); // Health modifier function declaration

	UFUNCTION(BlueprintCallable) // Callable from Unreal Blueprints
		void SetHunger(float amount); // Hunger modifier function declaration

	UFUNCTION(BlueprintCallable) // Callable from Unreal Blueprints
		void SetStamina(float amount); // Stamina modifier function declaration

	UFUNCTION() // Expose to reflection system
		void DecreaseStats(); // Automated stat decay function

	UFUNCTION() // Expose to reflection system
		void GiveResource(float amount, FString resourceType); // Add items to inventory
//--------------------Week3---------------------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable) // Expose to Blueprints
		void UpdateResources(float woodAmount, float stoneAmount, FString buildingObject); // Handle resource logic

	UFUNCTION(BlueprintCallable) // Expose to Blueprints
		void SpawnBuilding(int buildingID, bool& isSuccess); // Create building instance

	UFUNCTION() // Enable engine reflection
		void RotateBuilding(); // Handle part rotation
};