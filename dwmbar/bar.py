from dwmbar.modules import BarItem
import os
from time import sleep, time


class Bar:
    def __init__(
        self,
        items_count: int = 10,
        sep: str = ''
    ) -> None:
        self.sep = sep
        self.items = [BarItem(False) for _ in range(items_count)]

    def start(self, update_time: float = 0) -> None:
        """After call this function program will start infinity loop"""
        while True:
            start = time()
            for i in range(len(self.items)):
                self[i].update()
            self.write()
            finish = time()
            sleep_time = update_time - (finish - start)
            sleep(0 if sleep_time < 0 else sleep_time)

    def __getitem__(
        self,
        key: int
    ) -> BarItem:
        return self.items[key]

    def __setitem__(
        self,
        key: int,
        value: BarItem
    ) -> None:
        self.items[key] = value

    def __len__(self) -> int:
        return len(self.items)

    def write(self, reversed: bool = True) -> None:
        out = ' ' + ''.join(
            [str(self[i]) + ' / ' for i in range(len(self))
             if self[i]
             ]
        )[:-3] + ' '
        os.system(f"xsetroot -name \"{out}\"")
