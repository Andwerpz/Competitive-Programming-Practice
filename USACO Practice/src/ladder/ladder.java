//package ladder;

import java.util.*;
import java.io.*;

public class ladder {
	
	static int[] nums;
	
	public static boolean search(int low, int high, int target, int[] dp) {	//return whether or not the range has a decreasing segment
		//System.out.println("Search over segment " + low + " " + high);
		int temp = low;
		int mid = low + (high - low) / 2;
		int ansIndex = -1;
		while(low <= high) {
			if(dp[mid] == target) {
				low = mid + 1;
				if(ansIndex == -1 || ansIndex < mid) {
					ansIndex = mid;
				}
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		low = temp;
		high = ansIndex;
		mid = low + (high - low) / 2;
		while(low <= high) {
			//System.out.println(low + " " + high);
			if(nums[mid] > nums[mid + 1]) {
				return true;
			}
			else if(nums[mid] < nums[mid + 1]) {
				return true;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int[] dp = new int[n];	//Which ladder group this index falls into
		int pointer = 0;
		int counter = 0;
		boolean increasing = false;
		for(int i = 1; i < n; i++) {
			if(nums[i - 1] < nums[i] && !increasing) {
				counter ++;
				increasing = true;
			}
			if(nums[i - 1] > nums[i]) {
				increasing = false;
			}
			dp[i] = counter;
			//////System.out.print(dp[i] + " ");
		}
		for(int i : dp) {
			//System.out.print(i + " ");
		}
		//System.out.println();
		////System.out.println();
		StringBuilder fout = new StringBuilder();
		while(m -- > 0) {
			st = new StringTokenizer(fin.readLine());
			int l = Integer.parseInt(st.nextToken()) - 1;
			int r = Integer.parseInt(st.nextToken()) - 1;
			//System.out.println(dp[l] + " " + dp[r]);
			if(dp[l] != dp[r]) {
				if(dp[r] == dp[l + 1]) {
					fout.append("Yes\n");
				}
				else if(dp[r] == dp[l] + 1) {
					
					if(!search(l, r, dp[l], dp)) {
						fout.append("Yes\n");
					}
					else {
						fout.append("No\n");
					}
				}
				else {
					fout.append("No\n");
				}
			}
			else {
				fout.append("Yes\n");
			}
		}
		System.out.print(fout);
	}
}
