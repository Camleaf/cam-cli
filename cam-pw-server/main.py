import json,sys
from fastapi import FastAPI, HTTPException, Response
from pydantic import BaseModel
from fastapi.responses import HTMLResponse

from util.auth import PasswordSubmission, checkPassword
from router.db_operations import PWManager
# routers
from starlette.middleware.cors import CORSMiddleware
from slowapi.util import get_remote_address
from slowapi.errors import RateLimitExceeded
app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["https://www.mechmania.ca", "https://mechmania.ca", "http://localhost:5173"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)



@app.post("/password")
def verifyPassword(passwordSubmission:PasswordSubmission):
    result = checkPassword(passwordSubmission.password)
    return Response(status_code=200 if result else 401,content=json.dumps({'result':result}), headers={'content-type':'application/json'})

# include routers
#############################################################################################
app.include_router(PWManager)


@app.exception_handler(RateLimitExceeded)
async def HandlerRateLimit(request, exc):
    return Response(status_code=200,content=json.dumps({'status':429,'message':'Too many requests'}))
