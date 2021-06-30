//package arraysplitting;

import java.util.*;
import java.io.*;

public class arraysplitting {
	public static void main(String[] args) throws IOException {
		
		//you have to split the array into k subarrays. The cost of each subarray is equal to the maximum minus the minimum in the subarray. 
		//so the main priority when choosing subarrays is to choose subarrays that minimize the gaps between numbers within the subarray. 
		//so, if we just eliminate the first k - 1 gaps in the array, then we arrive at our minimum answer.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[] nums = new int[n];
		int[] gaps = new int[n - 1];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			if(i != 0) {
				gaps[i - 1] = nums[i] - nums[i - 1];
			}
		}
		Arrays.sort(gaps);
		int ans = nums[n - 1] - nums[0];
		for(int i = n - 2; i >= n - (k); i--) {
			ans -= gaps[i];
			//System.out.println(gaps[i]);
		}
		System.out.println(ans);
	}
}
