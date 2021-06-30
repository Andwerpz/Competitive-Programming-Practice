//package alyonaandnarrowfridge;

import java.util.*;
import java.io.*;	

public class alyonaandnarrowfridge {
	
	static int[] nums;
	
	public static boolean isValid(int k, int h) {
		int[] bottles = new int[k];
		for(int i = 0; i < k; i++) {
			bottles[i] = nums[i];
		}
		Arrays.sort(bottles);
		for(int i = k - 1; i >= 0; i -= 2) {
			int cost = Math.max(bottles[i], bottles[Math.max(i - 1, 0)]);
			h -= cost;
			if(h < 0) {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//you're trying to fit the most bottles of milk into the fridge as you can. First, you can binary search to test if a quantity of bottles is valid. 
		//to test if a number of bottles is valid, sort the bottles that you have to add, and add them in pairs, starting from the largest bottles downwards. 
		//we do the largest bottles first, because at the end, we want the smallest bottle to be alone, if the set of bottles is odd. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int h = Integer.parseInt(st.nextToken());
		nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int high = n;
		int low = 0;
		int mid = low + (high - low) / 2;
		int ans = low;
		while(low <= high) {
			//System.out.println(low + " " + high);
			if(isValid(mid, h)) {
				if(ans < mid) {
					ans = mid;
				}
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(ans);
	}
}
