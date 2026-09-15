import requests


from datetime import datetime, timedelta
from zoneinfo import ZoneInfo



DK_TIME = ZoneInfo("Europe/Copenhagen")

def get_price_data(YEAR, MONTH, DAY):
    url = (
        f"https://www.elprisenligenu.dk/api/v1/prices/"
        f"{YEAR}/{int(MONTH):02d}-{int(DAY):02d}_DK2.json"
    )

    response = requests.get(url)

    if response.status_code == 200:
        return response.json()

    print("ERROR:", response.status_code, url)
    return None


def print_price_data(data):
    for hour, item in enumerate(data):
        print(hour, item["DKK_per_kWh"], flush=True)


def print_prices(YEAR, MONTH, DAY):
    data = get_price_data(YEAR, MONTH, DAY)

    if data is None:
        return

    for item in data:
        start_time = datetime.fromisoformat(
            item["time_start"]
        ).astimezone(DK_TIME)

        hour = start_time.hour
        price = item["DKK_per_kWh"]

        print(hour, price, flush=True)


