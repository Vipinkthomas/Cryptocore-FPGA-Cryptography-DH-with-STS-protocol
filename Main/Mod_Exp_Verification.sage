file = open("/home/alice/e.txt", "rb")
e = file.read(4096)
e = '0x' + e.replace(',','')
e_integer = int(e, 16)
e_hex = hex(e_integer).rstrip("L")
print(e_hex)
file.close()
###################
file = open("/home/data_user/b.txt", "rb")
b = file.read(4096)
b = b.replace('0x','')
b = '0x' + b.replace(',','')
b_integer = int(b, 16)
b_hex = hex(b_integer).rstrip("L")
print(b_hex)
file.close()
##################3
file = open("/home/data_user/n.txt", "rb")
n = file.read(4096)
n = n.replace('0x','')
n = '0x' + n.replace(',','')
n_integer = int(n, 16)
n_hex = hex(n_integer).rstrip("L")
print(n_hex)
file.close()
##########################################
prec = 4096



def Prime_ModExp(b,e,n,prec):
 
	x = (1) % int(n)
	exp = int(e)
	for i in reversed(xrange(prec)):
		x = (int(x) * int(x)) % int(n)
		if(Integer(exp).digits(base=2,padto=prec)[i] == 1):
			x = (int(b) * int(x)) % int(n)
	c = x

	return(c)
Prime_ModExp(b_hex,e_hex,n_hex,prec)
