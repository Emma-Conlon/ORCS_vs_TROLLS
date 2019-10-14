/// <summary>
///EMMA CONLON
/// C00238065
/// </summary>

#include "Orc.h"

Orc::Orc()
{
	m_name = "Orc";
}

Orc::Orc(Character::WeaponChoice t_startingWep, Character::SpellChoice t_startingSpell, 
												Character::ShieldChoice t_startingShield)
{
	m_chosenWep = t_startingWep;
	m_chosenSpell = t_startingSpell;
	m_chosenShield = t_startingShield;
	m_name = "Orc";
}

Orc::~Orc() // unused
{
}

/// <summary>
/// Get the player to choose a Weapon
/// </summary>
void Orc::chooseWeapon()
{
	int weaponChoice = 0;

	while (weaponChoice <= 0 || weaponChoice > 7)  // make sure we're inside of range 1 to 7
	{												//  if the user puts in something wrong
		std::cout << "1: Lance\n2: Sword\n3: Axe\n4: Hammer\n5: Fists\n6: Dagger\n7: CROSSBOW\n"
			<< std::endl << "Choose your weapon: ";
		std::cin >> weaponChoice;

		if (weaponChoice > 0 && weaponChoice <= 7) // between 1 and 7
		{
			switch (weaponChoice)
			{
			case 1:
				std::cout << "You chose a Lance" << std::endl << std::endl;
				m_turnPriority = m_weaponPriorities[1];
				break;
			case 2:
				std::cout << "You chose a Sword" << std::endl << std::endl;
				m_turnPriority = m_weaponPriorities[2];
				break;
			case 3:
				std::cout << "You chose an Axe" << std::endl << std::endl;
				m_turnPriority = m_weaponPriorities[3];
				break;
			case 4:
				std::cout << "You chose a Hammer" << std::endl << std::endl;
				m_turnPriority = m_weaponPriorities[4];
				break;
			case 5:
				std::cout << "You chose your Fists" << std::endl << std::endl;
				m_turnPriority = m_weaponPriorities[5];
				break;
			case 6:
				std::cout << "You chose a Dagger" << std::endl << std::endl;
				m_turnPriority = m_weaponPriorities[6];
				break;
			case 7:
				std::cout << "You chose a CROSSBOW" << std::endl << std::endl;
				m_turnPriority = m_weaponPriorities[7];
				break;
			}

			m_chosenWep = static_cast<WeaponChoice>(weaponChoice);
		}
		else
		{
			std::cout << "Incorrect number given. Please choose again:" << std::endl << std::endl;
		}
	}
}

/// <summary>
/// Get the player to choose a Spell
/// </summary>
void Orc::chooseSpell()
{
	int spellChoice = 0;

	while (spellChoice <= 0 || spellChoice > 5) // make sure we're inside of range 1 to 5
	{												//  if the user puts in something wrong
		std::cout << "1: Dragon Breath\n2: Ignite\n3: Frostbite\n4: Ice Beam\n5: Skybolt\n"
			<< std::endl << "Choose your spell: ";
		std::cin >> spellChoice;

		if (spellChoice > 0 && spellChoice <= 5) // between 1 and 5
		{
			switch (spellChoice)
			{
			case 1:
				std::cout << "You chose Dragon Breath" << std::endl << std::endl;
				break;
			case 2:
				std::cout << "You chose Ignite" << std::endl << std::endl;
				break;
			case 3:
				std::cout << "You chose Frostbite" << std::endl << std::endl;
				break;
			case 4:
				std::cout << "You chose Ice Beam" << std::endl << std::endl;
				break;
			case 5:
				std::cout << "You chose Skybolt" << std::endl << std::endl;
				break;
			}

			m_chosenSpell = static_cast<SpellChoice>(spellChoice);
		}
		else
		{
			std::cout << "Incorrect number given. Please choose again:" << std::endl << std::endl;
		}
	}
}

/// <summary>
/// Get the player to choose a Shield
/// </summary>
void Orc::chooseShield()
{
	int shieldChoice = 0;

	while (shieldChoice <= 0 || shieldChoice > 3)   // make sure we're inside of range 1 to 3
	{												//  if the user puts in something wrong
		std::cout << "1: Fire Shield\n2: Ice Shield\n3: Electric Shield\n"
			<< std::endl << "Choose your shield: ";
		std::cin >> shieldChoice;

		if (shieldChoice > 0 && shieldChoice <= 3) // between 1 and 3
		{
			switch (shieldChoice)
			{
			case 1:
				std::cout << "You chose the Fire Shield" << std::endl;
				break;
			case 2:
				std::cout << "You chose the Ice Shield" << std::endl;
				break;
			case 3:
				std::cout << "You chose the Electric Shield" << std::endl;
				break;
			}

			m_chosenShield = static_cast<ShieldChoice>(shieldChoice);
		}
		else
		{
			std::cout << "Incorrect number given. Please choose again:" << std::endl << std::endl;
		}
	}
}

