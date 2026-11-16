#include "UI_EndTechDemoScreen.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UUI_EndTechDemoScreen::NativeConstruct()
{
	endButton->OnPressed.AddDynamic(this, &UUI_EndTechDemoScreen::ExitGame);
}

void UUI_EndTechDemoScreen::PlayEndAnimation()
{
	PlayAnimationForward(showEndScreenAnimation);
}

void UUI_EndTechDemoScreen::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
