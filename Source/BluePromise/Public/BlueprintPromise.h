// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BluePromise.h"
#include "BlueprintPromise.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBlueprintPromiseEvent);

/**
 * A special kind of BluePromise that can be implemented via Blueprints.
 */
UCLASS()
class UBlueprintPromise : public UBluePromise
{
	GENERATED_BODY()
	
public:
	/**
	 * Create a Blueprint Promise that can be completed from Blueprint.
	 * @param WorldContext	Object from which the world will be derived.
	 * @param ActionHandle  Shortcut to save the reference to this action to a variable. Useful for cancellation.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Create Blueprint Promise", meta=(WorldContext="WorldContext", BlueprintInternalUseOnly="true"), Category="Blue Promise")
	static UBlueprintPromise* BlueprintPromise(const UObject* WorldContext, class UPromiseContext* Context);
	
	/** A delegate called when the promise completes. */
	UPROPERTY(BlueprintAssignable)
	FBlueprintPromiseEvent OnComplete;

	/** A delegate called when the promise is cancelled. */
	UPROPERTY(BlueprintAssignable)
	FBlueprintPromiseEvent OnCancel;

	/** Complete the Blueprint Promise.*/
	UFUNCTION(BlueprintCallable)
	void Complete();

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
};
