

/*
状态模式
实现<涉及的技术>：
    1、在不同状态中进行switch
    2、每个状态封装到类，实体有个状态指针*pstate动态指向不同状态类
特点<应用逻辑场景和技术限制分析>：
    处理玩家的不同状态：跳，蹲，站，俯冲。每个状态有不同操作限制
    并发状态机：玩家的状态和武器的状态之间相互限制，可以通过共同维护一个01列表达到相互限制的作用
    层级状态机：一个状态机里，一个操作在多重状态下反应都是一样的，这就代表有代码重复，有重复就可以使用父类做完全部重复工作
    下推状态机：玩家有一个栈保存多个的状态机
*/


/*
FSM    基本做法

enum State
{
    STATE_STANDING,
    STATE_JUMPING,
    STATE_DUCKING,
    STATE_DIVING
};


void Heroine::handleInput(Input input)
{
    switch (state_)
    {
    case STATE_STANDING:
        if (input == PRESS_B)
        {
            state_ = STATE_JUMPING;
            yVelocity_ = JUMP_VELOCITY;
            setGraphics(IMAGE_JUMP);
        }
        else if (input == PRESS_DOWN)
        {
            state_ = STATE_DUCKING;
            chargeTime_ = 0;     //蓄能
            setGraphics(IMAGE_DUCK);
        }
        break;

    case STATE_JUMPING:
        if (input == PRESS_DOWN)
        {
            state_ = STATE_DIVING;
            setGraphics(IMAGE_DIVE);
        }
        break;

    case STATE_DUCKING:
        if (input == RELEASE_DOWN)
        {
            state_ = STATE_STANDING;
            setGraphics(IMAGE_STAND);
        }
        break;
    }
}

void Heroine::update()
{
    if (state_ == STATE_DUCKING)
    {
        chargeTime_++;
        if (chargeTime_ > MAX_CHARGE)
        {
            superBomb();
        }
    }
}

*/

class HeroineState
{
public:
    virtual ~HeroineState() {}
    virtual void handleInput(Heroine& heroine, Input input) {}
    virtual void update(Heroine& heroine) {}
public:
    static DuckingState ducking;   //下面3个同理
    static StandingState standing;
    static JumpingState jumping;
    static DivingState diving;
};

class DuckingState : public HeroineState
{
public:
    DuckingState()
        : chargeTime_(0)
    {}

    virtual void handleInput(Heroine& heroine, Input input) {
        if (input == RELEASE_DOWN)
        {
            // Change to standing state...
            heroine.setGraphics(IMAGE_STAND);
        }
    }

    virtual void update(Heroine& heroine) {
        chargeTime_++;
        if (chargeTime_ > MAX_CHARGE)
        {
            heroine.superBomb();
        }
    }

private:
    int chargeTime_;
};


class Heroine
{
public:
    virtual void handleInput(Input input)
    {
        state_->handleInput(*this, input);
    }

    virtual void update()
    {
        state_->update(*this);
    }

    // Other methods...
private:
    HeroineState* state_;   //指向不同的状态类
};