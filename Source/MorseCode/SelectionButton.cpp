#include "SelectionButton.h"
#include "Components/StaticMeshComponent.h"

ASelectionButton::ASelectionButton()
{
	PrimaryActorTick.bCanEverTick = false;

	buttonBox = CreateDefaultSubobject<UStaticMeshComponent>("Button Box");
	buttonBox->SetupAttachment(GetRootComponent());

	bIsPressed = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshFinder(TEXT("/Game/Testing/SM_Cube.SM_Cube"));
	if (meshFinder.Succeeded())
	{
		buttonBox->SetStaticMesh(meshFinder.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASelectionButton: Static Mesh not set within - %s"), *this->GetName());
	}


}

void ASelectionButton::BeginPlay()
{
	Super::BeginPlay();
}

void ASelectionButton::Interact(AActor* interactor)
{

	if (bIsPressed == true)
	{
		bIsPressed = false;
	}
	else
	{
		bIsPressed = true;
	}

	FString TOF = bIsPressed ? "True" : "False";
	UE_LOG(LogTemp, Display, TEXT("Interact: Interacted With - %s and is now %s"), *GetName(), *TOF);
	
	if (ButtonPressedEvent.IsBound())
	{
		ButtonPressedEvent.Execute(morseCodeActorUniqueTag, bIsPressed);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Interact: ButtonPressedEvent is not bound within - %s"), *GetName());
	}
}