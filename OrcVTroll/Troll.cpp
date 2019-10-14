/// <summary>
///EMMA CONLON
/// C00238065
/// </summary>

#include "Troll.h"

Troll::Troll()
{
	chooseWeapon();
	chooseSpell();
	chooseShield();
	m_name = "Troll";
}

/// <summary>
/// the trolls equiment 
/// </summary>
/// <param name="t_startingWep">the  weapon</param>
/// <param name="t_startingSpell">trolls  spelltype</param>
/// <param name="t_startingShield">the sheild type</param>
Troll::Troll(Character::WeaponChoice t_startingWep, Character::SpellChoice t_startingSpell, Character::ShieldChoice t_startingShield)
{
	m_chosenWep = t_startingWep;
	m_chosenSpell = t_startingSpell;
	m_chosenShield = t_startingShield;
	m_name = "Troll";
}

Troll::~Troll() // unused
{
	//troll is the AI 
	//to prevent errors 
}

/// <summary>
/// Randomly choose a weapon for the AI
/// </summary>
void Troll::chooseWeapon()
{
	int randomWep = rand() % 6 + 1; // 1 -> 7
	m_chosenWep = static_cast<WeaponChoice>(randomWep);
	m_turn = m_weaponPriorities[randomWep];
}

/// <summary>
/// Randomly choose a spell for the AI
/// </summary>
void Troll::chooseSpell()
{
	int randomSpell = rand() % 4 + 1; // 1 -> 5
	m_chosenSpell = static_cast<SpellChoice>(randomSpell);
}

/// <summary>
/// Randomly choose a shield for the AI
/// </summary>
void Troll::chooseShield()
{
	int randomShield = rand() % 2 + 1; // 1 -> 3
	m_chosenShield = static_cast<ShieldChoice>(randomShield);
}

void Troll::decreaseShieldDuration()
{
	if (m_shieldActive) // take away from the duration while the shield is active
		m_shieldDuration--;

	if (m_shieldDuration <= 0 && m_shieldActive) // once the shield's duration is up,
	{
		m_shieldActive = false; // the shield is no longer active
		std::cout << "Sheild had ran out sorry " << std::endl << std::endl;
	}
}

/// <summary>
/// Randomly decide if the shield will be used this action.
/// </summary>
bool Troll::useShield()
{
	bool shieldActivated = false;

	if (!m_shieldUsed) // make sure the shield hasn't already been used
	{
		int chance = 0;

		chance = rand() % 10 + 1;

		if (chance > 5 && !m_shieldActive) // 50% chance of deciding to activate shield
		{								   // make sure shield is not active before activating it
			m_shieldActive = true;
			m_shieldUsed = true;
			shieldActivated = true;
		}
	}

	return shieldActivated;
}

/// <summary>
/// Get the Player's weapon priority to decide turn order
/// </summary>
int Troll::getPriority() const
{
	return m_turn;
}

/// <summary>
/// Randomly pick an action for the AI to perform.
/// 1 -> 10: Use Weapon
/// 11 -> 20: Use Spell
/// 21 -> 30: Use Shield
/// </summary>
void Troll::pickAction()
{
	int chance = 0;//
	bool actionPicked = false;

	if (!m_paralysed)
	{
		while (!actionPicked)
		{
			chance = rand() % 30 + 1;

			if (chance > 0 && chance <= 10)
			{
				// use weapon
				m_usingWeapon = true;
				m_usingSpell = false;
				actionPicked = true;
			}
			else if (chance > 10 && chance <= 20)
			{
				// use spell
				m_usingSpell = true;
				m_usingWeapon = false;
				actionPicked = true;
			}
			else if (chance > 20 && chance <= 30)
			{
				// use shield
				if (useShield()) // returns a bool (true - activated shield, false didnt activate shield
				{
					actionPicked = true;
					m_usingSpell = false;
					m_usingWeapon = false;
				}
			}
		}
	}
	else
	{
		std::cout << "*******************************************" << std::endl;
		std::cout << "troll cannot move skip his turn !" << std::endl;
		std::cout << "*******************************************" << std::endl;
		m_paralysed = false; // now that their turn has been skipped for this round, let them act again next time
	}
	
}

/// <summary>
/// Is the AI using a weapon?
/// </summary>
/// <returns>If the AI is using a weapon</returns>
bool Troll::isUsingWep() const
{
	return m_usingWeapon;
}

/// <summary>
/// Is the AI using a spell?
/// </summary>
/// <returns>If the AI is using a spell</returns>
bool Troll::isUsingSpell() const
{
	return m_usingSpell;
}

