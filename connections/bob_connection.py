import socket
import threading


## This function will encode the message from user input and send it
def connect(s):
    '''receive messages from other party, and decode them'''

    while True:
        r_msg = s.recv(4096)
        if not r_msg:
            break
        if r_msg == '':
            pass
        else:
            print(r_msg.decode())

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
        elif s_msg.decode() == 'pubk':
            s.send(b'pubk')
            file = open("pubkey.pem", "rb")
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