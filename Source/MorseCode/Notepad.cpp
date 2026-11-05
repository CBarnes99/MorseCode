#include "Notepad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "UI_NotepadInput.h"
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
	notepadInputComp->SetDrawSize(FVector2D(100.f, 100.f));

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
	notepadInput = Cast<UUI_NotepadInput>(notepadInputComp->GetUserWidgetObject());

	notepadInput->TextCommittedEvent.BindUObject(this, &ANotepad::OnTextCommitted);
}

void ANotepad::Interact(AActor* interactor)
{
	if (!notepadInput)
	{
		UE_LOG(LogTemp, Error, TEXT("Interact: NOTEPAD INPUT NOT VALID!"));
		return;
	}

	notepadInput->SetFocusToNotepad();
}

void ANotepad::OnTextCommitted(const FText& outputText)
{

	if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
	{
		FInputModeGameOnly inputMode;
		playerController->SetShowMouseCursor(false);
		playerController->SetInputMode(inputMode);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnTextCommitted: Player Controller Not Valid!"));
	}
}


