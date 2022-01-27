//package rangeandpartition;

import java.util.*;
import java.io.*;

public class rangeandpartition {
	public static void main(String[] args) throws IOException {
		
		//1631D
		
		//given a range, [x, y], and an array, you can determine whether or not you can make the k subarrays. First count the number
		//of values in the array within [x, y]. If the difference between the number of values within the range and the ones outside the range
		//is greater or equal to k, then it is always possible to create k subarrays.
		
		//To find the optimal [x, y] range, you can binary search through the possible ranges. For each x, value, binary search the best
		//y value. Since you need to check n x values, you have to check each y value in constant time. To do this, you can make a prefix
		//sum to check for the number of values within a range. 
		
		//To create the final subarrays, start at the front of the array, and greedily add onto the array until the number of values in the 
		//range exceeds the number of outside values. When this happens, just start the next subarray.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			int[] pfx = new int[n + 1];
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				nums[i] = next;
				pfx[next] ++;
			}
			for(int i = 1; i < pfx.length; i++) {
				pfx[i] += pfx[i - 1];
			}
			//for each x, binary search minimum y so that (pfx[y] - pfx[x - 1]) - (n - (pfx[y] - pfx[x - 1])) >= k
			int[] minPair = new int[] {1, n};
			int min = Integer.MAX_VALUE;
			for(int i = 1; i <= n; i++) {
				int low = i;
				int high = n;
				int mid = low + (high - low) / 2;
				int ans = n;
				boolean isValid = false;
				while(low <= high) {
					int numInside = pfx[mid] - pfx[i - 1];
					if(numInside - (n - numInside) >= k) {
						isValid = true;
						ans = Math.min(ans, mid);
						high = mid - 1;
					}
					else {
						low = mid + 1;
					}
					mid = low + (high - low) / 2;
				}
				if(isValid && ans - i < min) {
					minPair[0] = i;
					minPair[1] = ans;
					min = ans - i;
				}
			}
			fout.append(minPair[0]).append(" ").append(minPair[1]).append("\n");
			//construct segments
			int p = 0;
			for(int i = 0; i < k - 1; i++) {
				int start = p;
				int in = 0;
				int out = 0;
				while(true) {
					int next = nums[p];
					if(minPair[0] <= next && next <= minPair[1]) {
						in ++;
					}
					else {
						out ++;
					}
					p ++;
					if(in > out) {
						fout.append(start + 1).append(" ").append(p).append("\n");
						break;
					}
				}
			}
			fout.append(p + 1).append(" ").append(n).append("\n");
		}
		System.out.print(fout);
	}
}
