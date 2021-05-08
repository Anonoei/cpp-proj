#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>

#include "Actions/Attacks/Attack.h"
#include "Actions/Defenses/Defense.h"
#include "Actions/Maneuvers/Maneuver.h"
#include "Actions/Spells/Spell.h"

#include "Core/Base.h"

enum struct EntityType
{
	//	Humanoid
	Human = 0,
	Vampire,
	Werewolf,
	Ogre,
	Zombie,
	Goblin,
	Cyclops,
	Mermaid,
	Minotaur,

	//	Creatures
	Pheonix,
	Griffin,
	Dragon,
	Hydra,
	Unicorn,

	//	Animals
	Dog,
	Cat,
	Mouse,
	Rat,

	None

};

class Entity
{
	struct Statistics;
	struct Abilities;
public:
	Entity() { this->Spawn(); }
	Entity(const char* name)
		: m_Name(name)
	{
		this->Spawn();
	}
	Entity(Statistics stats)
		: Stat(stats)
	{
		this->Spawn();
	}

	~Entity()
	{
		this->Death();
	}

	void Spawn() {};
	void Death() {};

	void Move(Action maneuver);
	void Strike(Action attack);
	void Defend(Action defense);
	void Cast(Action spell);

	/////////////////////////////////////////////////////////
	//                       GETTERS                       //
	/////////////////////////////////////////////////////////
	const char* GetName() { return this->m_Name; }	//	@return Entity's Name
	UUID GetUUID()        { return this->m_UUID; }	//	@return Entity's UUID
	EntityType GetType()  { return this->m_Type; }	//	@return Entity's EntityType
	//--  Statistics  --//
	Statistics& GetStatistics() { return this->Stat; }
	//	Health
	uint32_t    GetMaxHealth()   { return this->Stat.m_MaxHealth; }				//	@return Entity's Max Health
	uint32_t    GetHealth()      { return this->Stat.m_CurrentHealth; }			//	@return Entity's Current Health
	float       GetHealRate()    { return this->Stat.m_HealthRechargeRate; }	//	@return Entity's Health Recharge Rate
	//	Mana
	uint32_t    GetMaxMana()     { return this->Stat.m_MaxMana; }				//	@return Entity's Max Mana
	uint32_t    GetMana()        { return this->Stat.m_CurrentMana; }			//	@return Entity's Current Mana
	float       GetManaRate()    { return this->Stat.m_ManaRechargeRate; }		//	@return Entity's Mana Recharge Rate
	//	Stamina
	uint32_t    GetMaxStamina()  { return this->Stat.m_MaxStamina; }			//	@return Entity's Max Stamina
	uint32_t    GetStamina()     { return this->Stat.m_CurrentStamina; }		//	@return Entity's Current Stamina
	float       GetStaminaRate() { return this->Stat.m_StaminaRechargeRate; }	//	@return Entity's Stamina Recharge Rate
	//	Stat
	float GetDefenseStat() { return this->Stat.m_DefenseStat; }
	float GetAttackStat()  { return this->Stat.m_AttackStat; }
	float GetWalkSpeed()   { return this->Stat.m_WalkSpeed; }
	float GetRunSpeed()    { return this->Stat.m_RunSpeed; }

	//--  Abilities  --//
	Abilities& GetAbilities() { return this->Ability; }
	//	Maneuvers
	std::vector<Maneuver>& GetManeuvers() { return this->Ability.m_Maneuvers; }	//	@return Entity's Maneuvers Vector
	size_t GetMeaneuverSize() { return this->Ability.m_Maneuvers.size(); }		//	@return Entity's Maneuvers Vector Size
	//Maneuver& GetManeuver(Maneuver maneuver);										//	@return An Entity's Maneuver
	//size_t GetManeuverIndex(Maneuver maneuver);									//	@return An Entity's Maneuver Index
	//	Attacks
	std::vector<Attack>& GetAttacks()   { return this->Ability.m_Attacks; }		//	@return Entity's Attacks Vector
	size_t GetAttackSize() { return this->Ability.m_Attacks.size(); }			//	@return Entity's Attacks Vector Size
	//Attack& GetAttack(Attack attack);											//	@return An Entity's Attack
	//size_t GetAttackIndex(Attack attack);										//	@return An Entity's Attack Index
	//	Defenses
	std::vector<Defense>& GetDefenses()  { return this->Ability.m_Defenses; }	//	@return Entity's Defenses Vector
	size_t GetDefenseSize() { return this->Ability.m_Defenses.size(); }			//	@return Entity's Defenses Vector Size
	//Defense& GetDefense(Defense defense);											//	@return An Entity's Defense
	//size_t GetDefenseIndex(Defense defense);										//	@return An Entity's Defense Index
	//	Spells
	std::vector<Spell>& GetSpells()    { return this->Ability.m_Spells; }		//	@return Entity's Spells Vector
	size_t GetSpellSize() { return this->Ability.m_Spells.size(); }				//	@return Entity's Spells Vector Size
	//Spell& GetSpell(Spell spell);												//	@return An Entity's Spell
	//size_t GetSpellIndex(Spell spell);											//	@return An Entity's Spell Index

