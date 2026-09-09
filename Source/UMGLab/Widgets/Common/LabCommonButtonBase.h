// Copyright (c) 2026 Jo Sungmin. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "LabCommonButtonBase.generated.h"



class UCommonTextBlock;

UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class UMGLAB_API ULabCommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()
	
protected:
	//~ Begin UUserWidget Interface
	virtual void NativePreConstruct() override;
	//~ End UUserWidget Interface

	//~ Begin UCommonButtonBase Interface
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;
	//~ End UCommonButtonBase Interface
	
public:
	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InText);

protected:
	UPROPERTY(Transient, meta = (BindWidgetOptional))
	UCommonTextBlock* CommonTextBlock_ButtonText;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lab Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lab Button", meta = (AllowPrivateAccess = "true"))
	bool bUserUpperCaseForButtonText = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lab Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDescriptionText;
};
