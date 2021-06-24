#include <iostream>

class Singleton
{
public:
    static Singleton& get_instance()
    {
        static Singleton instance;
        return instance;
    }

    Singleton(const Singleton &) = delete;
    void operator=(const Singleton &) = delete;

private:
    Singleton() {}

public:
    int data;
};

int main()
{
    Singleton::get_instance().data = 2;
    std::cout << Singleton::get_instance().data;
    return 0;
}