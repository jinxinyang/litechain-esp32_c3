import requests

url = 'http://localhost:8000'
response = requests.get(url)

print(response.text)
