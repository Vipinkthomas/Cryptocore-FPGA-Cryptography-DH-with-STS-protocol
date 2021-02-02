# Have to add funcationality to check whether the files are avilable before sending it, 
#if not ask the permission to create the files 

import subprocess
import socket
import threading
import time
import os

## This function will encode the message from user input and send it
def connect(s):
    '''receive messages from other party, and decode them'''

    while True:
        received = s.recv(4096)
        if received:
            file = open("/home/bob/encMsgAlice.enc", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()

    

## This function will encode the message from user input and send it and also transfer files across
## chanel
def sendMsg(s):

    s_msg = userInput.encode('utf-8')
    ## if string message pubk received, bob will send a message "pubk" along with the pubk.pem file to alice
    ## which will later use it to decrypt the signature
    if s_msg.decode() == '2':
        file = open("/home/bob/encMsgBob.enc", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()



if __name__ == '__main__':

    PORT = 12345
    HOST = '127.0.0.1'  # address (localhost)

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    s.bind((HOST, PORT))

    # s.connect(('127.0.0.1', port))

    #sets up and start TCP listener
    s.listen(5)
    print('Bob is listening on port 12345 .... \n')

    #Establish connection with other party( BOB ).
    (conn, addr) = s.accept()



    thread1 = threading.Thread(target = connect, args = ([conn]))
    #thread for sending encoded messages
    thread2 = threading.Thread(target = sendMsg, args = ([conn]))
    
    thread1.start()
    thread2.start()

    while True:

        userInput = ''
        userInput = input("Enter the message: ")
        file = open("/home/bob/bobMsg.txt", "wb")
        
        file.write(bytes(userInput, 'UTF-8'))
        file.close()
        
        subprocess.call('openssl enc -salt -aes-256-cbc -in /home/bob/bobMsg.txt -kfile /home/bob/secret.txt -out /home/bob/encMsgBob.enc', shell=True)

        userInput = input("Enter 2 to send the encrypted message to ALICE: ")

        
        

            


    '''
    
        elif userMenuInput=='7':
            subprocess.call('openssl enc -salt -aes-256-cbc -in /home/bob/messageBob.txt -kfile /home/bob/secret.txt -out /home/bob/encMsgBob.enc', shell=True)
        elif userMenuInput=='8':
            subprocess.call('openssl enc -d -salt -aes-256-cbc -in /home/bob/encMsgBob.enc -kfile /home/bob/secret.txt -out /home/bob/messageAlice.txt', shell=True)
        
    # thread1.join()
    '''
