import datetime
import time
import re
import os
import bs4
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
import discord
from discord.ext import tasks

# Constants
GAS_STATION_NAME = 'NORWOOD YOUNG AMERICA'
GAS_STATION_URL = 'https://www.caseys.com/general-store/mn-ramsey/7222-sunwood-dr-nw/3460'
DISCORD_CHANNEL_ID = 123456789
FOOTER_TEXT = 'Designed by hiimmichael.com'
FOOTER_ICON_URL = 'https://hiimmichael.com/images/main_photo.png'
GOOGLE_MAPS_THUMBNAIL = 'https://maps.googleapis.com/maps/api/staticmap?center=45.2317415,-93.4505454&zoom=15&size=445x445&scale=2&markers=45.2317415,-93.4505454&key=[YOUR_GOOGLE_MAPS_API_KEY]'

# Environment variables
DISCORD_CLIENT_TOKEN = os.environ.get('DISCORD_CLIENT_TOKEN')
CHROME_DRIVER_PATH = os.environ.get('CHROME_DRIVER_PATH')

# Discord setup
intents = discord.Intents.default()
intents.message_content = True
intents.members = True
intents.reactions = True
intents.guilds = True
client = discord.Client(command_prefix=",", intents=intents)

async def send_message(gas):
    embed = discord.Embed(title=f'Gas Prices at {GAS_STATION_NAME}', color=0xFA8072, url=GAS_STATION_URL)
    for name, price in gas:
        embed.add_field(name=name, value=f'${price}/gal')
    embed.set_thumbnail(url=GOOGLE_MAPS_THUMBNAIL)
    embed.set_footer(text=f'{FOOTER_TEXT} | {datetime.datetime.now():%Y-%m-%d}', icon_url=FOOTER_ICON_URL)
    await client.get_channel(DISCORD_CHANNEL_ID).send(embed=embed)

def fetch_gas_prices():
    options = webdriver.ChromeOptions()
    options.add_argument('headless')
    service = Service(CHROME_DRIVER_PATH)
    driver = webdriver.Chrome(service=service, options=options)

    try:
        driver.get(GAS_STATION_URL)
        time.sleep(5)  # Wait for page to load

        page_source = driver.page_source
        soup = bs4.BeautifulSoup(page_source, 'html.parser')
        prices_row = soup.find_all('div', class_=re.compile("w-100 d-flex"))

        gas_prices = []
        for price in prices_row:
            gas_type = price.find('div', class_=re.compile("StoreFinderDetailsPage__details_item")).text
            prices = price.find('div', class_=re.compile("StoreFinderDetailsPage__details_item--price"))
            price_text = re.sub('\s+', ' ', prices.find('span', class_=re.compile("font-weight-bold")).text).strip()
            gas_prices.append((gas_type, price_text))

        return gas_prices
    except Exception as e:
        print(f'Error occurred while fetching gas prices: {e}')
        return []
    finally:
        driver.quit()

@client.event
async def on_ready():
    print(f'We have logged in as {client.user}')
    fetch_gas_prices_task.start()

@tasks.loop(seconds=3600)
async def fetch_gas_prices_task():
    gas_prices = fetch_gas_prices()
    if gas_prices:
        await send_message(gas_prices)
        print('Gas prices updated successfully.')
    else:
        print('Failed to fetch gas prices.')

if __name__ == "__main__":
    client.run(DISCORD_CLIENT_TOKEN)
