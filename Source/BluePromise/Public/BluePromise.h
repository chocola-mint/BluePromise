// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/CancellableAsyncAction.h"
#include "BluePromise.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBluePromiseEvent);

/**
 * Base class for Promise-like Async Action nodes.
 * Can be managed by PromiseContext, providing UX similar to Unity's coroutines.
 */
UCLASS(Abstract, BlueprintType)
class UBluePromise : public UCancellableAsyncAction
{
	GENERATED_BODY()
	
protected:
	void SetupBluePromise(class UPromiseContext* Context);

public:
	virtual void Activate() override;
	virtual void BeginDestroy() override;
	/**
	* (Pure virtual, must be overriden or else will crash)
	* Get reference to the Complete event delegate.
	* 
	* ~This cannot be C++ pure virtual because UClasses need to be constructable.
	*/
	virtual FBluePromiseEvent& GetCompleteEvent() 
	{
		check(false);
		return *(FBluePromiseEvent*)nullptr;
	}

	/**
	* End the BluePromise instance.
	*/
	UFUNCTION(BlueprintCallable)
	void End();

private:
	UPROPERTY()
	TObjectPtr<UPromiseContext> PromiseContext = nullptr;
};
