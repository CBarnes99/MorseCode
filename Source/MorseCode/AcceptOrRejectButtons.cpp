#include "AcceptOrRejectButtons.h"
#include "Components/StaticMeshComponent.h"

AAcceptOrRejectButtons::AAcceptOrRejectButtons()
{
	PrimaryActorTick.bCanEverTick = false;

	buttonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Mesh"));
	buttonMesh->SetupAttachment(RootComponent);
}

void AAcceptOrRejectButtons::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAcceptOrRejectButtons::Interact(AActor* interactor)
{
	if (!interactor)
	{
		UE_LOG(LogTemp, Error, TEXT("Interact: Interactor is INVALID! Exiting Function"));
		return;
	}

	FString buttonName = AcceptOrReject ? "Accpet Button" : "Reject Button";
	UE_LOG(LogTemp, Display, TEXT("Interact: Interacted with %s"), *buttonName);
	AcceptOrRejectButtonPressedEvent.ExecuteIfBound(AcceptOrReject);
}
