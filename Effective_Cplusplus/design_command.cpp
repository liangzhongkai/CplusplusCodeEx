
/*
��;��
    �߼��Ϸ��룺����һ������  ���<ִ�������Ķ���>���Լ��Ĳ���������AIҲ���Լ��Ĳ���������Ĳ���Ҫ�������з������
    �طŹ��ܣ�������¼ÿһ֡�ĺ��ڴ淽ʽ�����ü�¼����ִ������ķ�ʽ
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