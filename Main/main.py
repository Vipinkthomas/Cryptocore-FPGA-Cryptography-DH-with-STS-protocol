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

    
    received = s.recv(4096)
    if received == '':
        pass

    elif received.decode() == 'cAlice':
        ## if string message pubk received, alice will create a new file and write the pubk to pubkey.pem file
        ## which will later use it to decrypt the signature
        file = open("/home/bob/cAlice.txt", "wb")
        RecvData = s.recv(4096)
        file.write(RecvData)
        file.close()
        print("cAlice has been received")

    elif received.decode() == 'Cert':
        ## if string message cert received, alice will create a new file and write the certificate to Certificate.crt file
        ## which will use it to verify the sender
        file = open("/home/bob/alice.crt", "wb")
        RecvData = s.recv(4096)
        file.write(RecvData)
        file.close()

    elif received.decode() == 'encSig':
        ## if string message encSig "signatureAlice.enc" received, alice will create a new file and write the signature to 
        # signatureAlice.enc file
        ## this file will be decrypted and check if it matches with the hashing value of the original message
        file = open("/home/bob/signatureAlice.enc", "wb")
        RecvData = s.recv(4096)
        file.write(RecvData)
        file.close()

    elif received.decode() == 'Msg':
        ## if string message Msg "signatureAlice.enc" received, alice will create a new file and write the signature to 
        # encMsgAlice.enc file
        ## this file will be decrypted and check if it matches with the hashing value of the original message
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
        file = open("/home/bob/cBob", "rb")
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

    userMenuInput= ''

    while userMenuInput != '0':
        print("Enter 1 to generate secret exponent")
        userMenuInput=input()

        if userMenuInput == '1':
            subprocess.call('/home/bob/stoesd_ii_2020-21/applications/Bob/e', shell=True)
            break
            
    #--------------------------------------------------------------------------------------------->

    print("E has been generated")
    
    while userMenuInput != '0':
        print("please Enter 2 to generate cBob")
        userMenuInput=input()

        if userMenuInput =='2':
            subprocess.call('/home/bob/stoesd_ii_2020-21/applications/Bob/cbob', shell=True)
            break
    #--------------------------------------------------------------------------------------------->

    print("cBob has been generated")
    
    while userMenuInput != '0':
        print("please Enter 3 to generate the SECRET KEY")
        userMenuInput=input()

        while not os.path.isfile("/home/bob/cAlice.txt"):
            print('waiting for alice to send cAlice')
            time.sleep(1)
        print('Received cAlice')
            
        if userMenuInput =='3':
            subprocess.call('/home/bob/stoesd_ii_2020-21/applications/Bob/secret', shell=True)
            break

    print("SECRET KEY has been created")
#---------------------------------------------------------------------------------------------------->
    print("Now you can create the Certificate")
    
    while userMenuInput != '0':
        print("please Enter 4 to create bob's certificate it")
        userMenuInput=input()

        if userMenuInput == '4':
            subprocess.call(['sh','/home/bob/stoesd_ii_2020-21/Main/createCertificate.sh'])
            # subprocess.call('cd /home/bob/stoesd_ii_2020-21/Main ; ./createCertificate.sh', shell=True)
            
            break
#---------------------------------------------------------------------------------------------------->
    print("Now you can create the encrypted signature")
    
    while userMenuInput != '0':
        print("please Enter 5 to create a signature and encrypt it")
        userMenuInput=input()

        if userMenuInput == '5':
            subprocess.call(['sh','/home/bob/stoesd_ii_2020-21/Main/createEncSig.sh'])
            break
#------------------------------------------------------------------------------------------------------->
    print('Created signature.')

    while userMenuInput != '0':
        print("please Enter 6 to send Encrypted signature to Alice")
        userMenuInput=input()

        if userMenuInput == '6':
            thread2.start()
            
            break
    thread2.join()
#--------------------------------------------------------------------------------------------------->
    print('sent signature to Alice.')

    while userMenuInput != '0':
        print("please Enter 7 to send certificate to Alice")
        userMenuInput=input()

        if userMenuInput == '7':
            thread2.start()
            
            break
    thread2.join()
#--------------------------------------------------------------------------------------------------->
    print('sent certificate to Alice.')

    while userMenuInput != '0':
        print("please Enter 8 to send cBob to Alice")
        userMenuInput=input()

        if userMenuInput == '8':
            thread2.start()
            
            break

    thread2.join()


    #starting the two threads
    
    # thread2.start()
    
    #join the two threads
    thread1.join()
    # thread2.join()

    '''
    print("Diffie Hellmann(with STS protocol) Algorithm - Prototype")
    print("..........................................\n")
    print("Enter 0 for exit or press Enter to continue\n")
    
    userMenuInput=input()
    
    while userMenuInput!='0':
        
        print("\nMainMenu")
        print("..........................................\n")
        print("Enter c. Create Bob's Certificate\n")
        print("Enter 1. Create Exponent\n")
        print("Enter 2. Create cBob\n")
        print("Enter 3. Create secret\n")
        print("Enter 4. Create Encrypted Signature\n")
        print("Enter 5. Send Files")
        print("Enter 6. Verify Alice's Signature and Certificate \n")
        print("Enter 7. Encryption\n")
        print("Enter 8. Decryption\n")
        print("Enter 0. Exit\n")

        userMenuInput=input()
        
        if userMenuInput=='1':
            subprocess.call('home/bob/stoesd_ii_2020-21/applications/Bob/e', shell=True)
        elif userMenuInput=='2':
            subprocess.call('home/bob/stoesd_ii_2020-21/applications/Bob/cbob', shell=True)
        elif userMenuInput=='3':
            subprocess.call('home/bob/stoesd_ii_2020-21/applications/Bob/secret', shell=True)
        elif userMenuInput=='4':
            subprocess.call([r'createEncSig.sh'])
        elif userMenuInput=='5':
            thread2.start()
            thread2.join()
        elif userMenuInput=='6':
            subprocess.call([r'verifyCertSig.sh'])
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

    # thread1.join()
    '''
