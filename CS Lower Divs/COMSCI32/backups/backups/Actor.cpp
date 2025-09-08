#include "Actor.h"
#include "StudentWorld.h"

using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

StudentWorld* baseClass::getWorld() {
	return m_sw;
}

bool baseClass::alive() const {
	return isAlive;
}

void baseClass::setDead() {
	isAlive = false;
}

void baseClass::annoy(int val) {
	if (hp - val <= 0) {
		hp = 0;
	}
	else {
		hp -= val;
	}
}



void TunnelMan::doSomething() {
	//switch case using getworld to read input and move accordingly
	//checks for out of bounds movement and performs calls to studentworld to check if there are boulders in the path before moving with checkDir
	if (!alive()) {
		return;
	}

	int ch;

	if (getWorld()->getKey(ch) == true) {
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			if (getDirection() != left) {
				setDirection(left);
			}
			else {
				if (getX() - 1 >= 0) {
					if (checkDir(ch)) {
						moveTo(getX() - 1, getY());
					}
				}
			}
			break;
		case KEY_PRESS_RIGHT:
			if (getDirection() != right) {
				setDirection(right);
			}
			else {
				if (getX() + 1 <= 60) {
					if (checkDir(ch)) {
						moveTo(getX() + 1, getY());
					}
				}
			}
			break;
		case KEY_PRESS_UP:
			if (getDirection() != up) {
				setDirection(up);
			}
			else {
				if (getY() + 1 <= 60) {
					if (checkDir(ch)) {
						moveTo(getX(), getY() + 1);
					}
				}
			}
			break;
		case KEY_PRESS_DOWN:
			if (getDirection() != down) {
				setDirection(down);
			}
			else {
				if (getY() - 1 >= 0) {
					if (checkDir(ch)) {
						moveTo(getX(), getY() - 1);
					}
				}
			}
			break;
		case KEY_PRESS_SPACE:
			if (getWorld()->remainingWater > 0) {
				switch (getDirection())
				{
				case left:
					getWorld()->remainingWater--;
					getWorld()->spawnSquirt(getX() - 3, getY());
					getWorld()->playSound(SOUND_PLAYER_SQUIRT);
					break;
				case right:
					getWorld()->remainingWater--;
					getWorld()->spawnSquirt(getX() + 3, getY());
					getWorld()->playSound(SOUND_PLAYER_SQUIRT);
					break;
				case up:
					getWorld()->remainingWater--;
					getWorld()->spawnSquirt(getX(), getY() + 3);
					getWorld()->playSound(SOUND_PLAYER_SQUIRT);
					break;
				case down:
					getWorld()->remainingWater--;
					getWorld()->spawnSquirt(getX(), getY() - 3);
					getWorld()->playSound(SOUND_PLAYER_SQUIRT);
					break;
				default:
					return;
					break;
				}
			}
			break;
		case KEY_PRESS_ESCAPE:
			hp = 0;
			break;
		case KEY_PRESS_TAB:
			if (getWorld()->tGold > 0) {
				getWorld()->spawn_tGold(getX(), getY());
				getWorld()->tGold--;
			}
			break;
		case 'z':
		case 'Z':
			if (getWorld()->tSonar > 0) {
				getWorld()->activateSonar();
				getWorld()->tSonar--;
				getWorld()->playSound(SOUND_SONAR);
			}
			break;
		default:
			return;
			break;
		}
	}


}

