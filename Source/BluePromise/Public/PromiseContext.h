// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/CancellableAsyncAction.h"
#include "PromiseContext.generated.h"

/**
* Object that manages a group of BluePromises.
* BluePromises will register and unregister themselves to PromiseContexts.
* You can then cancel or destroy all active BluePromises with CancelAll or DestroyAll.
* PromiseContext will also call DestroyAll automatically when destroyed.
*/
UCLASS(BlueprintType)
class UPromiseContext : public UObject
{
	GENERATED_BODY()

	friend class UBluePromise;
public:	
	// Sets default values for this component's properties
	UPromiseContext();
	~UPromiseContext();

	/** 
	* Create a new Promise Context.
	* @param Context Outer object.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DefaultToSelf = "Context"), Category="Blue Promise")
	static UPromiseContext* CreatePromiseContext(UObject* Context);

	UFUNCTION(BlueprintCallable)
	// Cancel all active actions.
	void CancelAll();
	UFUNCTION(BlueprintCallable)
	// Abort all active actions directly, without cancellation.
	void AbortAll();

protected:
	
	void RegisterAction(class UBluePromise* Action);
	void UnregisterAction(class UBluePromise* Action);

private:	
	UPROPERTY()
	TSet<class UBluePromise*> Actions;
};
