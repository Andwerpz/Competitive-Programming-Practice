#Kattis - zebrasocelots

#~i = -(i + 1)

# b=input
# n,a=int(b()),0
# for i in range(n):a+=(b()=="O")<<n+~i
# print(a)

#use sum() to get rid of a=0, and print(a)
#63 chr

b=input
n=int(b())
print(sum((b()=="O")<<n+~i for i in range(n)))