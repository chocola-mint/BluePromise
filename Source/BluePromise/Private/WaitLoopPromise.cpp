// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitLoopPromise.h"
#include "Engine.h"
#include "Kismet/KismetSystemLibrary.h"

UWaitLoopPromise* UWaitLoopPromise::WaitLoopPromise(const UObject* WorldContext, UPromiseContext* Context)
{
	// We must have a valid contextual world for this action, so we don't even make it
	// unless we can resolve the UWorld from WorldContext.
	UWorld* ContextWorld = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
	if(!ensureAlwaysMsgf(IsValid(WorldContext), TEXT("World Context was not valid.")))
	{
		return nullptr;
	}

	UWaitLoopPromise* NewAction = NewObject<UWaitLoopPromise>();
	NewAction->ContextWorld = ContextWorld;
	NewAction->LoopCounter = 0;
	NewAction->StartTime = UKismetSystemLibrary::GetGameTimeInSeconds(WorldContext);
	NewAction->RegisterWithGameInstance(ContextWorld->GetGameInstance());
	NewAction->SetupBluePromise(Context);
	return NewAction;
}

void UWaitLoopPromise::ContinueOnNextTick()
{
	// When the promise is ready to activate, set a timer using the world's FTimerManager.
	if(const UWorld* World = GetWorld())
	{
		// The timer manager is a singleton, and GetTimerManger() accessor will always return a valid one.
		FTimerManager& TimerManager = World->GetTimerManager();
		
		LoopCounter++;
		OngoingDelay = TimerManager.SetTimerForNextTick(this, &UWaitLoopPromise::Internal_Continue);
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Failed to continue WaitLoopPromise!"));
	End();
}

void UWaitLoopPromise::ContinueAfterDelay(float DelayTime)
{
	// When the promise is ready to activate, set a timer using the world's FTimerManager.
	if(const UWorld* World = GetWorld())
	{
		// The timer manager is a singleton, and GetTimerManger() accessor will always return a valid one.
		FTimerManager& TimerManager = World->GetTimerManager();
		
		LoopCounter++;
		TimerManager.SetTimer(OngoingDelay, this, &UWaitLoopPromise::Internal_Continue, FMath::Max(DelayTime, 0.001f), false);
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Failed to continue WaitLoopPromise!"));
	End();
}

void UWaitLoopPromise::ContinueImmediately()
{
	Internal_Continue();
}

void UWaitLoopPromise::Break()
{
	OnBreak.Broadcast();
	End();
}

void UWaitLoopPromise::Internal_Continue() const
{
	if (IsActive())
	{
		OnContinue.Broadcast();
	}
}

void UWaitLoopPromise::Activate()
{
	Super::Activate();
	OnContinue.Broadcast();
}

void UWaitLoopPromise::Cancel()
{
	OnCancel.Broadcast();
	End();
}

void UWaitLoopPromise::SetReadyToDestroy()
{
	// Cancel the timer if it's ongoing, so OnComplete never broadcasts.
	if(OngoingDelay.IsValid())
	{
		if(const UWorld* World = GetWorld())
		{
			FTimerManager& TimerManager = World->GetTimerManager();
			TimerManager.ClearTimer(OngoingDelay);
		}
	}
	
	Super::SetReadyToDestroy();
}
