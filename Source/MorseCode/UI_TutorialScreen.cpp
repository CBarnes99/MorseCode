#include "UI_TutorialScreen.h"
#include "Components/Button.h"

void UUI_TutorialScreen::NativeConstruct()
{
	endTutorialButton->OnPressed.AddDynamic(this, &UUI_TutorialScreen::OnButtonPressed);
}

void UUI_TutorialScreen::StartTextDisplayAnimation()
{
	PlayAnimation(showTextAnimation, 0);
}

void UUI_TutorialScreen::OnButtonPressed()
{
	OnTutorialEndEvent.ExecuteIfBound();
}
