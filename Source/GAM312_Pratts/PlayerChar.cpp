#include "PlayerChar.h"

// Sets default values
APlayerChar::APlayerChar()
{
	PrimaryActorTick.bCanEverTick = true; // Enable frame updates
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Cam")); // Create camera component

	PlayerCamComp->SetupAttachment(GetMesh(), "head"); // Attach camera to head

	PlayerCamComp->bUsePawnControlRotation = true; // Use mouse for rotation

	ResourcesArray.SetNum(3); // Set array size
	ResourcesNameArray.Add(TEXT("Wood")); // Add Wood label
	ResourcesNameArray.Add(TEXT("Stone")); // Add Stone label
	ResourcesNameArray.Add(TEXT("Berry")); // Add Berry label
}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay(); // Call base logic

	FTimerHandle StatsTimerHandle; // Handle for timer
	GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, &APlayerChar::DecreaseStats, 2.0f, true); // Loop stats reduction
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call base update
}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); // Call base input
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerChar::MoveForward); // Bind movement forward
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerChar::MoveRight); // Bind movement right
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerChar::AddControllerPitchInput); // Bind vertical look
	PlayerInputComponent->BindAxis("Turn", this, &APlayerChar::AddControllerYawInput); // Bind horizontal look
	PlayerInputComponent->BindAction("JumpEvent", IE_Pressed, this, &APlayerChar::StartJump); // Bind jump start
	PlayerInputComponent->BindAction("JumpEvent", IE_Released, this, &APlayerChar::StopJump); // Bind jump stop
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerChar::FindObject); // Bind interaction key
}

void APlayerChar::MoveForward(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X); // Get forward vector
	AddMovementInput(Direction, axisValue); // Apply forward movement
}

void APlayerChar::MoveRight(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y); // Get right vector
	AddMovementInput(Direction, axisValue); // Apply right movement
}

void APlayerChar::StartJump()
{
	bPressedJump = true; // Set jump state
}

void APlayerChar::StopJump()
{
	bPressedJump = false; // Clear jump state
}

void APlayerChar::FindObject()
{
	FHitResult HitResult; // Store hit data
	FVector StartLocation = PlayerCamComp->GetComponentLocation(); // Trace start point
	FVector Direction = PlayerCamComp->GetForwardVector() * 800.0f; // Trace distance/direction
	FVector EndLocation = StartLocation + Direction; // Trace end point

	FCollisionQueryParams QueryParams; // Trace settings
	QueryParams.AddIgnoredActor(this); // Ignore player character
	QueryParams.bTraceComplex = true; // Use complex collision
	QueryParams.bReturnFaceIndex = true; // Return hit surface

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams)) // Execute line trace
	{
		AResource_M* HitResource = Cast<AResource_M>(HitResult.GetActor()); // Check for resource

		if (Stamina > 5.0f) // Check stamina level
		{
			if (HitResource) // If resource found
			{
				FString hitName = HitResource->resourceName; // Get resource type
				int resourceValue = HitResource->resourceAmount; // Get harvest amount

				HitResource->totalResource = HitResource->totalResource - resourceValue; // Reduce world resource

				if (HitResource->totalResource >= resourceValue) // If resource remains
				{
					GiveResource(resourceValue, hitName); // Add to inventory

					check(GEngine != nullptr); // Validate engine pointer
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Collected")); // Show success message

					UGameplayStatics::SpawnDecalAtLocation(GetWorld(), hitDecal, FVector(10.0f, 10.0f, 10.0f), HitResult.Location, FRotator(-90, 0, 0), 2.0f); // Spawn impact visual

					SetStamina(-5.0f); // Consume player stamina
				}
				else
				{
					HitResource->Destroy(); // Remove empty resource
					check(GEngine != nullptr); // Validate engine pointer
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted")); // Show depletion message
				}
			}
		}
	}
}

void APlayerChar::SetHealth(float amount)
{
	if (Health + amount < 100) // Check health cap
	{
		Health = Health + amount; // Apply health change
	}
}

void APlayerChar::SetHunger(float amount)
{
	if (Hunger + amount < 100) // Check hunger cap
	{
		Hunger = Hunger + amount; // Apply hunger change
	}
}

void APlayerChar::SetStamina(float amount)
{
	if (Stamina + amount < 100) // Check stamina cap
	{
		Stamina = Stamina + amount; // Apply stamina change
	}
}

void APlayerChar::DecreaseStats()
{
	if (Hunger > 0) // If not starving
	{
		SetHunger(-1.0f); // Reduce hunger over-time
	}

	SetStamina(10.0f); // Regenerate stamina over-time

	if (Hunger <= 0) // If starving
	{
		SetHealth(-3.0f); // Reduce health over-time
	}
}

void APlayerChar::GiveResource(float amount, FString resourceType)
{
	if (resourceType == "Wood") // Check if Wood
	{
		ResourcesArray[0] = ResourcesArray[0] + amount; // Increment wood count
	}

	if (resourceType == "Stone") // Check if Stone
	{
		ResourcesArray[1] = ResourcesArray[1] + amount; // Increment stone count
	}

	if (resourceType == "Berry") // Check if Berry
	{
		ResourcesArray[2] = ResourcesArray[2] + amount; // Increment berry count
	}
}