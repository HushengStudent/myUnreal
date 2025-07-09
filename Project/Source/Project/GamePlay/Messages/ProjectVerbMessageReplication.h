// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "ProjectVerbMessage.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "ProjectVerbMessageReplication.generated.h"

class UObject;
struct FProjectVerbMessageReplication;
struct FNetDeltaSerializeInfo;

USTRUCT(BlueprintType)
struct FProjectVerbMessageReplicationEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FProjectVerbMessageReplicationEntry()
	{}

	FProjectVerbMessageReplicationEntry(const FProjectVerbMessage& InMessage)
		: Message(InMessage)
	{
	}

	FString GetDebugString() const;

private:
	friend FProjectVerbMessageReplication;

	UPROPERTY()
	FProjectVerbMessage Message;
};

USTRUCT(BlueprintType)
struct FProjectVerbMessageReplication : public FFastArraySerializer
{
	GENERATED_BODY()

	FProjectVerbMessageReplication()
	{
	}

public:
	void SetOwner(UObject* InOwner) { Owner = InOwner; }

	// Broadcasts a message from server to clients
	void AddMessage(const FProjectVerbMessage& Message);

	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FProjectVerbMessageReplicationEntry, FProjectVerbMessageReplication>(CurrentMessages, DeltaParms, *this);
	}

private:
	void RebroadcastMessage(const FProjectVerbMessage& Message);

private:
	UPROPERTY()
	TArray<FProjectVerbMessageReplicationEntry> CurrentMessages;
	
	UPROPERTY()
	TObjectPtr<UObject> Owner = nullptr;
};

template<>
struct TStructOpsTypeTraits<FProjectVerbMessageReplication> : public TStructOpsTypeTraitsBase2<FProjectVerbMessageReplication>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};
