#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_StickyNoteText.generated.h"

class UMultiLineEditableTextBox;

UCLASS()
class MORSECODE_API UUI_StickyNoteText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UMultiLineEditableTextBox* noteTextBox;
};
