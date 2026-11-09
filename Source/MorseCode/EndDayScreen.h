#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndDayScreen.generated.h"

DECLARE_DELEGATE(FStartNextDayButtonPressedSigniture)

class UUI_FadeToBlack;

UCLASS()
class MORSECODE_API AEndDayScreen : public AActor
{
	GENERATED_BODY()
	
public:	

	FStartNextDayButtonPressedSigniture StartNextDayButtonPressedEvent;

	AEndDayScreen();

	UFUNCTION(BlueprintCallable)
	void SetValuesForWidget(int total, int correct, int incorect);

	UFUNCTION(BlueprintCallable)
	void PlayFadeAnimation(bool bPlayAnimationForward);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> fadeToBlackWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUI_FadeToBlack* fadeToBlackWidget;

	UFUNCTION(BlueprintCallable)
	void NewDayButtonPressed();

};
