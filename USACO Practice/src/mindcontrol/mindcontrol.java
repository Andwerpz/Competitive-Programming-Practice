//package mindcontrol;

import java.util.*;
import java.io.*;

public class mindcontrol {
	public static void main(String[] args) throws IOException {
		
		//1290A
		
		//notice that the order of mind controlled vs uncontrolled person doesn't matter, all their effects are additive. What you can do is for each configuration of mind controlled
		//person, find out the minimum number that you are guaranteed to get. Take the maximum out of all configurations.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int controlled = Math.min(m - 1, k);
			int uncontrolled = m - 1 - controlled;
			int[] nums = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int ans = 0;
			int initL = controlled;
			int initR = n - 1;
			while(initL >= 0) {
				int curAns = Integer.MAX_VALUE;
				int l = initL + uncontrolled;
				int r = initR;
				while(l >= initL) {
					curAns = Math.min(Math.max(nums[l], nums[r]), curAns);
					l --;
					r --;
				}
				ans = Math.max(curAns, ans);
				initL --;
				initR --;
			}
			
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
