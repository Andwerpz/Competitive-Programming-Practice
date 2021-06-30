//package kuroniandimpossiblecalculation;

import java.util.*;
import java.io.*;

public class kuroniandimpossiblecalculation {
	public static void main(String[] args) throws IOException {
		
		//1305C
		
		//first i must note that the solution doesn't require any fast way to calculate the product of all the differences. 
		//for all values of n that are <= m, you can just directly calculate the product. Since m is less than 1000, this works. 
		//for any value of n that is greater than m, you know that at least two numbers in the array have the same remainder when modded by m. 
		//this means their difference is a multiple of m, meaning that the entire product is a multiple of m, so the answer is always 0.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		long ans = 0;
		if(n <= m) {
			ans = 1;
			for(int i = 0; i < n; i++) {
				for(int j = i + 1; j < n; j++) {
					ans *= (long) Math.abs(nums[i] - nums[j]);
					ans %= m;
				}
			}
		}
		System.out.println(ans);
	}
}
