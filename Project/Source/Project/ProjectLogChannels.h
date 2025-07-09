// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Logging/LogMacros.h"

class UObject;

PROJECT_API DECLARE_LOG_CATEGORY_EXTERN(LogProject, Log, All);
PROJECT_API DECLARE_LOG_CATEGORY_EXTERN(LogProjectExperience, Log, All);
PROJECT_API DECLARE_LOG_CATEGORY_EXTERN(LogProjectAbilitySystem, Log, All);
PROJECT_API DECLARE_LOG_CATEGORY_EXTERN(LogProjectTeams, Log, All);

PROJECT_API FString GetClientServerContextString(UObject* ContextObject = nullptr);
