import re
regex = re.compile('app-(.*)-name.jar')
l = ['app-4.1.118-name.jar', 'app-4.1.119-name.jar', 'just', 'a', 'test']
matches = [string for string in l if re.search(regex, string)]

if len(matches) > 0:
    print 'There are matches'
else:
    print 'There are no'
