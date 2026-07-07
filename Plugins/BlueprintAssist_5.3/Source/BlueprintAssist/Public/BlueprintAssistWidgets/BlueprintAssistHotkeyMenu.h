// Copyright fpwong. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "BAFilteredList.h"
#include "BlueprintAssistTypes.h"

class SBlueprintContextTargetMenu;
class SWidget;
class FUICommandInfo;

struct FBAHotkeyItem : IBAFilteredListItem
{
	FName CommandName;
	FText CommandChord;
	FText CommandDesc;
	FText CommandLabel;
	FString SearchText;
	FName BindingContext;
	TSharedPtr<const FUICommandInfo> CommandInfo;

	FBAHotkeyItem(TSharedPtr<FUICommandInfo> Command);
	FBAHotkeyItem(UObject* SettingObj, FStructProperty* ChordProp, const FInputChord& Chord);

	virtual FString ToString() const override { return CommandLabel.ToString(); }

	virtual FString GetSearchText() const override;
};

class BLUEPRINTASSIST_API SBAHotkeyMenu : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SBAHotkeyMenu) {}
	SLATE_END_ARGS()

	static FVector2D GetWidgetSize() { return FVector2D(600, 500); }

	void Construct(const FArguments& InArgs);

	void InitListItems(TArray<TSharedPtr<FBAHotkeyItem>>& Items);

	void AddInputChords(TArray<TSharedPtr<FBAHotkeyItem>>& Items);

	TSharedRef<ITableRow> CreateItemWidget(TSharedPtr<FBAHotkeyItem> Item, const TSharedRef<STableViewBase>& OwnerTable) const;

	void SelectItem(TSharedPtr<FBAHotkeyItem> Item);

	TSharedPtr<SBAFilteredList<TSharedPtr<FBAHotkeyItem>>> FilteredList;

	void RefreshList();

	FBASettingsPropertyHook SettingsPropertyHook;
};
