//package berlandfair;

import java.util.*;
import java.io.*;

public class berlandfair {
	public static void main(String[] args) throws IOException {
		
		//1073D
		
		//go around once, buying all the candies that you can buy, and record the total cost. If the total cost is less than the current amount of money that you have, then the next time you go around, 
		//you'll buy the exact same amount of candies, and spend the same amount of money. You can easily get the amount of cycles using floor div. 
		
		//The key is that each time you find and remove cycles, the amount of money that you have will at least be halved. You'll end up only having to iterate through the shops
		//log(t) times. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long t = Long.parseLong(st.nextToken());
		long[] nums = new long[n];
		st = new StringTokenizer(fin.readLine());
		long min = Integer.MAX_VALUE;
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			min = Math.min(nums[i], min);
		}
		long ans = 0;
		while(t >= min) {
			long cycleCost = 0;
			long cycleAmt = 0;
			for(int i = 0; i < n; i++) {
				if(t >= nums[i]) {
					t -= nums[i];
					cycleCost += nums[i];
					ans ++;
					cycleAmt ++;
				}
			}
			long multiple = t / cycleCost;
			ans += multiple * cycleAmt;
			t -= multiple * cycleCost;
		}
		System.out.println(ans);
	}
}
