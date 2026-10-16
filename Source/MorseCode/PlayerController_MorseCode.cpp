#include "PlayerController_MorseCode.h"
#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
//#include "InputMappingContext.h"
//#include <EnhancedInputLibrary.h>
//#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"

void APlayerController_MorseCode::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* enhancedInputSubSystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		enhancedInputSubSystem->AddMappingContext(movementMappingContext, 0);
	}
}

void APlayerController_MorseCode::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	playerCharacter = Cast<APlayerCharacter>(InPawn);
	if (!playerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("OnPossess: Player Character Not Assigned In Player Controller!"));
	}
}

void APlayerController_MorseCode::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Binds the Input Actions assigned in the editor to the corisponding functions
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(moveAction, ETriggerEvent::Triggered, this, &APlayerController_MorseCode::Move);
		Input->BindAction(lookAction, ETriggerEvent::Triggered, this, &APlayerController_MorseCode::Look);
		Input->BindAction(clickAction, ETriggerEvent::Triggered, this, &APlayerController_MorseCode::Click);
	}
}

void APlayerController_MorseCode::Move(const FInputActionValue& InputValue)
{
	if (IsValid(playerCharacter))
	{
		playerCharacter->Move(InputValue);

		//const FVector2D MovementVector = InputValue.Get<FVector2D>();
		//const FVector Forward = playerCharacter->GetActorForwardVector();
		//const FVector Right = playerCharacter->GetActorRightVector();

		//playerCharacter->AddMovementInput(Forward, MovementVector.Y);
		//playerCharacter->AddMovementInput(Right, MovementVector.X);
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Move: Player Character Is Not VALID!!"));
	}
}

void APlayerController_MorseCode::Look(const FInputActionValue& InputValue)
{
	if (IsValid(playerCharacter))
	{
		playerCharacter->Look(InputValue);

		//const FVector2D LookAxisVector = InputValue.Get<FVector2D>();
		//playerCharacter->AddControllerPitchInput(-LookAxisVector.Y);
		//playerCharacter->AddControllerYawInput(LookAxisVector.X);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Look: Player Character Is Not VALID!!"));
	}

}

void APlayerController_MorseCode::Click()
{
	if (IsValid(playerCharacter))
	{
		playerCharacter->Click();

		//FHitResult hit;
		//FVector traceStartLoc = playerCharacter->GetPlayerCamera()->GetComponentLocation();
		//FVector traceEndLoc = traceStartLoc + (playerCharacter->GetPlayerCamera()->GetForwardVector() * 200.f);

		//FCollisionQueryParams params;
		//params.AddIgnoredActor(playerCharacter);

		//GetWorld()->LineTraceSingleByChannel(hit, traceStartLoc, traceEndLoc, ECC_Visibility, params);
		//DrawDebugLine(GetWorld(), traceStartLoc, traceEndLoc, FColor::Red, false, 2.f, 1.f);

		//if (hit.bBlockingHit == true)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Click: Trace Hit - %s"), *hit.GetActor()->GetName());
		//}
		//else
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Click: No Actor Hit"));
		//}

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Click: Player Character Is Not VALID!!"));
	}
}
