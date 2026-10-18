#include "MorseCodeInputSelectionSystem.h"
#include "Components/ChildActorComponent.h"
#include "SelectionButton.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "MorseCodeActor.h"

AMorseCodeInputSelectionSystem::AMorseCodeInputSelectionSystem()
{
	PrimaryActorTick.bCanEverTick = false;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(GetRootComponent());


	buttonComponent1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Button 1"));
	buttonComponent1->SetChildActorClass(ASelectionButton::StaticClass());
	buttonComponent1->SetupAttachment(baseMesh);

	buttonComponent2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Button 2"));
	buttonComponent2->SetChildActorClass(ASelectionButton::StaticClass());
	buttonComponent2->SetupAttachment(baseMesh);

	buttonComponent3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Button 3"));
	buttonComponent3->SetChildActorClass(ASelectionButton::StaticClass());
	buttonComponent3->SetupAttachment(baseMesh);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshFinder(TEXT("/Game/Testing/SM_Cube.SM_Cube"));
	if (meshFinder.Succeeded())
	{
		baseMesh->SetStaticMesh(meshFinder.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AMorseCodeInputSelectionSystem: Static Mesh not set within - %s"), *this->GetName());
	}

}

void AMorseCodeInputSelectionSystem::BeginPlay()
{
	Super::BeginPlay();

	SetAllMorseCodeActors();

	AddButtonsToArrayAndBindDelegates();
}

void AMorseCodeInputSelectionSystem::SetAllMorseCodeActors()
{
	TArray<AActor*> tempActorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMorseCodeActor::StaticClass(), tempActorArray);

	for (AActor* tempActor : tempActorArray)
	{
		morseCodeActorsArray.Add(Cast<AMorseCodeActor>(tempActor));
	}
}

void AMorseCodeInputSelectionSystem::AddButtonsToArrayAndBindDelegates()
{
	buttonArray.Add(Cast<ASelectionButton>(buttonComponent1->GetChildActor()));
	buttonArray.Add(Cast<ASelectionButton>(buttonComponent2->GetChildActor()));
	buttonArray.Add(Cast<ASelectionButton>(buttonComponent3->GetChildActor()));

	for (ASelectionButton* button : buttonArray)
	{
		button->ButtonPressedEvent.BindUObject(this, &AMorseCodeInputSelectionSystem::StartMorseCodeWithinActors);
	}
}

void AMorseCodeInputSelectionSystem::StartMorseCodeWithinActors(FGameplayTag uniqueMorseCodeTag, bool bIsPressed)
{
	for (AMorseCodeActor* morseCodeActor : morseCodeActorsArray)
	{
		if (morseCodeActor->uniqueActorTag == uniqueMorseCodeTag)
		{
			UE_LOG(LogTemp, Display, TEXT("StartMorseCodeWithinActors: Correct Tag witin %s"), *morseCodeActor->GetName());
			morseCodeActor->StartStopMorseCode(bIsPressed);
			break;
		}
	}
}
