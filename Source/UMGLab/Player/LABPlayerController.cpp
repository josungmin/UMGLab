// Copyright (c) 2026 Jo Sungmin. All rights reserved.


#include "Player/LABPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"



void ALABPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), FoundCameras);

	if (FoundCameras.IsEmpty() == false)
	{
		SetViewTarget(FoundCameras[0]);
	}
}
