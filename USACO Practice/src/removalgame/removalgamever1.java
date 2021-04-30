package removalgame;

import java.util.*;
import java.io.*;

public class removalgamever1 {
	
	static long[] nums;
	
	public static long solve(int high, int low) {
		System.out.println(low + " " + high);
		if(high - low <= 1) {
			System.out.println("final num " + Math.max(nums[high], nums[low]));
			return Math.max(nums[high], nums[low]);
		}
		else {
			long ans = Long.MIN_VALUE + 1;
			if(high - 2 >= low) {
				System.out.println("add " + nums[high]);
				ans = solve(high - 2, low) + nums[high];
			}
			if(high - 1 >= low + 1) {
				System.out.println("add " + nums[high] + " " + nums[low]);
				ans = Math.max(solve(high - 1, low + 1) + nums[high], Math.max(solve(high - 1, low + 1) + nums[low], ans));
			}
			if(high >= low + 2) {
				System.out.println("add " + nums[low]);
				ans = Math.max(ans, solve(high, low + 2) + nums[low]);
			}
			System.out.println("pick " + ans);
			return ans;
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		//very slow and dumb recursive solution
		//doesn't even work :((
		//it doesn't simulate the optimized behaviour of the second player.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		nums = new long[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		System.out.println(solve(n - 1, 0));
	}
}
