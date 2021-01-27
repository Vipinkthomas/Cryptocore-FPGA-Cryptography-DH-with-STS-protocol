openssl genrsa -out /home/alice/alice.key 2048
openssl req -sha256 -new -key /home/alice/alice.key -out /home/alice/alice.csr
openssl x509 -sha256 -req -in /home/alice/alice.csr -CA  /home/data_user/rootCA/ca.crt -CAkey  /home/data_user/rootCA/ca.key -CAcreateserial -out /home/alice/alice.crt -days 7300
