/*
优化模式
实现<涉及的技术>：

特点<应用逻辑场景和技术限制分析>：
    1、数组的内存访问可以利用cpu的caching特性，速度更快
    2、dirty flag，有更新才进行操作
    3、对象池-同1，最好下标访问

*/

class GameEntity
{
public:
GameEntity(AIComponent* ai,
PhysicsComponent* physics,
RenderComponent* render)
: ai_(ai), physics_(physics), render_(render)
{}

AIComponent* ai() { return ai_; }
PhysicsComponent* physics() { return physics_; }
RenderComponent* render() { return render_; }

private:
AIComponent* ai_;
PhysicsComponent* physics_;
RenderComponent* render_;
};

class AIComponent
{
public:
void update() {  /*Work with and modify state... */ }

private:
    // Goals, mood, etc. ...
};

class PhysicsComponent
{
public:
    void update() {  /*Work with and modify state...*/}

private:
    // Rigid body, velocity, mass, etc. ...
};

class RenderComponent
{
public:
    void render() {  /*Work with and modify state... */}

private:
    // Mesh, textures, shaders, etc. ...
};

/*
while (!gameOver)
{
    // Process AI.
    for (int i = 0; i < numEntities; i++)
    {
        entities[i]->ai()->update();
    }

    // Update physics.
    for (int i = 0; i < numEntities; i++)
    {
        entities[i]->physics()->update();
    }

    // Draw to screen.
    for (int i = 0; i < numEntities; i++)
    {
        entities[i]->render()->render();
    }

    // Other game loop machinery for timing...
}
*/


// 改进后
AIComponent* aiComponents =
new AIComponent[MAX_ENTITIES];
PhysicsComponent* physicsComponents =
new PhysicsComponent[MAX_ENTITIES];
RenderComponent* renderComponents =
new RenderComponent[MAX_ENTITIES];

//这样速度更快
while (!gameOver)
{
    // Process AI.
    for (int i = 0; i < numEntities; i++)
    {
        aiComponents[i].update();
    }

    // Update physics.
    for (int i = 0; i < numEntities; i++)
    {
        physicsComponents[i].update();
    }

    // Draw to screen.
    for (int i = 0; i < numEntities; i++)
    {
        renderComponents[i].render();
    }

    // Other game loop machinery for timing...
}
