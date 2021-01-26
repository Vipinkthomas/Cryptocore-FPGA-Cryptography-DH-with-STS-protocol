openssl x509 -pubkey -noout -in /home/bob/alice.crt  > /home/bob/pubkeyAlice.pem
openssl enc -d -salt -aes-256-cbc -in /home/bob/signatureAlice.enc -kfile /home/bob/secret.txt -out /home/bob/signatureAlice.base64
openssl enc -base64 -d -in /home/bob/signatureAlice.base64 -out /home/bob/signatureAlice.sha256
openssl dgst -sha256 -verify /home/bob/pubkeyAlice.pem -signature /home/bob/signatureAlice.sha256 /home/bob/cAliceBob.txt
openssl verify -CAfile /home/data_user/rootCA/ca.crt /home/bob/alice.crt
