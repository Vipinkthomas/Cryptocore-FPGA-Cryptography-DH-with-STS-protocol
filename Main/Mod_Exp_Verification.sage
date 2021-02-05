def Prime_ModExp(b,e,n,prec):
 
	x = (1) % n
	exp = e
	for i in reversed(xrange(prec)):
		x = (x * x) % n
		if(Integer(exp).digits(base=2,padto=prec)[i] == 1):
			x = (b * x) % n
	c = x

	return(c)

###################
#####READING E ####
###################
file = open("/home/alice/e.txt", "rb")
e = file.read(4096)
e = '0x'+e.replace(',','')
e = e.replace('\n','')
e = Integer(e)
print("e: 0x"+ str(hex(e)))
file.close()

###################
#####READING B ####
###################
file = open("/home/data_user/b.txt", "rb")
b = file.read(4096)
b = b.replace('0x','')
b ='0x'+ b.replace(',','')
b = b.replace('\n','')
b = Integer(b)
print("\nb: 0x"+ str(hex(b)))
file.close()

###################
#####READING n ####
###################
file = open("/home/data_user/n.txt", "rb")
n = file.read(4096)
n = n.replace('0x','')
n ='0x'+ n.replace(',','')
n = n.replace('\n','')
n= Integer(n)
print("\nn: 0x"+ str(hex(n)))
file.close()

###################
#####READING cBob ####
###################
file = open("/home/alice/cBob.txt", "rb")
cBob = file.read(4096)
cBob ='0x'+cBob.replace(',','')
cBob = cBob.replace('\n','')
cBob= Integer(cBob)
print("\ncBob: 0x"+ str(hex(cBob)))
file.close()

###################
#Verifying cAlice #
###################
prec = 4096
cAlice = hex(Prime_ModExp(b,e,n,4096))
print("\ncAlice: 0x"+ str(cAlice))

###################
#Verifying secret #
###################
secret=hex(Prime_ModExp(cBob,e,n,4096))
print("\nShared Secret Key: 0x"+ str(secret))
