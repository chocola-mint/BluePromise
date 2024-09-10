// Copyright Epic Games, Inc. All Rights Reserved.

#include "BluePromiseStyle.h"
#include "BluePromise.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FBluePromiseStyle::StyleInstance = nullptr;

void FBluePromiseStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FBluePromiseStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

TSharedRef< FSlateStyleSet > FBluePromiseStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("BluePromiseStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("BluePromise")->GetBaseDir() / TEXT("Resources"));
	return Style;
}

void FBluePromiseStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}
