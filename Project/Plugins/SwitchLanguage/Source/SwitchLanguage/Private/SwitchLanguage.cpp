// Description:switch the language displayed in the editor
// Author:Jiecool
// Date:2024/10/25
// Email:jiecool@qq.com

#include "SwitchLanguage.h"
#include "SwitchLanguageStyle.h"
#include "SwitchLanguageCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "Interfaces/IMainFrameModule.h"

#include "Editor/InternationalizationSettings/Classes/InternationalizationSettingsModel.h"


static const FName SwitchLanguageTabName("SwitchLanguage");

#define LOCTEXT_NAMESPACE "FSwitchLanguageModule"

void FSwitchLanguageModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSwitchLanguageStyle::Initialize();
	FSwitchLanguageStyle::ReloadTextures();

	FSwitchLanguageCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSwitchLanguageCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FSwitchLanguageModule::SwitchLanguageButtonClicked),
		FCanExecuteAction());

	IMainFrameModule& MainFrame = FModuleManager::GetModuleChecked<IMainFrameModule>("MainFrame");

	#if ENGINE_MAJOR_VERSION >=5
			TSharedPtr<FUICommandList> MainFrameCommands = MainFrame.GetMainFrameCommandBindings();
	#else
			TSharedRef<FUICommandList> MainFrameCommands = MainFrame.GetMainFrameCommands();
	#endif

	MainFrameCommands->Append(PluginCommands.ToSharedRef());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSwitchLanguageModule::RegisterMenus));
}

void FSwitchLanguageModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FSwitchLanguageStyle::Shutdown();

	FSwitchLanguageCommands::Unregister();
}

void FSwitchLanguageModule::SwitchLanguageButtonClicked()
{
	if (GConfig) {

		const TArray<FString> LocalizedCultureNames = FTextLocalizationManager::Get().GetLocalizedCultureNames(ELocalizationLoadFlags::Editor);

		FString SourceLangStr = "en";
		FString TargetLangStr = "zh-Hans";

		FString CurrentLanguage = UKismetInternationalizationLibrary::GetCurrentLanguage();
		FString NewLanguage = (CurrentLanguage == SourceLangStr) ? TargetLangStr : SourceLangStr;
		TWeakObjectPtr<UInternationalizationSettingsModel> SettingsModel;
		bool bExist = LocalizedCultureNames.Contains(NewLanguage);
		if (bExist) {
			SettingsModel->SetEditorLanguage(NewLanguage);
			// if (not SettingsModel->ShouldUseLocalizedPropertyNames()) {
			// 	SettingsModel->SetShouldUseLocalizedPropertyNames(bExist);
			// }
			// if (not SettingsModel->ShouldUseLocalizedNodeAndPinNames()) {
			// 	SettingsModel->SetShouldUseLocalizedNodeAndPinNames(bExist);
			// }
			FInternationalization& I18N = FInternationalization::Get();
			I18N.SetCurrentLanguage(NewLanguage);
			// Find all Schemas and force a visualization cache clear
			for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
			{
				UClass* CurrentClass = *ClassIt;

				if (UEdGraphSchema* Schema = Cast<UEdGraphSchema>(CurrentClass->GetDefaultObject()))
				{
					Schema->ForceVisualizationCacheClear();
				}
			}
		}


	}
}

void FSwitchLanguageModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("SwitchLanguage");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FSwitchLanguageCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
				Entry.Name = "SwitchLanguageButton";
				Entry.Label = FText::FromString(TEXT("SwitchLanguage"));
				Entry.ToolTip = FText::FromString(TEXT("全局快捷键:"));
			}
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("AssetEditor.DefaultToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("SwitchLanguage");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FSwitchLanguageCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
				Entry.Name = "SwitchLanguageButton";
				Entry.Label = FText::FromString(TEXT(""));
				Entry.ToolTip = FText::FromString(TEXT("全局快捷键:"));
			}
		}
	}

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSwitchLanguageModule, SwitchLanguage)