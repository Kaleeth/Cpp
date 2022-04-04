
class Unit {
    friend class Grid;

public:
    Unit(Grid* grid, double x, double y)
    : grid_(grid), x_(x), y_(y), prev_(nullptr), next_(nullptr) {
        grid_->add(this);
    }
    
    void move(double x, double y);

private:
    double x_, y_;
    Grid* grid_;
    Unit* prev_, *next_;
};

void move(double x, double y) {
    grid_->move(this, x, y);
}

class Grid {
public:
    Grid() {
        // Clear the grid.
        for (int x = 0; x < NUM_CELLS; x++) {
            for (int y = 0; y < NUM_CELLS; y++) {
               cells_[x][y] = nullptr;
            }
        }
    }
    
    void add(Unit* unit);
    void handleUnit(Unit* unit, Unit* other);
    void handleCell(int x, int y);
    void handleMelee();
    void move(Unit* unit, double x, double y);

    static const int NUM_CELLS = 10;
    static const int CELL_SIZE = 20;
private:
    Unit* cells_[NUM_CELLS][NUM_CELLS];
};

void Grid::add(Unit* unit) {
    // Determine which grid cell it's in.
    int cellX = (int)(unit->x_ / Grid::CELL_SIZE);
    int cellY = (int)(unit->y_ / Grid::CELL_SIZE);

    // Add to the front of list for the cell it's in.
    unit->prev_ = nullptr;
    unit->next_ = cells_[cellX][cellY];
    cells_[cellX][cellY] = unit;

    if (unit->next_ != nullptr) {
        unit->next_->prev_ = unit;
    }
}

void Grid::handleUnit(Unit* unit, Unit* other) {
    while (other != nullptr) {
        if (distance(unit, other) < ATTACK_DISTANCE) {
            handleAttack(unit, other);
        }
        other = other->next_;
    }
}

void Grid::handleCell(int x, int y) {
    Unit* unit = cells_[x][y];
    while (unit != nullptr) {
        // Handle other units in this cell.
        handleUnit(unit, unit->next_);

        // Also try the neighboring cells.
        if (x > 0 && y > 0) handleUnit(unit, cells_[x - 1][y - 1]);
        if (x > 0) handleUnit(unit, cells_[x - 1][y]);
        if (y > 0) handleUnit(unit, cells_[x][y - 1]);
        if (x > 0 && y < NUM_CELLS - 1) handleUnit(unit, cells_[x - 1][y + 1]);

        unit = unit->next_;
    }
}

void Grid::handleMelee() {
    for (int x = 0; x < NUM_CELLS; x++) {
        for (int y = 0; y < NUM_CELLS; y++) {
            handleCell(cells_[x][y]);
        }
    }
}

void Grid::move(Unit* unit, double x, double y) {
    // See which cell it was in.
    int oldCellX = (int)(unit->x_ / Grid::CELL_SIZE);
    int oldCellY = (int)(unit->y_ / Grid::CELL_SIZE);
    
    // See which cell it's moving to.
    int cellX = (int)(x / Grid::CELL_SIZE);
    int cellY = (int)(y / Grid::CELL_SIZE);
    unit->x_ = x;
    unit->y_ = y;
    
    // If it didn't change cells, we're done.
    if (oldCellX == cellX && oldCellY == cellY) return;
    
    // Unlink it from the list of its old cell.
    if (unit->prev_ != nullptr) {
        unit->prev_->next_ = unit->next_;
    }
    if (unit->next_ != nullptr) {
        unit->next_->prev_ = unit->prev_;
    }
    
    // If it's the head of a list, remove it.
    if (cells_[oldCellX][oldCellY] == unit) {
        cells_[oldCellX][oldCellY] = unit->next_;
    }
    
    // Add it back to the grid at its new cell.
    add(unit);
}