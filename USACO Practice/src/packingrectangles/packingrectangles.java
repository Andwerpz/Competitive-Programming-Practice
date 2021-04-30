//package packingrectangles;

import java.util.*;
import java.io.*;

public class packingrectangles {
	
	public static boolean isValid(int w, int h, long size, int n) {
		long sum = 0;
		sum = size / (long) w;
		sum *= size / (long) h;
		//System.out.println(sum);
		if(sum >= (long) n || sum < 0) {
			return true;
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int w = Integer.parseInt(st.nextToken());
		int h = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());
		long high = Long.MAX_VALUE;
		long low = 0;
		long mid = low + (high - low) / 2;
		long ans = high;
		while(low <= high) {
			//System.out.println(mid);
			if(isValid(w, h, mid, n)) {
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
