// Copyright Marco Freemantle

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Aura Gameplay Tags Singleton
 */
struct FAuraGameplayTags
{
public:
 static const FAuraGameplayTags& Get() { return GameplayTags; }
 static void InitialiseNativeGameplayTags();

 FGameplayTag Attributes_Vital_Health;
 FGameplayTag Attributes_Vital_Mana;

 FGameplayTag Attributes_Primary_Strength;
 FGameplayTag Attributes_Primary_Intelligence;
 FGameplayTag Attributes_Primary_Resilience;
 FGameplayTag Attributes_Primary_Vigor;

 FGameplayTag Attributes_Secondary_Armour;
 FGameplayTag Attributes_Secondary_ArmourPenetration;
 FGameplayTag Attributes_Secondary_BlockChance;
 FGameplayTag Attributes_Secondary_CriticalHitChance;
 FGameplayTag Attributes_Secondary_CriticalHitDamage;
 FGameplayTag Attributes_Secondary_CriticalHitResistance;
 FGameplayTag Attributes_Secondary_HealthRegeneration;
 FGameplayTag Attributes_Secondary_ManaRegeneration;
 FGameplayTag Attributes_Secondary_MaxHealth;
 FGameplayTag Attributes_Secondary_MaxMana;

 FGameplayTag Message_Burning;
 FGameplayTag Message_HealthCrystal;
 FGameplayTag Message_HealthPotion;
 FGameplayTag Message_ManaCrystal;
 FGameplayTag Message_ManaPotion;

private:
 static FAuraGameplayTags GameplayTags;
 
};
