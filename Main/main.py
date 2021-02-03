import subprocess
import socket
import threading
import sys
import os
import time

## This function will encode the message from user input and send it
def connect(s):
    '''receive messages from other party, and decode them'''

    received=''
    while received! = 'exit':

        received = s.recv(4096)

        if received == '':
            pass
            
        elif received=='exit':
            s.send(b'exit')

        elif received.decode() == 'cBob':
            
            file = open("/home/alice/cBob.txt", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()
            print("Received cBob")

        elif received.decode() == 'bobCertificate':
            
            file = open("/home/alice/bob.crt", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()
            print('Received Bob Certificate')

        elif received.decode() == 'bobSignature':
           
            file = open("/home/alice/signatureBob.enc", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()
            print('received bob signature')

        elif received.decode() == 'Msg':
            
            file = open("/home/alice/encMsgBob.enc", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()

        else:
            print(received.decode())   
        

## This function will encode the message from user input and send it and also transfer files across
## chanel
def sendMsg(s):

    
    
    s_msg = userMenuInput.encode('utf-8')

    if s_msg == '':
        pass

    
    elif s_msg.decode() == '3':
        s.send(b'cAlice')
        file = open("/home/alice/cAlice.txt", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    elif s_msg.decode() == '9':
        s.send(b'aliceCertificate')
        file = open("/home/alice/alice.crt", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    elif s_msg.decode() == '8':

        s.send(b'aliceSignature')
        file = open("/home/alice/signatureAlice.enc", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    elif s_msg.decode() == 'Msg':
        
        s.send(b'Msg')
        file = open("/home/alice/encMsgAlice.enc", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()


    else:
        s.sendall(s_msg)



if __name__ == '__main__':

    port = 12345

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    s.connect(('127.0.0.1', port))

    thread1 = threading.Thread(target = connect, args = ([s]))
    thread2 = threading.Thread(target = sendMsg, args = ([s]))
    
    thread3 = threading.Thread(target = sendMsg, args = ([s]))
    thread4 = threading.Thread(target = sendMsg, args = ([s]))

    
    thread1.start()
    
    #--------------------------------------------------------------------------------------------->

    userMenuInput= ''

    if userMenuInput != '0':
        print("Enter 1 to generate secret exponent")
        userMenuInput=input()

        if userMenuInput == '1':
            subprocess.call('/home/alice/stoesd_ii_2020-21/applications/prime/e', shell=True)
             
    #--------------------------------------------------------------------------------------------->

        print("E has been generated")
        print("please Enter 2 to generate cAlice")
        userMenuInput=input()

        if userMenuInput =='2':
            subprocess.call('/home/alice/stoesd_ii_2020-21/applications/prime/cAlice', shell=True)
            
    #--------------------------------------------------------------------------------------------->
    
        print("cAlice has been generated")
        print("please Enter 3 to send cALice to Bob")
        userMenuInput=input()

        if userMenuInput =='3':
            thread2.start()
            thread2.join()
            
        while not os.path.isfile("/home/alice/cBob.txt"):
            print('waiting for bob to send cBob')
            time.sleep(5)

#---------------------------------------------------------------------------------------------------->
        
        print("please Enter 4 to generate the SECRET KEY")
        userMenuInput=input()
        
            
        if userMenuInput =='4':
            subprocess.call('/home/alice/stoesd_ii_2020-21/applications/prime/secret', shell=True)

        print("SECRET KEY has been created")

#---------------------------------------------------------------------------------------------------->
        
        print("Now you can verify")
        print("please Enter 5 to verify bob's certificate and signature")
        userMenuInput=input()

        if userMenuInput == '5':
            subprocess.call(['sh','/home/alice/stoesd_ii_2020-21/Main/verifyCertSig.sh'])
            
#---------------------------------------------------------------------------------------------------->
        
        print("Now you can create the Certificate")
        print("please Enter 6 to create bob's certificate it")
        userMenuInput=input()

        if userMenuInput == '6':
            subprocess.call(['sh','/home/alice/stoesd_ii_2020-21/Main/createCertificate.sh'])
           
#---------------------------------------------------------------------------------------------------->
        
        print("Now you can create the encrypted signature")
        print("please Enter 7 to create a signature and encrypt it")
        userMenuInput=input()

        if userMenuInput == '7':
            subprocess.call(['sh','/home/alice/stoesd_ii_2020-21/Main/createEncSig.sh'])
#------------------------------------------------------------------------------------------------------->
        
        print('Created signature.')
        print("please Enter 8 to send Encrypted signature to Bob")
        userMenuInput=input()

        if userMenuInput == '8':
            thread3.start()
            thread3.join()
#--------------------------------------------------------------------------------------------------->
        
        print('sent signature to Bob.')
        print("please Enter 9 to send certificate to Bob")
        userMenuInput=input()

        if userMenuInput == '9':
            thread4.start()
            thread4.join()
#--------------------------------------------------------------------------------------------------->
        
        print("Congrats you have the key")
      
