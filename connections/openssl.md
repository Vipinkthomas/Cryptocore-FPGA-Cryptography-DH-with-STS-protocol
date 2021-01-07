```
openssl genrsa -aes256 -out ca.key 2048
openssl req -new -x509 -days 7300 -key ca.key -sha256 -extensions v3_ca -out ca.crt
openssl genrsa -out alice.key 2048
openssl req -sha256 -new -key alice.key -out alice.csr
openssl x509 -sha256 -req -in alice.csr -CA  /home/alice/rootCA/ca.crt -CAkey  /home/alice/rootCA/ca.key -CAcreateserial -out alice.crt -days 7300

openssl dgst -sha256 -sign alice.key -out sign.sha256 cAlice.txt
openssl enc -base64 -in sign.sha256 -out sign.sha256.base64

openssl rsa -noout -modulus -in alice.key | openssl md5
openssl x509 -noout -modulus -in alice.crt | openssl md5

openssl rsa -in alice.key -outform PEM -pubout -out alice_pub.key

openssl enc -salt -aes-256-cbc -in sign.sha256.base64 -kfile test.txt -out secret.enc
openssl enc -d -salt -aes-256-cbc -in secret.enc -kfile test.txt -out secret.txt

**Other side**

openssl enc -base64 -d -in sign.sha256.base64 -out sign.sha256
openssl dgst -sha256 -verify pubkey.pem -signature sign.sha256 test.txt


```

**Reference:**

```
*test.txt : K value (k.txt)*
*sign.sha256.base64 : signed value of (CBob,CAlice)*
```

> openssl rsautl -encrypt -inkey "publickey" -pubin -in sign.sha256.base64 -out sign.sha256.base64.enc

> openssl rsautl -decrypt -inkey "privatekey" -in sign.sha256.base64.enc -out sign.sha256.base64.enc

>openssl rand -base64 32 > key.bin

>openssl rsautl -encrypt -inkey alice_pub.key -pubin -in key.bin -out key.bin.enc

>openssl enc -aes-256-cbc -salt -in sign.sha256.base64 -out SECRET_FILE.enc -pass file:./key.bin

>openssl enc -d -salt -aes-256-cbc -in secret.enc -kfile test.txt -out secret.txt