bool TunnelMan::checkDir(int direction) {
	//use getworld to access the vector of actors and search for boulders, then if the boulder's 4x4 will overlap with tunnelman's 4x4 return false
	//otherwise this function clears tunnelman to move in the direction indicated by the key
	bool canMove = true;
	switch (direction) {
	case KEY_PRESS_LEFT:
		for (int i = 0; i < getWorld()->getActors().size(); i++) {
			if (getWorld()->getActors()[i]->getID() == TID_BOULDER && getWorld()->getActors()[i]->isVisible()) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 3; k++) {
						if (getX() == getWorld()->getActors()[i]->getX() + 4 && getY() + j == getWorld()->getActors()[i]->getY() + k) {
							canMove = false;
						}
					}
				}
			}
		}
		return canMove;
		break;
	case KEY_PRESS_RIGHT:
		for (int i = 0; i < getWorld()->getActors().size(); i++) {
			if (getWorld()->getActors()[i]->getID() == TID_BOULDER && getWorld()->getActors()[i]->isVisible()) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 3; k++) {
						if (getX() + 4 == getWorld()->getActors()[i]->getX() && getY() + j == getWorld()->getActors()[i]->getY() + k) {
							canMove = false;
						}
					}
				}
			}
		}
		return canMove;
		break;
	case KEY_PRESS_UP:
		for (int i = 0; i < getWorld()->getActors().size(); i++) {
			if (getWorld()->getActors()[i]->getID() == TID_BOULDER && getWorld()->getActors()[i]->isVisible()) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 3; k++) {
						if (getX() + j == getWorld()->getActors()[i]->getX() + k && getY() + 4 == getWorld()->getActors()[i]->getY()) {
							canMove = false;
						}
					}
				}
			}
		}
		return canMove;
		break;
	case KEY_PRESS_DOWN:
		for (int i = 0; i < getWorld()->getActors().size(); i++) {
			if (getWorld()->getActors()[i]->getID() == TID_BOULDER && getWorld()->getActors()[i]->isVisible()) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 3; k++) {
						if (getX() + j == getWorld()->getActors()[i]->getX() + k && getY() == getWorld()->getActors()[i]->getY() + 4) {
							canMove = false;
						}
					}
				}
			}
		}
		return canMove;
		break;
	default:
		return false;
		break;
	}
}

void TunnelMan::increaseInven(type item) {
	switch (item) {
	case gold:
		getWorld()->tGold++;
		break;
	case sonar:
		getWorld()->tSonar++;
		break;
	case squirt:
		getWorld()->remainingWater += 5;
		break;
	}
}

void Boulder::doSomething() {
	//doSomething boulder call
	//checks if the boulder is alive to make sure behavior cant be looped by a dead boulder
	//calls to the okDrop function which constantly checks if there is a 4x1 'hole' of 'empty' earth that the boulder can fall through
	//directly under it
	//if this ever returns true the boulder immediately enters a waiting state and stores the tick this triggered at in a member int
	//when the incrementing tick counter in student world reaches the stored tick value + 30 the boulder transitions its falling state bool to true
	//when this happens, every tick the boulder checks if its still falling and okDrop still returns true
	//if okDrop returns false, a bool fall is set to false, the boulder is marked as fell, and it is set to dead
	//the next tick after this it is set to invisible
	if (!alive()) {
		return;
	}

	if (getWorld()->okDrop(this) && !waiting && !falling) {
		wait(true);
		myTick = getWorld()->tickCount;

	}

	if (waiting && myTick + 30 == getWorld()->tickCount) {
		getWorld()->playSound(SOUND_FALLING_ROCK);
		wait(false);

		fall(true);
	}

	if (falling) {
		if (getWorld()->okDrop(this)) {
			moveTo(getX(), getY() - 1);

			bool hitTman = false;

			//collision check between tunnelman and boulder, will add protesters later
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {

					for (int l = 0; l < 4; l++) {
						for (int m = 0; m < 4; m++) {
							if (getX() + j == getWorld()->getMan()->getX() + l && getY() + k == getWorld()->getMan()->getY() + m) {
								if (!getWorld()->getMan()->touched) {
									hitTman = true;
									getWorld()->getMan()->touched = true;
								}
							}
						}
					}

					for (int i = 0; i < getWorld()->getActors().size(); i++) {
						if (getWorld()->getActors()[i]->getID() == TID_PROTESTER || getWorld()->getActors()[i]->getID() == TID_HARD_CORE_PROTESTER) {
							//add protester collision here
						}
					}
				}
			}

			if (hitTman) {
				getWorld()->getMan()->setDead();
				getWorld()->getMan()->annoy(getWorld()->getMan()->hp);
				getWorld()->kia = true;
			}
		}
		else {
			fall(false);
			setDead();
			fell = true;
		}
	}
}

