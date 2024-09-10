// Fill out your copyright notice in the Description page of Project Settings.


#include "BluePromise.h"
#include "PromiseContext.h"

void UBluePromise::SetupBluePromise(UPromiseContext* Context)
{
	PromiseContext = Context;
}

void UBluePromise::Activate()
{
	if (PromiseContext)
	{
		PromiseContext->RegisterAction(this);
	}
}

void UBluePromise::BeginDestroy()
{
	Super::Super::BeginDestroy();
}

void UBluePromise::End()
{
	if (PromiseContext)
	{
		PromiseContext->UnregisterAction(this);
	}
	SetReadyToDestroy();
}
