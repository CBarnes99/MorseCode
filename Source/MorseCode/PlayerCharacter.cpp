#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include <EnhancedInputLibrary.h>
#include "DrawDebugHelpers.h"
#include "I_Interactable.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StickyNoteBin.h"
#include "StickyNote.h"

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

	SwitchState(E_PlayerState::InteractingState);
}

void APlayerCharacter::SwitchState(E_PlayerState newPlayerState)
{
	TSubclassOf<UPlayerStates> stateClass = nullptr;

	switch (newPlayerState)
	{
	case E_PlayerState::InteractingState:
		stateClass = UInteractingState::StaticClass();
		break;

	case E_PlayerState::StickyNoteState:
		stateClass = UStickyNoteState::StaticClass();
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("SwitchState: newPlayerState not valid!!"));
		return;
	}

	if (!stateClass)
	{
		UE_LOG(LogTemp, Error, TEXT("SwitchState: State Class Is Not Valid!"));
		return;
	}

	UPlayerStates* newState = NewObject<UPlayerStates>(this, stateClass);
	newState->playerCharacter = this;

	currentState = newState;
	UE_LOG(LogTemp, Warning, TEXT("SwitchState: Current state is now - %s"), *currentState->GetStateName());
}

void APlayerCharacter::Look(const FInputActionValue& InputValue)
{
	const FVector2D LookAxisVector = InputValue.Get<FVector2D>();
	AddControllerPitchInput(-LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);

}

void APlayerCharacter::StateAction1()
{
	if (!currentState)
	{
		UE_LOG(LogTemp, Error, TEXT("StateAction1: currentState is INVALID"));
		return;
	}

	currentState->StateAction1();
}

void APlayerCharacter::StateAction2()
{
	if (!currentState)
	{
		UE_LOG(LogTemp, Error, TEXT("StateAction2: currentState is INVALID"));
		return;
	}
	currentState->StateAction2();
}

void APlayerCharacter::InteractAction()
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
		UE_LOG(LogTemp, Warning, TEXT("InteractAction: Trace Hit - %s"), *hit.GetActor()->GetName());

		if (hit.GetActor()->Implements<UI_Interactable>())
		{
			II_Interactable* interactableActor = Cast<II_Interactable>(hit.GetActor());
			interactableActor->Interact(this);
			return;
		}

		//For testing with blueprints
		//if (hit.GetActor()->Implements<UI_Interactable>())
		//{
		//	II_Interactable::Execute_BPInteract(hit.GetActor(), this);
		//	return;
		//}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractAction: No Actor Hit"));
	}
}

void APlayerCharacter::SetStickyNote(AStickyNote* newNote)
{
	heldStickyNote = newNote;
	SwitchState(E_PlayerState::StickyNoteState);
	UE_LOG(LogTemp, Display, TEXT("SetStickyNote: New note is - %s"), *heldStickyNote->GetName());
}

void APlayerCharacter::PlaceStickyNote()
{
	if (!heldStickyNote)
	{
		UE_LOG(LogTemp, Error, TEXT("PlaceStickyNote: No held sticky note actor within - %s"), *GetName());
		return;
	}

	SwitchState(E_PlayerState::InteractingState);

	FHitResult hit;
	FVector traceStartLoc = playerCamera->GetComponentLocation();
	FVector traceEndLoc = traceStartLoc + (playerCamera->GetForwardVector() * 400.f);

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(hit, traceStartLoc, traceEndLoc, ECC_Visibility, params);

	if (AStickyNoteBin* bin = Cast<AStickyNoteBin>(hit.GetActor()))
	{
		bin->DeleteHeldNote(heldStickyNote);
		heldStickyNote = nullptr;
		return;
	}

	FVector placeLocation = hit.Location;
	FRotator placeRotation = hit.ImpactNormal.Rotation();
	placeRotation.Pitch += 90.f;
	placeRotation.Roll += 180.f;
	
	heldStickyNote->SetActorLocationAndRotation(placeLocation, placeRotation);
	heldStickyNote->SetNoteState(E_StickyNoteState::Placed);
	heldStickyNote = nullptr;
}

void APlayerCharacter::StartTyping()
{
	if (!heldStickyNote)
	{
		UE_LOG(LogTemp, Error, TEXT("StartTyping: No held sticky note on - %s"), *GetName());
		return;
	}

	heldStickyNote->ToggleTyping();
}


