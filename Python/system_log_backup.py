# Michael Coughlin
# hiimmichael.com
# 2019

import os
import subprocess
import zipfile
import time
import datetime


def main():
    global zipf

    sleep_time = 3600 # one hour in seconds

    while True:
        now = datetime.datetime.now()
        # It is midnight
        if now.hour == 0:
           pass

        print('Sleeping for ' + str(sleep_time))
        time.sleep(sleep_time)


def clean_up_stale_logs(path):
    print('Removing stale log...')
    os.system('rm -r -f ' + path)


def create_log_zip():
    global zipf
    print('Creating SystemLogs.zip archive on microSD card')
    zipf = zipfile.ZipFile('Logs.zip', 'w', zipfile.ZIP_DEFLATED)
    zipdir('/Logs/')
    zipf.close()


def zipdir(path):
    global zipf

    for root, dirs, files in os.walk(path):
        for file in files:
            print('Adding file ' + str(file) + ' to SystemLogs.zip archive')
            zipf.write(os.path.join(root, file))

            
if __name__ == "__main__":
    main()
