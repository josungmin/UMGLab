// Copyright (c) 2026 Jo Sungmin. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LabUIGameInstanceSubsystem.generated.h"

struct FGameplayTag;
class ULabPrimaryLayoutWidget;
class ULabActivatableWidgetBase;
class ULabCommonButtonBase;



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate, ULabCommonButtonBase*, BroadcastingButton, FText, DescriptionText);

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

UCLASS()
class UMGLAB_API ULabUIGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	/** @return 제공된 월드와 연관된 게임 인스턴스의 ULabUIGameInstanceSubsystem를 반환합니다.*/
	static ULabUIGameInstanceSubsystem& Get(const UObject* InWorldContextObject);

	//~ Begin USubsyem Interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~ End USubsyem Interface

public:
	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(ULabPrimaryLayoutWidget* InCreatedWidget);

	void PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<ULabActivatableWidgetBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, ULabActivatableWidgetBase*)> AysncPushStateCallback);

	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;

private:
	UPROPERTY(Transient)
	ULabPrimaryLayoutWidget* CreatedPrimaryLayout;
};
