// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BluePromise.h"
#include "WaitUntilNextTickPromise.generated.h"

/**
 * A BluePromise that is equivalent to the Delay Until Next Tick node.
 */
UCLASS()
class UWaitUntilNextTickPromise : public UBluePromise
{
	GENERATED_BODY()

public:
	/**
	 * Start a delay that lasts until the next tick.
	 * @param WorldContext	Object from which the world will be derived.
	 * @param ActionHandle  Shortcut to save the reference to this action to a variable. Useful for cancellation.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Wait Until Next Tick", meta=(WorldContext="WorldContext", BlueprintInternalUseOnly="true"), Category="Blue Promise")
	static UWaitUntilNextTickPromise* WaitUntilNextTickPromise(const UObject* WorldContext, class UPromiseContext* Context);
	
	/** A delegate called when the promise completes. */
	UPROPERTY(BlueprintAssignable)
	FBluePromiseEvent OnComplete;

	virtual FBluePromiseEvent& GetCompleteEvent() override
	{
		return OnComplete;
	}

	/** A delegate called when the promise is cancelled. */
	UPROPERTY(BlueprintAssignable)
	FBluePromiseEvent OnCancel;

	// Start UCancellablePromise Functions
	virtual void Activate() override;
	virtual void Cancel() override;
	virtual void SetReadyToDestroy() override;
	// End UCancellablePromise Functions

	// Start UObject Functions
	virtual UWorld* GetWorld() const override
	{
		return ContextWorld.IsValid() ? ContextWorld.Get() : nullptr;
	}
	// End UObject Functions
	
private:
	/** The context world of this action. */
	TWeakObjectPtr<UWorld> ContextWorld = nullptr;

	/** The timer handle. */
	FTimerHandle OngoingDelay;	
};
