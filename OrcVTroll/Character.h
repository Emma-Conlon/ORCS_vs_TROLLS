/// <summary>
///EMMA CONLON
/// C00238065
/// </summary>

#pragma once
#include <iostream>

class Character
{
public:
	Character();
	~Character();

	enum WeaponChoice { NONE, LANCE, SWORD, AXE, HAMMER, FISTS, DAGGER, CROSSBOW };
	int m_weaponDamages[8]{ 0,3,2,5,6,2,3,4 }; // damage for each weapon, first entr yis 0 as its no weapon whatsoever
	enum SpellChoice { NOTHING, DBREATH, IGNITE, FBITE, IBEAM, SBOLT };
	int m_spellDamages[6]{ 0,8,4,6,4,3 }; // damage for each spell, first entry is 0 as its no spell whatsoever
	enum ShieldChoice { NONE_SH, FIRE, ICE, ELEC };
	int m_weaponPriorities[8]{ 0,1,1,0,0,2,2,1 }; // 0 is low priority, 1 is neutral, 2 is high priority

	

protected:

	static int m_weaponDamage;
	static int m_spellDamage;

	bool m_burning = false;
	bool m_frozen = false;
	bool m_paralysed = false;

	std::string m_name;

	WeaponChoice m_chosenWep{ FISTS };
	SpellChoice m_chosenSpell{ IBEAM };
	ShieldChoice m_chosenShield{ ICE };

public:

	virtual int calcDamage(WeaponChoice t_enemyWep, SpellChoice t_enemySpell, 
								   bool t_usingWeapon, bool t_usingSpell) = 0;

	virtual bool isUsingWep() const = 0;
	virtual bool isUsingSpell() const = 0;
	virtual void pickAction() = 0;

	std::string getName() const { return m_name; };
	WeaponChoice getWeapon() const { return m_chosenWep; };
	SpellChoice getSpell() const { return m_chosenSpell; };
	ShieldChoice getShield() const { return m_chosenShield; };
};

