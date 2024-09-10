// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitUntilNextTickPromise.h"

UWaitUntilNextTickPromise* UWaitUntilNextTickPromise::WaitUntilNextTickPromise(const UObject* WorldContext, UPromiseContext* Context)
{
	// We must have a valid contextual world for this action, so we don't even make it
	// unless we can resolve the UWorld from WorldContext.
	UWorld* ContextWorld = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
	if(!ensureAlwaysMsgf(IsValid(WorldContext), TEXT("World Context was not valid.")))
	{
		return nullptr;
	}

	UWaitUntilNextTickPromise* NewAction = NewObject<UWaitUntilNextTickPromise>();
	NewAction->ContextWorld = ContextWorld;
	NewAction->RegisterWithGameInstance(ContextWorld->GetGameInstance());
	NewAction->SetupBluePromise(Context);
	return NewAction;
}

void UWaitUntilNextTickPromise::Activate()
{
	Super::Activate();
	// When the promise is ready to activate, set a timer using the world's FTimerManager.
	if(const UWorld* World = GetWorld())
	{
		// The timer manager is a singleton, and GetTimerManger() accessor will always return a valid one.
		FTimerManager& TimerManager = World->GetTimerManager();

		// We pass in the callback function as a lambda.
		OngoingDelay = TimerManager.SetTimerForNextTick([WeakThis = TWeakObjectPtr<UWaitUntilNextTickPromise>(this)]()
			{
				// We're passing "this" as a weak pointer, because there is no guarantee that "this" will
				// exist by the time this lambda callback executes.
				if(WeakThis.IsValid() && WeakThis->IsActive())
				{
					// If everything went well, broadcast OnComplete (fire the On Complete pin), and wrap up.
					WeakThis->OnComplete.Broadcast();
					WeakThis->End();
				}
			});
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Failed to activate WaitUntilNextTickPromise!"));
	End();
}

void UWaitUntilNextTickPromise::Cancel()
{
	OnCancel.Broadcast();
	End();
}

void UWaitUntilNextTickPromise::SetReadyToDestroy()
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
