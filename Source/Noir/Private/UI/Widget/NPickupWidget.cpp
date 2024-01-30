// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/NPickupWidget.h"

FUIWidgetRow UNPickupWidget::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	FUIWidgetRow* FoundRow = DataTable->FindRow<FUIWidgetRow>(Tag.GetTagName(), TEXT(""));
	if (FoundRow)
	{
		return *FoundRow;
	}
	return FUIWidgetRow();
}
