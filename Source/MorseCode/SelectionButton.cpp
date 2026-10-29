#include "SelectionButton.h"
#include "Components/StaticMeshComponent.h"
#include "F_ButtonLightMaterials.h"
#include "Components/StaticMeshComponent.h"

ASelectionButton::ASelectionButton()
{
	PrimaryActorTick.bCanEverTick = false;

	buttonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Button Mesh");
	buttonMesh->SetupAttachment(GetRootComponent());

	lightMesh = CreateDefaultSubobject<UStaticMeshComponent>("Light Mesh");
	lightMesh->SetupAttachment(buttonMesh);

	bIsPressed = false;
	bIsEnabled = false;
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshFinder(TEXT("/Game/Testing/SM_Cube.SM_Cube"));
	if (meshFinder.Succeeded())
	{
		buttonMesh->SetStaticMesh(meshFinder.Object);
		lightMesh->SetStaticMesh(meshFinder.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASelectionButton: Static Mesh not set within - %s"), *this->GetName());
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> dataTableCheck(TEXT("/Game/DataTables/DT_LightMaterials.DT_LightMaterials"));
	if (dataTableCheck.Succeeded())
	{
		materialsDataTable = dataTableCheck.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ASelectionButton: Button Light Data Table not set within - %s"), *this->GetName());
	}

	lightMesh->SetRelativeScale3D(FVector(.2f, .2f, .2f));
	lightMesh->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
}

void ASelectionButton::BeginPlay()
{
	Super::BeginPlay();

	SetButtonToDisabled();
}

void ASelectionButton::Interact(AActor* interactor)
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

void ASelectionButton::SetButtonToDisabled()
{
	bIsEnabled = false;
	UE_LOG(LogTemp, Warning, TEXT("SetButtonToDisabled: %s - Is Disabled"), *GetName());

	SetLightMaterial("Red");
}

void ASelectionButton::SetButtonToEnabled()
{
	bIsEnabled = true;
	UE_LOG(LogTemp, Warning, TEXT("SetButtonToEnabled: %s - Is Enabled"), *GetName());

	SetLightMaterial("Orange");

}

void ASelectionButton::ButtonPressed()
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

void ASelectionButton::SetButtonNotPressed()
{
	if (bIsEnabled)
	{
		bIsPressed = false;
		SetLightMaterial("Orange");
	}
}

void ASelectionButton::SetButtonPressed()
{
	bIsPressed = true;
	SetLightMaterial("Green");
}

void ASelectionButton::SetLightMaterial(FName dataTableName)
{
	if (!lightMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("SetLightMaterial: lightMesh component is NULL!"));
		return;
	}

	F_ButtonLightMaterials* mats = materialsDataTable->FindRow< F_ButtonLightMaterials>(dataTableName, "Context");
	if (mats->material)
	{
		lightMesh->SetMaterial(0, mats->material);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SetLightMaterial: Light Materials Invalid!!"));
	}

}