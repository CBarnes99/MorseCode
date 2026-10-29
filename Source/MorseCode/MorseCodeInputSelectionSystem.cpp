#include "MorseCodeInputSelectionSystem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "SelectionButton.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "MorseCodeActor.h"
#include "AcceptOrReject.h"

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
		UE_LOG(LogTemp, Display, TEXT("AMorseCodeInputSelectionSystem: Static Mesh is set within - %s"), *this->GetName());

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
		button->ButtonPressedEvent.BindUObject(this, &AMorseCodeInputSelectionSystem::ButtonPressedToggleMorseCode);
	}

	if (!acceptOrRejectActor)
	{
		UE_LOG(LogTemp, Error, TEXT("AddButtonsToArrayAndBindDelegates: ACCEPT OR REJECT ACTOR NOT VALID!!"));
		return;
	}

	acceptOrRejectActor->AcceptOrRejectEvent.BindUObject(this, &AMorseCodeInputSelectionSystem::MorseCodeSignalAcceptOrReject);
}

void AMorseCodeInputSelectionSystem::ButtonPressedToggleMorseCode(ASelectionButton* buttonPressed)
{
	for (AMorseCodeActor* morseCodeActor : morseCodeActorsArray)
	{
		if (morseCodeActor->uniqueActorTag == buttonPressed->morseCodeActorUniqueTag)
		{
			UE_LOG(LogTemp, Display, TEXT("ButtonPressedToggleMorseCode: Correct Tag witin %s"), *morseCodeActor->GetName());
			currentMorseCodeActor = morseCodeActor;
			morseCodeActor->StartStopMorseCode(buttonPressed->bIsPressed);
		}
		else if (buttonPressed->bIsPressed)
		{
			morseCodeActor->StartStopMorseCode(false);
		}
	}

	if (buttonPressed->bIsPressed)
	{
		currentButtonActor = buttonPressed;
		for (ASelectionButton* button : buttonArray)
		{
			if (button != buttonPressed && button->bIsPressed)
			{
				button->SetButtonNotPressed();
			}
		}
	}
	else
	{
		currentButtonActor = nullptr;
	}
}

void AMorseCodeInputSelectionSystem::EnableButtonAndSetMorseCodeActorInformation(F_MorseCodeStringsAndEncryption& morseCodeData)
{
	//For debugging
	FString buttonName = "Not Set";
	FString morseCodeActorName = "Not Set";

	for (ASelectionButton* button : buttonArray)
	{
		if (button->morseCodeActorUniqueTag == morseCodeData.uniqueTagForMorseCodeActor)
		{
			button->SetButtonToEnabled();
			buttonName = button->GetName();
			break;
		}
	}
	
	for (AMorseCodeActor* actor : morseCodeActorsArray)
	{
		if (actor->uniqueActorTag == morseCodeData.uniqueTagForMorseCodeActor)
		{
			actor->SetMorseCodeInformation(morseCodeData.encryptionType, morseCodeData.sentenceToDecode);
			morseCodeActorName = actor->GetName();
			break;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("EnableButtonAndSetMorseCodeActorInformation: Button Enabled - %s, Morse Code Actor Info Set - %s"), *buttonName, *morseCodeActorName);
}


void AMorseCodeInputSelectionSystem::MorseCodeSignalAcceptOrReject(bool bAccept)
{

	if (!currentButtonActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("MorseCodeSignalAcceptOrReject: Nothing to Accept Or Reject"));
		return;
	}

	if (bAccept)
	{
		UE_LOG(LogTemp, Warning, TEXT("MorseCodeSignalAcceptOrReject: Morse Code Signal has been Accepted!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MorseCodeSignalAcceptOrReject: Morse Code Signal has been Rejected!"));

	}

	DisableMorseCodeActorsAfterAcceptOrReject();
}

void AMorseCodeInputSelectionSystem::DisableMorseCodeActorsAfterAcceptOrReject()
{
	if(currentButtonActor)
	{
		currentButtonActor->SetButtonToDisabled();
		currentButtonActor = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DisableMorseCodeActorsAfterAcceptOrReject: CURRENT BUTTON ACTOR NOT VALID"));
	}

	if (currentMorseCodeActor) 
	{
		currentMorseCodeActor->StartStopMorseCode(false);
		currentMorseCodeActor = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DisableMorseCodeActorsAfterAcceptOrReject: CURRENT MORSE CODE ACTOR NOT VALID"));
	}
}
