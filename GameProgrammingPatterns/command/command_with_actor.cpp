// allows player input to act on different methods/objects - actors
// more often used to allow usage of different AI 
// or AI controlling player's for demo

class GameActor { public: void jump(); };
class Command {
public:
    virtual ~Command() {}
    virtual void execute(GameActor& actor) = 0;
};

class JumpCommand : Command {
public:
    virtual void execute(GameActor& actor) {
        actor.jump();
    }
};

class InputHandler {
public:
    Command* handleInput();
    // Methods to bind controls...
private:
    Command* buttonX_;
    Command* buttonY_;
    Command* buttonA_;
    Command* buttonB_;
};
Command* InputHandler::handleInput() {
    if (isPressed(BUTTON_X)) buttonX_;
    if (isPressed(BUTTON_Y)) buttonY_;
    if (isPressed(BUTTON_A)) buttonA_;
    if (isPressed(BUTTON_B)) buttonB_;
    return nullptr;
}

int main() {
    GameActor actor;
    //...//
    Command* command = (new InputHandler())->handleInput();
    if (command) {
        command->execute(actor);
    }
}