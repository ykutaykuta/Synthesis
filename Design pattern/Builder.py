from abc import ABCMeta, abstractmethod

class Product:
    def __init__(self):
        self.m_parts = list()

    def print_parts(self):
        for ele in self.m_parts:
            print(ele)

class IBuilder(metaclass=ABCMeta):
    @abstractmethod
    def produce_part_a(self):
        pass

    @abstractmethod
    def produce_part_b(self):
        pass

    @abstractmethod
    def produce_part_c(self):
        pass

class ConcreteBuilder(IBuilder):
    def __init__(self):
        self.m_produce = Product()

    def produce_part_a(self):
        self.m_produce.m_parts.append("Part A")

    def produce_part_b(self):
        self.m_produce.m_parts.append("Part B")

    def produce_part_c(self):
        self.m_produce.m_parts.append("Part C")

class Director:
    def __init__(self):
        self.m_builder = None

    def build_minimal_featured_product(self):
        self.m_builder.produce_part_a()

    def build_full_featured_product(self):
        self.m_builder.produce_part_a()
        self.m_builder.produce_part_b()
        self.m_builder.produce_part_c()

if __name__ == "__main__":
    director = Director()

    builder = ConcreteBuilder()
    director.m_builder = builder
    director.build_minimal_featured_product()
    product = builder.m_produce
    product.print_parts()
    print("\n")

    builder = ConcreteBuilder()
    director.m_builder = builder
    director.build_full_featured_product()
    product = builder.m_produce
    product.print_parts()
    print("\n")