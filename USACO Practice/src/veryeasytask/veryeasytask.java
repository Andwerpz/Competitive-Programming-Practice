//package veryeasytask;

import java.util.*;
import java.io.*;

public class veryeasytask {
	
	public static boolean isValid(long targetTime, int n, int x, int y) {
		int a = Math.min(x, y);
		int b = Math.max(x, y);
		targetTime -= a;
		if(targetTime < 0) {
			return false;
		}
		else {
			long sum = 0;
			sum += targetTime / a;
			sum += targetTime / b;
			//System.out.println(sum + " " + targetTime);
			if(sum + 1 >= n) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int x = Integer.parseInt(st.nextToken());
		int y = Integer.parseInt(st.nextToken());
		long low = 0;
		long high = Long.MAX_VALUE;
		long mid = low + (high - low) / 2;
		long ans = high;
		while(low <= high) {
			//System.out.println(low + " " + high + " " + mid);
			if(isValid(mid, n, x, y)) {
				if(ans > mid) {
					ans = mid;
				}
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(ans);
	}
}
