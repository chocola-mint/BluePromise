// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BluePromise.h"
#include "WaitForSignalPromise.generated.h"

/**
 * A BluePromise that is able to listen to a SignalComponent and complete when it is emitted.
 */
UCLASS()
class UWaitForSignalPromise : public UBluePromise
{
	GENERATED_BODY()
	
public:
	/**
	 * Wait for the given Signal to emit.
	 * @param WorldContext	Object from which the world will be derived.
	 * @param Signal        The signal to listen to.
	 * @param ActionHandle  Shortcut to save the reference to this action to a variable. Useful for cancellation.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Wait For Signal", meta=(WorldContext="WorldContext", BlueprintInternalUseOnly="true"), Category="Blue Promise")
	static UWaitForSignalPromise* WaitForSignalPromise(const UObject* WorldContext, class UBlueSignal* Signal, class UPromiseContext* Context);
	
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
	/** The signal to listen to. If this is null, the event will never complete. */
	UPROPERTY()
	class UBlueSignal* SignalObject;
};
