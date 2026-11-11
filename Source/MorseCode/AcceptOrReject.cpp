#include "AcceptOrReject.h"
#include "Components/ChildActorComponent.h"
#include "AcceptOrRejectButtons.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "F_ButtonMaterials.h"

AAcceptOrReject::AAcceptOrReject()
{
	PrimaryActorTick.bCanEverTick = false;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(RootComponent);

	acceptButton = CreateDefaultSubobject<UChildActorComponent>(TEXT("Accept Button"));
	acceptButton->SetChildActorClass(AAcceptOrRejectButtons::StaticClass());
	acceptButton->SetupAttachment(baseMesh);

	rejectButton = CreateDefaultSubobject<UChildActorComponent>(TEXT("Reject Button"));
	rejectButton->SetChildActorClass(AAcceptOrRejectButtons::StaticClass());
	rejectButton->SetupAttachment(baseMesh);

	static ConstructorHelpers::FObjectFinder<UDataTable> buttonMaterialsDT(TEXT("/Game/DataTables/DT_ButtonMaterials.DT_ButtonMaterials"));
	if (buttonMaterialsDT.Succeeded())
	{
		buttonMaterials = buttonMaterialsDT.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AAcceptOrReject: BUTTON MATERIALS NOT SET IN - %s"), *GetName());
	}


}


void AAcceptOrReject::BeginPlay()
{
	Super::BeginPlay();

	BindButtonDelegates();
}

void AAcceptOrReject::BindButtonDelegates()
{
	buttonsArray.Add(Cast<AAcceptOrRejectButtons>(acceptButton->GetChildActor()));
	buttonsArray.Add(Cast<AAcceptOrRejectButtons>(rejectButton->GetChildActor()));
	F_ButtonMaterials* buttonMaterial;

	for (AAcceptOrRejectButtons* button : buttonsArray)
	{
		button->AcceptOrRejectButtonPressedEvent.BindUObject(this, &AAcceptOrReject::ButtonPressed);

		if (button->AcceptOrReject)
		{
			buttonMaterial = buttonMaterials->FindRow<F_ButtonMaterials>("Green", TEXT("Button Material Lookup"));
		}
		else
		{
			buttonMaterial = buttonMaterials->FindRow<F_ButtonMaterials>("Red", TEXT("Button Material Lookup"));
		}

		if (!buttonMaterial)
		{
			UE_LOG(LogTemp, Error, TEXT("BindButtonDelegates: No button material found"));
			return;
		}

		button->SetButtonMaterial(buttonMaterial->material);
	}
}

void AAcceptOrReject::ButtonPressed(bool value)
{
	AcceptOrRejectEvent.ExecuteIfBound(value);
}


