// Copyright (c) 2026 Jo Sungmin. All rights reserved.


#include "LabFunctionLibrary.h"
#include "LabDeveloperSettings/LabUIDeveloperSettings.h"



TSoftClassPtr<ULabActivatableWidgetBase> ULabFunctionLibrary::GetFrontendSoftWidgetClassByTag(UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InWidgetTag)
{
	const ULabUIDeveloperSettings* LabUIDeveloperSettings = GetDefault<ULabUIDeveloperSettings>();
	checkf(LabUIDeveloperSettings->WidgetMap.Contains(InWidgetTag), TEXT("Could not find the corresponding widget under the tag %s"), *InWidgetTag.ToString());

	return LabUIDeveloperSettings->WidgetMap.FindRef(InWidgetTag);
}