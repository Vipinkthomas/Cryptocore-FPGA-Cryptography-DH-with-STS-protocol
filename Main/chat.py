import subprocess
import socket
import threading

##Receiving messages from other party
def connect(s):
    '''receive messages from other party, and decode them'''

    while True:

        received = s.recv(4096)
        ##REceiving encrypted message from bob
        file = open("/home/alice/encMsgBob.enc", "wb")
        file.write(received)
        file.close()

        ##Decrypting message of bob using the secret key
        subprocess.call('openssl enc -d -salt -aes-256-cbc -in /home/alice/encMsgBob.enc -kfile /home/alice/secret.txt -out /home/alice/bobMessage.txt', shell=True)

        file = open("/home/alice/bobMessage.txt", "rb")
        ##printing out the message of bob for alice
        print("\nMessage from bob: ", (file.read(4096)).decode("utf-8"))
        file.close()

        print("\nEnter the message: ")

   
        

## This function will encode the message from user input and send it and also transfer files across
## chanel
def sendMsg(s):

    userInput = ''
    while userInput != 'exit':
        
        userInput = input("\nEnter the message: ")

        ##Writing alice message into a text file
        file = open("/home/alice/aliceMsg.txt", "wb")
        file.write(bytes(userInput, 'UTF-8'))
        file.close()
        
        #encrypting alice's message 
        subprocess.call('openssl enc -salt -aes-256-cbc -in /home/alice/aliceMsg.txt -kfile /home/alice/secret.txt -out /home/alice/encMsgAlice.enc', shell=True)

        file = open("/home/alice/encMsgAlice.enc", "rb")
        SendData = file.read(4096)
        s.send(SendData) #sending encrypted message to bob
        file.close()

    s.close()
    thread1.join()
    thread2.join()
   


if __name__ == '__main__':

    port = 12346 #connection port

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    s.connect(('127.0.0.1', port))

    #thread for receiving messages
    thread1 = threading.Thread(target = connect, args = ([s]))
    #thread for sending encoded messages
    thread2 = threading.Thread(target = sendMsg, args = ([s]))

    
    #starting the two threads
    thread1.start()
    thread2.start()
    # thread2.start()
    

