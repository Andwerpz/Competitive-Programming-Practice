//package oldfloppydrive;

import java.util.*;
import java.io.*;

public class oldfloppydrive {
	
	public static int search(long[] pfx, long val) {
		int high = pfx.length - 1;
		int low = 0;
		int mid = low + (high - low) / 2;
		int ans = high;
		while(low <= high) {
			if(pfx[mid] >= val) {
				ans = Math.min(ans, mid);
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1490G
		
		//first, determine the maximum value for each rotation, and the difference each rotation will make. Then, construct a pfx maximum for each rotation.
		//We can first determine whether or not we will ever reach the x value. If the difference is less than or equal to 0, then the maximum has to be greater or equal to the x value, 
		//reaching it on the first rotation. If it is not, then the input is invalid. if diff is greater than 0, then figure out the first rotation that the maximum will exceed x, 
		//then binary search over the pfx maximum array to find exactly how many seconds are required.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			long[] nums = new long[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			long max = 0;
			long diff = 0;
			long[] pfx = new long[n];
			for(int i = 0; i < n; i++) {
				pfx[i] = nums[i];
				if(i != 0) {
					pfx[i] += pfx[i - 1];
				}
				max = Math.max(max, pfx[i]);
			}
			diff = pfx[n - 1];
			for(int i = 1; i < n; i++) {
				pfx[i] = Math.max(pfx[i], pfx[i - 1]);
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < m; i++) {
				long next = Integer.parseInt(st.nextToken());
				next -= max;
				if(next <= 0) {
					next += max;
					fout.append(search(pfx, next));
				}
				else if(diff <= 0) {
					fout.append(-1);
				}
				else {
					next += max;
					long remainder = next % diff;
					remainder += ((max - remainder) / diff) * diff;
					next -= remainder;
					long rotations = next / diff;
					fout.append(rotations * n + search(pfx, remainder));
				}
				fout.append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
