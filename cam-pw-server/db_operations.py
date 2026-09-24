from fastapi import APIRouter, HTTPException, Request, Response
from .auth import db, PasswordSubmission, checkPassword
from typing import Any, final
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




MERGE,PRUNE = range(2)

class ContentBox(BaseModel):
    content:dict[str,dict[str,str]]
    mode:int


@PWManager.post("/update")
async def updateStored(passwordSubmission:PasswordSubmission, data:ContentBox):


    if not checkPassword(passwordSubmission.password):
        return HTTPException(401, detail=f"Access Denied")
    
    loaded_data:dict[str,dict[str,str]] = data.content
    try:
        collectionRef = db.collection('pwds')

        # adding items
        batch = db.batch()
        
        for service in loaded_data:
            doc_ref = collectionRef.document(service)
            if data.mode == PRUNE:
                batch.set(doc_ref,loaded_data[service])
            else:
                batch.set(doc_ref,loaded_data[service],merge=True)
                
            
        batch.commit()
        
        #deleting items if prune
        if (data.mode==PRUNE):
            batch = db.batch()

            prune_targets = set([x.id for x in collectionRef.stream()]).difference(set(loaded_data.keys()))
            
            for x in prune_targets:
                doc_ref = collectionRef.document(x)
                batch.delete(doc_ref)

            batch.commit()
        
    except KeyError as e:
        return HTTPException(422, detail="Missing fields")
    except Exception as e:
        return HTTPException(500, detail=f"Internal Server Error")
    
    return Response(status_code=200,content="Success",headers={'content-type':'text/plain'})
