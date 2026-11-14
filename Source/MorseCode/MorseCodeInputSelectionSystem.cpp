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


	switchComponent1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Switch 1"));
	switchComponent1->SetChildActorClass(ASelectionSwitch::StaticClass());
	switchComponent1->SetupAttachment(baseMesh);

	switchComponent2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Switch 2"));
	switchComponent2->SetChildActorClass(ASelectionSwitch::StaticClass());
	switchComponent2->SetupAttachment(baseMesh);

	switchComponent3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Switch 3"));
	switchComponent3->SetChildActorClass(ASelectionSwitch::StaticClass());
	switchComponent3->SetupAttachment(baseMesh);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshFinder(TEXT("/Game/Fab/Tool_Storage_Board/scene/StaticMeshes/scene.scene"));
	if (meshFinder.Succeeded())
	{
		baseMesh->SetStaticMesh(meshFinder.Object);
		UE_LOG(LogTemp, Display, TEXT("AMorseCodeInputSelectionSystem: Static Mesh is set within - %s"), *this->GetName());

	}
}

void AMorseCodeInputSelectionSystem::BeginPlay()
{
	Super::BeginPlay();

	SetAllMorseCodeActors();

	AddSwitchesToArrayAndBindDelegates();
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

void AMorseCodeInputSelectionSystem::AddSwitchesToArrayAndBindDelegates()
{
	switchArray.Add(Cast<ASelectionSwitch>(switchComponent1->GetChildActor()));
	switchArray.Add(Cast<ASelectionSwitch>(switchComponent2->GetChildActor()));
	switchArray.Add(Cast<ASelectionSwitch>(switchComponent3->GetChildActor()));

	for (ASelectionSwitch* currentSwitch : switchArray)
	{
		currentSwitch->SwitchToggledEvent.BindUObject(this, &AMorseCodeInputSelectionSystem::SwitchInteractedToggleMorseCode);
	}


	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), AAcceptOrReject::StaticClass());
	acceptOrRejectActor = Cast<AAcceptOrReject>(actor);

	if (!acceptOrRejectActor)
	{
		UE_LOG(LogTemp, Error, TEXT("AddSwitchesToArrayAndBindDelegates: ACCEPT OR REJECT ACTOR NOT VALID!!"));
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

	CheckIfMorseCodeSwitchesAreAvailable();
}

void AMorseCodeInputSelectionSystem::SwitchInteractedToggleMorseCode(ASelectionSwitch* buttonPressed)
{
	for (AMorseCodeActor* morseCodeActor : morseCodeActorsArray)
	{
		if (morseCodeActor->uniqueActorTag == buttonPressed->morseCodeActorUniqueTag)
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchInteractedToggleMorseCode: Correct Tag witin %s"), *morseCodeActor->GetName());
			currentMorseCodeActor = morseCodeActor;
			morseCodeActor->StartStopMorseCode(buttonPressed->bIsSwitchActive);
		}
		else if (buttonPressed->bIsSwitchActive)
		{
			morseCodeActor->StartStopMorseCode(false);
		}
	}

	if (buttonPressed->bIsSwitchActive)
	{
		currentSwitchActor = buttonPressed;
		for (ASelectionSwitch* selectionSwitch : switchArray)
		{
			if (selectionSwitch != buttonPressed && selectionSwitch->bIsSwitchActive)
			{
				selectionSwitch->SetSwitchNotActive();
			}
		}
	}
	else
	{
		currentSwitchActor = nullptr;
	}
}

void AMorseCodeInputSelectionSystem::CheckIfMorseCodeSwitchesAreAvailable()
{
	if (morseCodeInformationPool.Num() < 1)
		return;

	//For debugging
	FString buttonName = "Not Set";
	FString morseCodeActorName = "Not Set";

	bool buttonAvaliable = false;

	for (int i = 0; i < morseCodeInformationPool.Num(); i++)
	{
		for (ASelectionSwitch* button : switchArray)
		{
			if (button->morseCodeActorUniqueTag == morseCodeInformationPool[i].uniqueTagForMorseCodeActor && !button->bIsSwitchEnabled)
			{
				button->SetSwitchEnabledDisabled(true);

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

				UE_LOG(LogTemp, Warning, TEXT("CheckIfMorseCodeSwitchesAreAvailable: Button Enabled - %s, Morse Code Actor Info Set - %s"), *buttonName, *morseCodeActorName);
				return;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("CheckIfMorseCodeSwitchesAreAvailable: No buttons are available!"));
}

void AMorseCodeInputSelectionSystem::MorseCodeSignalAcceptOrReject(bool bAccept)
{

	if (!currentSwitchActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("MorseCodeSignalAcceptOrReject: Nothing to Accept Or Reject"));
		return;
	}

	OnAcceptOrRejectRecievedEvent.ExecuteIfBound(bAccept, currentMorseCodeActor->currentString);

	DisableCurrentMorseCodeActors();
}

void AMorseCodeInputSelectionSystem::DisableCurrentMorseCodeActors()
{
	if(currentSwitchActor)
	{
		currentSwitchActor->SetSwitchEnabledDisabled(false);
		currentSwitchActor = nullptr;
	}

	if (currentMorseCodeActor) 
	{
		currentMorseCodeActor->StartStopMorseCode(false);
		currentMorseCodeActor = nullptr;
	}
}

void AMorseCodeInputSelectionSystem::DisableAllMorseCodeActors()
{
	for (ASelectionSwitch* button : switchArray)
	{
		button->SetSwitchEnabledDisabled(false);
	}

	for (AMorseCodeActor* morseCodeActor : morseCodeActorsArray)
	{
		morseCodeActor->MorseCodeOff();
	}

	DisableCurrentMorseCodeActors();
}
