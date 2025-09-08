#include "StudentWorld.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

void StudentWorld::boulderGen() {

	srand(time(0));
	int paramA = getLevel() / 2 + 2;
	int B = std::min(paramA, 9);

	int coorX, coorY;
	
	for (int i = 0; i < B; i++) {

		coorX = rand() % (59 - 1 + 1) + 1;
		coorY = rand() % (55 - 20 + 1) + 20;

		if (coorX >= 26 && coorX <= 34) {
			while (coorX >= 26 && coorX <= 34) {
				coorX = rand() % (59 - 1 + 1) + 1;
			}
		}

		bool ok = false;

		while (!ok) {
			for (int j = 0; j < m_actors.size(); j++) {
				while (sqrt((pow(m_actors[j]->getX() - coorX, 2.0) + pow(m_actors[j]->getY() - coorY, 2.0))) <= 6) {
					coorX = rand() % (59 - 1 + 1) + 1;
					coorY = rand() % (55 - 20 + 1) + 20;

					if (coorX >= 26 && coorX <= 34) {
						while (coorX >= 26 && coorX <= 34) {
							
							coorX = rand() % (59 - 1 + 1) + 1;
						}
					}
				}
			}

			bool good = true;

			for (int j = 0; j < m_actors.size(); j++) {
				if (sqrt((pow(m_actors[j]->getX() - coorX, 2.0) + pow(m_actors[j]->getY() - coorY, 2.0))) <= 6) {
					good = false;
				}
			}

			if (good) {
				ok = true;
			}
		}
		m_actors.push_back(new Boulder(this, coorX, coorY));
	}
	/*
	for (int j = 0; j < m_actors.size(); j++) {
		for (int k = 0; k < m_actors.size(); k++) {
			double x1 = m_actors[j]->getX();
			double x2 = m_actors[k]->getX();

			double y1 = m_actors[j]->getY();
			double y2 = m_actors[k]->getY();
			if (m_actors[j] == m_actors[k]) {
				std::cout << "myself\n";
			}
			else {
				std::cout << sqrt((pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0))) << std::endl;
			}
		}
		std::cout << std::endl;
	}
	*/
}

void StudentWorld::earthGen() {
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			if ((i < 30 || i > 33) && (j < 60)) {
				m_earth[i][j] = new Earth(i, j);
				m_earth[i][j]->setVisible(true);
			}
			else {
				if (j > 4) {
					m_earth[i][j] = new Earth(i, j);
					m_earth[i][j]->setVisible(false);
				}
				else {
					m_earth[i][j] = new Earth(i, j);
					m_earth[i][j]->setVisible(true);
				}
			}
		}
	}
}

void StudentWorld::oilGen() {
	srand(time(0));

	int coorX, coorY;

	for (int i = 0; i < levelOil; i++) {

		bool ok = false;

		while (!ok) {

			coorX = rand() % (59 - 1 + 1) + 1;
			coorY = rand() % (55 - 1 + 1) + 1;

			if (coorX >= 26 && coorX <= 34) {
				while (coorX >= 26 && coorX <= 34) {
					coorX = rand() % (59 - 1 + 1) + 1;
				}
			}

			for (int j = 0; j < m_actors.size(); j++) {
				while (sqrt((pow(m_actors[j]->getX() - coorX, 2.0) + pow(m_actors[j]->getY() - coorY, 2.0))) <= 6) {
					coorX = rand() % (59 - 1 + 1) + 1;
					coorY = rand() % (55 - 20 + 1) + 20;

					if (coorX >= 26 && coorX <= 34) {
						while (coorX >= 26 && coorX <= 34) {
							coorX = rand() % (59 - 1 + 1) + 1;
						}
					}
				}
			}

			bool good = true;

			for (int j = 0; j < m_actors.size(); j++) {
				if (sqrt((pow(m_actors[j]->getX() - coorX, 2.0) + pow(m_actors[j]->getY() - coorY, 2.0))) <= 6) {
					good = false;
				}
			}

			if (good) {
				ok = true;
			}
		}
		m_actors.push_back(new Barrel(this, coorX, coorY));
	}
}

