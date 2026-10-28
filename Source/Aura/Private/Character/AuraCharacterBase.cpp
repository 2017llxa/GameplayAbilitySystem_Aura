// Copyright Druid Mechanics


#include "Character/AuraCharacterBase.h"
#include  "AbilitySystemBlueprintLibrary.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
	
}

void AAuraCharacterBase::ApplyEffectToSelf()
{
	InitializeDefaultAttributes(DefaultPrimaryAttribute,1);
	InitializeDefaultAttributes(DefaultSecondaryAttribute,1);
}

void AAuraCharacterBase::InitializeDefaultAttributes(TSubclassOf<UGameplayEffect> GamePlayEffect, float Level) const
{
	check(GetAbilitySystemComponent())
	check(GamePlayEffect)
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GamePlayEffect,Level,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),GetAbilitySystemComponent()); 
}


