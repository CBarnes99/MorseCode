#include "UI_MessageFromBoss.h"
#include "Components/TextBlock.h"

void UUI_MessageFromBoss::NativeConstruct()
{
	Super::NativeConstruct();
	currentKey.Empty();
	currentMessage.Empty();
}


void UUI_MessageFromBoss::SetKey(FString newKey)
{
	currentKey = newKey;
	SetTextBox();
}

void UUI_MessageFromBoss::SetNewMessage(FString newMessage)
{
	currentMessage = newMessage;
	SetTextBox();
}


void UUI_MessageFromBoss::SetTextBox()
{
	if (currentKey.IsEmpty() || currentMessage.IsEmpty())
		return;

	FString keyText = TEXT("Key = ");
	FString combinedMessage = currentMessage + TEXT("\n") + keyText + currentKey;

	textBox->SetText(FText::FromString(combinedMessage));

	currentKey.Empty();
	currentMessage.Empty();
}