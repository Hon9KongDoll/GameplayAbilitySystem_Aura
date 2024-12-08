// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

protected:

	/**
	 * BlueprintImplementableEvent:
	 * 在C++可以声明函数（不能定义，蓝图重写）
	 * 在C++里调用该函数，蓝图重写实现该函数
	*/

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

public:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
};
