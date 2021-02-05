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
    while received != 'exit':

        received = s.recv(4096)

        if received == '':
            pass
            
        elif received ==' exit':
            s.send(b'exit')

        elif received.decode() == 'cBob':   # Receiving cBob from bob and write it to cBob.txt
            
            file = open("/home/alice/cBob.txt", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()
            print("\n*Received cBob*")

        elif received.decode() == 'bobCertificate':   ## Receving the certificate for bob and save it in bob.crt
            
            file = open("/home/alice/bob.crt", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()
            print('\n*Received Bob Certificate*')

        elif received.decode() == 'bobSignature':    ##receving the signature from bob
           
            file = open("/home/alice/signatureBob.enc", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()
            print('\n*received bob signature*')

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

    elif s_msg.decode() == '3': ##reading cAlice and send it to bob

        s.send(b'cAlice')
        file = open("/home/alice/cAlice.txt", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    elif s_msg.decode() == '9': ##Reading alice's certificate and send it to bob

        s.send(b'aliceCertificate')
        file = open("/home/alice/alice.crt", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    elif s_msg.decode() == '8': ##reading alice's signature and send it to bob

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

    port = 12345 ##connection port

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    s.connect(('127.0.0.1', port))

    ##creating 4 threads
    #--------------------
    thread1 = threading.Thread(target = connect, args = ([s])) ##thread for receiving messages
    thread2 = threading.Thread(target = sendMsg, args = ([s])) ##thread for sending messages
    
    thread3 = threading.Thread(target = sendMsg, args = ([s])) ##thread for sending messages
    thread4 = threading.Thread(target = sendMsg, args = ([s])) ##thread for sending messages

    
    thread1.start()
    
    #--------------------------------------------------------------------------------------------->

    userMenuInput= ''

    if userMenuInput != '0':
        print("\nEnter 1 to generate secret exponent")
        userMenuInput=input()

        if userMenuInput == '1':
            ##generating the exponent by running the compiled c program ( e )
            subprocess.call('/home/alice/stoesd_ii_2020-21/applications/prime/e', shell=True)

        print("\n*E has been generated*")
    #--------------------------------------------------------------------------------------------->

        
        print("\nplease Enter 2 to generate cAlice")
        userMenuInput=input()

        if userMenuInput =='2':
            ##generating cAlice by running the compiled c program ( cAlice )
            subprocess.call('/home/alice/stoesd_ii_2020-21/applications/prime/cAlice', shell=True)
            
        print("\n*cAlice has been generated*")
    #--------------------------------------------------------------------------------------------->
    
        
        print("\nplease Enter 3 to send cALice to Bob")
        userMenuInput=input()

        if userMenuInput =='3':
            ##sending cAlice to bob
            thread2.start()
            thread2.join()
            
        while not os.path.isfile("/home/alice/cBob.txt"):
            ##waiting for bob to send cBob
            print('waiting for bob to send cBob')
            time.sleep(5)

#---------------------------------------------------------------------------------------------------->
        
        print("\nplease Enter 4 to generate the SECRET KEY")
        userMenuInput=input()
        
            
        if userMenuInput =='4':
            ##creating the secret key
            subprocess.call('/home/alice/stoesd_ii_2020-21/applications/prime/secret', shell=True)

        print("\n***SECRET KEY HAS BEEN CREATED***")

#---------------------------------------------------------------------------------------------------->
        
        print("\n*Now you can verify*")
        print("\nplease Enter 5 to verify bob's certificate and signature")
        userMenuInput=input()

        if userMenuInput == '5':
            ##verifying other's signature and certificate
            subprocess.call(['sh','/home/alice/stoesd_ii_2020-21/Main/verifyCertSig.sh'])
            
#---------------------------------------------------------------------------------------------------->
        
        print("\n*Now you can create the Certificate*")
        print("\nplease Enter 6 to create Alice's certificate it")
        userMenuInput=input()

        if userMenuInput == '6':
            ##creating alice's certificate
            subprocess.call(['sh','/home/alice/stoesd_ii_2020-21/Main/createCertificate.sh'])
           
#---------------------------------------------------------------------------------------------------->
        
        print("\n*Now you can create the encrypted signature*")
        print("\nplease Enter 7 to create a signature and encrypt it")
        userMenuInput=input()

        if userMenuInput == '7':
            #creating signature
            subprocess.call(['sh','/home/alice/stoesd_ii_2020-21/Main/createEncSig.sh'])

        print('\n*Created signature.*')
#------------------------------------------------------------------------------------------------------->
        
        
        print("\nplease Enter 8 to send Encrypted signature to Bob")
        userMenuInput=input()

        if userMenuInput == '8':
            ##sending signature to bob
            thread3.start()
            thread3.join()

        print('\n*sent signature to Bob.*')
#--------------------------------------------------------------------------------------------------->
        
        
        print("\nplease Enter 9 to send certificate to Bob")
        userMenuInput=input()

        if userMenuInput == '9':
            ##sending certificate to bob
            thread4.start()
            thread4.join()
        
        print('\n*sent certificate to Bob.*')
#--------------------------------------------------------------------------------------------------->
        
        print("\n***NOW YOU CAN USER THE KEY TO ENCRYPT/DECRYPT MESSAGES***")
      
