#include "UI_FadeToBlack.h"
#include "Animation/WidgetAnimation.h"

void UUI_FadeToBlack::NativeConstruct()
{
	Super::NativeConstruct();


	//AnimationFinishedEvent.BindDynamic(this, &UUI_FadeToBlack::AnimationFinished);
	//BindToAnimationFinished(fadeToBlackAnimation, AnimationFinishedEvent);

}

void UUI_FadeToBlack::PlayFadeAnimation(bool bPlayForward)
{
	SetVisibility(ESlateVisibility::Visible);
	//bPlayedForward = bPlayForward;
	if (bPlayForward)
	{
		PlayAnimation(fadeToBlackAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
	}
	else
	{
		PlayAnimation(fadeToBlackAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
	}

}

//void UUI_FadeToBlack::AnimationFinished()
//{
//	if (bPlayedForward)
//		this->SetVisibility(ESlateVisibility::Collapsed);
//}
