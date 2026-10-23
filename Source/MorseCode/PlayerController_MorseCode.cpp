#include "PlayerController_MorseCode.h"
#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
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


		Input->BindAction(doAThing1Action, ETriggerEvent::Triggered, this, &APlayerController_MorseCode::doAThing1Func);
		Input->BindAction(doAThing2Action, ETriggerEvent::Triggered, this, &APlayerController_MorseCode::doAThing2Func);

	}
}

void APlayerController_MorseCode::Move(const FInputActionValue& InputValue)
{
	if (IsValid(playerCharacter))
	{
		playerCharacter->Move(InputValue);		
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
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Click: Player Character Is Not VALID!!"));
	}
}



void APlayerController_MorseCode::doAThing1Func()
{
	if (IsValid(playerCharacter))
	{
		playerCharacter->DoAThing1();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("doAThing1Func: Player Character Is Not VALID!!"));
	}
}

void APlayerController_MorseCode::doAThing2Func()
{
	if (IsValid(playerCharacter))
	{
		playerCharacter->DoAThing2();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("doAThing2Func: Player Character Is Not VALID!!"));
	}
}