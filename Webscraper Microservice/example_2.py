# Michael Coughlin
# hiimmichael.com
# © 2022

import requests  # sudo python3 -m pip install requests
import bs4  # sudo python3 -m pip install bs4
from boto3.session import Session, boto3  # sudo python3 -m pip install boto3
import test_keys


if __name__ == '__main__':
    # Import keys and credentials, in a production setting these should be env variables
    table_name = 'Beer-List'
    access_key_id = test_keys.access_key_id
    secret_access_key = test_keys.secret_access_key

    # Create dynamodb resource and connect to our Beer-List table
    dynamodb = boto3.resource('dynamodb', aws_access_key_id=access_key_id, aws_secret_access_key=secret_access_key, region_name='us-east-1')
    table = dynamodb.Table(table_name)

    # Sets used to return difference between current and past menus
    current_menu = set()
    saved_menu = set()

    # Url to fetch beer list from
    url = 'https://10kbrew.com/menu-board/'

    # Bypass 403 error
    headers = {'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36'}

    # Perform a GET request on url
    result = requests.get(url, headers=headers)

    # Parsing the HTML result from request
    soup = bs4.BeautifulSoup(result.content, 'html.parser')
    s = soup.find('div', class_='bt_bb_row menu_board')
    content = s.find_all('div', class_="bt_bb_menu_item_content")

    # Parse/scrape through HTML content further to retrieve menu item names, prices, and descriptions
    for line in content:
        item_description = line.find('div', class_='bt_bb_menu_item_description').text.strip()
        item_price = line.find('div', class_='bt_bb_menu_item_price').text.strip()
        item_title = line.find('div', class_='bt_bb_menu_item_title').text.strip()

        current_menu.add(item_title)
        response = table.put_item(Item={'name' : item_title, 'price': item_price, 'description': item_description})
        print(response)

    # # Read past beer list which has been saved to memory
    res = table.scan()
    # print ('Scan results from table Beer-List: ')

    for item in res['Items']:
        print(item['name'])
        print(item['price'])
        print(item['description'])

        saved_menu.add(item['name'])

    # Return a set that contains the items that only exist in saved_menu, and not in current_menu:
    # Indicating a beverage has been removed from current the beer list
    print('Beers removed:')
    beers_removed_count = len(saved_menu.difference(current_menu))
    print(beers_removed_count)
    beers_removed = saved_menu.difference(current_menu)
    print(beers_removed)

    # Return a set that contains the items that only exist in current_menu, and not in saved_menu:
    # Indicating a beverage has been added to the current beer list
    print('Beers added:')
    beers_added_count = len(current_menu.difference(saved_menu))
    print(beers_added_count)
    beers_added = current_menu.difference(saved_menu)
    print(beers_added)
