#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

enum type{ barrel, gold, squirt, sonar };

class StudentWorld;

class baseClass : public GraphObject //base class
{
public:
	baseClass(StudentWorld* sw, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0)
		: GraphObject(imageID, startX, startY, dir, size, depth) {
		setVisible(true);
		isAlive = true;
		m_sw = sw;
	}

	~baseClass() {
		setVisible(false);
	}

	virtual void doSomething() = 0;

	StudentWorld* getWorld();

	bool alive() const;

	void setDead();

	void annoy(int val);

	int hp;

	int myTick;

protected:
	StudentWorld* m_sw = nullptr;

private:
	bool isAlive;
};

class Earth : public baseClass //earth class
{
public:
	Earth(int x, int y) : baseClass(nullptr, TID_EARTH, x, y, right, 0.25, 3) {}

	~Earth() {}

	virtual void doSomething() {}
};


class TunnelMan : public baseClass //tunnelman class
{
public:
	TunnelMan(StudentWorld* sw, int x, int y) : baseClass(sw, TID_PLAYER, x, y, right, 1.0, 0) {
		dug, touched = false;
		hp = 10;
	}

	~TunnelMan() {}

	virtual void doSomething();

	bool checkDir(int direction);

	void increaseInven(type item);

	bool dug;

	bool touched;
};

class Boulder : public baseClass //boulder class
{
public:
	Boulder(StudentWorld* sw, int x, int y) : baseClass(sw, TID_BOULDER, x, y, down, 1.0, 1) { falling, waiting, fell = false; }

	~Boulder() {}

	virtual void doSomething();

	void wait(bool state) { waiting = true; }
	void fall(bool state) { falling = true; }

private:
	bool falling;
	bool waiting;
	bool fell;
};

class Squirt : public baseClass
{
public:
	Squirt(StudentWorld* sw, int x, int y, Direction dir = down, int distance = 4) : baseClass(sw, TID_WATER_SPURT, x, y, dir, 1.0, 1) {
		initX = x;
		initY = y;
	}

	~Squirt() {}

	virtual void doSomething();

	void movement();

	int initX, initY;
};

class Barrel : public baseClass
{
public:
	Barrel(StudentWorld* sw, int x, int y) : baseClass(sw, TID_BARREL, x, y, right, 1, 2) {
		setVisible(false);
	}

	~Barrel() {}

	virtual void doSomething();
};

class Gold : public baseClass
{
public:
	//false is permanent, true is temporary
	Gold(StudentWorld* sw, int x, int y, bool state, int tick) : baseClass(sw, TID_GOLD, x, y, right, 1, 2) {
		setVisible(state); 
		gState = state;
		myTick = tick;
	}

	~Gold() {}

	virtual void doSomething();

private:
	bool gState;
};

class Sonar : public baseClass
{
public:
	Sonar(StudentWorld* sw, int x, int y, int tick) : baseClass(sw, TID_SONAR, x, y, right, 1, 2) {
		myTick = tick;
	}

	~Sonar() {}

	virtual void doSomething();

private:
};

class WaterPool : public baseClass
{
public:
	WaterPool(StudentWorld* sw, int x, int y, int tick) : baseClass(sw, TID_WATER_POOL, x, y, right, 1, 2) {}

	~WaterPool() {}

	virtual void doSomething();
};

class Protester : public baseClass
{
public:
	Protester(StudentWorld* sw, int x, int y) : baseClass(sw, TID_PROTESTER, x, y, left, 1, 0) {
		numSquaresToMoveInCurrentDirection = rand() % (60 - 8 + 1) + 8;
		resting, leaving, yelled = false;
	}

	~Protester() {}

	virtual void doSomething();

	void newSteps();

private:
	int numSquaresToMoveInCurrentDirection;

	bool resting;

	bool leaving;

	bool yelled;

	int yellTick = 0;
};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
