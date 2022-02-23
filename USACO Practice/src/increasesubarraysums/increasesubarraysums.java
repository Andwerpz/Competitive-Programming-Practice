//package increasesubarraysums;

import java.util.*;
import java.io.*;

public class increasesubarraysums {
	public static void main(String[] args) throws IOException {
		
		//1644C
		
		//instead of doing f(k) over subarrays of all sizes from 0 - n, try f(k, s), where s is the size of the subarray. 
		
		//notice that when you keep s constant and increase k, the maximum sum segment of size s stays constant. 
		
		//Proof:
		//Define a as the set of all subarrays of size s. If you maximize all of the subarrays in a using the k operations independently, 
		//and take the maximum sum, then it is guaranteed that you will ge tthe maximum subarray sum of length s. 
		
		//notice that when performing operations, the initial sum of the subarray is what determines which subarray is the maximum after the 
		//operations, because all you are doing is adding to the sum. Increasing k by 1 just means that you add another x to each of the 
		//subarray sums; their relative ordering doesn't change
		
		//Thus, the subarray with the highest initial sum will always be the highest after the operations.
		
		
		//to solve, you can just keep track of the maximum sum segment for each size 0 - n. As k increases, keep in mind that if k > s, 
		//then you can only add min(k, s) * x to the subarray sum, since you can only do 1 operation on each number.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			int[] nums = new int[n];
			int[] pfx = new int[n + 1];
			int[] segMax = new int[n + 1];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			pfx[1] = nums[0];
			for(int i = 2; i <= n; i++) {
				pfx[i] += pfx[i - 1] + nums[i - 1];
			}
			for(int i = 0; i < segMax.length; i++) {
				segMax[i] = Integer.MIN_VALUE;
			}
			for(int i = 0; i <= n; i++) {
				for(int j = 0; j + i < pfx.length; j++) {
					segMax[i] = Math.max(segMax[i], pfx[j + i] - pfx[j]);
				}
				//System.out.println(segMax[i]);
			}
			for(int i = 0; i <= n; i++) {
				int ans = 0;
				for(int j = 0; j <= n; j++) {
					ans = Math.max(ans, segMax[j] + Math.min(i, j) * x);
					//System.out.println(ans);
				}
				fout.append(ans).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
