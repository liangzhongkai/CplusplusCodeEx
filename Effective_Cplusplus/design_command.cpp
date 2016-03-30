
/*
用途：
    逻辑上分离：对于一个命令  玩家<执行名利的对象>有自己的操作，其他AI也有自己的操作，具体的操作要从命令中分离出来
    回放功能：放弃记录每一帧的耗内存方式，采用记录命令执行命令的方式
*/


class GameActor
{
public:
    void jump() {};
};

class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

class JumpCommand : public Command
{
public:
    virtual void execute(GameActor& actor)
    {
        actor.jump();
    }
};


class InputHandler
{
public:
#ifndef NULL
#define NULL (void*)0
#endif
    enum{BUTTON_X = 1, BUTTON_Y, BUTTON_A, BUTTON_B};
public:
    bool isPressed(int button) {};
    Command* handleInput();

    // Methods to bind commands...

private:
    Command* buttonX_;
    Command* buttonY_;
    Command* buttonA_;
    Command* buttonB_;
};

Command* InputHandler::handleInput()
{
    if (isPressed(BUTTON_X)) return buttonX_;
    if (isPressed(BUTTON_Y)) return buttonY_;
    if (isPressed(BUTTON_A)) return buttonA_;
    if (isPressed(BUTTON_B)) return buttonB_;

    // Nothing pressed, so do nothing.
    return (Command*)NULL;
}


int main()
{
    InputHandler inputHandler;
    GameActor actor;
    Command* command = inputHandler.handleInput();
    if (command)
    {
        command->execute(actor);
    }
    return 0;
}