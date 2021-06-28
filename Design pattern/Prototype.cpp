#include <iostream>
#include <map>
using namespace std;

class Prototype
{
public:
    Prototype() {}
    virtual ~Prototype() {}
    virtual Prototype *clone() const = 0;
    void print_data() const { cout << typeid(*this).name() << endl; }
};

class Prototype1 : public Prototype
{
public:
    Prototype1() {}
    Prototype* clone() const override { return new Prototype1(*this); }
};

class Prototype2 : public Prototype
{
public:
    Prototype2() {}
    Prototype* clone() const override { return new Prototype2(*this); }
};

class Factory
{
public:
    enum Type
    {
        PROTOTYPE_1 = 0,
        PROTOTYPE_2,
    };
    Factory()
    {
        m_prototypes.insert(pair<Type, Prototype *>(PROTOTYPE_1, new Prototype1()));
        m_prototypes.insert(pair<Type, Prototype *>(PROTOTYPE_2, new Prototype2()));
    }
    ~Factory()
    {
        delete m_prototypes[PROTOTYPE_1];
        delete m_prototypes[PROTOTYPE_2];
    }
    Prototype* get_prototype(Type type) const
    {
        return m_prototypes.at(type)->clone();
    }

private:
    map<Type, Prototype *> m_prototypes;
};

int main()
{
    Factory *fac = new Factory();
    Prototype *pro_1 = fac->get_prototype(Factory::PROTOTYPE_1);
    pro_1->print_data();
    Prototype *pro_2 = fac->get_prototype(Factory::PROTOTYPE_2);
    pro_2->print_data();
    delete pro_1;
    delete pro_2;
    delete fac;
    return 0;
}
