# Michael Coughlin
# hiimmichael.com
# © 2022

import requests  # sudo python3 -m pip install requests
import bs4  # sudo python3 -m pip install bs4
from boto3.session import Session, boto3  # sudo python3 -m pip install bs4
import test_keys
import json

# sudo python3 -m pip install --target . bs4
# sudo python3 -m pip install --target . requests

# if __name__ == '__main__':
def lambda_handler(event, context):
    # Import keys and credentials, in a production setting these should be env variables
    table_name = 'Beer-List'
    number = test_keys.number
    access_key_id = test_keys.access_key_id
    secret_access_key = test_keys.secret_access_key

    # Create a dictionaries to store beer names, prices, and descriptions
    current_beers = dict()
    saved_beers = dict()

    # Sets used to return difference between current and past menus
    current_menu = set()
    saved_menu = set()

    # Url to fetch beer list from
    url = 'https://10kbrew.com/menu-board/'

    # Bypass 403 error
    headers = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36'}

    # Perform a GET request on url
    result = requests.get(url, headers=headers)

    # Parsing the HTML result from request
    soup = bs4.BeautifulSoup(result.content, 'html.parser')
    s = soup.find('div', class_='bt_bb_row menu_board')
    content = s.find_all('div', class_="bt_bb_menu_item_content")

    # print(result)
    # print(content)
    # print(soup.prettify())
    # print(s)
    # print(content)

    # Parse/scrape through HTML content further to retrieve menu item names, prices, and descriptions
    for line in content:
        item_description = line.find('div', class_='bt_bb_menu_item_description').text.strip()
        item_price = line.find('div', class_='bt_bb_menu_item_price').text.strip()
        item_title = line.find('div', class_='bt_bb_menu_item_title').text.strip()

        current_beers[item_title] = [item_price, item_description]
        current_menu.add(item_title)
        # 	  response = table.put_item(Item={'name' : item_title, 'price': item_price, 'description': item_description})
        # 	  print(response)

    # Create dynamodb resource and connect to our Beer-List table
    dynamodb = boto3.resource('dynamodb', aws_access_key_id=access_key_id, aws_secret_access_key=secret_access_key,
                              region_name='us-east-1')
    table = dynamodb.Table(table_name)

    # Read past beer list which has been saved to memory
    res = table.scan()
    print ('Scan results from table Beer-List: ')

    for item in res['Items']:
        print(item['name'])
        print(item['price'])
        print(item['description'])

        saved_beers[item['name']] = [item['price'], item['description']]
        saved_menu.add(item['name'])

    # saved_menu.add('hiimmichael.com IPA')
    # saved_beers['hiimmichael.com IPA'] = ['$10', "Frail Pale Ale"]

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

    # Create a simple message to send via text if menu has changed
    message = "Beer Me Up Scotty! \n\n"
    try:
        # Create AWS SNS client for sending text messages
        client = boto3.client("sns", aws_access_key_id=access_key_id, aws_secret_access_key=secret_access_key,
                              region_name='us-east-1')

        # Create the topic if it doesn't exist (this is idempotent)
        topic = client.create_topic(Name="beerlist")
        topic_arn = topic['TopicArn']  # get its Amazon Resource Name

        # Add SMS Subscribers
        client.subscribe(
            TopicArn=topic_arn,
            Protocol='sms',
            Endpoint=number  # Phone number to send message to
        )

        # Create message if menu has changed
        if beers_removed_count > 0 or beers_added_count > 0:
            # A beer has been removed
            if beers_removed_count > 0:
                message = message + str(beers_removed_count) + ' menu item(s) have been removed: \n\n'
                for beer in beers_removed:
                    this_beer = saved_beers[beer]
                    print(beer + ' ' + this_beer[0] + ' ' + this_beer[1])
                    message = message + beer + ' ' + this_beer[1] + ' ' + this_beer[0] + '\n'

                message = message + '\n'

            # A beer has been added
            if beers_added_count > 0:
                message = message + str(beers_added_count) + ' menu item(s) have been added: \n\n'
                for beer in beers_added:
                    this_beer = current_beers[beer]
                    message = message + beer + ' ' + this_beer[1] + ' ' + this_beer[0] + '\n'
                    print(beer + ' ' + this_beer[0] + ' ' + this_beer[1])

                message = message + '\n'

            message = message + url

            # Delete old beer list
            try:
                flag = False
                scan = table.scan()
                while not flag:
               	    with table.batch_writer() as batch:
               		    for each in scan['Items']:
               			    batch.delete_item(Key={'name': each['name']})
               	    flag = True
            except Exception as e:
            	print (e)

            # Store current beer list
            # key : beer name
            # value[0] : beer price
            # value[1] : beer description
            for key, value in current_beers.items():
            	  print(key)
            	  print(value[0])
            	  print(value[1])
            	  print()
            	  response = table.put_item(Item={'name' : key, 'price': value[0], 'description': value[1]})
            	  print(response)

            # Publish a message.
            client.publish(Message=message, TopicArn=topic_arn)
    except Exception as e:
        print(e)

    return {
        'statusCode': 200,
        'body': json.dumps('Hello from Lambda!')
    }
