// Copyright (c) 2026 Jo Sungmin. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LABPlayerController.generated.h"



UCLASS()
class UMGLAB_API ALABPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	//~ Begin APlayerController Interface
	virtual void OnPossess(APawn* aPawn) override;
	//~ End APlayerController Interface
};
