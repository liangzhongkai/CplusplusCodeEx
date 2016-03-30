/*
观察者模式
用途：
    UI显示
    成就系统
    观察者系统
Observer：避免耗时操作、跨进程通讯(在另一个线程使用事件队列)
*/

class Observer
{
    friend class Subject;

public:
    Observer()
        : next_(NULL) {}

public:
    virtual ~Observer() {}
    virtual void onNotify(const Entity& entity, Event event) = 0;
    // Other stuff...
private:
    Observer* next_;
};

class Achievements : public Observer
{
public:
    virtual void onNotify(const Entity& entity, Event event)
    {
        switch (event)
        {
        case EVENT_ENTITY_FELL:
            if (entity.isHero() && heroIsOnBridge_)
            {
                unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
            }
            break;

            // Handle other events, and update heroIsOnBridge_...
        }
    }

private:
    void unlock(Achievement achievement)
    {
        // Unlock if not already unlocked...
    }

    bool heroIsOnBridge_;
};


class Subject
{
public:
    Subject()
        : head_(NULL)
    {}

    // Methods...
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notify(const Entity& entity, Event event);
private:
    Observer* head_;
};

void Subject::addObserver(Observer* observer)
{
    observer->next_ = head_;
    head_ = observer;
}

void Subject::removeObserver(Observer* observer)
{
    if (head_ == observer)
    {
        head_ = observer->next_;
        observer->next_ = NULL;
        return;
    }

    Observer* current = head_;
    while (current != NULL)
    {
        if (current->next_ == observer)
        {
            current->next_ = observer->next_;
            observer->next_ = NULL;
            return;
        }

        current = current->next_;
    }
}

void Subject::notify(const Entity& entity, Event event)
{
    Observer* observer = head_;
    while (observer != NULL)
    {
        observer->onNotify(entity, event);
        observer = observer->next_;
    }
}
