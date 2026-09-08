// Copyright (c) 2026 Jo Sungmin. All rights reserved.


#include "Widgets/Common/LabCommonButtonBase.h"
#include "Subsystems/LabUIGameInstanceSubsystem.h"
#include "CommonTextBlock.h"



void ULabCommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetButtonText(ButtonDisplayText);
}

void ULabCommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (CommonTextBlock_ButtonText && GetCurrentTextStyleClass())
	{
		CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
}

void ULabCommonButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();

	if (!ButtonDescriptionText.IsEmpty())
	{
		ULabUIGameInstanceSubsystem::Get(this).OnButtonDescriptionTextUpdated.Broadcast(this, ButtonDescriptionText);
	}
}

void ULabCommonButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	ULabUIGameInstanceSubsystem::Get(this).OnButtonDescriptionTextUpdated.Broadcast(this, FText::GetEmpty());
}

void ULabCommonButtonBase::SetButtonText(FText InText)
{
	if (CommonTextBlock_ButtonText && InText.IsEmpty() == false)
	{
		CommonTextBlock_ButtonText->SetText(bUserUpperCaseForButtonText ? InText.ToUpper() : InText);
	}
}
