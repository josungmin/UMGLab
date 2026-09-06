// Copyright (c) 2026 Jo Sungmin. All rights reserved.


#include "Widgets/LabPrimaryLayoutWidget.h"



UCommonActivatableWidgetContainerBase* ULabPrimaryLayoutWidget::FindWidgetStackByTag(const FGameplayTag& InTag) const
{
	checkf(RegisteredWidgetStackMap.Contains(InTag), TEXT("Can not find the widget stack by the tag %s"), *InTag.ToString());

	return RegisteredWidgetStackMap.FindRef(InTag);
}

void ULabPrimaryLayoutWidget::RegisterWidgetStack(UPARAM(meta = (Categories = "Frontend.WidgetStack")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
	if (IsDesignTime() == false)
	{
		if (RegisteredWidgetStackMap.Contains(InStackTag) == false)
		{
			RegisteredWidgetStackMap.Add(InStackTag, InStack);
		}
	}
}