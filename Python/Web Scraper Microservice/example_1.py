# Michael Coughlin
# hiimmichael.com
# © 2022

import requests  # sudo python3 -m pip install requests
import bs4  # sudo python3 -m pip install bs4


if __name__ == '__main__':
    # Url to fetch beer list from
    url = 'https://10kbrew.com/menu-board/'

    # Bypass 403 error
    headers = {'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36'}

    # Perform a GET request on url
    result = requests.get(url, headers=headers)

    # print(result.content)

    # Parsing the HTML result from request
    soup = bs4.BeautifulSoup(result.content, 'html.parser')

    # print(soup.prettify())

    s = soup.find('div', class_='bt_bb_row menu_board')

    # print(s)

    content = s.find_all('div', class_="bt_bb_menu_item_content")

    # print(content)

    # Parse/scrape through HTML content further to retrieve menu item names, prices, and descriptions
    for line in content:
        item_description = line.find('div', class_='bt_bb_menu_item_description').text.strip()
        item_price = line.find('div', class_='bt_bb_menu_item_price').text.strip()
        item_title = line.find('div', class_='bt_bb_menu_item_title').text.strip()

        print(item_title)
        print(item_price)
        print(item_description)
