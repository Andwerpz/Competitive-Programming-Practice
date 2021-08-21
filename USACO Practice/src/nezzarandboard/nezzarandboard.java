//package nezzarandboard;

import java.util.*;
import java.io.*;

public class nezzarandboard {
	
	public static long gcd(long a, long b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1477A
		
		//consider the case where you only have 2 numbers on the board, for example: 1, 3. Clearly, you can make every number from -infinity to +infinity in intervals of 2, with 1 and 3 in the set.
		//Notice that if you start with two numbers with a gap of 4, then you can only make every 4th number, and if they start with a gap of 1, then you can make every number. Now take a look
		//at the case with three starting numbers. Now, you can see that the interval is going to be the gcd of the three gaps, 1 -> 2, 2 -> 3, 3 -> 1. But you don't have to check every gap, if you 
		//sort the numbers then just checking 1 -> 2, and 2 -> 3 should be sufficient. If (k - nums[0]) % interval == 0, then you can make k.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			long k = Long.parseLong(st.nextToken());
			Long[] nums = new Long[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Long.parseLong(st.nextToken());
			}
			Arrays.sort(nums);
			long interval = nums[1] - nums[0];
			for(int i = 0; i < n - 1; i++) {
				interval = gcd(interval, nums[i + 1] - nums[i]);
			}
			if(Math.abs(k - nums[0]) % interval == 0) {
				fout.append("YES\n");
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
