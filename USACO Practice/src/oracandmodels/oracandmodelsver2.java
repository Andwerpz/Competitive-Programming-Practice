package oracandmodels;

import java.util.*;
import java.io.*;

public class oracandmodelsver2 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int[] dp = new int[n];	//stores the lowest ending value for the sequence ending on i numbers
			Arrays.fill(dp, -1);
			for(int i = 0; i < n; i++) {
				int next = nums[i];
				for(int j = 0; j < n; j++) {
					
				}
			}
		}
	}
}
