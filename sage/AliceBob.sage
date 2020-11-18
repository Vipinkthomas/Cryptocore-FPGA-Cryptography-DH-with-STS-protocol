def Alice1(b,n,prec):
	e1=0x0ff8ee958b0897a44a4a38f34da713c368f7b7c880e2fbcdd0f50460e1e7471d5fd20690ea38c7a012a4075248bfae37690d523
	ca911ec8b249caad3094f2f51
	if generatorValid(b,e1,n,prec):
		c1=Prime_ModExp(b,e1,n,prec)
		return(c1)
def Bob1(b,n,prec):
	e2=0x0ff8ee958b0897a44a4a38f34da713c368f7b7c880e2fbcdd0f50460e1e7471d5fd20690ea38c7a012a4075248bfae37690d523
	ca911ec8b249caad3094f2f51
	if generatorValid(b,e2,n,prec):
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

def generatorValid(b,e,n,prec):
	try:
		q=(n-1)/2
		if Prime_ModExp(b,2*q,n,prec)==1:
			if Prime_ModExp(b,q,n,prec)!=1:
				if Prime_ModExp(b,2,n,prec)!=1:
					return(1)



    
