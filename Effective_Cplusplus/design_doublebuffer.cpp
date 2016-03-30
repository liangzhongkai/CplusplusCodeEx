

/*
双缓冲模式
实现<涉及的技术>：
    1、类内有两个buffer数据和两个buffer指针，指针指向该数据
特点<应用逻辑场景和技术限制分析>：
    解决对状态同时进行修改和访问的冲突
    电脑屏幕从右下角到左上角的刷新显示
*/

class Framebuffer
{
public:
    Framebuffer() { clear(); }

    void clear()
    {
        for (int i = 0; i < WIDTH * HEIGHT; i++)
        {
            pixels_[i] = WHITE;
        }
    }

    void draw(int x, int y)
    {
        pixels_[(WIDTH * y) + x] = BLACK;
    }

    const char* getPixels()
    {
        return pixels_;
    }

private:
    static const int WIDTH = 160;
    static const int HEIGHT = 120;

    char pixels_[WIDTH * HEIGHT];
};


class Scene
{
public:
    Scene()
        : current_(&buffers_[0]),
        next_(&buffers_[1])
    {}

    void draw()
    {
        next_->clear();

        next_->draw(1, 1);
        // ...
        next_->draw(4, 3);

        swap();
    }

    Framebuffer& getBuffer() { return *current_; }

private:
    void swap()
    {
        // Just switch the pointers.
        Framebuffer* temp = current_;
        current_ = next_;
        next_ = temp;
    }

    Framebuffer  buffers_[2];
    Framebuffer* current_;
    Framebuffer* next_;
};


