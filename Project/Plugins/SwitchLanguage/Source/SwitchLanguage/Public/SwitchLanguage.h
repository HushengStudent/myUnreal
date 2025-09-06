// Description:switch the language displayed in the editor
// Author:Jiecool
// Date:2024/10/25
// Email:jiecool@qq.com

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FSwitchLanguageModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void SwitchLanguageButtonClicked();
	
private:

	void RegisterMenus();

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