	/////////////////////////////////////////////////////////
	//                       SETTERS                       //
	/////////////////////////////////////////////////////////
	void SetName(const char* name) { this->m_Name = name; }
	void SetUUID(UUID uuid)        { this->m_UUID = uuid; }
	void SetType(EntityType type)  { this->m_Type = type; }
	//--  Statistics  --//
	void SetStatistics(Statistics stats) { this->Stat = stats; }
	//	Health
	void SetMaxHealth(uint32_t health)   { this->Stat.m_MaxHealth = health; }
	void SetHealth(uint32_t health)      { this->Stat.m_CurrentHealth = health; }
	void SetHealRate(float rate)         { this->Stat.m_HealthRechargeRate = rate; }
	//	Mana
	void SetMaxMana(uint32_t mana)       { this->Stat.m_MaxMana = mana; }
	void SetMana(uint32_t mana)          { this->Stat.m_CurrentMana = mana; }
	void SetManaRate(float rate)         { this->Stat.m_ManaRechargeRate = rate; }
	//	Stamina
	void SetMaxStamina(uint32_t stamina) { this->Stat.m_MaxStamina = stamina; }
	void SetStamina(uint32_t stamina)    { this->Stat.m_CurrentStamina = stamina; }
	void SetStaminaRate(float rate)      { this->Stat.m_StaminaRechargeRate = rate; }
	//	Stat
	void SetDefenseStat(float defense) { this->Stat.m_DefenseStat = defense; }
	void SetAttackStat(float attack)   { this->Stat.m_DefenseStat = attack; }
	void SetWalkSpeed(float WalkSpeed) { this->Stat.m_WalkSpeed = WalkSpeed; }
	void SetRunSpeed(float RunSpeed)   { this->Stat.m_RunSpeed = RunSpeed; }

	//--  Abilities  --//
	//	Maneuver
	void AddManeuver(Maneuver maneuver) { this->Ability.m_Maneuvers.push_back(maneuver); }
	void PopManeuver() { this->Ability.m_Maneuvers.pop_back(); }
	//void RemoveManeuver(Maneuver maneuver);
	void RemoveManeuver(size_t index) { this->Ability.m_Maneuvers.erase(this->Ability.m_Maneuvers.begin() + index); }
	//	Attacks
	void AddAttack(Attack attack) { this->Ability.m_Attacks.push_back(attack); }
	void PopAttack() { this->Ability.m_Attacks.pop_back(); }
	//void RemoveAttack(Attack attack);
	void RemoveAttack(size_t index) { this->Ability.m_Attacks.erase(this->Ability.m_Attacks.begin() + index); }
	//	Defenses
	void AddDefense(Defense defense) { this->Ability.m_Defenses.push_back(defense); }
	void PopDefense() { this->Ability.m_Defenses.pop_back(); }
	//void RemoveDefense(Defense defense);
	void RemoveDefense(size_t index) { this->Ability.m_Defenses.erase(this->Ability.m_Defenses.begin() + index); }
	//	Spells
	void AddSpell(Spell spell) { this->Ability.m_Spells.push_back(spell); }
	void PopSpell() { this->Ability.m_Spells.pop_back(); }
	//void RemoveSpell(Spell spell);
	void RemoveSpell(size_t index) { this->Ability.m_Spells.erase(this->Ability.m_Spells.begin() + index); }
protected:
	const char* m_Name = "default";
	UUID m_UUID;
	EntityType m_Type = EntityType::None;

	struct Statistics
	{
		uint32_t m_MaxHealth = 100;
		uint32_t m_CurrentHealth = m_MaxHealth;
		float m_HealthRechargeRate = 0.1f;

		uint32_t m_MaxMana = 100;
		uint32_t m_CurrentMana = m_MaxMana;
		float m_ManaRechargeRate = 0.1f;

		uint32_t m_MaxStamina = 100;
		uint32_t m_CurrentStamina = m_MaxStamina;
		float m_StaminaRechargeRate = 0.1f;

		float m_DefenseStat = 1.0f;
		float m_AttackStat = 1.0f;
		float m_WalkSpeed = 0.1f;
		float m_RunSpeed = 0.2f;

		float m_Height = 180;	//	in centimeters
		float m_Weight = 68;	//	in kilograms
	} Stat;

	struct Abilities
	{
		std::vector<Maneuver> m_Maneuvers;
		std::vector<Attack> m_Attacks;
		std::vector<Defense> m_Defenses;
		std::vector<Spell> m_Spells;
	} Ability;
};

