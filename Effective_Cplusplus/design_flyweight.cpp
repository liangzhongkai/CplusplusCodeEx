
/*
享元模式
用途：
    提取公共数据部分，并在实例里使用指针，减少内存，达到共享作用
    If you find yourself creating an enum and doing lots of switches on it, consider this pattern instead. 
*/



/*
旧做法：
enum Terrain
{
    TERRAIN_GRASS,
    TERRAIN_HILL,
    TERRAIN_RIVER
    // Other terrains...
};

class World
{
    private:
    Terrain tiles_[WIDTH][HEIGHT];
};
int World::getMovementCost(int x, int y)
{
    switch (tiles_[x][y])
    {
        case TERRAIN_GRASS: return 1;
        case TERRAIN_HILL:  return 3;
        case TERRAIN_RIVER: return 2;
        // Other terrains...
    }
}

bool World::isWater(int x, int y)
{
    switch (tiles_[x][y])
    {
        case TERRAIN_GRASS: return false;
        case TERRAIN_HILL:  return false;
        case TERRAIN_RIVER: return true;
        // Other terrains...
    }
}
*/






enum Texture
{
    GRASS_TEXTURE,
    HILL_TEXTURE,
    RIVER_TEXTURE
    // Other terrains...
};

class Terrain
{
public:
    Terrain(int movementCost,
        bool isWater,
        Texture texture)
        : movementCost_(movementCost),
        isWater_(isWater),
        texture_(texture)
    {}

    int getMovementCost() const { return movementCost_; }
    bool isWater() const { return isWater_; }
    const Texture& getTexture() const { return texture_; }

private:
    int movementCost_;
    bool isWater_;
    Texture texture_;
};

class World
{
public:
    World()
        : grassTerrain_(1, false, GRASS_TEXTURE),
        hillTerrain_(3, false, HILL_TEXTURE),
        riverTerrain_(2, true, RIVER_TEXTURE)
    {}
    void generateTerrain();
private:
    Terrain grassTerrain_;
    Terrain hillTerrain_;
    Terrain riverTerrain_;

private:
    Terrain* tiles_[WIDTH][HEIGHT];//指向上面三个：grassTerrain_ hillTerrain_ riverTerrain_
};


void World::generateTerrain()
{
    // Fill the ground with grass.
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            // Sprinkle some hills.
            if (random(10) == 0)
            {
                tiles_[x][y] = &hillTerrain_;
            }
            else
            {
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