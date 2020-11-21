def Prime_ModExp(b,e,n,prec):
	x = (1) % n
	exp = e
	for i in reversed(xrange(prec)):
		x = (x * x) % n
		if(Integer(exp).digits(base=2,padto=prec)[i] == 1):
			x = (b * x) % n
	c = x
	return(c)

def generatorValid(b,n,prec):
	for i in reversed(xrange(prec)):
		if i<=15:
			Integer(b).digits()[i]=0
		else:
			break
	try:
		q=(n-1)/2
		if Prime_ModExp(b,q,n,prec)!=1:
			print("secondstep")
			if Prime_ModExp(b,2,n,prec)!=1:
				return("\n generator"+ b)
	except TypeError:
		print(TypeError)
