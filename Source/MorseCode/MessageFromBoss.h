#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MessageFromBoss.generated.h"

class UStaticMeshComponent;
class UWidgetComponent;
class UUI_MessageFromBoss;

UCLASS()
class MORSECODE_API AMessageFromBoss : public AActor
{
	GENERATED_BODY()
	
public:	

	AMessageFromBoss();



protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* baseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> widgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent* messageWidgetComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUI_MessageFromBoss* messageWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString key;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDataTable* dailyMessageDataTable;

	UFUNCTION(BlueprintCallable)
	void SetupWidget();

	UFUNCTION(BlueprintCallable)
	void BindDelegates();

	UFUNCTION(BlueprintCallable)
	void SetKey(FString newKey);

	UFUNCTION(BlueprintCallable)
	void SetCurrentMessageForUI(int currentDay);

};
