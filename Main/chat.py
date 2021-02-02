# Have to add funcationality to check whether the files are avilable before sending it, 
#if not ask the permission to create the files 

import subprocess
import socket
import threading
import sys
import os
import time

userInput = ''
## This function will encode the message from user input and send it

def connect(s):
    '''receive messages from other party, and decode them'''
    while True:
        received = s.recv(4096)
        if received:
            file = open("/home/alice/encMsgBob.enc", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()

   
        

## This function will encode the message from user input and send it and also transfer files across
## chanel
def sendMsg(s):

    ## if string message pubk received, bob will send a message "pubk" along with the pubk.pem file to alice
    ## which will later use it to decrypt the signature
    if userInput == '2':
        file = open("/home/alice/encMsgAlice.enc", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()
    
   


if __name__ == '__main__':

    port = 12345

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    s.connect(('127.0.0.1', port))

    thread1 = threading.Thread(target = connect, args = ([s]))
    #thread for sending encoded messages
    thread2 = threading.Thread(target = sendMsg, args = ([s]))

    
    #starting the two threads
    thread1.start()
    thread2.start()
    # thread2.start()
    while True:

        userInput = input("Enter the message: ")
        file = open("/home/alice/aliceMsg.txt", "wb")
        file.write(userInput)
        file.close()
        
        subprocess.call('openssl enc -salt -aes-256-cbc -in /home/alice/aliceMsg.txt -kfile /home/alice/secret.txt -out /home/alice/encMsgAlice.enc', shell=True)

        userInput = input("Enter 2 to send the encrypted message to ALICE: ")


    '''
        elif userMenuInput=='7':
            subprocess.call('openssl enc -salt -aes-256-cbc -in /home/bob/messageBob.txt -kfile /home/bob/secret.txt -out /home/bob/encMsgBob.enc', shell=True)
        elif userMenuInput=='8':
            subprocess.call('openssl enc -d -salt -aes-256-cbc -in /home/bob/encMsgBob.enc -kfile /home/bob/secret.txt -out /home/bob/messageAlice.txt', shell=True)
        elif userMenuInput=='7':
            subprocess.call('echo $HOME', shell=True)
        elif userMenuInput=='c':
            subprocess.call([r'createCertificate.sh'])
        elif userMenuInput=='0':
            break

    thread1.join()
    '''
