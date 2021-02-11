openssl x509 -pubkey -noout -in /home/alice/bob.crt  > /home/alice/pubkeyBob.pem
openssl enc -d -salt -aes-256-cbc -in /home/alice/signatureBob.enc -kfile /home/alice/secret.txt -out /home/alice/signatureBob.base64
openssl enc -base64 -d -in /home/alice/signatureBob.base64 -out /home/alice/signatureBob.sha256
openssl dgst -sha256 -verify /home/alice/pubkeyBob.pem -signature /home/alice/signatureBob.sha256 /home/alice/cAliceBob.txt
openssl verify -CAfile /home/data_user/rootCA/ca.crt /home/alice/bob.crt
