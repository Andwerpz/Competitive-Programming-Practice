//package ezzatandtwosubsequences;

import java.util.*;
import java.io.*;

public class ezzatandtwosubsequences {
	public static void main(String[] args) throws IOException {
		
		//1557A
		
		//put the largest number into a, and the rest into b. If you transfer the largest number from b to a, you decrease the values of both a and b, so this has to be the optimal solution.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			double[] nums = new double[n];
			double max = Integer.MIN_VALUE;
			double maxIndex = -1;
			for(int i = 0; i < n; i++) {
				nums[i] = Double.parseDouble(st.nextToken());
				if(nums[i] > max) {
					max = nums[i];
					maxIndex = i;
				}
			}
			double ans = 0;
			for(int i = 0; i < n; i++) {
				if(i != maxIndex) {
					ans += nums[i] / (n - 1);
				}
			}
			ans += max;
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
