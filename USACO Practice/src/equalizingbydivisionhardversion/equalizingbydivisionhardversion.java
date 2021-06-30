//package equalizingbydivisionhardversion;

import java.util.*;
import java.io.*;

public class equalizingbydivisionhardversion {
	public static void main(String[] args) throws IOException {
		
		//1213D2
		
		//for each number from 0 - 2 * 10^5, calculate how many operations it takes to make at least k numbers equal to it, if possible. First notice that for any number, there is a range
		//of numbers that only require 1 operation, a range that requires 2 operations, and so on. ex. 2 -> 4 - 5 -> 8 - 11 and so on. You can construct a pfx sum to retrieve the number of
		//values within those ranges quickly, so testing a single number only requires O(log(n)). Testing all numbers is O(n * log(n)), which is within the limits.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[] nums = new int[200001];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			nums[next] ++;
		}
		int[] pfx = new int[nums.length];
		pfx[0] = nums[0];
		for(int i = 1; i < pfx.length; i++) {
			pfx[i] = pfx[i - 1] + nums[i];
		}
		int min = Integer.MAX_VALUE;
		int vLow = 0;
		int low = 0;
		int high = 0;
		for(int i = 0; i < nums.length - 1; i++) {
			boolean isValid = false;
			int cur = nums[i];
			int cost = 0;
			int unitCost = 1;
			vLow = i;
			low = i * 2;
			high = i * 2 + 1;
			//System.out.println("CUR: " + cur);
			while(cur < k) {
				if(low > nums.length || vLow >= nums.length) {
					break;
				}
				int amt = pfx[Math.min(high, nums.length - 1)] - pfx[Math.max(vLow, low - 1)];
				//System.out.println("AMT: " + amt + " " + Math.max(vLow, low) + " " + high);
				if(k - cur <= amt) {
					cost += unitCost * (k - cur);
					cur = k;
					//System.out.println("cur: " + i);
					//System.out.println("COST: " + cost);
					isValid = true;
					break;
				}
				else if(k - cur > amt) {
					cost += amt * unitCost;
					cur += amt;
				}
				vLow = high;
				low *= 2;
				high = high * 2 + 1;
				unitCost ++;
				
			}
			//System.out.println("COST: " + cost);
			if(cur >= k) {
				min = Math.min(cost, min);
			}
		}
		System.out.println(min);
	}
}
