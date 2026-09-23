from fastapi import APIRouter, HTTPException, Request, Response
from .auth import db, PasswordSubmission, checkPassword
from typing import Any
from pydantic import BaseModel
from google.cloud import firestore_v1
import json

# get the new auth key
PWManager = APIRouter()




@PWManager.post("/retrieve")
async def retrieveStored(passwordSubmission:PasswordSubmission):


    if not checkPassword(passwordSubmission.password):
        return HTTPException(401, detail=f"Access Denied")
    
    loaded_data:dict[str,dict[str,str]] = {}
    try:

        x = db.collection('pwds').get()
        print(x)
        for y in x:
            z = y.to_dict()
            loaded_data[y.id] = z if z is not None else {}

    except KeyError as e:
        return HTTPException(422, detail="Missing fields")
    except Exception as e:
        return HTTPException(500, detail=f"Internal Server Error")
    
    return Response(status_code=200,content=json.dumps(loaded_data),headers={'content-type':'application/json'})



