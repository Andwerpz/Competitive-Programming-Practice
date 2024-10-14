#CSES - 1662

#copy paste from chatgpt lol

def count_subarrays_divisible_by_n(arr, n):
    # Initialize variables
    prefix_sum = 0
    count = 0
    mod_count = [0] * n
    mod_count[0] = 1  # To count subarrays starting from index 0

    # Iterate over the array
    for num in arr:
        # Calculate the prefix sum and modulo n
        prefix_sum = (prefix_sum + num) % n
        # Handle negative mod results
        prefix_sum = (prefix_sum + n) % n
        
        # Increment the count by the number of previous subarrays
        # which have the same modulo
        count += mod_count[prefix_sum]
        
        # Increase the count of the current modulo value
        mod_count[prefix_sum] += 1

    return count

# Input reading
n = int(input())
arr = list(map(int, input().split()))

# Output the result
print(count_subarrays_divisible_by_n(arr, n))