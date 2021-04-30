//package kingstask;

import java.util.*;
import java.io.*;

public class kingstask {
	public static void main(String[] args) throws IOException {
		
		//we notice that the changes result in a loop, so all we have to do is check whether the permutation falls into this loop
		//calculating the number of actions from there is simple.
		
		//actually, notice how applying an action twice in a row just resets the array back to the original state.
		//thus the only way to effectively sort the array is to apply the actions in an alternating fashion. 
		//since the actions when applied eventually go back to the original array, we just wait until that happens, and if we sorted it
		//somewhere in the middle, then return the answer, if not, -1.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n * 2];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < nums.length; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		//System.out.println();
		int ans = -1;
		for(int i = 0; i < nums.length; i++) {
			if(i % 2 == 0) {
				for(int j = 0; j < nums.length; j += 2) {
					int temp = nums[j];
					nums[j] = nums[j + 1];
					nums[j + 1] = temp;
				}
			}
			else {
				for(int j = 0; j < nums.length / 2; j++) {
					int temp = nums[j];
					nums[j] = nums[j + n];
					nums[j + n] = temp;
				}
			}
			boolean isValid = true;
			for(int j = 0; j < nums.length; j++) {
				if(nums[j] != j + 1) {
					isValid = false;
					break;
				}
			}
			
			if(isValid) {
				ans = Math.min(ans == -1? i + 1 : ans, i + 1);
			}
		}
		for(int i = 0; i < nums.length; i++) {	//for this one, we just apply the operations starting with the other operation
			if(i % 2 == 1) {
				for(int j = 0; j < nums.length; j += 2) {
					int temp = nums[j];
					nums[j] = nums[j + 1];
					nums[j + 1] = temp;
				}
			}
			else {
				for(int j = 0; j < nums.length / 2; j++) {
					int temp = nums[j];
					nums[j] = nums[j + n];
					nums[j + n] = temp;
				}
			}
			boolean isValid = true;
			for(int j = 0; j < nums.length; j++) {
				if(nums[j] != j + 1) {
					isValid = false;
					break;
				}
			}
			if(isValid) {
				ans = Math.min(ans == -1? i + 1 : ans, i + 1);
			}
		}
		boolean finalCheck = true;
		for(int j = 0; j < nums.length; j++) {
			if(nums[j] != j + 1) {
				finalCheck = false;
				break;
			}
		}
		if(finalCheck) {
			ans = 0;
		}
		System.out.println(ans);
	}
}
