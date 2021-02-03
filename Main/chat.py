import subprocess
import socket
import threading

## This function will encode the message from user input and send it
def connect(s):
    '''receive messages from other party, and decode them'''

    while True:
        received = s.recv(4096)
        
        file = open("/home/bob/encMsgAlice.enc", "wb")
        file.write(received)
        file.close()

        subprocess.call('openssl enc -d -salt -aes-256-cbc -in /home/bob/encMsgAlice.enc -kfile /home/bob/secret.txt -out /home/bob/aliceMessage.txt', shell=True)

        file = open("/home/bob/aliceMessage.txt", "rb")
        message = file.read(4096)
        print("\nMessage from Alice: " , message.decode("utf-8"))
        file.close()

        print("\nEnter the message: ")
        

    

## This function will encode the message from user input and send it and also transfer files across
## chanel
def sendMsg(s):

    userInput = ''
    while userInput != 'exit':
        
        userInput = input("\nEnter the message: ")

        file = open("/home/bob/bobMsg.txt", "wb")
        file.write(bytes(userInput, 'UTF-8'))
        file.close()
        
        subprocess.call('openssl enc -salt -aes-256-cbc -in /home/bob/bobMsg.txt -kfile /home/bob/secret.txt -out /home/bob/encMsgBob.enc', shell=True)

        
            
        file = open("/home/bob/encMsgBob.enc", "rb")
        SendData = file.read(4096)
        s.send(SendData)
        file.close()
    
    s.close()
    thread1.join()
    thread2.join()
    



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
    #thread for sending encoded messages
    thread2 = threading.Thread(target = sendMsg, args = ([conn]))
    
    thread1.start()
    thread2.start()
    

