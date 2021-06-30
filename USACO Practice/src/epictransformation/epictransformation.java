//package epictransformation;

import java.util.*;
import java.io.*;

public class epictransformation {
	public static void main(String[] args) throws IOException {
		
		//1506D
		
		//i don't exactly know why this solution works, but i can explain how it works.
		//Given a set of numbers, we can remove two different numbers at a time. What is the minimum size we can get this set to?
		//my idea was to focus on the largest and smallest set of numbers at any given time. Remove the numbers from the largest and smallest, and change
		//sets when the largest set changes. Exhaust all the smallest sets, from smallest to largest.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				dict.put(next, dict.getOrDefault(next, 0) + 1);
			}
			TreeMap<Integer, Integer> nums = new TreeMap<Integer, Integer>();
			for(int i : dict.keySet()){
				int next = dict.get(i);
				nums.put(next, nums.getOrDefault(next, 0) + 1);
			}
			//System.out.println("DICT: " + dict);
			//System.out.println("NUMS: " + nums);
			boolean done = false;
			while(!done) {
				int high = nums.lastKey();
				nums.put(high, nums.get(high) - 1);
				if(nums.get(high) == 0) {
					nums.remove(high);
				}
				if(nums.size() == 0) {
					nums.put(high, nums.getOrDefault(high, 0) + 1);
					done = true;
					break;
				}
				int low = nums.firstKey();
				nums.put(low, nums.get(low) - 1);
				if(nums.get(low) == 0) {
					nums.remove(low);
				}
				if(nums.size() == 0) {
					high -= low;
					nums.put(high, 1);
					done = true;
					break;
				}
				else {
					int diff = high - nums.lastKey() + 1;
					if(diff > low) {
						high -= low;
						nums.put(high, nums.getOrDefault(high, 0) + 1);
					}
					else {
						low -= diff;
						high -= diff;
						if(high != 0) {
							nums.put(high, nums.getOrDefault(high, 0) + 1);
						}
						if(low != 0) {
							nums.put(low, nums.getOrDefault(low, 0) + 1);
						}
					}
				}
			}
			//System.out.println("AFTER: " + nums);
			int ans = 0;
			for(int i : nums.keySet()) {
				ans += i * nums.get(i);
			}
			fout.append(ans).append("\n");
			//System.out.println();
		}
		System.out.print(fout);
	}
}
