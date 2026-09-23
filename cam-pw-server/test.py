import json
import os,requests
from dotenv import load_dotenv


#load environment variables
_=load_dotenv('.env')

pw:str = os.environ.get('ADMIN_PASSWORD') or "";

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
