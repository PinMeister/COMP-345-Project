#pragma once

class PlayerStrategy {
	public:
		virtual void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) = 0;
};

class HumanPlayerStrategy : public PlayerStrategy {
	public:
		void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void toDefend(PhaseObserver *phaseObserver);
        void toAttack(PhaseObserver *phaseObserver);
};

class AggressivePlayerStrategy : public PlayerStrategy {
	public:
		void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void toDefend(PhaseObserver *phaseObserver);
        void toAttack(PhaseObserver *phaseObserver);
};

class BenevolentPlayerStrategy : public PlayerStrategy {
	public:
		void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void toDefend(PhaseObserver *phaseObserver);
        void toAttack(PhaseObserver *phaseObserver);
};

class NeutralPlayerStrategy : public PlayerStrategy {
	public:
		void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void toDefend(PhaseObserver *phaseObserver);
        void toAttack(PhaseObserver *phaseObserver);
};
