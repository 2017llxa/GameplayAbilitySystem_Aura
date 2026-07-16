
#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	// 初始化属性值
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(10.f);
	InitMaxMana(50.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0,100);
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0,100);
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectPropertiesValue(Data,Props);

	/*
	打印结构体
	for (TFieldIterator<FProperty> It(FEffectProperties::StaticStruct()); It; ++It)
		{
			FProperty* Prop = *It;
			if (auto* ObjectProp = CastField<FObjectProperty>(Prop))
			{
			const void* ValuePtr = ObjectProp->ContainerPtrToValuePtr<void>(&Props);
			UObject* Obj = ObjectProp->GetObjectPropertyValue(ValuePtr);
				UE_LOG(LogTemp, Warning, TEXT("%s = %s"),
					*Prop->GetName(), *GetNameSafe(Obj));
			}
		}
	源对象（药水）
	UE_LOG(LogTemp, Log,TEXT("%s"),*GetNameSafe(Props.EffectContextHandle.GetSourceObject()))
	*/
}

void UAuraAttributeSet::SetEffectPropertiesValue(const FGameplayEffectModCallbackData& Data,FEffectProperties& Props)
{
	/*
	=== Target（承受者）===
		Data.Target 就是承受这次修改的 ASC
		UAbilitySystemComponent* TargetASC = Data.Target;
		AActor* TargetAvatar = Data.Target->GetAvatarActor();承受者角色（Pawn/Character）
	=== Source（施加者）===
		从 EffectSpec 的 Context 里取，而不是从 Data 取
		const FGameplayEffectContextHandle& Context = Data.EffectSpec.GetContext();
		UAbilitySystemComponent* SourceASC = Context.GetInstigatorAbilitySystemComponent();施加者 ASC
		}
	*/
	
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.Get())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

// Replication callbacks
void UAuraAttributeSet::OnRep_Health(FGameplayAttributeData OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(FGameplayAttributeData OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(FGameplayAttributeData OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(FGameplayAttributeData OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}


