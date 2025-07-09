// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "NativeGameplayTags.h"
#include "ProjectNotificationMessage.generated.h"

class UObject;

PROJECT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Project_AddNotification_Message);

class APlayerState;

USTRUCT(BlueprintType)
struct PROJECT_API FProjectNotificationMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category=Notification)
	FGameplayTag TargetChannel;

	UPROPERTY(BlueprintReadWrite, Category=Notification)
	TObjectPtr<APlayerState> TargetPlayer = nullptr;

	UPROPERTY(BlueprintReadWrite, Category=Notification)
	FText PayloadMessage;

	UPROPERTY(BlueprintReadWrite, Category=Notification)
	FGameplayTag PayloadTag;

	UPROPERTY(BlueprintReadWrite, Category=Notification)
	TObjectPtr<UObject> PayloadObject = nullptr;
};
