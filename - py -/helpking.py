from fractions import Fraction

# Codeforces - 98B

# bruh, should've asked to output the answer under mod or smth

def main():
    n = int(input())
    
    # Find cycle
    s = set()
    S = [1]
    ST = []
    C = []
    
    A = []
    B = []
    E = []
    
    while True:
        cur = S[-1]
        cnt = 0
        s.add(cur)
        while cur < n:
            cur *= 2
            cnt += 1
        ST.append(cur)
        C.append(cnt)
        cur %= n
        S.append(cur)
        A.append(Fraction(1) - Fraction(n, ST[-1]))
        B.append(C[-1])
        E.append(Fraction(0))
        
        if cur in s or cur == 0:
            break
    
    # for i in range(len(ST)):
    #     print(S[i], C[i], ST[i])
    
    # for i in range(len(ST)):
    #     print(f"E[{S[i]}] = {A[i]} E[{S[i + 1]}] + {B[i]}")
    
    # Close the cycle
    if S[-1] != 0:
        last = S.pop()
        while S[-1] != last:
            i = len(S) - 1
            na = A[i - 1] * A[i]
            nb = A[i - 1] * B[i] + B[i - 1]
            A[i - 1] = na
            B[i - 1] = nb
            S.pop()
            ST.pop()
            C.pop()
            A.pop()
            B.pop()
            E.pop()
        
        # print("CLOSE CYCLE :", B[-1] / (1 - A[-1]))
        E[-1] = B[-1] / (1 - A[-1])
    else:
        E[-1] = C[-1]  # E[0] = 0, E[2^C] = C
    
    # Compute everything else
    for i in range(len(E) - 2, -1, -1):
        E[i] = A[i] * E[i + 1] + B[i]
    
    print(E[0].numerator, "/", E[0].denominator, sep="")

if __name__ == "__main__":
    main()