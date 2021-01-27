# Have to add funcationality to check whether the files are avilable before sending it, 
#if not ask the permission to create the files 

import subprocess
import socket
import threading

## This function will encode the message from user input and send it
def connect(s):
    '''receive messages from other party, and decode them'''

    while True:

        received = s.recv(4096)
        if received == '':
            pass

        elif received.decode() == 'cBob':
            ## if string message pubk received, alice will create a new file and write the pubk to pubkey.pem file
            ## which will later use it to decrypt the signature
            file = open("/home/alice/cBob.txt", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()

        elif received.decode() == 'Cert':
            ## if string message cert received, alice will create a new file and write the certificate to Certificate.crt file
            ## which will use it to verify the sender
            file = open("/home/alice/bob.crt", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()

        elif received.decode() == 'encSig':
            ## if string message encSig "signatureAlice.enc" received, alice will create a new file and write the signature to 
            # signatureAlice.enc file
            ## this file will be decrypted and check if it matches with the hashing value of the original message
            file = open("/home/alice/signatureBob.enc", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()

        elif received.decode() == 'Msg':
            ## if string message Msg "signatureAlice.enc" received, alice will create a new file and write the signature to 
            # encMsgAlice.enc file
            ## this file will be decrypted and check if it matches with the hashing value of the original message
            file = open("/home/alice/encMsgBob.enc", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()

        else:
            print(received.decode())   
        

## This function will encode the message from user input and send it and also transfer files across
## chanel
def sendMsg(s):

    while True:
        
        s_msg = input().encode('utf-8')
        if s_msg == '':
            pass

        ## if string message pubk received, bob will send a message "pubk" along with the pubk.pem file to alice
        ## which will later use it to decrypt the signature
        elif s_msg.decode() == 'cAlice':
            s.send('cAlice')
            file = open("/home/alice/cAlice.txt", "rb")
            SendData = file.read(4096)
            s.send(SendData)
            file.close()

        ## if string message cert received, bob will send a message "cert" along with the Certificate.crt file to alice
        ## which will use it to verify the sender
        elif s_msg.decode() == 'Cert':
            s.send(b'cert')
            file = open("/home/alice/alice.crt", "rb")
            SendData = file.read(4096)
            s.send(SendData)
            file.close()

        ## if string message encMsg received, bob will send a message "encSig" along with the encrpyted sign.sha256.base64 file to alice 
        ## this file will be decrypted and check if it matches with the hashing value of the original message
        elif s_msg.decode() == 'encSig':

            s.send(b'encScrt')
            file = open("/home/alice/signatureAlice.enc", "rb")
            SendData = file.read(4096)
            s.send(SendData)
            file.close()

        elif s_msg.decode() == 'Msg':
            ## if string message encMsg received, bob will send a message "Msg" along with the encrpyted encMsgBob.enc file to alice 
            ## this file will be decrypted and check if it matches with the hashing value of the original message
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
    #thread for sending encoded messages
    thread2 = threading.Thread(target = sendMsg, args = ([s]))
    
    #starting the two threads
    thread1.start()
    thread2.start()

    #use join to "hold" on the main program
    thread1.join()
    thread2.join()

    '''
    print("Diffie Hellmann(with STS protocol) Algorithm - Prototype")
    print("..........................................\n")
    print("Enter 0 for exit or press Enter to continue\n")
    
    userMenuInput=input()
    
    while userMenuInput!='0':
        
        print("\nMainMenu")
        print("..........................................\n")
        print("Enter c. Create Alice's Certificate\n")
        print("Enter 1. Create Exponent\n")
        print("Enter 2. Create cAlice\n")
        print("Enter 3. Create secret\n")
        print("Enter 4. Create Encrypted Signature\n")
        print("Enter 5. Send Files")
        print("Enter 6. Verify Bob's Signature and Certificate \n")
        print("Enter 7. Encryption\n")
        print("Enter 8. Decryption\n")
        print("Enter 0. Exit\n")

        userMenuInput=input()
        
        if userMenuInput=='1':
            subprocess.call('home/alice/stoesd_ii_2020-21/applications/prime/e', shell=True)
        elif userMenuInput=='2':
            subprocess.call('home/alice/stoesd_ii_2020-21/applications/prime/cAlice', shell=True)
        elif userMenuInput=='3':
            subprocess.call('home/alice/stoesd_ii_2020-21/applications/prime/secret', shell=True)
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

    thread1.join()
    '''
