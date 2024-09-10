// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BluePromise.h"
#include "WaitLoopPromise.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitLoopPromiseEvent);

/**
 * A BluePromise that runs an asynchronous loop that can be continued manually with different delays.
 */
UCLASS()
class UWaitLoopPromise : public UBluePromise
{
	GENERATED_BODY()
	
public:
	/**
	 * Start a wait loop.
	 * @param WorldContext	Object from which the world will be derived.
	 * @param ActionHandle  Shortcut to save the reference to this action to a variable. Useful for cancellation.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Wait Loop", meta=(WorldContext="WorldContext", BlueprintInternalUseOnly="true"), Category="Blue Promise")
	static UWaitLoopPromise* WaitLoopPromise(const UObject* WorldContext, UPromiseContext* Context);
	
	/** A delegate called when the loop continues. */
	UPROPERTY(BlueprintAssignable)
	FWaitLoopPromiseEvent OnContinue;

	/** A delegate called when the loop is cancelled. */
	UPROPERTY(BlueprintAssignable)
	FWaitLoopPromiseEvent OnCancel;

	/** A delegate called when the loop breaks. */
	UPROPERTY(BlueprintAssignable)
	FWaitLoopPromiseEvent OnBreak;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int LoopCounter = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double StartTime = 0;
	
	/** Continue the loop when the next Tick happens.*/
	UFUNCTION(BlueprintCallable)
	void ContinueOnNextTick();
	
	/** Continue the loop after DelayTime. */
	UFUNCTION(BlueprintCallable)
	void ContinueAfterDelay(float DelayTime);

	/** Continue the loop immediately. This might cause an unintentional infinite loop so be careful! */
	UFUNCTION(BlueprintCallable)
	void ContinueImmediately();
	
	/** End the loop. */
	UFUNCTION(BlueprintCallable)
	void Break();

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

	UFUNCTION()
	void Internal_Continue() const;
};
