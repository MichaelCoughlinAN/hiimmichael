import os

# Michael Coughlin
# hiimmichael.com
# 2019

timezone = 'CST'
date = '2018-01-17 09:44:00'

os.system('export TZ=' + timezone)
os.system('date -s ' + date)
