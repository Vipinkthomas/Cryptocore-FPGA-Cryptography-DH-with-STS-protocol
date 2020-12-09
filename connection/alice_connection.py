import socket
import threading

if __name__ == '__main__':

    HOST = '127.0.0.1'  # address (localhost)
    PORT = 12345        # Port to listen on

    #creating new socket
    alice_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    alice_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    #binding address (hostname, port number) to alice_socket
    alice_socket.bind((HOST, PORT))

    #sets up and start TCP listener
    alice_socket.listen()

    #Establish connection with other party( BOB ).
    (conn, addr) = s.accept() 

    #creating two threads (one for connection and one for sending messages)
    thread1 = threading.Thread(target = connect, args = ([conn]))
    thread2 = threading.Thread(target = sendMsg, args = ([conn]))

    #starting the two threads
    thread1.start()
    thread2.start()
    
    #join the two threads
    thread1.join()
    thread2.join()
    
