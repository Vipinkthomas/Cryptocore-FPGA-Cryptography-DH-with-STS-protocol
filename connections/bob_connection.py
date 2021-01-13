import socket
import threading


## This function will encode the message from user input and send it
def connect(s):
    '''receive messages from other party, and decode them'''

    while True:
        received = s.recv(4096)
        if not received:
            break
        if received == '':
            pass

        elif received.decode() == 'exit':
            ## alice exits when bob exits
            print("exit")
            break

        elif received.decode() == 'cAlice':
            ## if string message pubk received, alice will create a new file and write the pubk to pubkey.pem file
            ## which will later use it to decrypt the signature
            file = open("cAlice.txt", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()

        elif received.decode() == 'cert':
            ## if string message cert received, alice will create a new file and write the certificate to Certificate.crt file
            ## which will use it to verify the sender
            file = open("Certificate.crt", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()

        elif received.decode() == 'encMsg':
            ## if string message encMsg received, alice will create a new file and write the signature to 
            # sign.sha256.base64 file
            ## this file will be decrypted and check if it matches with the hashing value of the original message
            file = open("sign.sha256.base64", "wb")
            RecvData = s.recv(4096)
            file.write(RecvData)
            file.close()

        elif received.decode() == 'msg':
            ## if string message msg received, alice will create a new file and write the message to msg.txt file
            ## This is the original message
            file = open("msg.txt", "wb")
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

        ## bob exits and send exit command to server
        if s_msg.decode() == 'exit':
            print("exit")
            s.send(b'exit')
            break

        ## if string message pubk received, bob will send a message "pubk" along with the pubk.pem file to alice
        ## which will later use it to decrypt the signature
        elif s_msg.decode() == 'cBob':
            s.send('cBob')
            file = open("/home/vipin/cBob.txt", "rb")
            SendData = file.read(4096)
            s.send(SendData)
            file.close()

        ## if string message cert received, bob will send a message "cert" along with the Certificate.crt file to alice
        ## which will use it to verify the sender
        elif s_msg.decode() == 'cert':
            s.send(b'cert')
            file = open("Certificate.crt", "rb")
            SendData = file.read(4096)
            s.send(SendData)
            file.close()

        ## if string message encMsg received, bob will send a message "encMsg" along with the sign.sha256.base64 file to alice 
        ## this file will be decrypted and check if it matches with the hashing value of the original message
        elif s_msg.decode() == 'encMsg':
            s.send(b'encMsg')
            file = open("sign.sha256.base64", "rb")
            SendData = file.read(4096)
            s.send(SendData)
            file.close()

        ## if string message gen received, bob will send a message "gen" along with the b.txt file to alice
        ## This is the generator
        elif s_msg.decode() == 'gen':
            s.send(b'gen')
            file = open("b.txt", "rb")
            SendData = file.read(4096)
            s.send(SendData)
            file.close()

        ## if string message mod received, bob will send a message "mod" along with the b.txt file to alice
        ## This is the prime modulus
        elif s_msg.decode() == 'mod':
            s.send(b'mod')
            file = open("n.txt", "rb")
            SendData = file.read(4096)
            s.send(SendData)
            file.close()

        ## if string message msg received, bob will send a message "msg" along with the b.txt file to alice
        ## This is the prime modulus
        elif s_msg.decode() == 'msg':
            s.send(b'msg')
            file = open("c2.txt", "rb")
            SendData = file.read(4096)
            s.send(SendData)
            file.close()

        else:
            s.sendall(s_msg)

if __name__ == '__main__':

    port = 12345 # Port to listen on


    #creating new socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    #listening to the port
    s.connect(('127.0.0.1', port))

    #thread for peer connection and receiving encoded messages
    thread1 = threading.Thread(target = connect, args = ([s]))

    #thread for sending encoded messages
    thread2 = threading.Thread(target = sendMsg, args = ([s]))

    #starting the two threads
    thread1.start()
    thread2.start()

    #use join to "hold" on the main program
    thread1.join()
    thread2.join()
