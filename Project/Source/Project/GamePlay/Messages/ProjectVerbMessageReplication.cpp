// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectVerbMessageReplication.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Project/GamePlay/Messages/ProjectVerbMessage.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ProjectVerbMessageReplication)

//////////////////////////////////////////////////////////////////////
// FProjectVerbMessageReplicationEntry

FString FProjectVerbMessageReplicationEntry::GetDebugString() const
{
	return Message.ToString();
}

//////////////////////////////////////////////////////////////////////
// FProjectVerbMessageReplication

void FProjectVerbMessageReplication::AddMessage(const FProjectVerbMessage& Message)
{
	FProjectVerbMessageReplicationEntry& NewStack = CurrentMessages.Emplace_GetRef(Message);
	MarkItemDirty(NewStack);
}

void FProjectVerbMessageReplication::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
// 	for (int32 Index : RemovedIndices)
// 	{
// 		const FGameplayTag Tag = CurrentMessages[Index].Tag;
// 		TagToCountMap.Remove(Tag);
// 	}
}

void FProjectVerbMessageReplication::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	for (const int32 Index : AddedIndices)
	{
		const FProjectVerbMessageReplicationEntry& Entry = CurrentMessages[Index];
		RebroadcastMessage(Entry.Message);
	}
}

void FProjectVerbMessageReplication::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
	for (const int32 Index : ChangedIndices)
	{
		const FProjectVerbMessageReplicationEntry& Entry = CurrentMessages[Index];
		RebroadcastMessage(Entry.Message);
	}
}

void FProjectVerbMessageReplication::RebroadcastMessage(const FProjectVerbMessage& Message)
{
	check(Owner);
	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(Owner);
	MessageSystem.BroadcastMessage(Message.Verb, Message);
}

