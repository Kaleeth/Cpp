class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Unit { public: void moveTo(int x, int y); int x(); int y(); };
// alternative solution for player actions -> concrete action
// move command created every time a player wants to move --> needs freeing garbage
class MoveUnitCommand : public Command {
public:
    MoveUnitCommand(Unit* unit, int x, int y) : unit_(unit), xBefore_(0), yBefore_(0), x_(x), y_(y) {};
    virtual void execute() {
        // Remember the unit's position before the move
        // so we can restore it.
        xBefore_ = unit_->x();
        yBefore_ = unit_->y();

        unit_->moveTo(x_, y_);
    }
    virtual void undo() { // redo if undo after undo
        unit_->moveTo(xBefore_, yBefore_);
    }
private:
    Unit* unit_;
    int xBefore_, yBefore_;
    int x_, y_;
};

Command* handleInput() {
    Unit* unit = getSelectedUnit();
    if (isPressed(BUTTON_UP)) {
        // Move the unit up one.
        int destY = unit->y() - 1;
        return new MoveUnitCommand(unit, unit->x(), destY);
    }
    if (isPressed(BUTTON_DOWN)) {
        // Move the unit down one.
        int destY = unit->y() + 1;
        return new MoveUnitCommand(unit, unit->x(), destY);
    }
    // Other moves...
    return nullptr;
} // code executing commands needs to effectively free