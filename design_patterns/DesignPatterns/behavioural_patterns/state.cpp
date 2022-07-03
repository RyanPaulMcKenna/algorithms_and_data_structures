#include <iostream>
#include <string>
class Player;

class State {
protected:
	Player* player;
public:
	State(Player* player) : player{ player } {}
	virtual std::string getClassName() = 0; // For deponstration purposes.
	virtual void clickLock() = 0;
	virtual void clickPlay() = 0;
	virtual void clickNext() = 0;
	virtual void clickPrevious() = 0;
};

class Player {
private:
	State* state;
	void prefixAction() {
		std::cout << "Player: " << std::endl;
	}
public:
	Player() : state{ nullptr } {}
	Player(State* state) : state{ state } {
		prefixAction();
		std::cout << "Inital state: " << state->getClassName() << std::endl;
	}
	void setState(State* state)
	{
		this->state = state;
	}
	void changeState(State* state) {
		std::string oldClassName = this->state->getClassName();
		std::string newClassName = state->getClassName();
		std::cout << "Change state from "
			<< oldClassName << " to "
			<< newClassName << std::endl;
		this->state = state;
	}
	void clickLock() {
		state->clickLock();
	}
	void clickPlay() {
		state->clickPlay();
	}
	void clickNext() {
		state->clickNext();
	}
	void clickPrevious() {
		state->clickPrevious();
	}
	void startPlayback() {
		prefixAction();
		std::cout << "Starting playback" << std::endl;
	}
	void stopPlayback() {
		prefixAction();
		std::cout << "Stopping playback" << std::endl;
	}
	void nextSong() {
		prefixAction();
		std::cout << "Next song" << std::endl;
	}
	void previousSong() {
		prefixAction();
		std::cout << "Previous song" << std::endl;
	}
	void fastForward() {
		prefixAction();
		std::cout << "Fast forwarding" << std::endl;
	}
	void rewind() {
		prefixAction();
		std::cout << "Rewinding" << std::endl;
	}
};

class ReadyState : public State {
private:
	void prefixAction() {
		std::cout << "\nReadyState: ";
	}
public:
	ReadyState(Player* player) : State(player) {}
	std::string getClassName();
	void clickLock();
	void clickPlay();
	void clickNext();
	void clickPrevious();
};
class PlayingState : public State {
private:
	void prefixAction() {
		std::cout << "\nPlayingState: ";
	}
public:
	PlayingState(Player* player) : State(player) {}
	std::string getClassName();
	void clickLock();
	void clickPlay();
	void clickNext();
	void clickPrevious();
};
class LockedState : public State {
private:
	void prefixAction() {
		std::cout << "\nLockedState: ";
	}
public:
	LockedState(Player* player) : State(player) {}
	std::string getClassName();
	void clickLock();
	void clickPlay();
	void clickNext();
	void clickPrevious();
};

// READY STATE 
std::string ReadyState::getClassName() {
	return "ReadyState";
}
void ReadyState::clickLock() {
	prefixAction();
	std::cout << "Click Lock" << std::endl;
	State::player->changeState(new LockedState(player));
}
void ReadyState::clickPlay() {
	prefixAction();
	std::cout << "Click Play" << std::endl;
	State::player->changeState(new PlayingState(player));
}
void ReadyState::clickNext() {
	prefixAction();
	std::cout << "Click Next" << std::endl;
	State::player->nextSong();
}
void ReadyState::clickPrevious() {
	prefixAction();
	std::cout << "Click Previous" << std::endl;
	State::player->previousSong();
}
// -------------

// LockedState
std::string LockedState::getClassName() {
	return "LockedState";
}
void LockedState::clickLock() {
	prefixAction();
	std::cout << "Click Lock" << std::endl;
	std::cout << "...already locked, nothing happens." << std::endl;
}
void LockedState::clickPlay() {
	prefixAction();
	std::cout << "Click Play" << std::endl;
	State::player->changeState(new ReadyState(player));
}
void LockedState::clickNext() {
	prefixAction();
	std::cout << "Click Next" << std::endl;
	State::player->changeState(new ReadyState(player));
}
void LockedState::clickPrevious() {
	prefixAction();
	std::cout << "Click Previous" << std::endl;
	State::player->changeState(new ReadyState(player));
}
// ------------

// PlayingState
std::string PlayingState::getClassName() {
	return "PlayingState";
}
void PlayingState::clickLock() {
	prefixAction();
	std::cout << "Click Lock" << std::endl;
	State::player->changeState(new LockedState(player));
}
void PlayingState::clickPlay() {
	prefixAction();
	std::cout << "Click Play" << std::endl;
	State::player->startPlayback();
}
void PlayingState::clickNext() {
	prefixAction();
	std::cout << "Click Next" << std::endl;
	State::player->changeState(new ReadyState(player));
}
void PlayingState::clickPrevious() {
	prefixAction();
	std::cout << "Click Previous" << std::endl;
	State::player->changeState(new ReadyState(player));
}
// ---------

int main() {
	Player* player = new Player();
	State* state = new LockedState(player);
	player->setState(state);
	player->clickLock();
	player->clickPlay();
	player->clickPlay();
	player->clickPlay();
}