// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/ABCommon.h"
#include "GameFramework/Character.h"
#include "Interface/ABCharacterWidgetInterface.h"
#include "CharacterStat/ABCharactorStatComponent.h"
#include "ABCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};


UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter, public IABCharacterWidgetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacterBase();
	virtual void SetupCharacterWidget(class UABUserWidget* InUserWidget) override
		;
	virtual void SetCharacterControlData(const class UABCharacterControlData* CharaterControlData);

	UPROPERTY(EditAnywhere, Category = CaracterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UABCharacterControlData*> CharacterControlManager;

//Combo Action Section
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABComboActionData> ComboActionData;

	void ProcessComboCommand();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

	void SetComboCheckTimer();
	void ComboCheck();

	void ComboInputCheck();
	void SetDelayInputTimer();

	int32 CurrentCombo = 0;

	FTimerHandle ComboTimerHandle;
	FTimerHandle ComboStartTimerHandle;
	FTimerHandle DeadTimerHandle;

	bool HasNextComboCommand = false;
	bool CanComboInput = false;
	bool ComboMiss = false;

	void SetDead();

//Stat Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABCharactorStatComponent> Stat;

// UI Widget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABWidgetComponent> HpBar;
};
