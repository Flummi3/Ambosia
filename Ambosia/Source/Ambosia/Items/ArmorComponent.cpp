// (C) Flumminard 2015

#include "Ambosia.h"
#include "ArmorComponent.h"

UArmorComponent::UArmorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	DefenceFactor = 1.0;
	MagicalDefenceFactor = 1.0;
}

float UArmorComponent::GetDefenceFactor()
{
	return this->DefenceFactor;
}

float UArmorComponent::AffectDamage(float RawDamage)
{
	if (RawDamage < 0)
	{
		return RawDamage / this->DefenceFactor;
	}
	else
		return RawDamage;
}

float UArmorComponent::GetMagicalDefenceFactor()
{
	return this->MagicalDefenceFactor;
}

float UArmorComponent::AffectMagicalDamage(float RawMagicalDamage)
{
	return RawMagicalDamage / this->MagicalDefenceFactor;
}