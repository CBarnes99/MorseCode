#include "MorseCodeInputSelectionSystem.h"

AMorseCodeInputSelectionSystem::AMorseCodeInputSelectionSystem()
{
	PrimaryActorTick.bCanEverTick = false;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(GetRootComponent());

}

void AMorseCodeInputSelectionSystem::BeginPlay()
{
	Super::BeginPlay();
	
}
