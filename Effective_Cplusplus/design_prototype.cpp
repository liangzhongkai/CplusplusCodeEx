/*
原型模式
用途：
    一种基础物件，有多重派生，但是生产类也只需一个，能针对不同类型的物件进行产出
*/

class Monster
{
public:
    virtual ~Monster() {}
    virtual Monster* clone() = 0;

    // Other stuff...
};

class Ghost : public Monster {
public:
    Ghost(int health, int speed)
        : health_(health),
        speed_(speed)
    {}

    virtual Monster* clone()
    {
        return new Ghost(health_, speed_);
    }

private:
    int health_;
    int speed_;
};

class Spawner
{
public:
    virtual ~Spawner() {}
    virtual Monster* spawnMonster() = 0;
};

template <class T>
class SpawnerFor : public Spawner
{
public:
    virtual Monster* spawnMonster() { return new T(); }
};


Spawner* ghostSpawner = new SpawnerFor<Ghost>();
ghostSpawner->spawnMonster();