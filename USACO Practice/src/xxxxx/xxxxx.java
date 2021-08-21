//package xxxxx;

import java.util.*;
import java.io.*;

public class xxxxx {
	public static void main(String[] args) throws IOException {
		
		//1364A
		
		//first to check whether the array is valid, make a pfx sum mod array. If all entries are 0, then the input is invalid.
		
		//if the input is valid, and if the last entry isn't 0, then the entire array is the ans.
		
		//else, then we know that the first entry is 0. Find the first entry that isn't zero, and the last entry that isn't zero. From there, we can easily find two answers, and take the maximum out of them.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			int[] nums = new int[n];
			st = new StringTokenizer(fin.readLine());
			boolean isValid = false;
			int firstNotZero = -1;
			int lastNotZero = -1;
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken()) % x;
				if(i != 0) {
					nums[i] += nums[i - 1];
					nums[i] %= x;
				}
				if(nums[i] != 0) {
					if(!isValid) {
						firstNotZero = i;
						isValid = true;
					}
					lastNotZero = i;
				}
			}
			if(isValid) {
				int ans = 0;
				if(nums[n - 1] != 0) {
					ans = n;
				}
				else {
					ans = Math.max(n - firstNotZero - 1, lastNotZero + 1);
				}
				fout.append(ans).append("\n");
			}
			else {
				fout.append("-1\n");
			}
		}
		System.out.print(fout);
	}
}
