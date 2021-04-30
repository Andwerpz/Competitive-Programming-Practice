//package binaryremovals;

import java.io.*;
import java.util.*;

public class binaryremovals {
	public static void main(String[] args) throws IOException {
		
		//for each test case, loop through all the indexes once.
		//for each index, assign it as the "pivot index" where before this index, remove all 1s and after, remove all 0s.
		//if any pivot index is valid, return true, else return false
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			String test = fin.readLine();
			int[] nums = new int[test.length()];
			for(int i = 0; i < test.length(); i++) {
				nums[i] = Integer.parseInt(test.charAt(i) + "");
			}
			boolean isValid = false;
			for(int i = 0; i < nums.length; i++) {	//setting the pivot index
				isValid = true;
				for(int j = 0; j <= i - 1; j++) {
					if(nums[j] == 1 && nums[j + 1] == 1) {
						isValid = false;
					}
				}
				for(int j = i + 1; j < nums.length - 1; j++) {
					if(nums[j] == 0 && nums[j + 1] == 0) {
						isValid = false;
					}
				}
				if(isValid) {
					break;
				}
			}
			if(isValid) {
				fout.append("YES\n");
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
