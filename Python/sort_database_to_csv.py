# Michael Coughlin
# hiimmichael.com
# 2019

import csv

txt_file = r"tables.txt"
csv_file = r"mycsv.csv"

in_txt = csv.reader(open(txt_file, "rb"), delimiter = '|')
out_csv = csv.writer(open(csv_file, 'wb'))

out_csv.writerows(in_txt)
