//package setordecrease;

import java.util.*;
import java.io.*;

public class setordecrease {
	
	public static boolean isValid(long val, Long[] nums, long k) {
		long sum = 0;
		long min = nums[nums.length - 1];
		for(int i = 0; i < nums.length - 1; i++) {
			sum += nums[i];
		}
		if(val > nums.length - 1) {
			min -= (val - (nums.length - 1));
			val = nums.length - 1;
		}
		for(int i = 0; i < val; i++) {
			sum -= (nums[i] - min);
		}
		if(sum + min <= k) {
			return true;
		}
		for(int i = (int) val - 1; i >= 0; i--) {
			sum += nums[i] - min;
			sum -= i;
			min --;
			if(sum + min <= k) {
				return true;
			}
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1622C
		
		//binary search through the amount of moves required.
		
		//for each amount of moves, brute force the minimum sum that you can reach.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			long k = Long.parseLong(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			Long[] nums = new Long[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Long.parseLong(st.nextToken());
			}
			Arrays.sort(nums, (a, b) -> -Long.compare(a, b));
			long ans = Long.MAX_VALUE / 2;
			long high = ans;
			long low = 0;
			long mid = low + (high - low) / 2;
			while(low <= high) {
				if(isValid(mid, nums, k)) {
					ans = Math.min(ans, mid);
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
				mid = low + (high - low) / 2;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