void StudentWorld::goldGen() {
	srand(time(0));

	int coorX, coorY;

	for (int i = 0; i < levelGold; i++) {

		bool ok = false;

		while (!ok) {

			coorX = rand() % (59 - 1 + 1) + 1;
			coorY = rand() % (55 - 1 + 1) + 1;

			if (coorX >= 26 && coorX <= 34) {
				while (coorX >= 26 && coorX <= 34) {
					coorX = rand() % (59 - 1 + 1) + 1;
				}
			}

			for (int j = 0; j < m_actors.size(); j++) {
				while (sqrt((pow(m_actors[j]->getX() - coorX, 2.0) + pow(m_actors[j]->getY() - coorY, 2.0))) <= 6) {
					coorX = rand() % (59 - 1 + 1) + 1;
					coorY = rand() % (55 - 20 + 1) + 20;

					if (coorX >= 26 && coorX <= 34) {
						while (coorX >= 26 && coorX <= 34) {

							coorX = rand() % (59 - 1 + 1) + 1;
						}
					}
				}
			}

			bool good = true;

			for (int j = 0; j < m_actors.size(); j++) {
				if (sqrt((pow(m_actors[j]->getX() - coorX, 2.0) + pow(m_actors[j]->getY() - coorY, 2.0))) <= 6) {
					good = false;
				}
			}

			if (good) {
				ok = true;
			}
		}
		m_actors.push_back(new Gold(this, coorX, coorY, false, tickCount));
	}
}

void StudentWorld::setDisplayText() {

	string stats = "";

	int level = getLevel();
	int lives = getLives();
	int health = m_tman->hp * 10;
	int wShots = remainingWater;
	int gold = tGold;
	int remainingBarrels = levelOil;
	int sonar = tSonar;
	int score = getScore();

	ostringstream format;
	format.setf(ios::fixed);

	format << setfill('0') << setw(6) << score;

	stats += "Scr: " + format.str() + "  Lvl:  " + to_string(level) + "  Lives: " + to_string(lives) + "  Hlth: " + to_string(health) + "%  Wtr: " +
		to_string(wShots) + "  Gld: " + to_string(gold) + "  Sonar: " + to_string(sonar) + "  Oil Left: " + to_string(remainingBarrels);

	setGameStatText(stats);
	//Scr: 321000 Lvl: 52 Lives: 3 Hlth: 80% Wtr: 20 Gld: 3 Sonar: 1 Oil Left: 2
}

void StudentWorld::dig_collisionCheck(TunnelMan& m_tman, Earth* m_earth[64][64]) { //collision detection between earth and tunnelman
	
	m_tman.dug = false;

	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			if (m_earth[m_tman.getX() + j][m_tman.getY() + k]->isVisible()) {
				m_tman.dug = true;
				m_earth[m_tman.getX() + j][m_tman.getY() + k]->setVisible(false);
				
			}
		}
	}

	if (m_tman.dug) {
		playSound(SOUND_DIG);
	}
}

void StudentWorld::cleanBoulders(Earth* m_earth[64][64], baseClass*& m_boulder) {
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			if (m_earth[m_boulder->getX() + j][m_boulder->getY() + k]->isVisible()) {
				m_earth[m_boulder->getX() + j][m_boulder->getY() + k]->setVisible(false);
			}
		}
	}
}

std::vector<baseClass*> StudentWorld::getActors() {
	return m_actors;
}

TunnelMan* StudentWorld::getMan() {
	return m_tman;
}

bool StudentWorld::okDrop(baseClass* m_boulder) {

	//checks if the 1x4 under the boulder is void of any earth, prompting it is ready to drop/keep dropping

	for (int i = 0; i < m_actors.size(); i++) {
		if (m_actors[i] == m_boulder) {
			bool canWait = true;

			for (int j = 0; j < 4; j++) {
				if (m_earth[m_actors[i]->getX() + j][m_actors[i]->getY() - 1]->isVisible() || m_actors[i]->getY() - 1 < 0) {
					canWait = false;
				}
			}

			for (int j = 0; j < m_actors.size(); j++) {
				if (m_actors[j]->getID() == TID_BOULDER) {
					for (int k = 0; k < 4; k++) {
						if (m_actors[j]->getX() + j == m_actors[i]->getX() + j && m_actors[j]->getY() + 4 == m_actors[i]->getY()) {
							canWait = false;
						}
					}
				}
			}

			return canWait;
		}
	}

	return false;
}

