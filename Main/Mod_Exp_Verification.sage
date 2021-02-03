file = open("/home/alice/e.txt", "rb")
e = file.read(4096)
e = '0x' + e.replace(',','')
e_integer = int(e, 16)
e_hex = hex(e_integer)
print(e_hex)
file.close()
###################
file = open("/home/data_user/b.txt", "rb")
b = file.read(4096)
b = b.replace('0x','')
b = '0x' + b.replace(',','')
b_integer = int(b, 16)
b_hex = hex(b_integer)
print(b_hex)
file.close()
##################3
file = open("/home/data_user/n.txt", "rb")
n = file.read(4096)
n = n.replace('0x','')
n = '0x' + n.replace(',','')
n_integer = int(n, 16)
n_hex = hex(n_integer)
print(n)
file.close()
##########################################
prec = 4096



def Prime_ModExp(b,e,n,prec):
 
	x = (1) % n
	exp = e
	for i in reversed(xrange(prec)):
		x = (x * x) % n
		if(Integer(exp).digits(base=2,padto=prec)[i] == 1):
			x = (b * x) % n
	c = x

	return(hex(c))
#Prime_ModExp(b,e,n,prec)
