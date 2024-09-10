// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BlueSignal.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSignalEmitSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSignalEmitDynamicSignature);

/**
 * BlueSignals are events that can be listened to by WaitForSignalPromise nodes.
 */
UCLASS(BlueprintType)
class UBlueSignal : public UObject
{
	GENERATED_BODY()
	
public:
	/**
	* Emit the signal, firing all registered delegates.
	*/
	UFUNCTION(BlueprintCallable)
	void EmitSignal();

	FOnSignalEmitSignature OnSignalEmitDelegate;
	FOnSignalEmitSignature OnSignalEmitOneShotDelegate;

private:
	// Called when Emit Signal is called.
	UPROPERTY(BlueprintAssignable)
	FOnSignalEmitDynamicSignature OnSignalEmit;
	// Same as On Signal Emit, but the event is cleared every time.
	UPROPERTY(BlueprintAssignable)
	FOnSignalEmitDynamicSignature OnSignalEmitOneShot;
};