void Squirt::doSomething() {
	if (!alive()) {
		return;
	}

	//spawning and collision checks performed in auxillary functions here and in studentworld
	movement();
	for (int i = 0; i < getWorld()->getActors().size(); i++) {
		if (getWorld()->getActors()[i]->getID() == TID_PROTESTER || getWorld()->getActors()[i]->getID() == TID_HARD_CORE_PROTESTER) {

			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {

					for (int l = 0; l < 4; l++) {
						for (int m = 0; m < 4; m++) {
							if (getX() + j == getWorld()->getActors()[i]->getX() + l && getY() + k == getWorld()->getActors()[i]->getY() + m) {
								if (getWorld()->getActors()[i]->alive()) {
									//getWorld()->getActors()[i]->annoy(2);
									setDead();
								}
							}
						}
					}

				}
			}

		}

		//earth collision
		if (getWorld()->water_collision(this)) {
			setDead();
		}

		//boulder collision
		if (getWorld()->getActors()[i]->getID() == TID_BOULDER) {

			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {

					for (int l = 0; l < 3; l++) {
						for (int m = 0; m < 3; m++) {
							if (getX() + j == getWorld()->getActors()[i]->getX() + l && getY() + k == getWorld()->getActors()[i]->getY() + m) {
								setDead();
							}
						}
					}

				}
			}
		}

	}
}

void Squirt::movement() {
	switch (getDirection())
	{
	case left:
		if (getX() == initX - 4) {
			setDead();
		}

		if (getX() - 1 > 0) {
			moveTo(getX() - 1, getY());
		}
		else {
			setDead();
		}
		break;
	case right:
		if (getX() == initX + 4) {
			setDead();
		}

		if (getX() + 1 < 64) {
			moveTo(getX() + 1, getY());
		}
		else {
			setDead();
		}
		break;
	case up:
		if (getY() == initY + 4) {
			setDead();
		}

		if (getY() + 1 < 64) {
			moveTo(getX(), getY() + 1);
		}
		else {
			setDead();
		}
		break;
	case down:
		if (getY() == initY - 4) {
			setDead();
		}

		if (getY() - 1 > 0) {
			moveTo(getX(), getY() - 1);
		}
		else {
			setDead();
		}
		break;
	default:
		return;
		break;
	}
}

void Barrel::doSomething() {
	if (!alive()) {
		return;
	}

	int outcome = getWorld()->goodie_collision(this);

	if (outcome == 1) {
		setDead();
		getWorld()->levelOil--;
		getWorld()->increaseScore(1000);
		getWorld()->playSound(SOUND_FOUND_OIL);
	}
	else if (outcome == 2) {
		setVisible(true);
	}
	
}

void Gold::doSomething() {
	if (!alive()) {
		return;
	}

	if (gState == false) {
		int outcome = getWorld()->goodie_collision(this);

		if (outcome == 1) {
			setDead();
			getWorld()->fieldGold--;
			getWorld()->getMan()->increaseInven(gold);
			getWorld()->increaseScore(10);
			getWorld()->playSound(SOUND_GOT_GOODIE);
		}
		else if (outcome == 2) {
			setVisible(true);
		}
	}
	else {
		//protester interactions here

		if (myTick + 100 == getWorld()->tickCount) {
			setDead();
		}
	}
}

