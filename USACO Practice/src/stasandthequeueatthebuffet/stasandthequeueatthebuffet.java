//package stasandthequeueatthebuffet;

import java.util.*;
import java.io.*;

public class stasandthequeueatthebuffet {
	public static void main(String[] args) throws IOException {
		
		//1151D
		
		//instead of focusing on the values of a and b, instead focus on their differences. If a and b are equal, then it doesn't matter where you place that person, their 
		//dissatisfaction is always going to be the same. If a or b is overwhelmingly greater, then it would be best to place that person at one end. For each person, 
		//get the value of a - b for that person, and sort them based on that value. That is the order that they should be in to minimize dissatisfaction.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long[][] nums = new long[n][3];
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long a = Integer.parseInt(st.nextToken());
			long b = Integer.parseInt(st.nextToken());
			nums[i] = new long[] {a, b, a - b};
		}
		Arrays.sort(nums, (a, b) -> -Long.compare(a[2], b[2]));
		long ans = 0;
		for(int i = 0; i < n; i++) {
			ans += nums[i][0] * i + nums[i][1] * (n - i - 1);
		}
		System.out.println(ans);
	}
}
