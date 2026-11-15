#include "StickyNoteBin.h"
#include "Components/StaticMeshComponent.h"
#include "StickyNote.h"
#include <UObject/ConstructorHelpers.h>

AStickyNoteBin::AStickyNoteBin()
{
	PrimaryActorTick.bCanEverTick = false;

	binMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bin Mesh"));
	RootComponent = binMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Game/Fab/Steel_bin/steel_bin/StaticMeshes/steel_bin.steel_bin"));
	if (mesh.Succeeded())
	{
		binMesh->SetStaticMesh(mesh.Object);
	}
}

void AStickyNoteBin::BeginPlay()
{
	Super::BeginPlay();
}

void AStickyNoteBin::DeleteHeldNote(AStickyNote* noteToDelete)
{
	if (noteToDelete)
	{
		noteToDelete->Destroy();
		UE_LOG(LogTemp, Display, TEXT("DeleteHeldNote: Held Note Deleted"));
	}
}
