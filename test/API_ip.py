import sys
import requests
import json
import markdown
from prettytable import PrettyTable 


def queryIPInfo(ip_addres):

  output_data = {
    "Country": "",
    "Region": "",
    "City": "",
    "Latitude": "",
    "Longitude": "",
    "Org": ""
    }
  #conect to API
  r = requests.get(f'https://ipinfo.io/{ip_addres}')
  
  if r.status_code == 404:
    print("Error 404 - The requested site was not found ")
    exit()

  data = r.text

  #update output_data
  output_data['City'] = json.loads(data)['city']
  output_data['Country'] = json.loads(data)['country']
  output_data['Region'] = json.loads(data)['region']

  loc = json.loads(data)['loc']
  output_data['Latitude'] = loc.split(",")[0]
  output_data['Longitude'] = loc.split(",")[1]

  output_data['Org'] = json.loads(data)['org']
  
  
  #make table
  keys = output_data.keys()
  values = output_data.values()
  
  myTable = PrettyTable(keys) 
  myTable.add_row(values) 

  return myTable


output = markdown.markdown('''
#I could not display the table with markdown without working with an 'md' file#
_Open an 'md' file, write to it and then read from it_
**I at least preferred to present with a table from the Python library**
''')

print(f"{output}\n")

if __name__ == "__main__":
	if len(sys.argv) < 2:
		print("Please enter an IP address, exiting.")
		sys.exit()
	
	print(queryIPInfo(sys.argv[1]))  


