//package sagesbirthdayhardversion;

import java.util.*;
import java.io.*;

public class sagesbirthdayhardversionver1 {
	public static void main(String[] args) throws IOException {
		
		//oh, we can just sort all the nums, and do a two pointer sort of thing, where one pointer is at the top, and the other is at the halfway point
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		TreeMap<Integer, Integer> dict = new TreeMap<Integer, Integer>();
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			dict.put(next, dict.getOrDefault(next, 0) + 1);
		}
		boolean high = true;
		for(int i = 0; i < n; i++) {
			int next = 0;
			if(high) {
				next = dict.lastKey();
				high = false;
			}
			else {
				if(dict.floorKey(dict.lastKey() - 1) == null) {
					next = dict.lastKey();
				}
				else {
					next = dict.floorKey(dict.lastKey() - 1);
				}
				high = true;
			}
			dict.put(next, dict.get(next) - 1);
			if(dict.get(next) == 0) {
				dict.remove(next);
			}
			nums[i] = next;
		}
		int ans = 0;
		for(int i = 1; i < n - 1; i++) {
			if(nums[i] < nums[i + 1] && nums[i] < nums[i - 1]) {
				ans ++;
			}
		}
		StringBuilder fout = new StringBuilder();
		fout.append(ans).append("\n");
		for(int i = 0; i < n; i++) {
			fout.append(nums[i]).append(" ");
		}
		System.out.println(fout);
	}
}
