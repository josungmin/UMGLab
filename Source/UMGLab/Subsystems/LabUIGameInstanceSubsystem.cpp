// Copyright (c) 2026 Jo Sungmin. All rights reserved.


#include "Subsystems/LabUIGameInstanceSubsystem.h"
#include "Engine/AssetManager.h"
#include "LabGameplayTags.h"
#include "LabFunctionLibrary.h"

#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/LabPrimaryLayoutWidget.h"
#include "Widgets/LabActivatableWidgetBase.h"
#include "Widgets/LabUIConfirmScreen.h"



ULabUIGameInstanceSubsystem& ULabUIGameInstanceSubsystem::Get(const UObject* InWorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(InWorldContextObject, EGetWorldErrorMode::Assert);
	check(World);

	ULabUIGameInstanceSubsystem* Subsystem = UGameInstance::GetSubsystem<ULabUIGameInstanceSubsystem>(World->GetGameInstance());
	check(Subsystem);

	return *Subsystem;
}

bool ULabUIGameInstanceSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance() == false)
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}

	return false;
}

void ULabUIGameInstanceSubsystem::RegisterCreatedPrimaryLayoutWidget(ULabPrimaryLayoutWidget* InCreatedWidget)
{
	check(InCreatedWidget);

	CreatedPrimaryLayout = InCreatedWidget;
}

void ULabUIGameInstanceSubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<ULabActivatableWidgetBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, ULabActivatableWidgetBase*)> AysncPushStateCallback)
{
	check(InSoftWidgetClass.IsNull() == false);

	// 위젯 생성 시 호출될 콜백
	auto OnWidgetCreated = [AysncPushStateCallback](ULabActivatableWidgetBase& CreatedWidgetInstance)
		{
			AysncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);
		};

	// 에셋 비동기 로드 완료 시 호출될 콜백
	auto OnAsyncLoadComplete = [this, OnWidgetCreated, InSoftWidgetClass, InWidgetStackTag, AysncPushStateCallback]()
		{
			UClass* LoadedWidgetClass = InSoftWidgetClass.Get();
			check(LoadedWidgetClass && CreatedPrimaryLayout);

			UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);
			check(FoundWidgetStack);

			ULabActivatableWidgetBase* CreatedWidget = FoundWidgetStack->AddWidget<ULabActivatableWidgetBase>(
				LoadedWidgetClass,
				OnWidgetCreated
			);

			AysncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
		};

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(OnAsyncLoadComplete)
	);
}

void ULabUIGameInstanceSubsystem::PushConfirmScreenToModalStackAynsc(EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
	UConfirmScreenInfoObject* CreatedInfoObject = nullptr;

	switch (InScreenType)
	{
	case EConfirmScreenType::Ok:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateOKScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::YesNo:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::OKCancel:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateOkCancelScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::Unknown:
		break;
	default:
		break;
	}

	check(CreatedInfoObject);

	PushSoftWidgetToStackAsync(
		LabGameplayTags::Lab_WidgetStack_Modal,
		ULabFunctionLibrary::GetFrontendSoftWidgetClassByTag(LabGameplayTags::Lab_Widget_ConfirmScreen),
		[CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushState, ULabActivatableWidgetBase* PushedWidget)
		{
			if (InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				ULabUIConfirmScreen* CreatedConfirmScreen = CastChecked<ULabUIConfirmScreen>(PushedWidget);
				CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject, ButtonClickedCallback);
			}
		}
	);
}
