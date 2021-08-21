//package strangebeauty;

import java.util.*;
import java.io.*;

public class strangebeauty {
	public static void main(String[] args) throws IOException {
		
		//1475G
		
		//notice that if an array is beautiful, you can pick all the items in the array by first picking the smallest value, and then picking the lowest value in the array that is a multiple of that value.
		//repeat. It follows that if you want to remove as few items as possible, you need to create the largest beautiful array from the items that you have, and then remove everything else.
		//To get the largest, you can do a simple dp solution. For each value, update all values that are multiples of that value. The largest is naturally the maximum value in the dp array.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] dp = new int[200001];
			int[] repeats = new int[200001];
			int numOnes = 0;
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(next == 1) {
					numOnes ++;
				}
				else {
					dp[next] ++;
					repeats[next] ++;
				}
			}
			int ans = 0;
			for(int i = 0; i < dp.length; i++) {
				if(dp[i] != 0) {
					for(int j = i * 2; j < dp.length; j += i) {
						if(dp[j] != 0) {
							dp[j] = Math.max(dp[j], repeats[j] + dp[i]);
						}
					}
					ans = Math.max(ans, dp[i]);
				}
				//System.out.print(dp[i] + " ");
			}
			//System.out.println();
			fout.append(n - (ans + numOnes)).append("\n");
		}
		System.out.print(fout);
	}
}
