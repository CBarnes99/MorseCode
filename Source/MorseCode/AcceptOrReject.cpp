#include "AcceptOrReject.h"
#include "Components/ChildActorComponent.h"
#include "AcceptOrRejectButtons.h"
#include "Components/StaticMeshComponent.h"

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

	for (AAcceptOrRejectButtons* button : buttonsArray)
	{
		button->AcceptOrRejectButtonPressedEvent.BindUObject(this, &AAcceptOrReject::ButtonPressed);
	}

}

void AAcceptOrReject::ButtonPressed(bool value)
{
	AcceptOrRejectEvent.ExecuteIfBound(value);
}


