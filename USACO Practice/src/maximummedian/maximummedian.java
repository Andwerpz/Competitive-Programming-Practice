//package maximummedian;

import java.util.*;
import java.io.*;

public class maximummedian {
	
	static int[] nums;
	
	public static boolean isValid(int num, long k) {
		long sum = 0;
		for(int i = nums.length / 2; i < nums.length; i++) {
			if(nums[i] < num) {
				sum += num - nums[i];
			}
		}
		return k >= sum;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long k = Integer.parseInt(st.nextToken());
		nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(nums);
		int high = Integer.MAX_VALUE - 1;
		int low = 0;
		int mid = low + (high - low) / 2;
		int ans = low;
		while(low <= high) {
			//System.out.print(mid);
			if(isValid(mid, k)) {
				//System.out.println(" is valid");
				if(mid > ans) {
					ans = mid;
				}
				low = mid + 1;
			}
			else {
				//System.out.println(" invalid");
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(ans);
	}
}
