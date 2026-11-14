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

	//bIsPressed = false;
	bIsSwitchEnabled = false;
	bIsSwitchActive = false;

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

	static ConstructorHelpers::FObjectFinder<USoundWave> switchEnabledFXCheck(TEXT("/Game/SFX/SW_SwitchEnabledSFX.SW_SwitchEnabledSFX"));
	if (switchEnabledFXCheck.Succeeded())
	{
		switchEnabledSFX = switchEnabledFXCheck.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASelectionSwitch: Switch Enabled SFX not set within - %s"), *this->GetName());
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> lightMaterialsDTCheck(TEXT("/Game/DataTables/DT_SelectionSwitchLightMaterials.DT_SelectionSwitchLightMaterials"));
	if (lightMaterialsDTCheck.Succeeded())
	{
		lightsMaterialsDataTable = lightMaterialsDTCheck.Object;
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

	//bIsSwitchEnabled = false;
	//SetLightMaterial("Red");
	SetSwitchEnabledDisabled(false);

	FOnTimelineVector switchProgressDelegate;
	switchProgressDelegate.BindUFunction(this, FName("HandleSwitchProgress"));
	switchTimelineComponent->AddInterpVector(switchMovementCurve, switchProgressDelegate);

}

void ASelectionSwitch::Interact(AActor* interactor)
{

	if (bIsSwitchEnabled == false)
	{
		UE_LOG(LogTemp, Display, TEXT("Interact: Switch - %s - Is Not Enabled!"), *GetName());
		return;
	}

	SwitchTriggered();

	FString TOF = bIsSwitchEnabled ? "True" : "False";
	UE_LOG(LogTemp, Display, TEXT("Interact: Interacted With - %s and is now %s"), *GetName(), *TOF);
	
	if (SwitchToggledEvent.IsBound())
	{
		SwitchToggledEvent.Execute(this);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Interact: SwitchToggledEvent is not bound within - %s"), *GetName());
	}
}

//void ASelectionSwitch::SetButtonToDisabled()
//{
//	if (bIsEnabled)
//	{
//		bIsEnabled = false;
//		UE_LOG(LogTemp, Warning, TEXT("SetButtonToDisabled: %s - Is Disabled"), *GetName());
//		SetLightMaterial("Red");
//		PlayAnimationAndSFX(false);
//	}
//}

void ASelectionSwitch::SetSwitchEnabledDisabled(bool bSetSwitchEnabled)
{
	if (bSetSwitchEnabled)
	{
		//Enable switch if it isnt already enabled
		if (!bIsSwitchEnabled)
		{
			bIsSwitchEnabled = true;
			UE_LOG(LogTemp, Warning, TEXT("SetButtonToEnabled: %s - Is Enabled"), *GetName());

			SetLightMaterial("Orange");
			audioComponent->Stop();
			audioComponent->SetSound(switchEnabledSFX);
			audioComponent->Play();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SetSwitchEnabledDisabled: Switch is already Enabled - %s"), *GetName());
		}
	}
	else
	{
		//Disable switch if it isnt already disabled
		if (bIsSwitchEnabled)
		{
			bIsSwitchEnabled = false;
			UE_LOG(LogTemp, Warning, TEXT("SetButtonToDisabled: %s - Is Disabled"), *GetName());
			SetLightMaterial("Red");
			PlayAnimationAndSFX(false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SetSwitchEnabledDisabled: Switch is already Disabled - %s"), *GetName());
		}
	}
}

void ASelectionSwitch::SwitchTriggered()
{
	if (!bIsSwitchActive)
	{
		SetSwitchActive();
	}
	else
	{
		SetSwitchNotActive();
	}
}

void ASelectionSwitch::SetSwitchNotActive()
{
	if (bIsSwitchActive)
	{
		bIsSwitchActive = false;
		SetLightMaterial("Orange");
		PlayAnimationAndSFX(false);
	}
}

void ASelectionSwitch::SetSwitchActive()
{
	if (!bIsSwitchActive)
	{
		bIsSwitchActive = true;
		SetLightMaterial("Green");
		PlayAnimationAndSFX(true);
	}
}

void ASelectionSwitch::SetLightMaterial(FName dataTableName)
{
	if (!lightMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("SetLightMaterial: lightMesh component is NULL!"));
		return;
	}

	F_ButtonLightMaterials* mats = lightsMaterialsDataTable->FindRow< F_ButtonLightMaterials>(dataTableName, "Context");
	if (mats->material)
	{
		lightMesh->SetMaterial(1, mats->material);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SetLightMaterial: Light Materials Invalid!!"));
	}

}

void ASelectionSwitch::PlayAnimationAndSFX(bool bIsSwitchActivated)
{
	audioComponent->Stop();


	if (bIsSwitchActivated)
	{
		switchTimelineComponent->PlayFromStart();
		bIsSwitchActive = true;
		audioComponent->SetSound(switchOnSFX);

	}
	else
	{
		switchTimelineComponent->ReverseFromEnd();
		bIsSwitchActive = false;
		audioComponent->SetSound(switchOffSFX);

	}
	audioComponent->Play();
}

void ASelectionSwitch::HandleSwitchProgress(FVector value)
{
	FRotator offset(value.Y, value.Z, value.X);
	switchHandleMesh->SetRelativeRotation(startingSwitchRotation + offset);
}