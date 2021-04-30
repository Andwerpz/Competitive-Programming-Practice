//package andsequences;

import java.util.*;
import java.io.*;

public class andsequences {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		int mod = 1000000007;
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int min = Integer.MAX_VALUE;
			for(int i = 0; i < n; i++) {
				if(min > nums[i]) {
					min = nums[i];
				}
			}
			boolean isValid = true;
			int count = 0;
			for(int i = 0; i < n; i++) {
				if(min == nums[i]) {
					count++;
				}
				if((min & nums[i]) != min) {
					isValid = false;
					break;
				}
			}
			//System.out.println(min + " " + count);
			if(!isValid) {
				fout.append("0\n");
				continue;
			}
			int fact = 1;
			for(int i = 1; i <= n - 2; i++) {
				fact = (int) (((long) 1 * fact * i) % mod);
			}
			int ans = (int) (((long) 1 * count * (count - 1)) % mod);
			ans = (int) (((long) 1 * ans * fact) % mod);
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
