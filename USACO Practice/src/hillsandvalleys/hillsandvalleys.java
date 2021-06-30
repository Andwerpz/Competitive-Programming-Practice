//package hillsandvalleys;

import java.util.*;
import java.io.*;

public class hillsandvalleys {
	public static void main(String[] args) throws IOException {
		
		//1467B
		
		//brute force
		
		//since you can only change one number, we can iterate through all the numbers and check what difference we can make if we only 
		//change that number. The number we change it to is either one of its neighbors. This guarantees that if the neighbor is a hill or valley, then the change will 
		//make it cease being so, and if the number in question is a hill or valley, then it will also cease being one. One thing you have to be careful about is
		//if the other neighbor is not already a hill or valley, then the change might cause it to be one.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			int[] hillOrValley = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int init = 0;
			for(int i = 1; i < n - 1; i++) {
				if(nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
					init ++;
					hillOrValley[i] = 1;
				}
				else if(nums[i] < nums[i - 1] && nums[i] < nums[i + 1]) {
					init ++;
					hillOrValley[i] = -1;
				}
			}
			int ans = init;
			for(int i = 1; i < n - 1; i++) {
				int cur = init;
				int temp = nums[i - 1];
				if(i - 2 >= 0 && (hillOrValley[i - 1] == 1 || hillOrValley[i - 1] == -1)) {
					cur --;
				}
				if(i + 2 < n) {
					if((hillOrValley[i + 1] == 1 && nums[i + 1] <= temp || hillOrValley[i + 1] == -1 && nums[i + 1] >= temp)) {
						cur --;
					}
					else if(hillOrValley[i + 1] == 0 && (nums[i + 1] > temp && nums[i + 1] > nums[i + 2] || nums[i + 1] < temp && nums[i + 1] < nums[i + 2])) {
						cur ++;
					}
				}
				if(hillOrValley[i] == 1 || hillOrValley[i] == -1) {
					cur --;
				}
				ans = Math.min(cur, ans);
				cur = init;
				temp = nums[i + 1];
				if(i - 2 >= 0) {
					if((hillOrValley[i - 1] == 1 && nums[i - 1] <= temp || hillOrValley[i - 1] == -1 && nums[i - 1] >= temp)) {
						cur --;
					}
					else if(hillOrValley[i - 1] == 0 && (nums[i - 1] > temp && nums[i - 1] > nums[i - 2] || nums[i - 1] < temp && nums[i - 1] < nums[i - 2])) {
						cur ++;
					}
				}
				if(i + 2 < n && (hillOrValley[i + 1] == 1 || hillOrValley[i + 1] == -1)) {
					cur --;
				}
				if(hillOrValley[i] == 1 || hillOrValley[i] == -1) {
					cur --;
				}
				ans = Math.min(cur, ans);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
