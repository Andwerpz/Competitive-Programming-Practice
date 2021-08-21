//package maxmedian;

import java.util.*;
import java.io.*;

public class maxmedian {
	
	public static boolean isValid(int[] nums, int val, int k) {
		TreeSet<Integer> before = new TreeSet<Integer>();
		int sum = 0;
		int beforeSum = 0;
		for(int i = 0; i < k; i++) {
			if(nums[i] >= val) {
				sum ++;
			}
			else {
				sum --;
			}
		}
		before.add(0);
		if(sum > 0) {
			return true;
		}
		for(int i = k; i < nums.length; i++) {
			beforeSum += nums[i - k] >= val? 1 : -1;
			before.add(beforeSum);
			sum += nums[i] >= val? 1 : -1;
			if(before.floor(sum - 1) != null) {
				return true;
			}
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1486D
		
		//we can binary search for the answer. Testing whether the answer is greater than or equal to a given value can be achieved in O(n). 
		
		//To test, we can use a prefix sum. Given a value that we want to test, tranform the original array into 1s and -1s. 1 for values greater than or equal to the given value, and -1s for values less than. 
		//calculate the prefix sum of this new array.
		
		//for a given index i that is greater than k, if there is an index less than i - k that is less than the value stored at k, then we know that this median is valid. We know this because the net sum between those
		//two indicies must be positive, indicating that there were more values that were greater, than less than for that segment.
		
		//to check each index in constant time, we just have to keep track of the minimum prefix value that we have seen. If the current value is greater than the minimum prefix, then we have a valid segment.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int low = 0;
		int high = n;
		int ans = 0;
		int mid = low + (high - low) / 2;
		while(low <= high) {
			//System.out.println(mid);
			if(isValid(nums, mid, k)) {
				ans = Math.max(ans, mid);
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(ans);
	}
}
