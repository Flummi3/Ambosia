// (C) Flumminard 2015

#include "Ambosia.h"
#include "InventoryComponent.h"
#include "GameplayValuesComponent.h"


// Sets default values for this component's properties
UGameplayValuesComponent::UGameplayValuesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	TimeToNextRegen = 1;

	HealthPoints = 200;
	HealthPointsLimit = 200;
	AttackPoints = 100;
	Mana = 0;
	ManaLimit = 0;
	MagicalAttackPoints = 0;
	ManaRegenerationPerSec = 0;
}

void UGameplayValuesComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	this->TimeToNextRegen -= DeltaTime;
	if (this->TimeToNextRegen <= 0)
	{
		this->SetMana(this->GetMana() + GetManaRegenerationPerSec());
		this->TimeToNextRegen = 1;
	}
}

void UGameplayValuesComponent::AffectHealthPoints(float Delta)
{
	UInventoryComponent* Inventory = dynamic_cast<UInventoryComponent*>(this->GetOwner()->GetComponentByClass(TSubclassOf<UInventoryComponent>()));
	if (Inventory == nullptr)
		return;
	UArmorComponent* Armor = Inventory->GetArmor();
	if (Armor == nullptr)
		return;
	Delta = Armor->AffectDamage(Delta);
	this->SetHealthPoints(this->GetHealthPoints() + Delta);
}

float UGameplayValuesComponent::GetHealthPoints()
{
	return this->HealthPoints;
}

void UGameplayValuesComponent::SetHealthPoints(float NewHealthPoints)
{
	if (NewHealthPoints > this->HealthPointsLimit)
	{
		this->HealthPoints = this->HealthPointsLimit;
	}
	else if (NewHealthPoints <= 0)
	{
		this->GetOwner()->Destroy();
	}
	else
	{
		this->HealthPoints = NewHealthPoints;
	}
}

float UGameplayValuesComponent::GetHealthPointsLimit()
{
	return this->HealthPoints;
}

void UGameplayValuesComponent::SetHealthPointsLimit(float NewHealthPointsLimit)
{
	this->HealthPointsLimit = NewHealthPointsLimit;
	if (this->HealthPoints > this->HealthPointsLimit)
		this->HealthPoints = this->HealthPointsLimit;
}

float UGameplayValuesComponent::GetAttackPoints()
{
	return this->AttackPoints;
}

void UGameplayValuesComponent::SetAttackPoints(float NewAttackPoints)
{
	this->AttackPoints = NewAttackPoints;
}

float UGameplayValuesComponent::GetMana()
{
	return this->Mana;
}

void UGameplayValuesComponent::SetMana(float NewMana)
{
	if (NewMana <= this->ManaLimit)
		this->Mana = NewMana;
	else
		this->Mana = this->ManaLimit;
}

float UGameplayValuesComponent::GetManaLimit()
{
	return this->ManaLimit;
}

void UGameplayValuesComponent::SetManaLimit(float NewManaLimit)
{
	this->ManaLimit = NewManaLimit;
	if (this->Mana > this->ManaLimit)
		this->Mana = this->ManaLimit;
}

float UGameplayValuesComponent::GetMagicalAttackPoints()
{
	return this->MagicalAttackPoints;
}

void UGameplayValuesComponent::SetMagicalAttackPoints(float NewMagicalAttackPoints)
{
	this->MagicalAttackPoints = NewMagicalAttackPoints;
}

float UGameplayValuesComponent::GetManaRegenerationPerSec()
{
	return this->ManaRegenerationPerSec;
}

void UGameplayValuesComponent::SetManaRegenerationPerSec(float NewManaReg)
{
	this->ManaRegenerationPerSec = NewManaReg;
}