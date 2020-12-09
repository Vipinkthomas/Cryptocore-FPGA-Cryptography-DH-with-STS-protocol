import socket
import threading

def connect(conn):
    '''receive messages from other party, and decode them'''
    
    while True:
        #encoded received message
        received = conn.recv(4096)

        if received ==' ':
            pass

        elif received.decode() == 'pubk':
            ## if string message pubk received, alice will create a new file and write the pubk to pubkey.pem file
            ## which will later use it to decrypt the signature
            file = open("pubkey.pem", "wb")
            RecvData = conn.recv(4096)
            file.write(RecvData)
            file.close()

        elif received.decode() == 'cert':
            ## if string message cert received, alice will create a new file and write the certificate to Certificate.crt file
            ## which will use it to verify the sender
            file = open("Certificate.crt", "wb")
            RecvData = conn.recv(4096)
            file.write(RecvData)
            file.close()

        elif received.decode() == 'encMsg':
            ## if string message encMsg received, alice will create a new file and write the signature to 
            # sign.sha256.base64 file
            ## this file will be decrypted and check if it matches with the hashing value of the original message
            file = open("sign.sha256.base64", "wb")
            RecvData = conn.recv(4096)
            file.write(RecvData)
            file.close()

        elif received.decode() == 'msg':
            ## if string message msg received, alice will create a new file and write the message to msg.txt file
            ## This is the original message
            file = open("msg.txt", "wb")
            RecvData = conn.recv(4096)
            file.write(RecvData)
            file.close()

        else:
            print(received.decode())


def send_msg(conn):
    ## This function will encode the message from user input and send it
    while True:
        msg = input().encode()
        if msg == ' ':
            pass
        else:
            conn.sendall(msg)


if __name__ == '__main__':

    HOST = '127.0.0.1'  # address (localhost)
    PORT = 12345        # Port to listen on

    #creating new socket
    alice_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    alice_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    #binding address (hostname, port number) to alice_socket
    alice_socket.bind((HOST, PORT))

    #sets up and start TCP listener
    alice_socket.listen(5)

    #Establish connection with other party( BOB ).
    (conn, addr) = alice_socket.accept() 

    #creating two threads (one for connection and one for sending messages)
    thread1 = threading.Thread(target = connect, args = ([conn]))
    thread2 = threading.Thread(target = send_msg, args = ([conn]))

    #starting the two threads
    thread1.start()
    thread2.start()
    
    #join the two threads
    thread1.join()
    thread2.join()
    
