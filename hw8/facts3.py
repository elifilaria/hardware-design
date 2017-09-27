# print square roots in Python language.  R. Brown, 9/2

print("n\tn!\n----------------")

def factorial(i):
    global ans
    if i==0:
        return 1
    else:
        ans = ans*i
        return ans

ans=1

for n in range(0, 6):
    print(n,'\t', factorial(n))
