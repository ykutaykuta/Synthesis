#include <iostream>
using namespace std;

class IFuniture
{
public:
    virtual void print_funiture() = 0;
};

class WoodTable : public IFuniture
{
public:
    void print_funiture() override
    {
        cout << typeid(*this).name() << endl;
    }
};

class PlasticTable : public IFuniture
{
public:
    void print_funiture() override
    {
        cout << typeid(*this).name() << endl;
    }
};

class WoodChair : public IFuniture
{
public:
    void print_funiture() override
    {
        cout << typeid(*this).name() << endl;
    }
};

class PlasticChair : public IFuniture
{
public:
    void print_funiture() override
    {
        cout << typeid(*this).name() << endl;
    }
};

class IMaterialFactory
{
public:
    virtual IFuniture* create_chair() = 0;
    virtual IFuniture* create_table() = 0;
};

class WoodFactory : public IMaterialFactory
{
public:
    IFuniture* create_chair() override
    {
        return new WoodChair();
    }
    IFuniture* create_table() override
    {
        return new WoodTable();
    }
};

class PlasticFactory : public IMaterialFactory
{
public:
    IFuniture* create_chair() override
    {
        return new PlasticChair();
    }
    IFuniture* create_table() override
    {
        return new PlasticTable();
    }
};

class Factory
{
public:
    enum MaterialType
    {
        WOOD = 0,
        PLASTIC
    };
    static IMaterialFactory* get_factory(MaterialType type)
    {
        if (type == WOOD)
        {
            return new WoodFactory();
        }
        else if (type == PLASTIC)
        {
            return new PlasticFactory();
        }
        else
        {
            return nullptr;
        }
    }
};

int main()
{
    IMaterialFactory *factory;
    IFuniture *funiture;

    factory = Factory::get_factory(Factory::WOOD);
    funiture = factory->create_chair();
    funiture->print_funiture();
    delete funiture;
    funiture = factory->create_table();
    funiture->print_funiture();
    delete funiture;

    factory = Factory::get_factory(Factory::PLASTIC);
    funiture = factory->create_chair();
    funiture->print_funiture();
    delete funiture;
    funiture = factory->create_table();
    funiture->print_funiture();
    delete funiture;

    delete factory;
}