void StudentWorld::checkForDead() {
	//at the beginning of every new tick, this function will check for dead ones, set them visible, and delete them, if any

	for (int i = 0; i < m_actors.size(); i++) {
		if (!m_actors[i]->alive()) {
			m_actors[i]->setVisible(false);
			std::vector<baseClass*>::iterator itr;
			itr = std::find(m_actors.begin(), m_actors.end(), m_actors[i]);

			if (itr != m_actors.end()) {
				m_actors.erase(itr);
			}
		}
	}
}

bool StudentWorld::water_collision(baseClass* squirt) {
	//basic checks for whether or not the hitbox of the squirt overlaps/touches the hitboxes of the designated items(boulder, earth, protester variants
	for (int j = 0; j < 3; j++) {
		for (int k = 0; k < 3; k++) {
			if (m_earth[squirt->getX() + j][squirt->getY() + k]->isVisible()) {
				return true;
			}
		}
	}

	return false;
}

void StudentWorld::spawnSquirt(int spawnX, int spawnY) {
	m_actors.push_back(new Squirt(this, spawnX, spawnY, m_tman->getDirection()));
}

void StudentWorld::spawn_tGold(int x, int y) {
	for (int i = 0; i < m_actors.size(); i++) {
		if (m_actors[i]->getID() == TID_GOLD && m_actors[i]->getX() == x && m_actors[i]->getY() == y) {
			return;
		}
		else {
			m_actors.push_back(new Gold(this, x, y, true, tickCount));
		}
	}
}

void StudentWorld::spawn_pool() {
	srand(time(0));

	int coorX, coorY;
	/*
	for (int k = 0; k < 4; k++) {
		for (int l = 0; l < 4; l++) {
			if (m_earth[coorX + k][coorY + l]->isVisible()) {
				while (m_earth[coorX + k][coorY + l]->isVisible()) {
					coorX = rand() % (59 - 1 + 1) + 1;
					coorY = rand() % (55 - 1 + 1) + 1;
				}
			}
		}
	}
	*/
	bool ok = false;

	while (!ok) {

		coorX = rand() % (59 - 1 + 1) + 1;
		coorY = rand() % (55 - 1 + 1) + 1;

		for (int i = 0; i < m_actors.size(); i++) {
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 4; l++) {
					while (sqrt((pow(m_actors[i]->getX() - coorX, 2.0) + pow(m_actors[i]->getY() - coorY, 2.0))) <= 6 && m_earth[coorX + k][coorY + l]->isVisible()) {
						coorX = rand() % (59 - 1 + 1) + 1;
						coorY = rand() % (55 - 1 + 1) + 1;
					}
				}
			}
		}

		bool good = true;

		for (int i = 0; i < m_actors.size(); i++) {
			if (sqrt((pow(m_actors[i]->getX() - coorX, 2.0) + pow(m_actors[i]->getY() - coorY, 2.0))) <= 6) {
				good = false;
			}
		}

		for (int k = 0; k < 4; k++) {
			for (int l = 0; l < 4; l++) {
				if (m_earth[coorX + k][coorY + l]->isVisible()) {
					good = false;
				}
			}
		}

		if (good) {
			ok = true;
		}
	}

	bool canSpawn = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (m_tman->getX() + i != coorX && m_tman->getY() + j != coorY) {
				canSpawn = false;
			}
		}
	}
	if (canSpawn) {
		m_actors.push_back(new WaterPool(this, coorX, coorY, tickCount));
	}
}
/* //thought gold could respawn in the level
void StudentWorld::rspawn_gold() {
	int coorX, coorY;

	coorX = rand() % (59 - 1 + 1) + 1;
	coorY = rand() % (55 - 1 + 1) + 1;

	if (coorX >= 26 && coorX <= 34) {
		while (coorX >= 26 && coorX <= 34) {
			coorX = rand() % (59 - 1 + 1) + 1;
		}
	}

	bool ok = false;

	while (!ok) {
		for (int j = 0; j < m_actors.size(); j++) {
			while (sqrt((pow(m_actors[j]->getX() - coorX, 2.0) + pow(m_actors[j]->getY() - coorY, 2.0))) <= 6) {
				coorX = rand() % (59 - 1 + 1) + 1;
				coorY = rand() % (55 - 1 + 1) + 1;

				if (coorX >= 26 && coorX <= 34) {
					while (coorX >= 26 && coorX <= 34) {

						coorX = rand() % (59 - 1 + 1) + 1;
					}
				}
			}
		}

		bool good = true;

		for (int j = 0; j < m_actors.size(); j++) {
			if (sqrt((pow(m_actors[j]->getX() - coorX, 2.0) + pow(m_actors[j]->getY() - coorY, 2.0))) <= 6) {
				good = false;
			}
		}

		if (good) {
			ok = true;
		}
	}
		m_actors.push_back(new Gold(this, coorX, coorY, false, tickCount));
}
*/
int StudentWorld::goodie_collision(baseClass* goodie) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			if (!goodie->isVisible()) {
				for (int k = 0; k < 4; k++) {
					for (int l = 0; l < 4; l++) {
						if (m_tman->getX() + i == goodie->getX() + k && m_tman->getY() + j == goodie->getY() + l) {
							return 2;
						}
					}
				}
			}

			if (goodie->alive()) {
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						if (m_tman->getX() + i == goodie->getX() + k && m_tman->getY() + j == goodie->getY() + l) {
							return 1;
						}
					}
				}
			}

		}
	}

	return 3;
}

