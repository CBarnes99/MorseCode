#include "MorseCodeInputSelectionSystem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "SelectionSwitch.h"
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
	buttonComponent1->SetChildActorClass(ASelectionSwitch::StaticClass());
	buttonComponent1->SetupAttachment(baseMesh);

	buttonComponent2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Button 2"));
	buttonComponent2->SetChildActorClass(ASelectionSwitch::StaticClass());
	buttonComponent2->SetupAttachment(baseMesh);

	buttonComponent3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Button 3"));
	buttonComponent3->SetChildActorClass(ASelectionSwitch::StaticClass());
	buttonComponent3->SetupAttachment(baseMesh);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshFinder(TEXT("/Game/Fab/Tool_Storage_Board/scene/StaticMeshes/scene.scene"));
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
	buttonArray.Add(Cast<ASelectionSwitch>(buttonComponent1->GetChildActor()));
	buttonArray.Add(Cast<ASelectionSwitch>(buttonComponent2->GetChildActor()));
	buttonArray.Add(Cast<ASelectionSwitch>(buttonComponent3->GetChildActor()));

	for (ASelectionSwitch* button : buttonArray)
	{
		button->ButtonPressedEvent.BindUObject(this, &AMorseCodeInputSelectionSystem::ButtonPressedToggleMorseCode);
	}


	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), AAcceptOrReject::StaticClass());
	acceptOrRejectActor = Cast<AAcceptOrReject>(actor);

	if (!acceptOrRejectActor)
	{
		UE_LOG(LogTemp, Error, TEXT("AddButtonsToArrayAndBindDelegates: ACCEPT OR REJECT ACTOR NOT VALID!!"));
		return;
	}

	acceptOrRejectActor->AcceptOrRejectEvent.BindUObject(this, &AMorseCodeInputSelectionSystem::MorseCodeSignalAcceptOrReject);
}

void AMorseCodeInputSelectionSystem::SetAmountOfMorseCodeAndKeyForToday(int amount, FString key)
{
	if (AmountOfMorseCodeAndKeyForTodayEvent.IsBound())
	{
		UE_LOG(LogTemp, Display, TEXT("SetAmountOfMorseCodeAndKeyForToday: CORRECTLY BOUND!!"));

		AmountOfMorseCodeAndKeyForTodayEvent.ExecuteIfBound(amount, key);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SetAmountOfMorseCodeAndKeyForToday: NOT BOUND!!"));
	}
}

void AMorseCodeInputSelectionSystem::AddMorseCodeInformationToPool(F_MorseCodeStringsAndEncryption& morseCodeData)
{
	morseCodeInformationPool.Add(morseCodeData);

	CheckIfMorseCodeButtonsAreAvailable();
}

void AMorseCodeInputSelectionSystem::ButtonPressedToggleMorseCode(ASelectionSwitch* buttonPressed)
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
		for (ASelectionSwitch* selectionSwitch : buttonArray)
		{
			if (selectionSwitch != buttonPressed && selectionSwitch->bIsPressed)
			{
				selectionSwitch->SetButtonNotPressed();
			}
		}
	}
	else
	{
		currentButtonActor = nullptr;
	}
}

void AMorseCodeInputSelectionSystem::CheckIfMorseCodeButtonsAreAvailable()
{
	//For debugging
	FString buttonName = "Not Set";
	FString morseCodeActorName = "Not Set";

	bool buttonAvaliable = false;

	//F_MorseCodeStringsAndEncryption data : morseCodeInformationPool

	for (int i = 0; i < morseCodeInformationPool.Num(); i++)
	{
		for (ASelectionSwitch* button : buttonArray)
		{
			if (button->morseCodeActorUniqueTag == morseCodeInformationPool[i].uniqueTagForMorseCodeActor && !button->bIsEnabled)
			{
				button->SetButtonToEnabled();

				buttonAvaliable = true;

				buttonName = button->GetName();
				break;
			}
		}

		if (!buttonAvaliable)
		{
			continue;
		}

		for (AMorseCodeActor* actor : morseCodeActorsArray)
		{
			if (actor->uniqueActorTag == morseCodeInformationPool[i].uniqueTagForMorseCodeActor)
			{
				actor->SetMorseCodeInformation(morseCodeInformationPool[i].encryptionType, morseCodeInformationPool[i].sentenceToDecode);
				morseCodeActorName = actor->GetName();

				morseCodeInformationPool.RemoveAt(i);

				UE_LOG(LogTemp, Warning, TEXT("CheckIfMorseCodeButtonsAreAvailable: Button Enabled - %s, Morse Code Actor Info Set - %s"), *buttonName, *morseCodeActorName);
				return;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("CheckIfMorseCodeButtonsAreAvailable: No buttons are available!"));



	//for (ASelectionSwitch* button : buttonArray)
	//{
	//	if (button->morseCodeActorUniqueTag == morseCodeData.uniqueTagForMorseCodeActor)
	//	{
	//		button->SetButtonToEnabled();
	//		buttonName = button->GetName();
	//		break;
	//	}
	//}
	//
	//for (AMorseCodeActor* actor : morseCodeActorsArray)
	//{
	//	if (actor->uniqueActorTag == morseCodeData.uniqueTagForMorseCodeActor)
	//	{
	//		actor->SetMorseCodeInformation(morseCodeData.encryptionType, morseCodeData.sentenceToDecode);
	//		morseCodeActorName = actor->GetName();
	//		break;
	//	}
	//}

	//UE_LOG(LogTemp, Warning, TEXT("CheckIfMorseCodeButtonsAreAvailable: Button Enabled - %s, Morse Code Actor Info Set - %s"), *buttonName, *morseCodeActorName);
}

void AMorseCodeInputSelectionSystem::MorseCodeSignalAcceptOrReject(bool bAccept)
{

	if (!currentButtonActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("MorseCodeSignalAcceptOrReject: Nothing to Accept Or Reject"));
		return;
	}

	OnAcceptOrRejectRecievedEvent.ExecuteIfBound(bAccept, currentMorseCodeActor->currentString);

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
