// Copyright Epic Games, Inc. All Rights Reserved.

#include "BluePromiseModule.h"
#include "BluePromiseStyle.h"

#define LOCTEXT_NAMESPACE "FBluePromiseModule"

void FBluePromiseModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FBluePromiseStyle::Initialize();
	FBluePromiseStyle::ReloadTextures();
}

void FBluePromiseModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FBluePromiseStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBluePromiseModule, BluePromise)
