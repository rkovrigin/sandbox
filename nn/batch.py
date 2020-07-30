import math
import matplotlib.pyplot as plt
from time import sleep
from random import randint, randrange
import numpy as np


j = lambda x: x[0]*2 + x[1]*3 + randrange(-abs(200), abs(200)+1)

def f(x, t):
	return sum([_x * _t for _x, _t in zip(x, t)])

def grad(t, X, Y, alpha=0.01):
	n = 1000
	while n:
		for i in range(len(Y)):
			x = X[i]
			y = Y[i]
			z = sum([x[j] * t[j] for j in range(len(x))]) - y
			z = z / len(t)
			_t = [_x * z for _x in x]
			for i in range(len(t)):
				_t[i] = t[i] - (_t[i]*alpha) / len(t)
			if abs(sum(_t)) / len(X) < alpha/10:
				return t
			t = list(_t)
		n -= 1
	return t

def grad_m(t, X, Y, alpha=0.01):
	t = np.asarray(t)
	X = np.asarray(X)
	Y = np.asarray(Y)
	n = 1000
	while n:
		_t = (X@t - Y)*alpha/len(X)
		_t = np.asarray([_t])@X
		if abs(sum(_t[0])) / len(X) < alpha/10:
			break
		t = t - _t[0]
		n -= 1
	return t

N = 1000
R = [randint(-100, 100) for _ in range(N)]
X = [[1, i] for i in R]
Y = [j(i) for i in X]
t = grad([0, 0], X, Y, 0.00001)
_t = grad_m([0, 0], X, Y, 0.00001)
print(t)
print(_t)

plt.scatter(R, Y, label= "stars", marker= "*", color="blue", s=30)
plt.plot(R, [f([1, i], t) for i in R], label= "line", color="red")
plt.plot(R, [f([1, i], _t) for i in R], label= "line", color="green")

plt.legend()
plt.show()