/// <summary>
/// Decrease how long the shield stays active for, once it's activated
/// </summary>
void Orc::decreaseShieldDuration()
{
	if (m_shieldActive) // take away from the duration while the shield is active
		m_shieldDuration--;

	if (m_shieldDuration <= 0 && m_shieldActive) // once the shield's duration is up,
	{
		m_shieldActive = false; // the shield is no longer active
		std::cout << "Shield ran out!" << std::endl << std::endl;
	}
}

/// <summary>
/// Let the Orc use a Shield (if available)
/// </summary>
/// <returns>If the shield was used, returns true</returns>
bool Orc::useShield()
{
	bool shieldActivated = false;

	if (!m_shieldUsed) // make sure the shield hasn't already been used
	{
		m_shieldActive = true;
		m_shieldUsed = true;
		std::cout << "Shield used!" << std::endl << std::endl;
		shieldActivated = true;
	}
	else if (m_shieldActive && m_shieldUsed)
	{
		std::cout << "Shield already used and currently active!" << std::endl << std::endl;
	} 
	else if (!m_shieldActive && m_shieldUsed)
	{
		std::cout << "Shield is out of uses!" << std::endl << std::endl;
	}

	return shieldActivated;
}

/// <summary>
/// Let the Orc use a spell (if needed)
/// </summary>
/// <returns>If the spell was used</returns>
bool Orc::useSpell()
{
	bool spellUsed = false;

	if (m_spellsLeft > 0) // only use spells if a spell is left to use
	{
		spellUsed = true;
		m_spellsLeft--; // take away a spell use now that one is being used
	}
	else
	{
		std::cout << "You are out of spell uses!" << std::endl << std::endl;
	}

	return spellUsed;
}

/// <summary>
/// Get the Player's weapon priority to decide turn order
/// </summary>
/// <returns></returns>
int Orc::getPriority() const
{
	return m_turnPriority;
}

/// <summary>
/// Get the Player to choose an action for the Orc
/// </summary>
void Orc::pickAction()
{
	int chosenAction = 0;
	bool hasChosen = false;

	if (!m_paralysed) // only let the player choose an action if they're not paralysed!
	{
		while (chosenAction <= 0 || chosenAction > 3 && !hasChosen)
		{
			std::cout << "1: Use Weapon\n2: Use Spell\n3: Use Shield (lasts this round only!)" << std::endl;
			std::cout << "Please choose an action: ";
			std::cin >> chosenAction;
			std::cout << std::endl;

			if (chosenAction == 1) // use weapon
			{
				m_usingWeapon = true;
				m_usingSpell = false;
				hasChosen = true;
			}
			else if (chosenAction == 2) // use spell
			{
				if (useSpell())
				{
					hasChosen = true;
					m_usingWeapon = false;
					m_usingSpell = true;
				}
				else
				{
					hasChosen = false;
					chosenAction = 0;
				}
			}
			else if (chosenAction == 3) // use shield
			{
				if (useShield())
				{
					hasChosen = true;
					m_usingWeapon = false;
					m_usingSpell = false;
				}
				else
				{
					hasChosen = false;
					chosenAction = 0;
				}
			}
			else // they choose something that wasn't intended
			{
				std::cout << "Incorrect chosen given! Please choose again." << std::endl << std::endl;
			}
		}
	}
	else
	{
		std::cout << "*******************************************" << std::endl;
		std::cout << "Orc is paralysed! They cannot act this turn!" << std::endl;
		std::cout << "*******************************************" << std::endl;
		m_paralysed = false; // now that their turn has been skipped for this round, let them act again next time
	}
}

/// <summary>
/// Is the Orc using a Weapon to attack?
/// </summary>
/// <returns>Orc is using Wep: True, Orc isn't using Wep: False</returns>
bool Orc::isUsingWep() const
{
	return m_usingWeapon;
}

/// <summary>
/// Is the Orc using a Spell to attack>
/// </summary>
/// <returns>Orc is using Spell: True, Orc isn't using Spell: False</returns>
bool Orc::isUsingSpell() const
{
	return m_usingSpell;
}

