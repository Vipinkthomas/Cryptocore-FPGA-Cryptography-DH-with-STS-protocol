openssl genrsa -out /home/bob/bob.key 2048
openssl req -sha256 -new -key /home/bob/bob.key -out /home/bob/bob.csr
openssl x509 -sha256 -req -in /home/bob/bob.csr -CA  /home/data_user/rootCA/ca.crt -CAkey  /home/data_user/rootCA/ca.key -CAcreateserial -out /home/bob/bob.crt -days 7300
