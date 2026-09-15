import requests

##//GET https://www.elprisenligenu.dk/api/v1/prices/2026/09-15_DK2.json - url provided by distributor

def get_price_data():
    url = "https://www.elprisenligenu.dk/api/v1/prices/2026/09-15_DK2.json"
    response = requests.get(url)
    if response.status_code == 200:
        data = response.json()
        print (data)
        return data
    else:
        return None
    
