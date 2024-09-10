// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BluePromise.h"
#include "WaitForSecondsPromise.generated.h"

/**
 * A BluePromise that is equivalent to the Delay node.
 */
UCLASS()
class UWaitForSecondsPromise : public UBluePromise
{
	GENERATED_BODY()
	
public:
	/**
	 * Start a delay.
	 * @param DelayTime		How long the delay will last.
	 * @param WorldContext	Object from which the world will be derived.
	 * @param ActionHandle  Shortcut to save the reference to this action to a variable. Useful for cancellation.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Wait For Seconds", meta=(WorldContext="WorldContext", BlueprintInternalUseOnly="true"), Category="Blue Promise")
	static UWaitForSecondsPromise* WaitForSecondsPromise(const UObject* WorldContext, float DelayTime, UPromiseContext* Context);
	
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

	/** The time this action will wait before finishing. */
	float DelayTime = 0.f;

	/** The timer handle. */
	FTimerHandle OngoingDelay;
};
