//package shorttask;

import java.util.*;
import java.io.*;

public class shorttaskver3 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int[] nums = new int[10000001];
		int[] ans = new int[10000001];
		for(int i = 2; i < nums.length; i++) {
			long val = i;
			for(int j = i; j < nums.length; j += i) {
				nums[j] += val;
			}
		}
		for(int i = 1; i < nums.length; i++) {
			int next = nums[i] + 1;
			if(next < ans.length && ans[next] == 0) {
				ans[next] = i;
			}
		}
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int c = Integer.parseInt(fin.readLine());
			if(ans[c] == 0) {
				fout.append("-1\n");
			}
			else {
				fout.append(ans[c]).append("\n");
			}
		}
		System.out.print(fout);
	}
}
