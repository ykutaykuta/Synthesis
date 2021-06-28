from abc import ABCMeta, abstractmethod
import copy

class Prototype(metaclass=ABCMeta):
    def print_data(self):
        print(type(self).__name__)

class Prototype1(Prototype):
    pass

class Prototype2(Prototype):
    pass

class Factory:
    PROTOTYPE_1 = 1
    PROTOTYPE_2 = 2

    def __init__(self):
        self.m_prototypes = {Factory.PROTOTYPE_1: Prototype1(), Factory.PROTOTYPE_2: Prototype2()}

    def get_prototype(self, t):
        return copy.deepcopy(self.m_prototypes[t])

if __name__ == "__main__":
    fac = Factory()
    print(fac.m_prototypes)
    pro1 = fac.get_prototype(Factory.PROTOTYPE_1)
    print(pro1)
    pro1.print_data()
    pro2 = fac.get_prototype(Factory.PROTOTYPE_2)
    print(pro2)
    pro2.print_data()
