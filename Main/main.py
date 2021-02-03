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
            pass

        elif received.decode() == 'cAlice':
            
            file = open("/home/bob/cAlice.txt", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()
            print("\n*cAlice has been received*")

        elif received.decode() == 'aliceCertificate':
            
            file = open("/home/bob/alice.crt", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()
            print("\n*Alice's certificate has been received*")

        elif received.decode() == 'aliceSignature':
            
            file = open("/home/bob/signatureAlice.enc", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()
            print("\n*Alice's signature has been received*")


        elif received.decode() == 'Msg':
            
            file = open("/home/bob/encMsgAlice.enc", "wb")
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

    
    elif s_msg.decode() == '6':
        s.send(b'bobSignature')
        file = open("/home/bob/signatureBob.enc", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    
    elif s_msg.decode() == '7':
        s.send(b'bobCertificate')
        file = open("/home/bob/bob.crt", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    
    elif s_msg.decode() == '8':

        s.send(b'cBob')
        file = open("/home/bob/cBob.txt", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    elif s_msg.decode() == 'Msg':
        
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

    #sets up and start TCP listener
    s.listen(5)
    print('Bob is listening on port 12345 .... \n')

    #Establish connection with other party( BOB ).
    (conn, addr) = s.accept()


    thread1 = threading.Thread(target = connect, args = ([conn]))
    thread2 = threading.Thread(target = sendMsg, args = ([conn]))
    
    thread3 = threading.Thread(target = sendMsg, args = ([conn]))
    thread4 = threading.Thread(target = sendMsg, args = ([conn]))

    
    thread1.start()

    userMenuInput= ''

    if userMenuInput != '0':
        print("\nEnter 1 to generate secret exponent")
        userMenuInput=input()

        if userMenuInput == '1':
            subprocess.call('/home/bob/stoesd_ii_2020-21/applications/Bob/e', shell=True)
            
        print("\n*E has been generated*")
    #--------------------------------------------------------------------------------------------->

        print("\nplease Enter 2 to generate cBob")
        userMenuInput=input()

        if userMenuInput =='2':
            subprocess.call('/home/bob/stoesd_ii_2020-21/applications/Bob/cbob', shell=True)
        
        print("\n*cBob has been generated*")
    #--------------------------------------------------------------------------------------------->

        
        print("\nplease Enter 3 to generate the SECRET KEY")
        userMenuInput=input()

        while not os.path.isfile("/home/bob/cAlice.txt"):
            print('waiting for alice to send cAlice')
            time.sleep(1)
        print('\n*Received cAlice*')
            
        if userMenuInput =='3':
            subprocess.call('/home/bob/stoesd_ii_2020-21/applications/Bob/secret', shell=True)

        print("\n***SECRET KEY HAS BEEN CREATED***")

#---------------------------------------------------------------------------------------------------->
        print("\n*Now you can create the Certificate*")
        print("\nplease Enter 4 to create bob's certificate it")
        userMenuInput=input()

        if userMenuInput == '4':
            subprocess.call(['sh','/home/bob/stoesd_ii_2020-21/Main/createCertificate.sh'])
#---------------------------------------------------------------------------------------------------->
        
        print("\n*Now you can create the encrypted signature*")
        print("\nplease Enter 5 to create a signature and encrypt it")
        userMenuInput=input()

        if userMenuInput == '5':
            subprocess.call(['sh','/home/bob/stoesd_ii_2020-21/Main/createEncSig.sh'])
#------------------------------------------------------------------------------------------------------->
        
        print('\n*Created signature.*')
        print("\nplease Enter 6 to send Encrypted signature to Alice")
        userMenuInput=input()

        if userMenuInput == '6':
            thread2.start()

        print('\n*sent signature to Alice.*')
#--------------------------------------------------------------------------------------------------->
        
        
        print("\nplease Enter 7 to send certificate to Alice")
        userMenuInput=input()

        if userMenuInput == '7':
            thread3.start()
            
        print('*sent certificate to Alice.*')
#--------------------------------------------------------------------------------------------------->
        
        
        print("\nplease Enter 8 to send cBob to Alice")
        userMenuInput=input()

        if userMenuInput == '8':
            thread4.start()
            thread4.join()

        while not os.path.isfile("/home/bob/alice.crt"):
            print('waiting for alice to send certificate')
            time.sleep(5)
        
        print("\nplease Enter 9 to verify alice's certificate and signature")
        userMenuInput=input()

        if userMenuInput == '9':
            subprocess.call(['sh','/home/bob/stoesd_ii_2020-21/Main/verifyCertSig.sh'])
            

        print("\n***NOW YOU CAN USER THE KEY TO ENCRYPT/DECRYPT MESSAGES***")
        
    
