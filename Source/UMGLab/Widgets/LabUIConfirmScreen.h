// Copyright (c) 2026 Jo Sungmin. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/LabActivatableWidgetBase.h"
#include "DataTypes/LabUIDataTypes.h"
#include "LabUIConfirmScreen.generated.h"



class UCommonTextBlock;
class UDynamicEntryBox;



USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConfirmScreenButtonType ConfirmScreenButtonType = EConfirmScreenButtonType::Unknown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ButtonTextToDisplay;
};

UCLASS()
class UMGLAB_API UConfirmScreenInfoObject : public UObject
{
	GENERATED_BODY()

public:
	static UConfirmScreenInfoObject* CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMsg);
	static UConfirmScreenInfoObject* CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMsg);
	static UConfirmScreenInfoObject* CreateOkCancelScreen(const FText& InScreenTitle, const FText& InScreenMsg);

	UPROPERTY(Transient)
	FText ScreenTitle;

	UPROPERTY(Transient)
	FText ScreenMessage;

	UPROPERTY(Transient)
	TArray<FConfirmScreenButtonInfo> AvailableScreenButtons;
};

UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class UMGLAB_API ULabUIConfirmScreen : public ULabActivatableWidgetBase
{
	GENERATED_BODY()
	
public:
	// 이 위젯이 생성될 때, 그리고 Model Stack에 Push되기 전에 클래스 외부에서 호출됩니다.
	void InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject, TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback);

private:
	UPROPERTY(Transient, meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Title;

	UPROPERTY(Transient, meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Message;

	UPROPERTY(Transient, meta = (BindWidget))
	UDynamicEntryBox* DynamicEntryBox_Buttons;
};