/// <summary>
/// Calculate damage the Player will take based on what the AI chose
/// </summary>
/// <param name="t_enemyWep">Enemy's weapon type</param>
/// <param name="t_enemySpell">Enemy's chosen spell</param>
/// <returns>Total damage taken</returns>
int Orc::calculateDamage(Character::WeaponChoice t_enemyWep, Character::SpellChoice t_enemySpell, 
													   bool t_usingWeapon, bool t_usingSpell)
{//only for the WEAPONS 
	int finalDamage = 0; // total damage taken 
	int chance = 0; // decide if effects go through

	if (t_usingWeapon) // if the enemy is using their weapon
	{
		switch (t_enemyWep)
		{
		case WeaponChoice::LANCE:
			finalDamage += m_weaponDamages[WeaponChoice::LANCE];
			std::cout << "Hit with Lance! Orc takes " << m_weaponDamages[WeaponChoice::LANCE] << " damage!" << std::endl;
			break;
		case WeaponChoice::SWORD:
			finalDamage += m_weaponDamages[WeaponChoice::SWORD];
			std::cout << "Hit with Sword! Orc takes " << m_weaponDamages[WeaponChoice::SWORD] << " damage!" << std::endl;
			break;
		case WeaponChoice::AXE:
			finalDamage += m_weaponDamages[WeaponChoice::AXE];
			std::cout << "Hit with Axe! Orc takes " << m_weaponDamages[WeaponChoice::AXE] << " damage!" << std::endl;
			break;
		case WeaponChoice::HAMMER:
			finalDamage += m_weaponDamages[WeaponChoice::HAMMER];
			std::cout << "Hit with Hammer! Orc takes " << m_weaponDamages[WeaponChoice::HAMMER] << " damage!" << std::endl;
			break;
		case WeaponChoice::FISTS:
			finalDamage += m_weaponDamages[WeaponChoice::FISTS];
			std::cout << "Hit with Fists! Orc takes " << m_weaponDamages[WeaponChoice::FISTS] << " damage!" << std::endl;
			break;
		case WeaponChoice::DAGGER:
			finalDamage += m_weaponDamages[WeaponChoice::DAGGER];
			std::cout << "Hit with Dagger! Orc takes " << m_weaponDamages[WeaponChoice::DAGGER] << " damage!" << std::endl;
			break;
		case WeaponChoice::CROSSBOW:
			finalDamage += m_weaponDamages[WeaponChoice::CROSSBOW];
			std::cout << "Hit with CROSSBOW! Orc takes " << m_weaponDamages[WeaponChoice::CROSSBOW] << " damage!" << std::endl;
			break;
		default:
			std::cout << "error with weapon choice" << std::endl;
			break;
		}
	}
	//this is for SPELLS ONLY 
//-------------------------------------------------------------------------------------------------
	if (t_usingSpell) // if the enemy is using a spell
	{
		switch (t_enemySpell)
		{
		case SpellChoice::DBREATH:
			if (!m_shieldActive || m_chosenShield != ShieldChoice::FIRE) // if they don't have their shield up
			{														 // or if the shield they chose wasn't fire
				finalDamage += m_spellDamages[SpellChoice::DBREATH];
				std::cout << "\nHit with Dragon Breath! Orc took " << m_spellDamages[SpellChoice::DBREATH] << " damage!" << std::endl;
			}
			else // otherwise if it's active and it's the right shield
			{
				std::cout << "\nDragon Breath was blocked by Fire Shield!" << std::endl;
			}
			break;
		case SpellChoice::IGNITE:

			if (!m_shieldActive || m_chosenShield != ShieldChoice::FIRE)  // if they don't have their shield up
			{														  // or if the shield they chose wasn't fire
				finalDamage += m_spellDamages[SpellChoice::IGNITE];
				std::cout << "\nHit with Ignite! Orc took " << m_spellDamages[SpellChoice::IGNITE] << " damage!" << std::endl;

				if (!m_burning) // if the orc isn't already burning
				{
					chance = rand() % 10 + 1;
					if (chance > 8) // 20% chance to burn
					{
						m_burning = true;
						std::cout << "\nIgnite has set the Orc on fire!" << std::endl;
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

			if (!m_shieldActive || m_chosenShield != ShieldChoice::ICE)  //if they don't have their shield up
			{
				finalDamage += m_spellDamages[SpellChoice::FBITE];
				std::cout << "Hit with Frost Bite! Orc took " << m_spellDamages[SpellChoice::FBITE] << " damage!" << std::endl;;
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
				std::cout << "Hit with Ice Beam! Orc took " << m_spellDamages[SpellChoice::IBEAM] << " damage!" << std::endl;

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
				std::cout << "Hit with Sky Bolt! Orc took " << m_spellDamages[SpellChoice::SBOLT] << " damage!" << std::endl;

				chance = rand() % 10 + 1;

				if (chance > 9) // 10% chance to paralyse
				{
					m_paralysed = true;
					std::cout << "Orc was paralysed! Orc misses their next action!" << std::endl;
				}
			}
			else
			{
				std::cout << "Skybolt was blocked by Electric Shield!" << std::endl;
				m_paralysed = false; // make sure the orc isn't paralysed if the shield is active
			}
			break;
		default:
			std::cout << "Error with shield choice -- may be unassigned, or assigned incorrectly!" << std::endl;
			break;
		}
	}

	if (m_burning) // if the orc is on fire, burn them
	{
		finalDamage += 2;
		std::cout << "On fire! Orc took 2 damage." << std::endl;
	}

	if (m_frozen)
	{
		m_turnPriority = 0; // if frozen, always go last (unless both players have low priority)
	}

	return finalDamage;
}