import json
import os,requests
from dotenv import load_dotenv


#load environment variables
_=load_dotenv('.env')

pw:str = os.environ.get('ADMIN_PASSWORD') or "";


def writeUpdate(json_data:dict[str,dict[str,str]]
):
    response=requests.post(
        "http://127.0.0.1:8000/update",
        json.dumps(
            {
                "passwordSubmission": {
                    "password": pw
                },
                "data": {
                    "content": json_data,
                    "mode": 1
                }
            }
        ),
        headers={
            'Content-Type':"application/json"
        }
        
    )    
    print(response.text)

def getLoaded():
    response=requests.post(
        "http://127.0.0.1:8000/retrieve",
        json.dumps(
            {
                "password":pw,

            }
        ),
        headers={
            'Content-Type':"application/json"
        }
        
    )    
    print(response.text)

getLoaded()



