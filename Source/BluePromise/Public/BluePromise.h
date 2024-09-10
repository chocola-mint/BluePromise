// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/CancellableAsyncAction.h"
#include "BluePromise.generated.h"

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
	* End the BluePromise instance.
	*/
	UFUNCTION(BlueprintCallable)
	void End();

private:
	UPROPERTY()
	TObjectPtr<UPromiseContext> PromiseContext = nullptr;
};
