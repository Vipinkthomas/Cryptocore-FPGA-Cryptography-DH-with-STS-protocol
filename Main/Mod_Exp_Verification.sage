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
file = open("/home/bob/e.txt", "rb")
e = file.read(4096)
e = '0x'+e.replace(',','')
e = e.replace('\n','')
print(e)
file.close()
###################
file = open("/home/data_user/b.txt", "rb")
b = file.read(4096)
b = b.replace('0x','')
b ='0x'+ b.replace(',','')
b = b.replace('\n','')
print(b)
file.close()
##################
file = open("/home/data_user/n.txt", "rb")
n = file.read(4096)
n = n.replace('0x','')
n ='0x'+ n.replace(',','')
n = n.replace('\n','')
print(n)
file.close()
##########################################
file = open("/home/bob/cAlice.txt", "rb")
cAlice = file.read(4096)
cAlice ='0x'+cAlice.replace(',','')
cAlice = cAlice.replace('\n','')
print(cAlice)
file.close()
##########################################
prec = 4096
Prime_ModExp(hex(b),hex(e),hex(n),4096)

##########################################
Prime_ModExp(hex(cAlice),hex(e),hex(n),4096)
