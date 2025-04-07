// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUserSettings/PPGameUserSettings.h"
#include "GameUserSettings/PPGameSetting.h"
#include "GameUserSettings/PPGameSettingCollection.h"

UPPGameUserSettings::UPPGameUserSettings()
{

}

UPPGameUserSettings* UPPGameUserSettings::Get()
{
	if (!GEngine)
	{
		return nullptr;
	}

	UPPGameUserSettings* Settings = Cast<UPPGameUserSettings>(GEngine->GetGameUserSettings());
	if (Settings)
	{
		Settings->Initialize();
	}

	return Settings;
}

UPPGameSettingCollection* UPPGameUserSettings::GetSettingCollection(FString& InSettingCollectionName)
{
	for (UPPGameSettingCollection* SettingCollection : RegisteredSettings)
	{
		if (IsValid(SettingCollection))
		{
			if (SettingCollection->GetName() == InSettingCollectionName)
			{
				return SettingCollection;
			}
		}
	}

	return nullptr;
}

void UPPGameUserSettings::Initialize()
{
	RegisteredSettings.Add(InitializeVideoSettings());
	RegisteredSettings.Add(InitializeAudioSettings());
}

UPPGameSettingCollection* UPPGameUserSettings::InitializeVideoSettings()
{
	UPPGameSettingCollection* Screen = NewObject<UPPGameSettingCollection>();
	Screen->SetName("VideoCollection");
	Screen->SetDisplayName("Graphics");
	
	{
		{
			UPPGameSetting* Setting = NewObject<UPPGameSetting>();
			Setting->SetName("Anti-Aliasing");
			Setting->AddOption(0, FText::FromString("Low"));
			Setting->AddOption(1, FText::FromString("Medium"));
			Setting->AddOption(2, FText::FromString("High"));
			Setting->AddOption(3, FText::FromString("Epic"));
			Setting->AddGetter([&]() { return GetAntiAliasingQuality(); });
			Setting->AddSetter([&](int32 Level) { SetAntiAliasingQuality(Level); });

			Screen->AddSetting(Setting);
		}

		{
			UPPGameSetting* Setting = NewObject<UPPGameSetting>();
			Setting->SetName("Textures");
			Setting->AddOption(0, FText::FromString("Low"));
			Setting->AddOption(1, FText::FromString("Medium"));
			Setting->AddOption(2, FText::FromString("High"));
			Setting->AddOption(3, FText::FromString("Epic"));
			Setting->AddGetter([&]() { return GetTextureQuality(); });
			Setting->AddSetter([&](int32 Level) { SetTextureQuality(Level); });

			Screen->AddSetting(Setting);
		}

		{
			UPPGameSetting* Setting = NewObject<UPPGameSetting>();
			Setting->SetName("Global Illumination");
			Setting->AddOption(0, FText::FromString("Low"));
			Setting->AddOption(1, FText::FromString("Medium"));
			Setting->AddOption(2, FText::FromString("High"));
			Setting->AddOption(3, FText::FromString("Epic"));
			Setting->AddGetter([&]() { return GetGlobalIlluminationQuality(); });
			Setting->AddSetter([&](int32 Level) { SetGlobalIlluminationQuality(Level); });

			Screen->AddSetting(Setting);
		}

		{
			UPPGameSetting* Setting = NewObject<UPPGameSetting>();
			Setting->SetName("Shadows");
			Setting->AddOption(0, FText::FromString("Low"));
			Setting->AddOption(1, FText::FromString("Medium"));
			Setting->AddOption(2, FText::FromString("High"));
			Setting->AddOption(3, FText::FromString("Epic"));
			Setting->AddGetter([&]() { return GetShadowQuality(); });
			Setting->AddSetter([&](int32 Level) { SetShadowQuality(Level); });

			Screen->AddSetting(Setting);
		}

		{
			UPPGameSetting* Setting = NewObject<UPPGameSetting>();
			Setting->SetName("Post Processing");
			Setting->AddOption(0, FText::FromString("Low"));
			Setting->AddOption(1, FText::FromString("Medium"));
			Setting->AddOption(2, FText::FromString("High"));
			Setting->AddOption(3, FText::FromString("Epic"));
			Setting->AddGetter([&]() { return GetPostProcessingQuality(); });
			Setting->AddSetter([&](int32 Level) { SetPostProcessingQuality(Level); });

			Screen->AddSetting(Setting);
		}

		{
			UPPGameSetting* Setting = NewObject<UPPGameSetting>();
			Setting->SetName("View Distance");
			Setting->AddOption(0, FText::FromString("Low"));
			Setting->AddOption(1, FText::FromString("Medium"));
			Setting->AddOption(2, FText::FromString("High"));
			Setting->AddOption(3, FText::FromString("Epic"));
			Setting->AddGetter([&]() { return GetViewDistanceQuality(); });
			Setting->AddSetter([&](int32 Level) { SetViewDistanceQuality(Level); });

			Screen->AddSetting(Setting);
		}

		{
			UPPGameSetting* Setting = NewObject<UPPGameSetting>();
			Setting->SetName("Visual Effect Quality");
			Setting->AddOption(0, FText::FromString("Low"));
			Setting->AddOption(1, FText::FromString("Medium"));
			Setting->AddOption(2, FText::FromString("High"));
			Setting->AddOption(3, FText::FromString("Epic"));
			Setting->AddGetter([&]() { return GetVisualEffectQuality(); });
			Setting->AddSetter([&](int32 Level) { SetVisualEffectQuality(Level); });

			Screen->AddSetting(Setting);
		}

		{
			UPPGameSetting* Setting = NewObject<UPPGameSetting>();
			Setting->SetName("Reflection Quality");
			Setting->AddOption(0, FText::FromString("Low"));
			Setting->AddOption(1, FText::FromString("Medium"));
			Setting->AddOption(2, FText::FromString("High"));
			Setting->AddOption(3, FText::FromString("Epic"));
			Setting->AddGetter([&]() { return GetReflectionQuality(); });
			Setting->AddSetter([&](int32 Level) { SetReflectionQuality(Level); });

			Screen->AddSetting(Setting);
		}
	}

	return Screen;
}

UPPGameSettingCollection* UPPGameUserSettings::InitializeAudioSettings()
{
	return nullptr;
}
