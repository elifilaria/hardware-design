def factorial(n):
	if n==0:
		return 1
	else:
		return n*factorial(n-1)

print(factorial(10))

if (factorial(10) == 3628800):
	print("Indeed 10! is 3628800")