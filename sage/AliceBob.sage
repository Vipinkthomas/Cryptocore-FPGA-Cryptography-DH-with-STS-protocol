def Alice1(b,e1,n,prec):
	c1=Prime_ModExp(b,e1,n,prec)
	return(c1)
def Bob1(b,e2,n,prec):
	c2=Prime_ModExp(b,e2,n,prec)
	return(c2)
def Alice2(b,c2,n,prec):
	shared_key=Prime_ModExp(b,c2,n,prec)
	return(shared_key)

def Bob2(b,c1,n,prec):
	shared_key=Prime_ModExp(b,c1,n,prec)
	return(shared_key)


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
	try:
		q=(n-1)/2
		if Prime_ModExp(b,2*q,n,prec)==1:
			print("firststep")
			if Prime_ModExp(b,q,n,prec)!=1:
				print("secondstep")
				if Prime_ModExp(b,2,n,prec)!=1:
					return(b)
	except TypeError:
		print(TypeError)



    
