#include "SelectionSwitch.h"
#include "Components/StaticMeshComponent.h"
#include "F_ButtonLightMaterials.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveVector.h" 

ASelectionSwitch::ASelectionSwitch()
{
	PrimaryActorTick.bCanEverTick = false;

	switchBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = switchBaseMesh;

	switchHandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Handle Mesh"));
	switchHandleMesh->SetupAttachment(switchBaseMesh);

	lightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light Mesh"));
	lightMesh->SetupAttachment(switchBaseMesh);

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	audioComponent->SetupAttachment(switchBaseMesh);

	switchTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timneline Component"));

	bIsPressed = false;
	bIsEnabled = false;
	bSwitchIsDown = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> baseMesh(TEXT("/Game/Fab/electric_switch/StaticMeshes/SM_SwitchBase.SM_SwitchBase"));
	if (baseMesh.Succeeded())
	{
		switchBaseMesh->SetStaticMesh(baseMesh.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASelectionSwitch: Base Mesh not set within - %s"), *this->GetName());
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> switchMesh(TEXT("/Game/Fab/electric_switch/StaticMeshes/SM_SwitchHandle.SM_SwitchHandle"));
	if (switchMesh.Succeeded())
	{
		switchHandleMesh->SetStaticMesh(switchMesh.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASelectionSwitch: Switch Mesh not set within - %s"), *this->GetName());
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> lMesh(TEXT("/Game/Fab/FlatLight/SM_FlatLight.SM_FlatLight"));
	if (lMesh.Succeeded())
	{
		lightMesh->SetStaticMesh(lMesh.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASelectionSwitch: Light Mesh not set within - %s"), *this->GetName());
	}

	lightMesh->SetRelativeLocation(FVector(0.f, -10.f, 40.f));
	lightMesh->SetRelativeRotation(FRotator(90.f, 0.f, 90.f));

	static ConstructorHelpers::FObjectFinder<USoundWave> switchOnSFXCheck(TEXT("/Game/SFX/SW_SwitchOn.SW_SwitchOn"));
	if (switchOnSFXCheck.Succeeded())
	{
		switchOnSFX = switchOnSFXCheck.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASelectionSwitch: Switch On SFX not set within - %s"), *this->GetName());
	}

	static ConstructorHelpers::FObjectFinder<USoundWave> switchOffSFXCheck(TEXT("/Game/SFX/SW_SwitchOff.SW_SwitchOff"));
	if (switchOffSFXCheck.Succeeded())
	{
		switchOffSFX = switchOffSFXCheck.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASelectionSwitch: Switch Off SFX not set within - %s"), *this->GetName());
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> lightMaterialsDTCheck(TEXT("/Game/DataTables/DT_SelectionSwitchLightMaterials.DT_SelectionSwitchLightMaterials"));
	if (lightMaterialsDTCheck.Succeeded())
	{
		materialsDataTable = lightMaterialsDTCheck.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASelectionSwitch: Light Materials DT not set within - %s"), *this->GetName());
	}

	static ConstructorHelpers::FObjectFinder<UCurveVector> curve (TEXT("/Game/Curves/C_SwitchCurve.C_SwitchCurve"));
	if (curve.Succeeded())
	{
		switchMovementCurve = curve.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASelectionSwitch: Curve not set within - %s"), *this->GetName());
	}

}

void ASelectionSwitch::BeginPlay()
{
	Super::BeginPlay();

	bIsEnabled = false;
	SetLightMaterial("Red");

	FOnTimelineVector switchProgressDelegate;
	switchProgressDelegate.BindUFunction(this, FName("HandleSwitchProgress"));
	switchTimelineComponent->AddInterpVector(switchMovementCurve, switchProgressDelegate);

}

void ASelectionSwitch::Interact(AActor* interactor)
{

	if (bIsEnabled == false)
	{
		UE_LOG(LogTemp, Display, TEXT("Interact: Button - %s - Is Not Enabled!"), *GetName());
		return;
	}

	ButtonPressed();

	FString TOF = bIsPressed ? "True" : "False";
	UE_LOG(LogTemp, Display, TEXT("Interact: Interacted With - %s and is now %s"), *GetName(), *TOF);
	
	if (ButtonPressedEvent.IsBound())
	{
		//ButtonPressedEvent.Execute(morseCodeActorUniqueTag, bIsPressed);
		ButtonPressedEvent.Execute(this);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Interact: ButtonPressedEvent is not bound within - %s"), *GetName());
	}
}

void ASelectionSwitch::SetButtonToDisabled()
{
	bIsEnabled = false;
	UE_LOG(LogTemp, Warning, TEXT("SetButtonToDisabled: %s - Is Disabled"), *GetName());
	SetLightMaterial("Red");
	PlaySFX(false);
}

void ASelectionSwitch::SetButtonToEnabled()
{
	bIsEnabled = true;
	UE_LOG(LogTemp, Warning, TEXT("SetButtonToEnabled: %s - Is Enabled"), *GetName());

	SetLightMaterial("Orange");
	
}

void ASelectionSwitch::ButtonPressed()
{
	if (bIsPressed == true)
	{
		SetButtonNotPressed();
	}
	else
	{
		SetButtonPressed();
	}
}

void ASelectionSwitch::SetButtonNotPressed()
{
	if (bIsEnabled)
	{
		bIsPressed = false;
		SetLightMaterial("Orange");
		PlaySFX(false);
	}
}

void ASelectionSwitch::SetButtonPressed()
{
	bIsPressed = true;
	SetLightMaterial("Green");
	PlaySFX(true);
}

void ASelectionSwitch::SetLightMaterial(FName dataTableName)
{
	if (!lightMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("SetLightMaterial: lightMesh component is NULL!"));
		return;
	}

	F_ButtonLightMaterials* mats = materialsDataTable->FindRow< F_ButtonLightMaterials>(dataTableName, "Context");
	if (mats->material)
	{
		lightMesh->SetMaterial(1, mats->material);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SetLightMaterial: Light Materials Invalid!!"));
	}

}

void ASelectionSwitch::PlaySFX(bool bIsOn)
{
	audioComponent->Stop();
	if (bIsOn)
	{
		audioComponent->SetSound(switchOnSFX);
		switchTimelineComponent->PlayFromStart();
	}
	else
	{
		audioComponent->SetSound(switchOffSFX);
		switchTimelineComponent->ReverseFromEnd();

	}
	audioComponent->Play();
}

void ASelectionSwitch::HandleSwitchProgress(FVector value)
{
	FRotator offset(value.Y, value.Z, value.X);
	switchHandleMesh->SetRelativeRotation(startingSwitchRotation + offset);
}

//void ASelectionSwitch::HandleSwitchFinished()
//{
//
//}
