// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitForSignalPromise.h"
#include "BlueSignal.h"

UWaitForSignalPromise* UWaitForSignalPromise::WaitForSignalPromise(const UObject* WorldContext, UBlueSignal* Signal, UPromiseContext* Context)
{
	// We must have a valid contextual world for this action, so we don't even make it
	// unless we can resolve the UWorld from WorldContext.
	UWorld* ContextWorld = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
	if(!ensureAlwaysMsgf(IsValid(WorldContext), TEXT("World Context was not valid.")))
	{
		return nullptr;
	}

	UWaitForSignalPromise* NewAction = NewObject<UWaitForSignalPromise>();
	NewAction->SignalObject = Signal;
	NewAction->RegisterWithGameInstance(ContextWorld->GetGameInstance());
	NewAction->SetupBluePromise(Context);
	return NewAction;
}

void UWaitForSignalPromise::Activate()
{
	if (!SignalObject)
		return;
	Super::Activate();
	SignalObject->OnSignalEmitOneShotDelegate.AddWeakLambda(this, [this]()
		{
			if (this->IsActive())
			{
				this->OnComplete.Broadcast();
				this->End();
			}
		});
}

void UWaitForSignalPromise::Cancel()
{
	OnCancel.Broadcast();
	End();
}

void UWaitForSignalPromise::SetReadyToDestroy()
{
	Super::SetReadyToDestroy();
}
