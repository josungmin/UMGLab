// Copyright (c) 2026 Jo Sungmin. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "LabFunctionLibrary.generated.h"

class ULabActivatableWidgetBase;



UCLASS()
class UMGLAB_API ULabFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Lab Function Library")
	static TSoftClassPtr<ULabActivatableWidgetBase> GetFrontendSoftWidgetClassByTag(UPARAM(meta = (Categories = "Lab.Widget")) FGameplayTag InWidgetTag);
};
