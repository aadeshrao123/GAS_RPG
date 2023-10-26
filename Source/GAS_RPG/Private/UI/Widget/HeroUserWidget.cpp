// Copyright AadeshRao


#include "UI/Widget/HeroUserWidget.h"

void UHeroUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
