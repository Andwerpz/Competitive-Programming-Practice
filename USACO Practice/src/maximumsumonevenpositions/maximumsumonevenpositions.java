//package maximumsumonevenpositions;

import java.util.*;
import java.io.*;

public class maximumsumonevenpositions {
	
	static long[] b;
	
	public static long maxSubarray() {
		long max = Long.MIN_VALUE / 2;
		long curMax = Long.MIN_VALUE / 2;
		for(int i = 0; i < b.length; i++) {
			curMax = Math.max(curMax + b[i], b[i]);
			max = Math.max(max, curMax);
			//System.out.print(b[i] + " ");
		}
		//System.out.println();
		return max;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1373D
		
		//first notice that you can only change the sum of even numbers if you flip a even length subarray. If you flip an odd length subarray, all the even numbers in the subarray
		//will just get put into different even locations. This means that we have a situation where every even number "maps" to an odd number that is adjacent to it. 
		//so construct a difference array, saving the change in sum you will get from flipping this value, and find the maximum subarray. You need to do this again with the other side, 
		//since each even value can be flipped with either their right or left. Take the maximum and if it is positive, add it to the original answer.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			long[] nums = new long[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			b = new long[n / 2];
			long ans = 0;
			for(int i = 0; i < n; i++) {
				if(i % 2 == 0) {
					ans += nums[i];
					if(i + 1 != n) {
						b[i / 2] = nums[i + 1] - nums[i];
					}
				}
			}
			//System.out.println("CUR ANS: " + ans);
			long add = maxSubarray();
			if(n % 2 == 1) {
				b = new long[n / 2];
				for(int i = n - 1; i > 0; i--) {
					if(i % 2 == 0) {
						b[i / 2 - 1] = nums[i - 1] - nums[i];
					}
				}
				add = Math.max(add, maxSubarray());
			}
			else {
				b = new long[n / 2 - 1];
				for(int i = n - 2; i > 0; i--) {
					if(i % 2 == 0) {
						b[i / 2 - 1] = nums[i - 1] - nums[i];
					}
				}
				add = Math.max(add, maxSubarray());
			}
			//System.out.println("ADD: " + add);
			ans = Math.max(ans, ans + add);
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
