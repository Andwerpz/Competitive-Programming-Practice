//package longestkgoodsegment;

import java.util.*;
import java.io.*;

public class longestkgoodsegment {
	public static void main(String[] args) throws IOException {
		
		//616D
		
		//classic 2 pointer question, for each number, what is the longest subarray ending at this number satisfying the conditions
		//to check, just use hashmap as dictionary. The size of the map is equal to the number of unique elements in the subarray.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int rightIndex = -1;
		int leftIndex = -1;
		int max = 0;
		int pointer = 0;
		st = new StringTokenizer(fin.readLine());
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			dict.put(nums[i], dict.getOrDefault(nums[i], 0) + 1);
			while(dict.size() > k) {
				int next = nums[pointer];
				if(dict.get(next) == 1) {
					dict.remove(next);
				}
				else {
					dict.put(next, dict.get(next) - 1);
				}
				pointer ++;
			}
			int cur = i - pointer + 1;
			//System.out.println(cur + " " + pointer + " " + i);
			if(max < cur) {
				max = cur;
				rightIndex = i + 1;
				leftIndex = pointer + 1;
			}
		}
		System.out.println(leftIndex + " " + rightIndex);
	}
}
