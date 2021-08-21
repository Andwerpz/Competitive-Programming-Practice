//package coffeeandcourseworkhardversion;

import java.util.*;
import java.io.*;

public class coffeeandcourseworkhardversion {
	
	public static boolean isValid(int val, int m, Long[] nums) {
		int pointer = nums.length - 1;
		int amt = (nums.length / val) + (nums.length % val != 0? 1 : 0);
		long sum = 0;
		outer:
		for(int i = 0; i < amt; i++) {
			for(int j = 0; j < val; j++) {
				sum += Math.max(nums[pointer] - i, 0L);
				pointer --;
				if(pointer == -1) {
					break outer;
				}
			}
		}
		if(sum >= m) {
			return true;
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1118D2
		
		//nevermind, what i said in the easy version was false. At least empirically.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		Long[] nums = new Long[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Long.parseLong(st.nextToken());
		}
		Arrays.sort(nums);
		int high = n;
		int low = 1;
		int mid = low + (high - low) / 2;
		int ans = -1;
		while(low <= high) {
			if(isValid(mid, m, nums)) {
				if(ans == -1) {
					ans = mid;
				}
				ans = Math.min(ans, mid);
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(ans);
	}
}
