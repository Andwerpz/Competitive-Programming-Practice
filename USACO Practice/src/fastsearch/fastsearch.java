//package fastsearch;

import java.util.*;
import java.io.*;

public class fastsearch {
	public static void main(String[] args) throws IOException {
		
		//how many numbers are in between l and r inclusive
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(nums);
		int k = Integer.parseInt(fin.readLine());
		while(k -- > 0) {
			int highIndex = -1;
			int lowIndex = -1;
			st = new StringTokenizer(fin.readLine());
			int low = 0;
			int high = n - 1;
			int mid = low + (high - low) / 2;
			int target = Integer.parseInt(st.nextToken());
			while(low <= high) {
				if(nums[mid] >= target) {
					if(mid < lowIndex || lowIndex == -1) {
						lowIndex = mid;
					}
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
				mid = low + (high - low) / 2;
			}
			low = 0;
			high = n - 1;
			mid = low + (high - low) / 2;
			target = Integer.parseInt(st.nextToken());
			while(low <= high) {
				if(nums[mid] <= target) {
					if(mid > highIndex || highIndex == -1) {
						highIndex = mid;
					}
					low = mid + 1;
				}
				else {
					high = mid - 1;
				}
				mid = low + (high - low) / 2;
			}
			if(lowIndex == -1 || highIndex == -1) {	//make sure that l and r are within the range of the array
				fout.append("0").append("\n");
			}
			else {
				fout.append(highIndex - lowIndex + 1).append(" ");
			}
			
		}
		System.out.print(fout.substring(0, fout.length() - 1));
	}
}
