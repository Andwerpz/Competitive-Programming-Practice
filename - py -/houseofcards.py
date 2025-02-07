#Kattis - houseofcards

#just keep incrementing h0 until you find some pyramid that's divisible by 4. 

h0 = int(input())
while True:
    amt = h0 * (h0 + 1) // 2
    amt *= 3
    amt -= h0
    if(amt % 4 == 0):
        break
    h0 += 1
print(h0)