

/*
�ֽ���ģʽ
    Դ�ڽ�����ģʽ
ʵ��<�漰�ļ���>��
    1��
�ص�<Ӧ���߼������ͼ������Ʒ���>��
    �Զ����ֽ��룬��������������ɻ�����
    ���˼·��1���ֽ�����������ʶ�ջ�����ַ�񣺻���ջ  &  ���ڼĴ���
              2��Ӧ������Щָ��
              3������ֵ�ı�ʾ��ʽ��union
              4����������ֽ��룺�����﷨��ʵ�ַ��������﷨������
*/

/*
������ģʽ
class Expression
{
public:
    virtual ~Expression() {}
    virtual double evaluate() = 0;
};

//����
class NumberExpression : public Expression
{
public:
    NumberExpression(double value)
    : value_(value)
    {}

    virtual double evaluate()
    {
        return value_;
    }

private:
    double value_;
};

//�ӷ�
class AdditionExpression : public Expression
{
public:
    AdditionExpression(Expression* left, Expression* right)
    : left_(left),
    right_(right)
    {}

    virtual double evaluate()
    {
        // Evaluate the operands.
        double left = left_->evaluate();
        double right = right_->evaluate();

        // Add them.
        return left + right;
    }

private:
    Expression* left_;
    Expression* right_;
};

*/



enum Instruction
{
    INST_SET_HEALTH = 0x00,
    INST_SET_WISDOM = 0x01,
    INST_SET_AGILITY = 0x02,
    INST_PLAY_SOUND = 0x03,
    INST_SPAWN_PARTICLES = 0x04
};

class VM1
{
public:
    void interpret(char bytecode[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            char instruction = bytecode[i];
            switch (instruction)
            {
                // Cases for each instruction...
                case INST_SET_HEALTH:
                    setHealth(0, 100);
                    break;

                case INST_SET_WISDOM:
                    setWisdom(0, 100);
                    break;

                case INST_SET_AGILITY:
                    setAgility(0, 100);
                    break;

                case INST_GET_HEALTH:
                {
                    int wizard = pop();
                    push(getHealth(wizard));
                    break;
                }

                case INST_GET_WISDOM:
                case INST_GET_AGILITY:
                    // You get the idea...

                case INST_ADD:
                {
                    int b = pop();
                    int a = pop();
                    push(a + b);
                    break;
                }

                case INST_PLAY_SOUND:
                    playSound(SOUND_BANG);
                    break;

                case INST_SPAWN_PARTICLES:
                    spawnParticles(PARTICLE_FLAME);
                    break;
            }
        }
    }
};

class VM
{
public:
    VM() : stackSize_(0) {}

    // Other stuff...

public:
    void interpret(char bytecode[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            char instruction = bytecode[i];
            switch (instruction)
            {
            case INST_SET_HEALTH:
            {
                int amount = pop();
                int wizard = pop();
                setHealth(wizard, amount);
                break;
            }

            case INST_SET_WISDOM:
            case INST_SET_AGILITY:
                // Same as above...

            case INST_PLAY_SOUND:
                playSound(pop());
                break;

            case INST_SPAWN_PARTICLES:
                spawnParticles(pop());
                break;
            }
        }
    }

private:
    void push(int value)
    {
        // Check for stack overflow.
        assert(stackSize_ < MAX_STACK);
        stack_[stackSize_++] = value;
    }

    int pop()
    {
        // Make sure the stack isn't empty.
        assert(stackSize_ > 0);
        return stack_[--stackSize_];
    }
private:
    static const int MAX_STACK = 128;
    int stackSize_;
    int stack_[MAX_STACK];
};



enum ValueType
{
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING
};

struct Value
{
    ValueType type;
    union
    {
        int    intValue;
        double doubleValue;
        char*  stringValue;
    };
};