void Sonar::doSomething() {
	if (!alive()) {
		return;
	}

	int outcome = getWorld()->goodie_collision(this);

	if (outcome == 1) {
		setDead();
		getWorld()->fieldSonar--;
		getWorld()->getMan()->increaseInven(sonar);
		getWorld()->increaseScore(75);
		getWorld()->playSound(SOUND_GOT_GOODIE);
	}
	else if (outcome == 2) {
		setVisible(true);
	}

	if (myTick + getWorld()->itemLife == getWorld()->tickCount) {
		setDead();
	}
}

void WaterPool::doSomething() {
	if (!alive()) {
		return;
	}

	int outcome = getWorld()->goodie_collision(this);

	if (outcome == 1) {
		setDead();
		getWorld()->getMan()->increaseInven(squirt);
		getWorld()->increaseScore(100);
		getWorld()->playSound(SOUND_GOT_GOODIE);
	}

	if (myTick + getWorld()->itemLife == getWorld()->tickCount) {
		setDead();
	}
}

void Protester::doSomething() {
	//behavior 1
	if (!alive()) {
		return;
	}

	if (!leaving) {

		if (getWorld()->ticksToWaitBetweenMoves > 0) {
			//behavior 2
			if (resting) {
				if (myTick + getWorld()->ticksToWaitBetweenMoves == getWorld()->tickCount) {
					resting = false;
				}
				else {
					return;
				}
			}
		}

		if (yelled) {
			yellTick++;
		}

		if (yelled && yellTick == 15) {
			yelled = false;
			yellTick = 0;
		}
		/*
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				for (int k = 0; k < 5; k++) {
					for (int l = 0; l < 5; l++) {
						if (getX() + i == getWorld()->getMan()->getX() + k && getY() + j == getWorld()->getMan()->getY() + l) {
							if (!yelled && yellTick == 0) {
								yelled = true;
								cout << "yelled, yell is on cooldown.\n";
							}
							myTick = getWorld()->tickCount;
							resting = true;
							return;
						}
					}
				}
			}
		}
		*/

		//behavior 4
		switch (getDirection()) {
		case up:
			for (int i = 0; i < 4; i++) {
				if (getX() + i == getWorld()->getMan()->getX() && getY() + 4 == getWorld()->getMan()->getY()) {
					if (!yelled && yellTick == 0) {
						getWorld()->playSound(SOUND_PROTESTER_YELL);
						getWorld()->getMan()->annoy(2);
						if (getWorld()->getMan()->hp == 0) {
							getWorld()->kia = true;
						}
						yelled = true;
					}
					myTick = getWorld()->tickCount;
					resting = true;
					return;
				}
			}
			break;
		case down:
			for (int i = 0; i < 4; i++) {
				if (getX() + i == getWorld()->getMan()->getX() && getY() == getWorld()->getMan()->getY()) {
					if (!yelled && yellTick == 0) {
						getWorld()->playSound(SOUND_PROTESTER_YELL);
						getWorld()->getMan()->annoy(2);
						if (getWorld()->getMan()->hp == 0) {
							getWorld()->kia = true;
						}
						yelled = true;
					}
					myTick = getWorld()->tickCount;
					resting = true;
					return;
				}
			}
			break;
		case left:
			for (int i = 0; i < 4; i++) {
				if (getX() == getWorld()->getMan()->getX() + 4 && getY() + i == getWorld()->getMan()->getY()) {
					if (!yelled && yellTick == 0) {
						getWorld()->playSound(SOUND_PROTESTER_YELL);
						getWorld()->getMan()->annoy(2);
						if (getWorld()->getMan()->hp == 0) {
							getWorld()->kia = true;
						}
						yelled = true;
					}
					myTick = getWorld()->tickCount;
					resting = true;
					return;
				}
			}
			break;
		case right:
			for (int i = 0; i < 4; i++) {
				if (getX() + 4 == getWorld()->getMan()->getX() && getY() + i == getWorld()->getMan()->getY()) {
					if (!yelled && yellTick == 0) {
						getWorld()->playSound(SOUND_PROTESTER_YELL);
						getWorld()->getMan()->annoy(2);
						if (getWorld()->getMan()->hp == 0) {
							getWorld()->kia = true;
						}
						yelled = true;
					}
					myTick = getWorld()->tickCount;
					resting = true;
					return;
				}
			}
			break;
		}
		//end behavior 4

		for (int x = getX(); x > 0; x--) {
			for (int y = getY(); y < 4; y++) {
				if (getX() == 1) {
					cout << "end reached";
				}
			}
		}

		//behavior 5
		//add boulder blockage test
		Direction search = getWorld()->p_LoS(this);
		double tDist = sqrt((pow(getWorld()->getMan()->getX() - getX(), 2.0) + pow(getWorld()->getMan()->getY() - getY(), 2.0)));
		if (search != none && tDist > 4) {
			setDirection(search);

			switch (search) {
			case up:
			case down:
				moveTo(getX(), getY() - 1);
				myTick = getWorld()->tickCount;
				//newSteps();
				resting = true;
				return;
			case left:
			case right:
				break;
			}
		}
		else {//end behavior 5
			//behavior 6
			if (numSquaresToMoveInCurrentDirection != 0) {
				switch (getDirection()) {
				case left:
					if (getX() - 1 >= 0) {
						moveTo(getX() - 1, getY());
						numSquaresToMoveInCurrentDirection--;
						myTick = getWorld()->tickCount;
						resting = true;
					}
					else {
						numSquaresToMoveInCurrentDirection = 0;
						myTick = getWorld()->tickCount;
						resting = true;
					}
					break;
				case right:
					if (getX() + 1 <= 60) {
						moveTo(getX() + 1, getY());
						numSquaresToMoveInCurrentDirection--;
						myTick = getWorld()->tickCount;
						resting = true;
					}
					else {
						numSquaresToMoveInCurrentDirection = 0;
						myTick = getWorld()->tickCount;
						resting = true;
					}
					break;
				case up:
					if (getY() + 1 <= 60) {
						moveTo(getX(), getY() + 1);
						numSquaresToMoveInCurrentDirection--;
						myTick = getWorld()->tickCount;
						resting = true;
					}
					else {
						numSquaresToMoveInCurrentDirection = 0;
						myTick = getWorld()->tickCount;
						resting = true;
					}
					break;
				case down:
					if (getY() - 1 >= 0) {
						moveTo(getX(), getY() - 1);
						numSquaresToMoveInCurrentDirection--;
						myTick = getWorld()->tickCount;
						resting = true;
					}
					else {
						numSquaresToMoveInCurrentDirection = 0;
						myTick = getWorld()->tickCount;
						resting = true;
					}
					break;
				}

			}//end behavior 6
			else {//behavior 8 & 9
				int randDir = rand() % (4 - 1 + 1) + 1;

				bool good = false;

				while (!good) {

					bool pass = true;

					switch (randDir) {
					case 1:
						if (!getWorld()->p_moveCheck(this, up)) {
							pass = false;
						}
						break;
					case 2:
						if (!getWorld()->p_moveCheck(this, down)) {
							pass = false;
						}
						break;
					case 3:
						if (!getWorld()->p_moveCheck(this, left)) {
							pass = false;
						}
						break;
					case 4:
						if (!getWorld()->p_moveCheck(this, right)) {
							pass = false;
						}
						break;
					}

					if (pass) {
						good = true;
					}
					else {
						randDir = rand() % (4 - 1 + 1) + 1;
					}
				}

				switch (randDir) {
				case 1:
					setDirection(up);
					break;
				case 2:
					setDirection(down);
					break;
				case 3:
					setDirection(left);
					break;
				case 4:
					setDirection(right);
					break;
				}
				newSteps();
			}
		}//end behavior 8 & 9
	}
	else {
	//behavior 3
	//leaving the oil field behavior
	}
}

void Protester::newSteps() {
	numSquaresToMoveInCurrentDirection = rand() % (60 - 8 + 1) + 8;
}