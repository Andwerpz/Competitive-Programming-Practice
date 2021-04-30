//package binarysearch;

import java.util.*;
import java.io.*;

public class binarysearch {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		while(k -- > 0) {
			int target = Integer.parseInt(st.nextToken());
			int high = n - 1;
			int low = 0;
			int mid = low + (high - low) / 2;
			int ans = -1;
			while(low <= high) {
				if(nums[mid] == target) {
					ans = mid;
					break;
				}
				else if(nums[mid] > target) {
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
				mid = low + (high - low) / 2;
			}
			fout.append(ans == -1? "NO\n" : "YES\n");
		}
		System.out.print(fout);
	}
}
