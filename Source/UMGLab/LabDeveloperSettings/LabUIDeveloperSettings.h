// Copyright (c) 2026 Jo Sungmin. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "LabUIDeveloperSettings.generated.h"

class ULabActivatableWidgetBase;



UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Lab UI Settings"))
class UMGLAB_API ULabUIDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta = (ForceInlineRow, Categories = "Lab.Widget"))
	TMap< FGameplayTag, TSoftClassPtr<ULabActivatableWidgetBase> > WidgetMap;
};
