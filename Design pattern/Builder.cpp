#include <iostream>
#include <vector>
using namespace std;

class Product
{
public:
    void print_parts() const
    {
        for (size_t i = 0; i < m_parts.size(); i++)
        {
            cout << m_parts[i] << endl;
        }
    }

public:
    vector<string> m_parts;
};

class IBuilder
{
public:
    virtual ~IBuilder() {}
    virtual void produce_part_a() = 0;
    virtual void produce_part_b() = 0;
    virtual void produce_part_c() = 0;
};

class ConcreteBuilder : public IBuilder
{
public:
    ConcreteBuilder() { m_product = new Product(); }
    ~ConcreteBuilder() { delete m_product; }

    void produce_part_a() override { m_product->m_parts.push_back("Part A"); }
    void produce_part_b() override { m_product->m_parts.push_back("Part B"); }
    void produce_part_c() override { m_product->m_parts.push_back("Part C"); }

public:
    Product *m_product;
};

class Director
{
public:
    void set_builder(IBuilder *builder) { m_builder = builder; }
    void build_minimal_featured_product() const
    {
        m_builder->produce_part_a();
    }
    void build_full_featured_product() const
    {
        m_builder->produce_part_a();
        m_builder->produce_part_b();
        m_builder->produce_part_c();
    }

private:
    IBuilder *m_builder;
};

int main()
{
    Director *dir;
    IBuilder *builder;
    Product *product;

    dir = new Director();

    builder = new ConcreteBuilder();
    product = static_cast<ConcreteBuilder*>(builder)->m_product;
    dir->set_builder(builder);
    dir->build_minimal_featured_product();
    product->print_parts();
    cout<<endl;
    delete builder;

    builder = new ConcreteBuilder();
    product = static_cast<ConcreteBuilder*>(builder)->m_product;
    dir->set_builder(builder);
    dir->build_full_featured_product();
    product->print_parts();
    cout<<endl;
    delete builder;

    delete dir;
}