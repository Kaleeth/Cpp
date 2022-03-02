class HeroineState { 
public:
    virtual ~HeroineState() {}
    virtual void handleInput(Heroine& heroine, Input input) {}
    virtual void update(Heroine& heroine) {}
    virtual void enter(Heroine& heroine) {} // entry action consolidating common behaviour; possible use of exit action as well
    // static states
    static StandingState standing;
    static DuckingState ducking;
};
// Hierarchical state machine superstate with common behaviour
class OnGroundState : public HeroineState { 
public:
    virtual void handleInput(Heroine& heroine, Input input) {
        if (input == PRESS_B) {
            // Jump...
        }
        else if (input == PRESS_DOWN) {
            // Duck...
        }
    }
};

// classes for each state
class StandingState : public OnGroundState {
public:
    virtual void enter(Heroine& heroine) {
        heroine.setGraphics(IMAGE_STAND); // to control 
    }
    // Other code...
};
class DuckingState : public HeroineState { 
public:
    DuckingState() : chargeTime_(0) {}
    void handleInput(Heroine& heroine, Input input) {
        if (input == RELEASE_DOWN) {
            // Stand up...
        }
        else {
            OnGroundState::handleInput(heroine, input);
        }
    }
    // HeroineState* handleInput(Heroine& heroine, Input input) {
    //     if (input == RELEASE_DOWN) {
    //         // Change to standing state...
    //         return new StandingState(); // optional; for non-static states
    //     }
    //     // Other inputs...
    //     return nullptr; // optional; for non-static states
    // }
    void update(Heroine& heroine) {
        chargeTime_++;
        if (chargeTime_ > MAX_CHARGE) {
            heroine.superBomb();
        }
    }
private:
    int chargeTime_;
};

class Heroine { 
public:
    virtual void handleInput(Input input) {
        state_->handleInput(*this, input);
        equipment_->handleInput(*this, input); // concurrent; consider to make only one state machine to consume input
        // Call the enter action on the new state.
        state_->enter(*this);
    }
    virtual void update() {
        state_->update(*this);
        
    }
    // Other methods...
private:
    HeroineState* state_;
    // in case of concurrent state machines
    HeroineState* equipment_;
};

// in case of non-static "stateful" states
void Heroine::handleInput(Input input) {
    HeroineState* state = state_->handleInput(*this, input);
    if (state != nullptr) {
        delete state_;
        state_ = state;
        // Call the enter action on the new state.
        state_->enter(*this);
    }
}