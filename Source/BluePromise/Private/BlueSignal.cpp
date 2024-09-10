// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueSignal.h"

void UBlueSignal::EmitSignal()
{
	OnSignalEmitDelegate.Broadcast();
	OnSignalEmitOneShotDelegate.Broadcast();
	OnSignalEmitOneShotDelegate.Clear();
	OnSignalEmit.Broadcast();
	OnSignalEmitOneShot.Broadcast();
	OnSignalEmitOneShot.Clear();
}
