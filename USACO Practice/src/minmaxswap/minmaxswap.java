//package minmaxswap;

import java.util.*;
import java.io.*;

public class minmaxswap {
	public static void main(String[] args) throws IOException {
		
		//1631A
		
		//my instinct tells me that we want to minimize one array, and maximize another array. 
		//turns out my instinct is correct.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int a = 0;
			int b = 0;
			int n = Integer.parseInt(fin.readLine());
			int[][] nums = new int[n][2];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i][0] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i][1] = Integer.parseInt(st.nextToken());
				a = Math.max(a, Math.min(nums[i][0], nums[i][1]));
				b = Math.max(b, Math.max(nums[i][0], nums[i][1]));
			}
			fout.append(a * b).append("\n");
		}
		System.out.print(fout);
	}
}
