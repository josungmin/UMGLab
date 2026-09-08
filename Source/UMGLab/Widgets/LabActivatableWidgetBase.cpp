// Copyright (c) 2026 Jo Sungmin. All rights reserved.


#include "Widgets/LabActivatableWidgetBase.h"
#include "Player/LABPlayerController.h"



ALABPlayerController* ULabActivatableWidgetBase::GetOwningLabPlayerController()
{
	if (CachedOwningPlayerController.IsValid() == false)
	{
		CachedOwningPlayerController = GetOwningPlayer<ALABPlayerController>();
	}

	return CachedOwningPlayerController.IsValid() ? CachedOwningPlayerController.Get() : nullptr;
}
