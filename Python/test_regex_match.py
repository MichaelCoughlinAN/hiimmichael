import re

# Michael Coughlin
# hiimmichael.com
# 2019

regex = re.compile('application-(.*)-name.jar')
l = ['application-4.1.118-name.jar', 'application-4.1.119-name.jar', 'just', 'a', 'test']

matches = [string for string in l if re.search(regex, string)]

if len(matches) > 0:
    print 'There are matches!'
else:
    print 'There are no matches ...'
