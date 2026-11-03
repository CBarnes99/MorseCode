#include "Notepad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "NotepadInput.h"
#include "PlayerCharacter.h"

ANotepad::ANotepad()
{
	PrimaryActorTick.bCanEverTick = false;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(RootComponent);
	
	notepadInputComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Notepad Input"));
	notepadInputComp->SetupAttachment(baseMesh);
	notepadInputComp->SetWidgetSpace(EWidgetSpace::World);
	notepadInputComp->SetPivot(FVector2D(0.5f, 0.5f));
	notepadInputComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	notepadInputComp->SetUsingAbsoluteScale(true);
	notepadInputComp->SetWindowFocusable(true);

}

void ANotepad::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("notepadInputComp: %s | Found by class: %s"),
		notepadInputComp ? TEXT("valid") : TEXT("NULL"),
		FindComponentByClass<UWidgetComponent>() ? TEXT("yes") : TEXT("no"));
	SetNotepadComp();
}

void ANotepad::SetNotepadComp()
{
	if (!notepadWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("SetNotepadComp: NOTEPAD WIDGET CLASS NOT SET!!"));
		return;
	}

	notepadInputComp->SetWidgetClass(notepadWidgetClass);
	notepadInputComp->InitWidget();
	notepadInput = Cast<UNotepadInput>(notepadInputComp->GetUserWidgetObject());

	//notepadInput = CreateWidget<UNotepadInput>(GetWorld(), notepadWidgetClass);
	//notepadInputComp->SetWidget(notepadInput);
	notepadInput->TextCommittedEvent.BindUObject(this, &ANotepad::OnTextCommitted);

}

void ANotepad::Interact(AActor* interactor)
{
	playerRef = Cast<APlayerCharacter>(interactor);
	if (playerRef)
	{
		playerRef->SwitchState(E_PlayerState::NotepadState);
		notepadInput->SetFocusToNotepad();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Interact: Player Not Valid!"));
	}
}

void ANotepad::OnTextCommitted(const FText& outputText)
{

	if (playerRef)
	{
		playerRef->SwitchState(E_PlayerState::MovingState);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnTextCommitted: Player Not Valid!"));
	}
	//if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
	//{
	//	FInputModeGameOnly inputMode;
	//	playerController->SetInputMode(inputMode);
	//	playerController->SetShowMouseCursor(false);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("OnTextCommitted: Player Controller Not Valid!"));
	//}
}


