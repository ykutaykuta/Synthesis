class SingletonMeta(type):
    __instances = {}

    def __call__(cls, *args, **kwargs):
        if cls not in SingletonMeta.__instances:
            SingletonMeta.__instances[cls] = super(SingletonMeta, cls).__call__(*args, **kwargs)
        return SingletonMeta.__instances[cls]


class Singleton(metaclass=SingletonMeta):
    def __init__(self, value):
        self.data = value


if __name__ == "__main__":
    a = Singleton(1)
    b = Singleton(2)
    print(a is b, a.data, b.data)
