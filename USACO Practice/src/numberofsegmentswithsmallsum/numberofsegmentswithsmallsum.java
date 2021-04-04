//package numberofsegmentswithsmallsum;

import java.util.*;
import java.io.*;

public class numberofsegmentswithsmallsum {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long s = Long.parseLong(st.nextToken());
		int[] nums = new int[n];
		long ans = 0;
		long sum = 0;
		int low = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			sum += nums[i];
			while(low < n && sum > s) {
				sum -= nums[low];
				low++;
			}
			if(low <= i) {
				ans += i - low + 1;
			}
			//System.out.println(low + " " + i);
		}
		System.out.println(ans);
	}
}
