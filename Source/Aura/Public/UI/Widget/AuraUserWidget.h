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
	 * ��C++�����������������ܶ��壬��ͼ��д��
	 * ��C++����øú�������ͼ��дʵ�ָú���
	*/

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

public:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
};