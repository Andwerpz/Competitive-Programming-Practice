#NCPC 2024 - I

#python used !!

def binarystring_toint(x):
    res = 0
    for y in x:
        res = res * 2
        if y == '1':
            res = res + 1

    return res

s_bin = input()
d_bin = input()
m_bin = input()

s = binarystring_toint(s_bin)
d = binarystring_toint(d_bin)
m = binarystring_toint(m_bin)

day = 0

for i in range(1,1000000):

    if m == 0:
        # print(day)
        st = ""
        while day != 0:
            st += str(day & 1)
            day = day // 2
        res = ""
        for i in range(len(st)):
            res += st[len(st)-i-1]
        print(res)
        break

    m = m // 2
    if i > 0 and i % d == 0:
        m = m + s

    day = day + 1

if m != 0:
    print("Infinite money!")