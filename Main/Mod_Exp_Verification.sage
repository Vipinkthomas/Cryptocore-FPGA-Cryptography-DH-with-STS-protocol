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
e = e.replace('0x','')
e = e.replace(',','')
e_hex = hex(e_integer).rstrip("L")
print(e_hex)
file.close()
###################
file = open("/home/data_user/b.txt", "rb")
b = file.read(4096)
b = b.replace('0x','')
b = b.replace(',','')
b_hex = hex(b_integer).rstrip("L")
print(b_hex)
file.close()
##################
file = open("/home/data_user/n.txt", "rb")
n = file.read(4096)
n = n.replace('0x','')
n = n.replace(',','')
n_hex = hex(n_integer).rstrip("L")
print(n_hex)
file.close()
##########################################
prec = 4096
print(type(n_hex))
Prime_ModExp(hex(b_hex),hex(e_hex),hex(n_hex),4096)
##########################################
file = open("/home/bob/cAlice.txt", "rb")
cAlice = file.read(4096)
cAlice =n.replace(',','')
cAlice_hex = hex(n_integer).rstrip("L")
print(cAlice_hex)
file.close()
##########################################
Prime_ModExp(hex(cAlice_hex),hex(e_hex),hex(n_hex),4096)
