def Prime_ModExp(b,e,n,prec):
 
	x = (1) % n
	exp = e
	for i in reversed(xrange(prec)):
		x = (x * x) % n
		if(Integer(exp).digits(base=2,padto=prec)[i] == 1):
			x = (b * x) % n
	c = x

	return(c)

def generatorValid(b,n,prec,e):
	try:
		q=(b-1)
		if Prime_ModExp(b,q,n,prec)!=0x1:
			if Prime_ModExp(b,2,n,prec)!=0x1:
				return(b)
	except TypeError:
		print(TypeError)
