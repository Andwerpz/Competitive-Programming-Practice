//package unmerge;

import java.util.*;
import java.io.*;

public class unmerge {
	public static void main(String[] args) throws IOException {
		
		//1381B
		
		//this is a 0/1 knapsack problem, just disguised a little bit. The key is to notice that you can only switch over to the other array when you reach a pfx maximum
		//in the array going left to right. Then, all you have to do is record the length of each segment, and see if you can add them up to make n.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			int max = 0;
			int counter = 0;
			ArrayList<Integer> values = new ArrayList<Integer>();
			for(int i = 0; i < n * 2; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(next > max) {
					max = next;
					if(i != 0) {
						values.add(counter);
					}
					counter = 0;
				}
				counter ++;
			}
			values.add(counter);
			//System.out.println(values);
			boolean[] dp = new boolean[n + 1];
			dp[0] = true;
			for(int i = 0; i < values.size(); i++) {
				int next = values.get(i);
				for(int j = dp.length - 1; j >= 0; j--) {
					if(dp[j] && j + next <= n) {
						dp[j + next] = true;
					}
				}
			}
			fout.append(dp[n]? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}	
