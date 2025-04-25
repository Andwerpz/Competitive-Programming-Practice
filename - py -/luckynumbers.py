
# Kattis - luckynumber

# 'first k digits' means first k digits from the left as if the number were a string, not first k least
# significant digits. 

# if you write a brute force, you'll notice that the number of lucky numbers first goes up, and then 
# goes back down to 0, so for n >= 30, the answer is simply 0. Actually the total amount of lucky numbers
# isn't too high, so you can just compute them all for each n. 

n = int(input())
a = [i for i in range(1, 10)]
for i in range(2, n + 1):
    b = []
    for x in a:
        x *= 10
        for d in range(0, 10):
            if((x + d) % i == 0):
                b.append(x + d)
    a = b
# print(a)
print(len(a))