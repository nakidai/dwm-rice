import subprocess


def get_command_out(command: str) -> None:
    return subprocess.check_output(
        command,
        shell=True
    ).decode("utf-8")
