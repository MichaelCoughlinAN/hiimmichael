# Michael Coughlin
# hiimmichael.com
# 2019

import argparse
import os
import time
import datetime
import psutil

from datetime import timedelta
from pywinauto import timings
from pywinauto.application import Application

# Default settings
window_name = '- Power BI Desktop'
refresh_rate = '60'


def type_keys(string, element):
    for char in string:
        element.type_keys(char)


def load_settings():
    global window_name, refresh_rate
    print('Loading settings:\n')

    filename = 'Python/settings.txt'

    file = open(filename, "r")
    for line in file:
        setting = line.strip(' \n')
        print(setting)

        if 'WindowTitle' in setting:
            window_name = setting.split('=')[1]
        else:
            refresh_rate = setting.split('=')[1]


def main():
    global window_name, refresh_rate

    print('Starting Automatic Refresh Script')

    # Parse arguments from cmd
    parser = argparse.ArgumentParser()
    parser.add_argument("workbook", help="Path to .pbix file")
    parser.add_argument("--workspace", help="name of online Power BI service work space to publish in", default="My workspace")
    parser.add_argument("--refresh-timeout", help="refresh timeout", default=30000)
    parser.add_argument("--no-publish", dest='publish', help="don't publish, just save", default=True, action='store_false')
    parser.add_argument("--init-wait", help="initial wait time on startup", default=15)
    args = parser.parse_args()

    load_settings()

    timings.after_clickinput_wait = 1
    WORKBOOK = args.workbook
    INIT_WAIT = args.init_wait

    # Kill running PBI
    PROCNAME = "PBIDesktop.exe"
    for proc in psutil.process_iter():
        # check whether the process name matches
        if proc.name() == PROCNAME:
            proc.kill()
    time.sleep(3)

    print("\nStarting Power BI")

    os.system('start "" "' + WORKBOOK + '"')
    time.sleep(INIT_WAIT)

    print("Identifying Power BI window")

    app = Application(backend='uia').connect(path=PROCNAME)
    win = app.window(title_re='.*' + window_name)

    time.sleep(5)

    win.wait("enabled", timeout=300)
    win.Save.wait("enabled", timeout=300)
    win.set_focus()
    win.Home.click_input()
    win.Save.wait("enabled", timeout=300)
    win.wait("enabled", timeout=300)

    print('Refreshing ' + window_name + ' every ' + refresh_rate + ' seconds')
    rate = int(refresh_rate)

    while True:
        win.set_focus()
        win.Refresh.click_input()
        win.Refresh.click_input()
        win.Refresh.click_input()

        win.wait("enabled", timeout=300)

        now = datetime.datetime.now()
        now_plus_refresh_rate = now + datetime.timedelta(seconds=rate)
        print('Next refresh will occur on ' + str(now_plus_refresh_rate))

        time.sleep(rate)


if __name__ == '__main__':
    main()
