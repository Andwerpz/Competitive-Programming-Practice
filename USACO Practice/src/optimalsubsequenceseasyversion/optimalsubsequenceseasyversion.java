//package optimalsubsequenceseasyversion;

import java.util.*;
import java.io.*;

public class optimalsubsequenceseasyversion {
	public static void main(String[] args) throws IOException {
		
		//1227D1 
		
		//this solution is very brute force. i don't really want to explain it lol.
		
		//if you sort the values, then the kth value in the sorted list is the bottom value. You will take all occurrences of any value that is greater than the bottom
		//value, and you will take none of any that are lower than the bottom value.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		int[] numsSorted = new int[n];
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			numsSorted[i] = nums[i];
			dict.put(nums[i], dict.getOrDefault(nums[i], 0) + 1);
		}
		Arrays.sort(numsSorted);
		int q = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(q-- > 0) {
			st = new StringTokenizer(fin.readLine());
			int k = Integer.parseInt(st.nextToken());
			int pos = Integer.parseInt(st.nextToken());
			int bottomVal = numsSorted[n - k];
			int numLeft = 0;
			for(int i = n - k; i < n; i++) {
				if(numsSorted[i] == bottomVal) {
					numLeft ++;
				}
				else {
					break;
				}
			}
			int ans = 0;
			for(int i = 0; i < n; i++) {
				if(nums[i] > bottomVal) {
					pos --;
				}
				else if(nums[i] == bottomVal && numLeft != 0) {
					pos --;
					numLeft --;
				}
				if(pos == 0) {
					ans = nums[i];
					break;
				}
			}
			//System.out.println(bottomVal);
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
