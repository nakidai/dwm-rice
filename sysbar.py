import dwmbar


def main() -> None:
    # kernel_ver = dwmbar.get_command_out("uname -r")[:-1]

    bar = dwmbar.Bar()
    bar[9] = dwmbar.modules.TimeItem()
    bar[8] = dwmbar.modules.RAMItem()
    # bar[7] = dwmbar.modules.DiskUsageItem()
    # bar[6] = dwmbar.modules.CPUUsageItem()
    bar[5] = dwmbar.modules.BatteryItem(True)

    # bar[1] = dwmbar.modules.InfoItem(kernel_ver)
    bar[2] = dwmbar.modules.VolumeItem()
    bar[1] = dwmbar.modules.LayoutItem()
    bar[0] = dwmbar.modules.MusicItem()
    bar.start(1)


if __name__ == '__main__':
    main()
