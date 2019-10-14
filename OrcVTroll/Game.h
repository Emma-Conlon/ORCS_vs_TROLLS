/// <summary>
///EMMA CONLON
/// C00238065
/// </summary>

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "Character.h"
#include "Troll.h"
#include "Orc.h"
#include <time.h>   // allows use of time() function

struct Game
{
public:
	Game() = default;
	~Game();
	/// <summary>
	/// Main method for game
	/// </summary>
	void run(); // starts the game

	const int m_MAX_TURNS = 2;
	const int m_MAX_ROUNDS = 4;//the amount of times you will battle

private:
	void update();

	enum GameState { MENU, GAMEPLAY, QUIT };
	enum TurnState{TROLL, ORC, WAITING};
	GameState m_currentState{ MENU };
	TurnState m_currentTurn{ ORC };

	int m_quitGame = 0;

	int m_trollDamage = 0;
	int m_orcDamage = 0;

	Troll m_troll{ Character::WeaponChoice::SWORD, Character::SpellChoice::DBREATH, Character::ShieldChoice::ICE };
	// make the troll start with a sword, dragon breath and ice shield

	Orc m_orc;

	int m_count = 0;
	int m_roundCount = 0;

	Character * m_currentPlayer = &m_troll;
	Character* m_charTakingDamage = &m_troll;
	int* m_currentDamage = &m_trollDamage;
	std::string m_currentName = m_currentPlayer->getName();
};

#endif // !GAME_HPP