
from typing import Any, List
from pydantic import BaseModel
import google.cloud.firestore_v1

import json, os
from dotenv import load_dotenv


#load environment variables
_=load_dotenv('.env')


# load firestore client
KeyString:str = os.environ.get('FIREBASE_SERVICE_ACCOUNT_KEY') or '{}'
if KeyString == '{}':
    raise ValueError(
        "Firestore key no exist for some reason"
        "Vercel is screwing with something"
    )
db = google.cloud.firestore_v1.Client.from_service_account_info(json.loads(KeyString))


class PasswordSubmission(BaseModel):
    password:str

def checkPassword(password:str):
  return password == os.environ.get('ADMIN_PASSWORD')
