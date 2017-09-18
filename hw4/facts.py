# print square roots in Python language.  R. Brown, 9/2

print("n\tn!\n----------------")

def factorial(n):
    if n==0:
        return 1
    else:
        return n*factorial(n-1)

for n in range(0, 6):
    print(n,'\t', factorial(n))
