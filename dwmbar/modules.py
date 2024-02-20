from subprocess import CalledProcessError
import psutil
from datetime import datetime
from dwmbar.other import get_command_out


class BarItem:
    def __init__(
        self,
        filled: bool = True
    ) -> None:
        self.filled = bool(filled)
        self.out = ''

    def update(self) -> None:
        pass

    def __str__(self) -> str:
        return self.out

    def __bool__(self) -> bool:
        return self.filled


class TimeItem(BarItem):
    def update(self) -> None:
        # 
        now = datetime.now()
        if now.strftime("%p") == "AM":
            self.out = " "
        else:
            self.out = " "
        self.out += datetime.now().strftime("%I:%M")


class RAMItem(BarItem):
    def __init__(self) -> None:
        """RAM in G"""
        super().__init__(True)
        self.divider = 2**30
        self.total = round(psutil.virtual_memory()[0] / self.divider, 1)

    def update(self) -> None:
        used = round(psutil.virtual_memory()[3] / self.divider, 1)
        self.out = f" {used}G"


class LayoutItem(BarItem):
    def update(self) -> None:
        self.out = ' ' + get_command_out("getlayout").upper()


class CPUUsageItem(BarItem):
    def update(self) -> None:
        usage = psutil.cpu_percent()
        usage = f"{usage}" if usage % 1 else f"{int(usage)}.0"
        self.out = f" {usage:0>4}%"


class DiskUsageItem(BarItem):
    def __init__(self, divider: int = 10**9) -> None:
        super().__init__(True)
        """Disk in GB"""
        self.divider = 10**9
        self.total = round(psutil.disk_usage('/').total / self.divider, 1)

    def update(self) -> None:
        used = round(psutil.disk_usage('/').used / self.divider, 1)
        self.out = F" {used}G/{self.total}G"


class BatteryItem(BarItem):
    def __init__(self, hide_if_full: bool = False) -> None:
        super().__init__(True)
        # self.hide_if_full = hide_if_full

    def update(self) -> None:
        battery = psutil.sensors_battery()
        # plugged = battery.power_plugged
        percent = round(battery.percent)
        # self.out = f" {'#' if plugged else '*'}{percent}%"
        self.out = f" {percent}%"
        # self.filled = False if self.hide_if_full and percent == 100 else True


class VolumeItem(BarItem):
    def update(self) -> None:
        volume = get_command_out(
            "amixer get Master | awk -F'[][]' 'END{ print $4\":\"$2 }'"
        )
        self.out = " " + volume[volume.find(":") + 1:-1]


class MusicItem(BarItem):
    def update(self) -> None:
        try:
            status = get_command_out("cmus-remote -Q")
        except CalledProcessError:
            self.out = " cmus"
            return
        if "file" not in status:
            self.out = " cmus"
            return
        for var in status.split("\n"):
            args = var.split()
            if not args:
                continue
            match args[0]:
                case "status":
                    if args[1] == "playing":
                        self.out = ""
                    else:
                        self.out = ""
                case "file":
                    filename = var[var.rfind("/") + 1:var.rfind(".")]
                    self.out += " " + filename


class InfoItem(BarItem):
    def __init__(self, text: str) -> None:
        super().__init__()
        self.out = text

