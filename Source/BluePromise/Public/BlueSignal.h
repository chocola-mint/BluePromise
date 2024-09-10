// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BlueSignal.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSignalEmitSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSignalEmitDynamicSignature);

/**
 * 
 */
UCLASS(BlueprintType)
class UBlueSignal : public UObject
{
	GENERATED_BODY()
	
public:
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