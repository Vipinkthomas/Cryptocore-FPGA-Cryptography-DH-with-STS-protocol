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
        if received == '':
            file = open("/home/bob/cAlice.txt", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()
            print("cAlice has been received")
            pass

           
    

## This function will encode the message from user input and send it and also transfer files across
## chanel
def sendMsg(s):

    
    s_msg = userMenuInput.encode('utf-8')
    if s_msg == '':
        pass

    ## if string message pubk received, bob will send a message "pubk" along with the pubk.pem file to alice
    ## which will later use it to decrypt the signature
    elif s_msg.decode() == '6':
        s.send(b'bobSignature')
        file = open("/home/bob/signatureBob.enc", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    ## if string message cert received, bob will send a message "cert" along with the Certificate.crt file to alice
    ## which will use it to verify the sender
    elif s_msg.decode() == '7':
        s.send(b'bobCertificate')
        file = open("/home/bob/bob.crt", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    ## if string message encMsg received, bob will send a message "encSig" along with the encrpyted sign.sha256.base64 file to alice 
    ## this file will be decrypted and check if it matches with the hashing value of the original message
    elif s_msg.decode() == '8':

        s.send(b'cBob')
        file = open("/home/bob/cBob.txt", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    elif s_msg.decode() == 'Msg':
        ## if string message encMsg received, bob will send a message "Msg" along with the encrpyted encMsgBob.enc file to alice 
        ## this file will be decrypted and check if it matches with the hashing value of the original message
        s.send(b'Msg')
        file = open("/home/bob/encMsgBob.enc", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()


    else:
        s.sendall(s_msg)



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

    userMenuInput= ''
            


    '''
    
        elif userMenuInput=='7':
            subprocess.call('openssl enc -salt -aes-256-cbc -in /home/bob/messageBob.txt -kfile /home/bob/secret.txt -out /home/bob/encMsgBob.enc', shell=True)
        elif userMenuInput=='8':
            subprocess.call('openssl enc -d -salt -aes-256-cbc -in /home/bob/encMsgBob.enc -kfile /home/bob/secret.txt -out /home/bob/messageAlice.txt', shell=True)
        
    # thread1.join()
    '''
