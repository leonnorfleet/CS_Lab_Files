#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <cmath>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir) : GameWorld(assetDir) {}

	~StudentWorld() {}

	virtual int init()
	{
		int oilMin = 2 + getLevel();
		levelOil = std::min(oilMin, 21);

		int goldMin = 5 - getLevel() / 2;
		levelGold = std::max(goldMin, 2);
		fieldGold = levelGold;

		int itemMax = 300 - 10 * getLevel();
		itemLife = std::max(100, itemMax);

		int pMax = 3 - getLevel() / 4;
		ticksToWaitBetweenMoves = std::max(0, pMax);

		remainingWater = 5;
		tSonar = 1;

		m_tman = new TunnelMan(this, 30, 60);
		
		earthGen();
		boulderGen();
		oilGen();
		goldGen();
		m_actors.push_back(new Protester(this, 60, 60));
		
		/*//Distance Calc
		double x1 = m_actors[0]->getX();
		double x2 = m_actors[1]->getX();

		double y1 = m_actors[0]->getY();
		double y2 = m_actors[1]->getY();

		std::cout << sqrt((pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0))) << std::endl;
		*///////
		
		for (int i = 0; i < m_actors.size(); i++) {
			if (m_actors[i]->getID() == TID_BOULDER) {
				cleanBoulders(m_earth, m_actors[i]);
			}
		}
		//std::cout << m_actors.size() << std::endl;

		std::cout << "ADD PROTESTERS\n";
		std::cout << "ADD PROTESTER SQUIRT COLLISIONS\n";
		std::cout << "ADD PROTESTER BOULDER COLLISIONS\n";
		std::cout << "ADD PROTESTER TEMPORARY GOLD COLLISIONS\n";
		
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		tickCount++;
		
		m_tman->doSomething();

		dig_collisionCheck(*m_tman, m_earth);

		for (int i = 0; i < m_actors.size(); i++) {
			m_actors[i]->doSomething();
		}

		
		int goodieRoll = rand() % (getLevel() * 25 + 300);

		if (goodieRoll == 100) {
			int itemRoll = rand() % 5;
			if (itemRoll == 4) {
				if (fieldSonar == 0) {
					bool canSpawn = true;
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							if (m_tman->getX() + i != 0 && m_tman->getY() + j != 60) {
								canSpawn = false;
							}
						}
					}
					if (canSpawn) {
						m_actors.push_back(new Sonar(this, 0, 60, tickCount));
						fieldSonar++;
					}
				}
			}
			else {
				spawn_pool();
			}
		}

		setDisplayText();

		if (m_tman->hp < 1) {
			decLives();
			if (kia) {
				playSound(SOUND_PLAYER_GIVE_UP);
			}
			return GWSTATUS_PLAYER_DIED;
		}

		if (levelOil == 0) {
			return GWSTATUS_FINISHED_LEVEL;
		}

		checkForDead();

		return GWSTATUS_CONTINUE_GAME;
	}

	virtual void cleanUp()
	{
		if (m_tman != nullptr) {
			delete m_tman;
		}

		for (int i = 0; i < 64; i++) {
			for (int j = 0; j < 64; j++) {
				if (m_earth[i][j] != nullptr) {
				delete[] m_earth[i][j];
				}
			}
		}
		
		for (int i = 0; i < m_actors.size(); i++) {
			delete m_actors[i];
			m_actors[i] = nullptr;
		}
		
		m_actors.clear();
		
	}

	void boulderGen();

	void earthGen();

	void oilGen();

	void goldGen();

	void setDisplayText();

	void dig_collisionCheck(TunnelMan& m_tman, Earth* m_earth[64][64]);

	void cleanBoulders(Earth* m_earth[64][64], baseClass*& m_boulder);

	std::vector<baseClass*> getActors();

	void checkForDead();

	TunnelMan* getMan();
	
	bool okDrop(baseClass* m_boulder);

	bool water_collision(baseClass* squirt);

	void spawnSquirt(int spawnX, int spawnY);

	void spawn_tGold(int spawnX, int spawnY);

	void rspawn_gold();

	void spawn_pool();

	int goodie_collision(baseClass* gold);

	void activateSonar();

	bool p_moveCheck(baseClass* prot, baseClass::Direction dir);

	baseClass::Direction p_LoS(baseClass* prot);
	
	int tickCount = 0;

	int ticksToWaitBetweenMoves = 0;

	//player squirt count
	int remainingWater = 0;

	//gold on the field
	int fieldGold = 0;

	//player gold
	int tGold = 0;

	//total amount of oil in the current level
	int levelOil = 0;

	//amount of gold that should be in levels
	int levelGold = 0;

	//lifetime of the sonar on the screen
	int itemLife = 0;

	//sonar on the field
	int fieldSonar = 0;

	//player sonar count
	int tSonar = 0;

	bool kia = false;

private:
	TunnelMan* m_tman = nullptr;
	Earth* m_earth[64][64];
	std::vector<baseClass*> m_actors;
};

#endif // STUDENTWORLD_H_
