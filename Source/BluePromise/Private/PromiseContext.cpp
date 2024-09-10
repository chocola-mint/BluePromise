// Fill out your copyright notice in the Description page of Project Settings.


#include "PromiseContext.h"
#include "BluePromise.h"

// Sets default values for this component's properties
UPromiseContext::UPromiseContext()
{
}

UPromiseContext::~UPromiseContext()
{
}

UPromiseContext* UPromiseContext::CreatePromiseContext(UObject* Context)
{
	return NewObject<UPromiseContext>(Context);
}

void UPromiseContext::RegisterAction(UBluePromise* Action)
{
	Actions.Add(Action);
}

void UPromiseContext::UnregisterAction(UBluePromise* Action)
{
	Actions.Remove(Action);
}

void UPromiseContext::CancelAll()
{
	for (auto Iter = Actions.begin(); Iter;)
	{
		auto Action = *Iter;		
		++Iter;
		Action->Cancel();
	}
}

void UPromiseContext::AbortAll()
{
	for (auto Action : Actions)
	{
		Action->SetReadyToDestroy();
	}
	Actions.Empty();
}
