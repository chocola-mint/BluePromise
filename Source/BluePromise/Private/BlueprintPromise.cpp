// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintPromise.h"

UBlueprintPromise* UBlueprintPromise::BlueprintPromise(const UObject* WorldContext, UPromiseContext* Context)
{
	// We must have a valid contextual world for this action, so we don't even make it
	// unless we can resolve the UWorld from WorldContext.
	UWorld* ContextWorld = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
	if(!ensureAlwaysMsgf(IsValid(WorldContext), TEXT("World Context was not valid.")))
	{
		return nullptr;
	}

	UBlueprintPromise* NewAction = NewObject<UBlueprintPromise>();
	NewAction->RegisterWithGameInstance(ContextWorld->GetGameInstance());
	NewAction->SetupBluePromise(Context);
	return NewAction;
}

void UBlueprintPromise::Complete()
{
	OnComplete.Broadcast();
	End();
}

void UBlueprintPromise::Activate()
{
	Super::Activate();
}

void UBlueprintPromise::Cancel()
{
	OnCancel.Broadcast();
	End();
}

void UBlueprintPromise::SetReadyToDestroy()
{
	Super::SetReadyToDestroy();
}
