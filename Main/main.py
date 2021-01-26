import subprocess
import socket
import threading

## This function will encode the message from user input and send it
def connect(s):
    '''receive messages from other party, and decode them'''
    received = s.recv(4096)
    if received == '':
        pass

    elif received.decode() == 'cAlice':
        ## if string message pubk received, alice will create a new file and write the pubk to pubkey.pem file
        ## which will later use it to decrypt the signature
        file = open("cAlice.txt", "wb")
        RecvData = s.recv(4096)
        file.write(RecvData)
        file.close()

    elif received.decode() == 'Cert':
        ## if string message cert received, alice will create a new file and write the certificate to Certificate.crt file
        ## which will use it to verify the sender
        file = open("alice.crt", "wb")
        RecvData = s.recv(4096)
        file.write(RecvData)
        file.close()

    elif received.decode() == 'encScrt':
        ## if string message encMsg "signatureAlice.enc" received, alice will create a new file and write the signature to 
        # signatureAlice.enc file
        ## this file will be decrypted and check if it matches with the hashing value of the original message
        file = open("signatureAlice.enc", "wb")
        RecvData = s.recv(4096)
        file.write(RecvData)
        file.close()

    else:
        print(received.decode())   
        

## This function will encode the message from user input and send it and also transfer files across
## chanel
def sendMsg(s):
    s_msg = input().encode('utf-8')
    if s_msg == '':
        pass

    ## if string message pubk received, bob will send a message "pubk" along with the pubk.pem file to alice
    ## which will later use it to decrypt the signature
    elif s_msg.decode() == 'cBob':
        s.send('cBob')
        file = open("/home/bob/cBob.txt", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    ## if string message cert received, bob will send a message "cert" along with the Certificate.crt file to alice
    ## which will use it to verify the sender
    elif s_msg.decode() == 'Cert':
        s.send(b'cert')
        file = open("/home/bob/bob.crt", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()

    ## if string message encMsg received, bob will send a message "encSig" along with the encrpyted sign.sha256.base64 file to alice 
    ## this file will be decrypted and check if it matches with the hashing value of the original message
    elif s_msg.decode() == 'encSig':

        s.send(b'encScrt')
        file = open("/home/bob/signatureBob.enc", "rb")
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
    thread1.start()

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
        print("Enter 7. Encryption(soon coming)\n")
        print("Enter 0. Exit\n")

        userMenuInput=input()
        
        if userMenuInput=='1':
            subprocess.call('home/bob/stoesd_ii_2020-21/applications/Bob/e', shell=True)
        elif userMenuInput=='2':
            subprocess.call('home/bob/stoesd_ii_2020-21/applications/Bob/cbob', shell=True)
        elif userMenuInput=='3':
            subprocess.call('home/bob/stoesd_ii_2020-21/applications/Bob/secret', shell=True)
        elif userMenuInput=='4':
            thread2.start()
            thread2.join()
        elif userMenuInput=='5':
            subprocess.call([r'createEncSig.sh'])
        elif userMenuInput=='6':
            subprocess.call([r'verifyCertSig.sh'])
        elif userMenuInput=='7':
            subprocess.call('echo $HOME', shell=True)
        elif userMenuInput=='c':
            subprocess.call([r'createCertificate.sh'])
        elif userMenuInput=='0':
            break

    thread1.join()
