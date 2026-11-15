#include "StickyNoteStack.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerCharacter.h"

AStickyNoteStack::AStickyNoteStack()
{
	PrimaryActorTick.bCanEverTick = false;

	stickyNoteStackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sticky Note Stack"));
	RootComponent = stickyNoteStackMesh;
	stickyNoteStackMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> stackMesh(TEXT("/Game/Fab/Post_it_notes/post_it_notes/StaticMeshes/SM_StickynoteStack.SM_StickynoteStack"));
	if (stackMesh.Succeeded())
	{
		stickyNoteStackMesh->SetStaticMesh(stackMesh.Object);
	}
}

void AStickyNoteStack::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStickyNoteStack::Interact(AActor* interactor)
{
	if (APlayerCharacter* player = Cast<APlayerCharacter>(interactor))
	{
		player->SetStickyNote(SpawnStickyNote());
	}
}

AStickyNote* AStickyNoteStack::SpawnStickyNote()
{

	if (!stickyNoteClass)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnStickyNote: No PostItNoteClass Set in - %s"), *GetName());
		return nullptr;
	}

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AStickyNote* newNote = GetWorld()->SpawnActor<AStickyNote>(stickyNoteClass, this->GetTransform(), spawnParams);

	return newNote;
}