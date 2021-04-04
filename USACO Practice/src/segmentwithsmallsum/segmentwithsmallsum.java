//package segmentwithsmallsum;

import java.util.*;
import java.io.*;

public class segmentwithsmallsum {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long s = Long.parseLong(st.nextToken());
		int max = 0;
		long sum = 0;
		int low = 0;
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			sum += nums[i];
			if(low < n && sum > s) {
				sum -= nums[low];
				low++;
			}
			if(i - low + 1 > max) {
				max = i - low + 1;
			}
		}
		System.out.println(max);
	}
}
