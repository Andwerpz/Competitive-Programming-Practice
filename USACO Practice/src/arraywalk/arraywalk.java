//package arraywalk;

import java.util.*;
import java.io.*;

public class arraywalk {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int z = Integer.parseInt(st.nextToken());
			int ans = 0;
			int[] nums = new int[n];
			int[] pfx = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				if(i == 0) {
					pfx[i] = nums[i];
				}
				else {
					pfx[i] = pfx[i - 1] + nums[i];
				}
			}
			int curSum = nums[0];
			int remaining = k;
			for(int i = 1; i < Math.min(n, k + 1); i++) {
				
				curSum += nums[i];
				remaining --;
				//System.out.println("index " + i + " " + curSum);
				int cur = curSum;
				if(remaining > 0) {
					int movesRemaining = remaining;
					//System.out.println("moves remaining " + movesRemaining);
					if(movesRemaining >= z * 2) {
						movesRemaining -= z * 2;
						cur += (nums[i] + nums[i - 1]) * z;
					}
					else {
						int base = movesRemaining / 2;
						int remainder = movesRemaining % 2;
						cur += (nums[i] + nums[i - 1]) * base + nums[i - 1] * remainder;
						movesRemaining = 0;
					}
					int end = Math.min(i + movesRemaining, n - 1);
					cur += pfx[end] - pfx[i];
				}
				//System.out.println("cur " + cur);
				if(cur > ans) {
					ans = cur;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}	
