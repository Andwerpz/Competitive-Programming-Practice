//package ehabandprefixmexs;

import java.util.*;
import java.io.*;

public class ehabandprefixmexs {
	public static void main(String[] args) throws IOException {
		
		//1364C
		
		//the goal is to make a pfx array, array b, for array a that for any index i in array, retrieve the pfx of array b. All the numbers in the pfx is a set, and 
		//the a[i] is the smallest non-negative value not included in that set. Constraints on a are a[i] <= a[i + 1] and 0 <= a[i] <= i. This means that you should be able
		//to construct a pfx array that fits the constraints given the constraints on the a array. Keep a pointer variable p, and an index variable i, and start it at 0. If you find that p is equal to a 
		//number in a which index is greater than i, then increment p past it, and add the previous p value into a set, s. When you get to the first number that is not
		//contained, then add p to the ans array at i, and increment i. Doing the second time, check a[i]. If the number of future occurrences is reduced to 0, and it is 
		//included in s, then you pick that number to put into ans[i], else repeat the first step. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		HashMap<Integer, Integer> numsLeft = new HashMap<Integer, Integer>();
		HashSet<Integer> skipped = new HashSet<Integer>();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			numsLeft.put(nums[i], numsLeft.getOrDefault(nums[i], 0) + 1);
		}
		int pointer = 0;
		int[] ans = new int[n];
		boolean isValid = true;
		for(int i = 0; i < n; i++) {
			boolean putNum = false;
			if(i != 0) {
				numsLeft.put(nums[i - 1], numsLeft.get(nums[i - 1]) - 1);
				if(numsLeft.get(nums[i - 1]) == 0) {
					numsLeft.remove(nums[i - 1]);
					if(skipped.contains(nums[i - 1])) {
						ans[i] = nums[i - 1];
						putNum = true;
					}
				}
			}
			if(!putNum) {
				while(numsLeft.containsKey(pointer)) {
					skipped.add(pointer);
					pointer ++;
				}
				ans[i] = pointer;
				pointer ++;
				putNum = true;
			}
			if(pointer + 1 < nums[i]) {
				isValid = false;
				break;
			}
		}
		if(isValid) {
			StringBuilder fout = new StringBuilder();
			for(int i = 0; i < n; i++) {
				fout.append(ans[i]).append(" ");
			}
			System.out.println(fout);
		}
		else {
			System.out.println(-1);
		}
	}
}
