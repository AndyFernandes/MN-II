from math import abs

def function(float var):
	return var


def Integral(float a, float b, float tolerancia):
	Ic = Ia = 0.0
	n = 1
	parte = 0
	
	while (tolerancia < abs(Ic - Ia)/ Ic):
		deltaX = (b - a) / n
		Ia = Ic

		while (parte < n):
			xpart = a + deltaX/2 + parte * deltaX
			Ic += deltaX * function(xpart)
			parte += 1
	
		n *= 2
	return Ic