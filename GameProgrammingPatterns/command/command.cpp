class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

void jump(), fireGun(); // we assume the existence of such general functions
class JumpCommand : Command {
public:
    virtual void execute() { jump(); }
};
class FireCommand : public Command { 
public:
    virtual void execute() { fireGun(); }
};
// You get the idea...
class NullCommand : public Command { // Null Object pattern
public:
    virtual void execute() {}
};

class InputHandler {
public:
    void handleInput();
    // Methods to bind controls...

private:
    Command* buttonX_;
    Command* buttonY_;
    Command* buttonA_;
    Command* buttonB_;
    Command* buttonOther_; // eventually not assigned
};

void InputHandler::handleInput() {
    if (isPressed(BUTTON_X)) buttonX_->execute();
    else if (isPressed(BUTTON_Y)) buttonY_->execute();
    else if (isPressed(BUTTON_A)) buttonA_->execute();
    else if (isPressed(BUTTON_B)) buttonB_->execute();
    else if (isPressed(BUTTON_OTHER)) buttonOther_->execute(); 
}