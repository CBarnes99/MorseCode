#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include <EnhancedInputLibrary.h>
#include "PlayerStates.h"
#include "DrawDebugHelpers.h"
#include "I_Interactable.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	playerCamera->SetupAttachment(RootComponent);
	playerCamera->bUsePawnControlRotation = true;
	currentState = new StateOne();

}

void APlayerCharacter::CreateState(PlayerStates* newState)
{
	if (currentState != nullptr)
		delete currentState;

	currentState = newState;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

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
	DrawDebugLine(GetWorld(), traceStartLoc, traceEndLoc, FColor::Red, false, 2.f, 1.f, .1f);

	if (hit.bBlockingHit == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Click: Trace Hit - %s"), *hit.GetActor()->GetName());

		//if (hit.GetActor()->Implements<UI_Interactable>())
		//{
		//	II_Interactable* interactableActor = Cast<II_Interactable>(hit.GetActor());
		//	interactableActor->Interact(this);
		//	return;
		//}

		//For testing with blueprints
		if (hit.GetActor()->Implements<UI_Interactable>())
		{
			II_Interactable::Execute_BPInteract(hit.GetActor(), this);
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Click: No Actor Hit"));
	}
}
