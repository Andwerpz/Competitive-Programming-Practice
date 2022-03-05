//package swords;

import java.util.*;
import java.io.*;

public class swords {
	
	public static long gcd(long a, long b) {
		while(b != 0) {
			long t = b;
			b = a % b;
			a = t;
		}
		return a;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1216D
		
		//all you have to do to find the minimum amount of people is to find the maximum amount each of them could have stolen.
		
		//find the maximum number, max, and then find each numbers difference from max from nums[0] to nums[i].
		
		//the largest possible amount each of them could steal has to divide all the differences evenly, so what
		//you are really trying to find is the gcd of all the differences.
		
		//to find gcd, you can just do gcd in series. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long[] nums = new long[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		long max = 0;
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			max = Math.max(max, nums[i]);
		}
		long gcd = 0;
		for(int i = 0; i < n; i++) {
			if(gcd == 0) {
				if(nums[i] != max) {
					gcd = max - nums[i];
				}
			}
			else if(max != nums[i]){
				gcd = gcd(gcd, max - nums[i]);
			}
		}
		long ans = 0;
		for(int i = 0; i < n; i++) {
			ans += (max - nums[i]) / gcd;
		}
		System.out.println(ans + " " + gcd);
	}
}
