// Copyright (c) 2026 Jo Sungmin. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LabActivatableWidgetBase.generated.h"



class ALABPlayerController;

UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class UMGLAB_API ULabActivatableWidgetBase : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintPure)
	ALABPlayerController* GetOwningLabPlayerController();

private:
	TWeakObjectPtr<ALABPlayerController> CachedOwningPlayerController;
};
