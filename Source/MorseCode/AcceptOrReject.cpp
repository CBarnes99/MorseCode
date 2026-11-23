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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Game/Fab/Megascans/3D/Electrical_Box_tdgtdedda/Medium/tdgtdedda_tier_2/StaticMeshes/tdgtdedda_tier_2.tdgtdedda_tier_2"));
	if (mesh.Succeeded())
	{
		baseMesh->SetStaticMesh(mesh.Object);
	}
}

void AAcceptOrReject::BeginPlay()
{
	Super::BeginPlay();

	BindButtonDelegates();
}

void AAcceptOrReject::BindButtonDelegates()
{
	//Binds to the on button pressed event and change the button material based on if its an accecpt or reject button
	buttonsArray.Add(Cast<AAcceptOrRejectButtons>(acceptButton->GetChildActor()));
	buttonsArray.Add(Cast<AAcceptOrRejectButtons>(rejectButton->GetChildActor()));
	F_ButtonMaterials* buttonMaterial;

	for (AAcceptOrRejectButtons* button : buttonsArray)
	{
		button->AcceptOrRejectButtonPressedEvent.BindUObject(this, &AAcceptOrReject::SwitchTriggered);

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

void AAcceptOrReject::SwitchTriggered(bool value)
{
	AcceptOrRejectEvent.ExecuteIfBound(value);
}


