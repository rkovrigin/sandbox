import math
import matplotlib.pyplot as plt
from time import sleep
from random import randint, randrange


j = lambda x: x[0]*2 + x[1]*3 + randrange(-100000, 100000) / randrange(1, 10) + x[2]*17

def f(x, t):
	return sum([_x * _t for _x, _t in zip(x, t)])

def grad(t, X, Y, alpha=0.01):
	for i in range(len(Y)):
		x = X[i]
		y = Y[i]
		z = sum([x[j] * t[j] for j in range(len(x))]) - y
		z = z / len(t)
		_t = [_x*z for _x in x]
		for i in range(len(t)):
			#add checking for convergence
			t[i] = t[i] - _t[i]*alpha
	print(t)
	return t

N = 100
X = [[1, i, i**2] for i in range(1, N)]
Y = [j(i) for i in X]
t = grad([0, 0, 0], X, Y, 0.00000001)

plt.scatter(range(1, N), Y, label= "stars", marker= "*", color="blue", s=30)
plt.plot(range(1, N), [f([1, i, i**2], t) for i in range(1,N)], label= "line", color="red")

plt.legend()
plt.show()
