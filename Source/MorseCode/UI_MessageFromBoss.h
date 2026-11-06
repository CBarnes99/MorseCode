#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_MessageFromBoss.generated.h"

class UTextBlock;

UCLASS()
class MORSECODE_API UUI_MessageFromBoss : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* textBox;

	UFUNCTION(BlueprintCallable)
	void SetKey(FString newKey);

	UFUNCTION(BlueprintCallable)
	void SetNewMessage(FString newMessage);

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString currentKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString currentMessage;

	UFUNCTION(BlueprintCallable)
	void SetTextBox();
};
