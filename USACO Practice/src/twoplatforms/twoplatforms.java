//package twoplatforms;

import java.util.*;
import java.io.*;

public class twoplatforms {
	
	static Integer[] nums;
	
	public static int numsInRange(int l, int r) {	//gets all values in range of l - r inclusive
		int lowAns = nums.length - 1;
		int highAns = 0;
		int low = 0;
		int high = nums.length - 1;
		int mid = low + (high - low) / 2;
		while(low <= high) {
			if(nums[mid] >= l) {
				lowAns = Math.min(lowAns, mid);
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		low = 0;
		high = nums.length - 1;
		mid = low + (high - low) / 2;
		while(low <= high) {
			if(nums[mid] <= r) {
				highAns = Math.max(highAns, mid);
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		//System.out.println(lowAns + " " + highAns + " " + l + " " + r);
		return highAns - lowAns + 1;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1409E
		
		//just like diamond collector from usaco. Since there is no greedy solution, the only option left is to try out all possible combinations. But you don't have to try them all out.
		//given the position of one platform, you can just figure out the optimal position of the other platform. To do this, use a pfx maximum array. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			nums = new Integer[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			fin.readLine();
			Arrays.sort(nums);
			int[] pfx = new int[n];
			for(int i = 0; i < n; i++) {
				int cur = numsInRange(nums[i] - k, nums[i]);
				if(i == 0) {
					pfx[i] = cur;
				}
				else {
					pfx[i] = Math.max(pfx[i - 1], cur);
				}
				//System.out.print(pfx[i] + " ");
			}
			//System.out.println();
			int ans = 0;
			int pointer = -1;
			for(int i = 0; i < n; i++) {
				int next = nums[i];
				while(Math.abs(next - nums[pointer + 1]) > k) {
					pointer ++;
				}
				if(pointer == -1) {
					ans = Math.max(pfx[i], ans);
				}
				else {
					ans = Math.max(pfx[pointer] + numsInRange(next - k, next), ans);
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
