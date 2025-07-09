// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProjectVerbMessageHelpers.generated.h"

struct FGameplayCueParameters;
struct FProjectVerbMessage;
class APlayerController;
class APlayerState;
class UObject;
struct FFrame;


UCLASS()
class PROJECT_API UProjectVerbMessageHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Project")
	static APlayerState* GetPlayerStateFromObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "Project")
	static APlayerController* GetPlayerControllerFromObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "Project")
	static FGameplayCueParameters VerbMessageToCueParameters(const FProjectVerbMessage& Message);

	UFUNCTION(BlueprintCallable, Category = "Project")
	static FProjectVerbMessage CueParametersToVerbMessage(const FGameplayCueParameters& Params);
};
