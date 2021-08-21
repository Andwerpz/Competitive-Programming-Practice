//package makeitequal;

import java.util.*;
import java.io.*;

public class makeitequal {
	
	public static int search(int val, Integer[] nums) {	//return number of values greater than or equal to given val.
		int low = 0;
		int high = nums.length - 1;
		int mid = low + (high - low) / 2;
		int ans = 0;
		while(low <= high) {
			if(nums[mid] >= val) {
				low = mid + 1;
				ans = Math.max(ans, mid + 1);
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1065C
		
		//every operation, you want to remove as many blocks as possible. To find out the cost per operation, just use binary search.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		Integer[] nums = new Integer[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(nums, (a, b) -> -Integer.compare(a, b));
		int ans = 0;
		int pointer = nums[0];
		int curCost = 0;
		while(true) {
			//System.out.println(pointer);
			int nextCost = search(pointer, nums);
			if(nextCost == n) {
				break;
			}
			if(curCost + nextCost > k) {
				ans ++;
				curCost = nextCost;
			}
			else {
				curCost += nextCost;
			}
			pointer --;
		}
		if(curCost != 0) {
			ans ++;
		}
		System.out.println(ans);
	}
}
