#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include <EnhancedInputLibrary.h>
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	playerCamera->SetupAttachment(RootComponent);
	playerCamera->bUsePawnControlRotation = true;

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

//UCameraComponent* APlayerCharacter::GetPlayerCamera()
//{
//	return playerCamera;
//}

void APlayerCharacter::Move(const FInputActionValue& InputValue)
{
	const FVector2D MovementVector = InputValue.Get<FVector2D>();
	const FVector Forward = GetActorForwardVector();
	const FVector Right = GetActorRightVector();

	AddMovementInput(Forward, MovementVector.Y);
	AddMovementInput(Right, MovementVector.X);
}

void APlayerCharacter::Look(const FInputActionValue& InputValue)
{
	const FVector2D LookAxisVector = InputValue.Get<FVector2D>();
	AddControllerPitchInput(-LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);

}

void APlayerCharacter::Click()
{
	FHitResult hit;
	FVector traceStartLoc = playerCamera->GetComponentLocation();
	FVector traceEndLoc = traceStartLoc + (playerCamera->GetForwardVector() * 400.f);

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(hit, traceStartLoc, traceEndLoc, ECC_Visibility, params);
	DrawDebugLine(GetWorld(), traceStartLoc, traceEndLoc, FColor::Red, false, 2.f, 1.f);

	if (hit.bBlockingHit == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Click: Trace Hit - %s"), *hit.GetActor()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Click: No Actor Hit"));
	}
}
