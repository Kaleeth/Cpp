class Terrain { 
public:
    Terrain(int movementCost, bool isWater, Texture texture)
        : movementCost_(movementCost), isWater_(isWater), texture_(texture) {}
    int getMovementCost() const { return movementCost_; }
    bool isWater() const { return isWater_; }
    const Texture& getTexture() const { return texture_; }
private:
    int movementCost_;
    bool isWater_;
    Texture texture_;
};
int Terrain::getMovementCost() const {
    return movementCost_;
}
bool Terrain::isWater() const {
    return isWater_;
}

class World { 
public:
    // storing types of terrain directly to limit the complexity of their lifetime
    World() : grassTerrain_(1, false, GRASS_TEXTURE), hillTerrain_(3, false, HILL_TEXTURE), riverTerrain_(2, true, RIVER_TEXTURE) {}
    void generateTerrain();
    const Terrain& World::getTile(int x, int y) const;
private:
    // worth considering hiding construction of different terrains using Factory
    // and constructing on demand if needed first time
    Terrain grassTerrain_;
    Terrain hillTerrain_;
    Terrain riverTerrain_;
    Terrain* tiles_[WIDTH][HEIGHT]; 
    
    // other stuff...
};
void World::generateTerrain() {
    // Fill the ground with grass.
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            // Sprinkle some hills.
            if (random(10) == 0) {
                tiles_[x][y] = &hillTerrain_;
            }
            else {
                tiles_[x][y] = &grassTerrain_;
            }
        }
    }
    // Lay a river.
    int x = random(WIDTH);
    for (int y = 0; y < HEIGHT; y++) {
        tiles_[x][y] = &riverTerrain_;
    }
}
const Terrain& World::getTile(int x, int y) const {
    return *tiles_[x][y];
}

int main() {
    World world;
    // ... //
    int cost = world.getTile(2, 3).getMovementCost();
}