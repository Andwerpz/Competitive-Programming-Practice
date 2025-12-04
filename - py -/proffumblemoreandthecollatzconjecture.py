
#ECNA 2023 - E

# not good at math, so just look through first 1000 powers of 2 to find an answer. 

def ispow2(x):
    while(x != 1):
        if(x % 2):
            return False
        x //= 2
    return True

def sim_backwards(start, s):
    for _ in range(len(s)):
        i = len(s) - 1 - _
        if(s[i] == 'O' and (start % 2) == 0) :
            return -1
        if(s[i] == 'E' and (start % 2) == 1) :
            return -1
        if(s[i - 1] == 'O'):
            if(start == 1) :
                return -1
        else :
            if(ispow2(start)) :
                return -1
        if(i != 0) :
            if(s[i - 1] == 'O'):
                if((start - 1) % 3 != 0) :
                    return -1
                start = (start - 1) // 3
            else :
                start *= 2
    return start

s = input()
n = len(s)
if(s[n - 1] != 'O'):
    print("INVALID")
    exit(0)
for i in range(n):
    if(s[i] != 'E' and s[i] != 'O'):
        print("INVALID")
        exit(0)
for i in range(n - 1):
    if(s[i] == 'O' and s[i + 1] == 'O'):
        print("INVALID")
        exit(0)
s = s + "E"

ans = -1
start = 1
for i in range(1000):
    cur = sim_backwards(start, s)
    if(cur != -1) :
        if ans == -1:
            ans = cur
        ans = min(ans, cur)
    start *= 2

print(ans)
