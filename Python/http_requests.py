# Michael Coughlin
# hiimmichael.com
# 2019

import requests


def main():
    url = 'https://www.wikipedia.org/'
    request = requests.get(url)
    html = request.text
    print html
    
if __name__ == "__main__":
    main()
