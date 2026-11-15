#include "StickyNote.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerCharacter.h"
#include "UI_StickyNoteText.h"
#include "Components/MultiLineEditableTextBox.h"

AStickyNote::AStickyNote()
{
	PrimaryActorTick.bCanEverTick = true;

    bIsTyping = false;

    stickyNoteMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sticky Note Mesh"));
    RootComponent = stickyNoteMesh;
    stickyNoteMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    widgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
    widgetComp->SetupAttachment(stickyNoteMesh);
    widgetComp->SetWidgetSpace(EWidgetSpace::World);
    widgetComp->SetDrawSize(FVector2D(1000.f, 1000.f));
    widgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    widgetComp->SetRelativeRotation(FRotator(90.f, 180.f, 0.f));
    widgetComp->SetRelativeScale3D(FVector(0.075f, 0.075f, 0.075f));
    widgetComp->SetRelativeLocation(FVector(0.f, 0.f, 0.2f));

    currentState = E_StickyNoteState::Held;
    heldOffset = FVector(15.f, 0.f, -3.f);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh1(TEXT("/Game/Fab/Post_it_notes/post_it_notes/StaticMeshes/SM_Stickynote1.SM_Stickynote1"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh2(TEXT("/Game/Fab/Post_it_notes/post_it_notes/StaticMeshes/SM_Stickynote2.SM_Stickynote2"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh3(TEXT("/Game/Fab/Post_it_notes/post_it_notes/StaticMeshes/SM_Stickynote1.SM_Stickynote3"));

    if (mesh1.Succeeded())
        stickNoteMeshes.Add(mesh1.Object);
    if (mesh2.Succeeded())
        stickNoteMeshes.Add(mesh2.Object);
    if (mesh3.Succeeded())
        stickNoteMeshes.Add(mesh3.Object);
    
    stickyNoteMesh->SetStaticMesh(stickNoteMeshes[FMath::RandRange(0, stickNoteMeshes.Num() - 1)]);

    static ConstructorHelpers::FClassFinder<UUserWidget> widgetFinder(TEXT("/Game/Blueprints/Widgets/WBP_StickyNoteText"));
    if (widgetFinder.Succeeded())
    {
        widgetComp->SetWidgetClass(widgetFinder.Class);
    }
}

void AStickyNote::BeginPlay()
{
    Super::BeginPlay();

    playerController = UGameplayStatics::GetPlayerController(this, 0);
    if (!playerController)
    {
        UE_LOG(LogTemp, Error, TEXT("BeginPlay: PLAYER CONTROLLER NOT SET WITHIN - %s"), *GetName());
        return;
    }
}

void AStickyNote::Tick(float DeltaTime)
{
    if (currentState == E_StickyNoteState::Held)
    {
        FVector camLoc;
        FRotator camRot;
        playerController->GetPlayerViewPoint(camLoc, camRot);

        FRotationMatrix camMatrix(camRot);
        FVector ForwardDir = camMatrix.GetUnitAxis(EAxis::X);
        FVector RightDir = camMatrix.GetUnitAxis(EAxis::Y);
        FVector UpDir = camMatrix.GetUnitAxis(EAxis::Z);

        // Calculate target location relative to the cameras axes
        FVector TargetLoc = camLoc + (ForwardDir * heldOffset.X) + (RightDir * heldOffset.Y) + (UpDir * heldOffset.Z);

        //Makes the mesh look at the player beacuse the defualt mesh is facing upwards
        camRot.Pitch += 90;
        SetActorLocationAndRotation(TargetLoc, camRot);


    }
}

void AStickyNote::Interact(AActor* interactor)
{
    if (APlayerCharacter* player = Cast<APlayerCharacter>(interactor))
    {
        player->SetStickyNote(this);
        SetNoteState(E_StickyNoteState::Held);
    }
}

void AStickyNote::SetNoteState(E_StickyNoteState newState)
{
    currentState = newState;
    switch (currentState)
    {
    case E_StickyNoteState::Placed:
        stickyNoteMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        if (bIsTyping)
        {
            ToggleTyping();
        }
        break;

    case E_StickyNoteState::Held:
        stickyNoteMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        break;
    }
}

void AStickyNote::ToggleTyping()
{
    if (!playerController)
    {
        UE_LOG(LogTemp, Error, TEXT("ToggleTyping: No player controller within - %s"), *GetName());
        return;
    }

    bIsTyping = !bIsTyping;

    if (bIsTyping)
    {
        FInputModeGameAndUI inputMode;
        UUI_StickyNoteText* stickyNoteWidget = Cast<UUI_StickyNoteText>(widgetComp->GetUserWidgetObject());
        if (stickyNoteWidget)
        {
            inputMode.SetWidgetToFocus(stickyNoteWidget->noteTextBox->TakeWidget());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("ToggleTyping: Cant get widget from name within - %s"), *GetName());
            return;
        }
        playerController->SetInputMode(inputMode);
    }
    else
    {
        FInputModeGameOnly inputMode;
        playerController->SetInputMode(inputMode);
    }
}