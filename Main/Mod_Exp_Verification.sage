file = open("/home/alice/e.txt", "rb")
e = file.read(4096)
e = e.replace(',','')
file.close()
###################
file = open("/home/data_user/b.txt", "rb")
b = file.read(4096)
print(b)
file.close()
##################3
file = open("/home/data_user/n.txt", "rb")
n = file.read(4096)
print(n)
file.close()
##########################################

print(e)
print('\n')
print(b)
print('\n')
print(n)
print('\n')


def Prime_ModExp(b,e,n,prec):
 
	x = (1) % n
	exp = e
	for i in reversed(xrange(prec)):
		x = (x * x) % n
		if(Integer(exp).digits(base=2,padto=prec)[i] == 1):
			x = (b * x) % n
	c = x

	return(c)
