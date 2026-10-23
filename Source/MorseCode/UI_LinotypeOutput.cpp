#include "UI_LinotypeOutput.h"
#include "Components/TextBlock.h"

void UUI_LinotypeOutput::NativeConstruct()
{
	textBox->SetText(FText::FromString(stringToDisplay));
}
