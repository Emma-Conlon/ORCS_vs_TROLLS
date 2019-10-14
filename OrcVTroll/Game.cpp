/// <summary>
///EMMA CONLON
/// C00238065
/// </summary>

#include "Game.h"

Game::~Game()
{
	// we won't be using the deconstructor but it must be declared
}

void Game::run()
{
	srand(time(NULL)); // set a random seed

	while (m_currentState != GameState::QUIT)
	{
		update();
		// keep the game running while the player hasn't quit
	}

	std::cout << "Thanks for playing :)" << std::endl;
}

/// <summary>
/// controls the game 
/// </summary>
void Game::update()
{
	// loop gameplay
	std::cout << "*********************************************" << std::endl;
	std::cout << "ORCS VS TROLLS THE GAME\nPRESS ANY OTHER NUMBER TO CONTINUE\nOR PRESS 0 OR LETTER KEY TO END THE GAME\n";
	std::cout << "*********************************************" << std::endl;

	std::cin >> m_quitGame;

	if (m_quitGame == 0)
	{
		m_currentState = GameState::QUIT;
		std::cout << "you battle has ended\n...so your city now belongs to the trolls\n:(" << std::endl;
	}
	else
	{
		m_currentState = GameState::GAMEPLAY;
		
		std::cout << "*********************************************" << std::endl;
		std::cout << "once there was 2 cities an or city and a troll city.\n";
		std::cout << "each city had a grest fighter,\n both of which never met, but niethier the orc fighter or the troll fighter\n had ever lost a battle against an orc or troll.\n";
		std::cout << "************************************************\n";
		std::cout << "you play as the greatest orc fighter ever and always protect youer city\n by never losing a single battle \n";
		std::cout << "one day the trolls attack your city.\n";
		std::cout << "but there is a way to save your city from the trolls by going against the best troll fighter.\n";
		std::cout << "If you beat the greatest Troll fighter, you can easily claim their City. However..\n";
		std::cout << "If you lose your city will be run by the Trolls.\n";
		std::cout << "Good luck.\n";
		std::cout << "*********************************************" << std::endl << std::endl;

		//makes you choose your stuff for the battle 
		m_orc.chooseWeapon();
		m_orc.chooseSpell();
		m_orc.chooseShield();
		//troll chooses his stuff
		m_troll.chooseWeapon();
		m_troll.chooseSpell();
		m_troll.chooseShield();
		std::cout << std::endl << "*********************************************" << std::endl;
		std::cout << "Both you and the greatest fighter of the Trolls both finally meet, and raise your weapons.\n" << std::endl;
		std::cout << "he tells you that he has also never lost a battle.\n";
		std::cout << "you laugh :).\n";

		while (m_currentState == GameState::GAMEPLAY)
		{
			if (m_currentTurn == TurnState::ORC) // if it's the Orc's turn
			{
				m_currentPlayer = &m_orc; //set up name and damage for the Troll
				m_currentDamage = &m_trollDamage;
				m_charTakingDamage = &m_troll;
				// since the Orc will be attacking the Troll

				m_count++; // Increase the turn count (2 turns per round)

				// figure out who's turn it will be for the next loop

				if (m_count >= m_MAX_TURNS)
				{
					m_currentTurn = TurnState::WAITING; // if both players have taken their turns,
														// give the player a chance to look over the results
				}
				else
				{ 
					m_currentTurn = TurnState::TROLL; // otherwise it is the other player's turn
				}
			}
			else if (m_currentTurn == TurnState::TROLL)
			{
				m_currentPlayer = &m_troll;
				m_currentDamage = &m_orcDamage;
				m_charTakingDamage = &m_orc;

				m_count++; // Increase the turn count (2 turns per round)

				// figure out who's turn it will be for the next loop

				if (m_count >= m_MAX_TURNS)
				{
					m_currentTurn = TurnState::WAITING; // if both players have taken their turns,
														// give the player a chance to look over the results
				}
				else
				{
					m_currentTurn = TurnState::ORC; // otherwise it is the other player's turn
				}
			}
			else
			{
				std::cout << "Both turns taken." << std::endl;
				system("Pause");
				m_count = 0;
				m_roundCount++;

				if (m_roundCount < m_MAX_ROUNDS) // as long as there are rounds left, keeping going through turns
				{	
					std::cout << "Deciding next turn: ";

					m_orc.decreaseShieldDuration(); // take away from troll/orc shield duration now that the round is over.
					m_troll.decreaseShieldDuration(); // only doing it now as shield decreases per round, not per turn.

					if (m_orc.getPriority() > m_troll.getPriority()) // if the orc has priority
					{
						m_currentTurn = TurnState::ORC;
						std::cout << "Orc has priority! Orc goes first" << std::endl;
					}
					else if (m_troll.getPriority() > m_orc.getPriority()) // if the troll has priority
					{
						m_currentTurn = TurnState::TROLL;
						std::cout << "Troll has priority! Troll goes first" << std::endl;
					}
					else if (m_orc.getPriority() == m_troll.getPriority()) // if priority is the same
					{ // randomly decide who goes first

						int chance = 0;

						chance = rand() % 10 + 1; // 1 -> 10

						if (chance > 5) // 50% chance
						{
							m_currentTurn = TurnState::ORC;
							std::cout << "Orc goes first" << std::endl;
						}
						else
						{
							m_currentTurn = TurnState::TROLL;
							std::cout << "Troll goes first" << std::endl;
						}
					}
				}
				else
				{
					std::cout << "Round over." << std::endl;
					std::cout << "Troll took: " << m_trollDamage << std::endl;
					std::cout << "Orc(you) took: " << m_orcDamage << std::endl << std::endl;
					if (m_trollDamage > m_orcDamage)
					{
						std::cout << "Troll took more damage. Orc wins!" << std::endl;
						std::cout << "your city is saved and has expanded as you now own the troll city!!!" << std::endl;
					} else if (m_orcDamage > m_trollDamage)
					{
						std::cout << "Orc took more damage. Troll wins!" << std::endl;
						std::cout << "your city is now run by trolls and you are off to the work camp!!!!" << std::endl;
					}
					else
					{
						std::cout << "Both Players took the same damage. It's a Tie!" << std::endl;
					}
					system("Pause");
					m_currentState = GameState::QUIT; // we're done, so we break out of the loop
				}
			}

			if (m_count != 0)
			{ // turn count always gets increased by 1 when a turn is decided,
			  // when it isnt your turn you dont get any scores
				m_currentName = m_currentPlayer->getName();
				m_currentPlayer->pickAction();
				*m_currentDamage += m_charTakingDamage->calcDamage(m_currentPlayer->getWeapon(),
					m_currentPlayer->getSpell(),
					m_currentPlayer->isUsingWep(),
					m_currentPlayer->isUsingSpell());

				std::cout << m_charTakingDamage->getName() << " has taken " << *m_currentDamage
					<< " damage total from the " << m_currentName << std::endl << std::endl;
			}
			
		}
	}
}