void StudentWorld::activateSonar() {
	for (int i = 0; i < m_actors.size(); i++) {
		if (sqrt((pow(m_actors[i]->getX() - m_tman->getX(), 2.0) + pow(m_actors[i]->getY() - m_tman->getY(), 2.0))) <= 12) {
			if (!m_actors[i]->isVisible()) {
				m_actors[i]->setVisible(true);
			}
		}
	}
}

bool StudentWorld::p_moveCheck(baseClass* prot, baseClass::Direction dir) {
	switch (dir)
	{
	case baseClass::up://up
		if (prot->getY() + 1 > 60) {
			return false;
		}

		for (int i = 0; i < 4; i++) {
			if (m_earth[prot->getX() + i][prot->getY() + 4]->isVisible()) {
				return false;
			}
		}
		
		return true;
		break;
	case baseClass::down://down
		if (prot->getY() - 1 < 0) {
			return false;
		}

		for (int i = 0; i < 4; i++) {
			if (m_earth[prot->getX() + i][prot->getY() - 1]->isVisible()) {
				return false;
			}
		}

		return true;		
		break;
	case baseClass::left://left
		if (prot->getX() - 1 < 0) {
			return false;
		}

		if (prot->getX() - 1 < 0) {
			return false;
		}

		return true;
		break;
	case baseClass::right://right
		if (prot->getX() + 1 > 60) {
			return false;
		}

		if (prot->getX() + 1 > 60) {
			return false;
		}

		return true;	
		break;
	}

	return false;
}

baseClass::Direction StudentWorld::p_LoS(baseClass* prot) {
	//'raycast' 4 invisible lines starting at protester's x,y and see if it 'touches tunnelman
	/*
	//up raycast
	for (int y = prot->getY(); y < 64; y++) {
		for (int x = prot->getX(); x < prot->getX() + 4; x++) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (x == m_tman->getX() + i && y == m_tman->getY() + j) {
						cout << "tman detected in up region\n";
						return baseClass::up;
					}
				}
			}
		}
	}
	*/
	//down raycast
	for (int y = prot->getY(); y < 64; y++) {
		for (int x = prot->getX(); x < prot->getX() + 4; x++) {

			if (m_earth[x][y]->isVisible()) {
				return baseClass::none;
			}

			if (prot->getX() == m_tman->getX()) {
				if (prot->getX() + 1 == m_tman->getX() + 1) {
					if (prot->getX() + 2 == m_tman->getX() + 2) {
						if (prot->getX() + 3 == m_tman->getX() + 3) {
							cout << "tman detected in down region\n";
							return baseClass::down;
						}
					}
				}
			}
		}
	}
	/*
	//left raycast
	for (int x = prot->getX(); x > 0; x--) {
		for (int y = prot->getY(); y < prot->getY() + 4; y++) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (x == m_tman->getX() + i && y == m_tman->getY() + j) {
						cout << "tman detected in down region\n";
						return true;
					}
				}
			}
		}
	}

	//right raycast
	*/
	cout << "No LoS :(\n";
	
	return baseClass::none;
}