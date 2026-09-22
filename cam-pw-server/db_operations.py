from fastapi import APIRouter, HTTPException, Request, Response
from .auth import db, PasswordSubmission, checkPassword
from typing import Any
from pydantic import BaseModel
from google.cloud import firestore_v1
import json

# get the new auth key
ScoreboardRouter = APIRouter()
@ScoreboardRouter.put("/get")



@ScoreboardRouter.post("/needname")
async def setBoard(request:Request, passwordSubmission:PasswordSubmission):


    if not checkPassword(passwordSubmission.password):
        return HTTPException(401, detail=f"Access Denied")
    req = (await request.json())
    try:
        docRef = db.collection('stored').document('Games')
        docRef2 = db.collection('scoreboard').document('teams')
        docRef3 = db.collection('page').document('status')

        batch = db.batch()
        batch.set(docRef,req['games'])
        batch.set(docRef2,req['teams'])
        batch.set(docRef3, {'scoreboard':req['enabled']})
        batch.commit()

    except KeyError as e:
        return HTTPException(422, detail="Missing fields")
    except Exception as e:
        return HTTPException(500, detail=f"Internal Server Error")
    
    return Response(status_code=200,content="Success",headers={'content-type':'text/plain'})



