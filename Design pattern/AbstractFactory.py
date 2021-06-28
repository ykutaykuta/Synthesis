from abc import ABCMeta, abstractmethod

class IProduce(metaclass=ABCMeta):
    def print_product(self):
        print(type(self).__name__)

class WoodChair(IProduce):
    pass

class PlasticChair(IProduce):
    pass

class WoodTable(IProduce):
    pass

class PlasticTable(IProduce):
    pass

class MaterialFactory(metaclass=ABCMeta):
    @abstractmethod
    def create_chair(self):
        pass

    @abstractmethod
    def create_table(self):
        pass

class WoodFactory(MaterialFactory):
    def create_chair(self):
        return WoodChair()

    def create_table(self):
        return WoodTable()

class PlasticFactory(MaterialFactory):
    def create_chair(self):
        return PlasticChair()

    def create_table(self):
        return PlasticTable()

class Factory:
    WOOD = 0
    PLASTIC = 1

    @staticmethod
    def get_material_factory(materialType) -> MaterialFactory:
        if materialType == Factory.WOOD:
            return WoodFactory()
        elif materialType == Factory.PLASTIC:
            return PlasticFactory()
        else:
            return None

if __name__ == "__main__":
    factory = Factory.get_material_factory(Factory.WOOD)
    product = factory.create_chair()
    product.print_product()
    product = factory.create_table()
    product.print_product()

    factory = Factory.get_material_factory(Factory.PLASTIC)
    product = factory.create_chair()
    product.print_product()
    product = factory.create_table()
    product.print_product()