/// <summary>
/// Calculate damage the AI will take, based on what the Player chose to do
/// </summary>
/// <param name="t_enemyWep">Enemy's weapon type</param>
/// <param name="t_enemySpell">Enemy's chosen spell</param>
/// <returns>Total damage taken</returns>
int Troll::calcDamage(Character::WeaponChoice t_enemyWep, Character::SpellChoice t_enemySpell,
	bool t_usingWeapon, bool t_usingSpell)
{
	int finalDamage = 0; // total damage taken 
	int chance = 0; // decide if effects go through

	if (t_usingWeapon) // if the enemy is using their weapon
	{
		switch (t_enemyWep)
		{
		case WeaponChoice::LANCE:
			finalDamage += m_weaponDamages[WeaponChoice::LANCE];//how much damage taken for that weapon 
			std::cout << "Hit with Lance! Troll takes " << m_weaponDamages[WeaponChoice::LANCE] << " damage!" << std::endl;
			break;
		case WeaponChoice::SWORD:
			finalDamage += m_weaponDamages[WeaponChoice::SWORD];
			std::cout << "Hit with Sword! Troll takes " << m_weaponDamages[WeaponChoice::SWORD] << " damage!" << std::endl;
			break;
		case WeaponChoice::AXE:
			finalDamage += m_weaponDamages[WeaponChoice::AXE];
			std::cout << "Hit with Axe! Troll takes " << m_weaponDamages[WeaponChoice::AXE] << " damage!" << std::endl;
			break;
		case WeaponChoice::HAMMER:
			finalDamage += m_weaponDamages[WeaponChoice::HAMMER];
			std::cout << "Hit with Hammer! Troll takes " << m_weaponDamages[WeaponChoice::HAMMER] << " damage!" << std::endl;
			break;
		case WeaponChoice::FISTS:
			finalDamage += m_weaponDamages[WeaponChoice::FISTS];
			std::cout << "Hit with Fists! Troll takes " << m_weaponDamages[WeaponChoice::FISTS] << " damage!" << std::endl;
			break;
		case WeaponChoice::DAGGER:
			finalDamage += m_weaponDamages[WeaponChoice::DAGGER];
			std::cout << "Hit with Dagger! Troll takes " << m_weaponDamages[WeaponChoice::DAGGER] << " damage!" << std::endl;
			break;
		case WeaponChoice::CROSSBOW:
			finalDamage += m_weaponDamages[WeaponChoice::CROSSBOW];
			std::cout << "Hit with CROSSBOW! Troll takes " << m_weaponDamages[WeaponChoice::CROSSBOW] << " damage!" << std::endl;
			break;
		default:
			std::cout << "error with weapon choice" << std::endl;
			break;
		}
	}

	if (t_usingSpell) // if the enemy is using a spell
	{
		switch (t_enemySpell)
		{
		case SpellChoice::DBREATH:
			if (!m_shieldActive || m_chosenShield != ShieldChoice::FIRE) // if they don't have their shield up
			{														 // or if the shield they chose wasn't fire
				finalDamage += m_spellDamages[SpellChoice::DBREATH];
				std::cout << "Hit with Dragon Breath! Troll took " << m_spellDamages[SpellChoice::DBREATH] << " damage!" << std::endl;
			}
			else // otherwise if it's active and it's the right shield
			{
				std::cout << "Dragon Breath was blocked by Fire Shield!" << std::endl;
			}
			break;
		case SpellChoice::IGNITE:

			if (!m_shieldActive || m_chosenShield != ShieldChoice::FIRE)  // if they don't have their shield up
			{														  // or if the shield they chose wasn't fire
				finalDamage += m_spellDamages[SpellChoice::IGNITE];
				std::cout << "Hit with Ignite! Troll took " << m_spellDamages[SpellChoice::IGNITE] << " damage!" << std::endl;

				if (!m_burning) // if the troll isn't already burning
				{
					chance = rand() % 10 + 1;
					if (chance > 8) // 20% chance to burn
					{
						m_burning = true;
						std::cout << "Ignite has set the Troll on fire!" << std::endl;
					}
				}

			}
			else // otherwise if it's active and it's the right shield
			{
				std::cout << "Ignite was blocked by Fire Shield!" << std::endl;
				m_burning = false;
			}
			break;
		case SpellChoice::FBITE:

			if (!m_shieldActive || m_chosenShield != ShieldChoice::ICE)  // if they don't have their shield up
			{															 // or if the shield they chose wasn't ice
				finalDamage += m_spellDamages[SpellChoice::FBITE];
				std::cout << "Hit with Frost Bite! Troll took " << m_spellDamages[SpellChoice::FBITE] << " damage!" << std::endl;;
			}
			else
			{
				std::cout << "Frost Bite was blocked by Ice Shield!" << std::endl;
			}

			break;
		case SpellChoice::IBEAM:

			if (!m_shieldActive || m_chosenShield != ShieldChoice::ICE)  // if they don't have their shield up
			{														  // or if the shield they chose wasn't ice
				finalDamage += m_spellDamages[SpellChoice::IBEAM];;
				std::cout << "Hit with Ice Beam! Troll took " << m_spellDamages[SpellChoice::IBEAM] << " damage!" << std::endl;

				chance = rand() % 10 + 1;

				if (chance > 5) // 50% chance to freeze
				{
					m_frozen = true;
					std::cout << "Orc was frozen solid! They may go second in the next round!" << std::endl;
				}
			}
			else
			{
				std::cout << "Ice Beam was blocked by Ice Shield!" << std::endl;
				m_frozen = false;
			}
			break;
		case SpellChoice::SBOLT:

			if (!m_shieldActive || m_chosenShield != ShieldChoice::ELEC)  // if they don't have their shield up
			{														  // or if the shield they chose wasn't electric
				finalDamage += m_spellDamages[SpellChoice::SBOLT];
				std::cout << "Hit with Sky Bolt! Troll took " << m_spellDamages[SpellChoice::SBOLT] << " damage!" << std::endl;

				chance = rand() % 10 + 1;

				if (chance > 9) // 10% chance to paralyse
				{
					m_paralysed = true;
					std::cout << "Troll was paralysed! Troll misses their next action!" << std::endl;
				}
			}
			else
			{
				std::cout << "Skybolt was blocked by Electric Shield!" << std::endl;
				m_paralysed = false; // make sure the troll isn't paralysed if the shield is active
			}
			break;
		default:
			std::cout << "Error with shield choice -- may be unassigned, or assigned incorrectly!" << std::endl;
			break;
		}
	}
	
	if (m_burning)
	{
		finalDamage += 2;
		std::cout << "On fire! Troll took 2 damage." << std::endl;
	}

	if (m_frozen)
	{
		m_turn = 0; // if frozen, always go last (unless both players have low priority)
	}

	return finalDamage;
}
