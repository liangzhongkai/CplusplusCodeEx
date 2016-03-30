

/*
״̬ģʽ
ʵ��<�漰�ļ���>��
    1���ڲ�ͬ״̬�н���switch
    2��ÿ��״̬��װ���࣬ʵ���и�״ָ̬��*pstate��ָ̬��ͬ״̬��
�ص�<Ӧ���߼������ͼ������Ʒ���>��
    ������ҵĲ�ͬ״̬�������ף�վ�����塣ÿ��״̬�в�ͬ��������
    ����״̬������ҵ�״̬��������״̬֮���໥���ƣ�����ͨ����ͬά��һ��01�б�ﵽ�໥���Ƶ�����
    �㼶״̬����һ��״̬���һ�������ڶ���״̬�·�Ӧ����һ���ģ���ʹ����д����ظ������ظ��Ϳ���ʹ�ø�������ȫ���ظ�����
    ����״̬���������һ��ջ��������״̬��
*/


/*
FSM    ��������

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
            chargeTime_ = 0;     //����
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
    static DuckingState ducking;   //����3��ͬ��
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
    HeroineState* state_;   //ָ��ͬ��״̬��
};