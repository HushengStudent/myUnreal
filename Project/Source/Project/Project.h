// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define IS_CLIENT (NM_Client == GetNetMode())

#define IS_SERVER (NM_DedicatedServer == GetNetMode() || NM_ListenServer == GetNetMode())


#define CHECK_CONDITION(Condition)\
	if (false == (Condition))\
	{\
		return;\
	}

#define CHECK_CONDITION_WITH_MSG(Condition, LogCategory, LogType, Msg, ...)\
	if (false == (Condition))\
	{\
		UE_LOG(LogCategory, LogType, Msg, ##__VA_ARGS__);\
		return;\
	}
