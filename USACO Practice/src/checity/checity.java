//package checity;

import java.util.*;
import java.io.*;

public class checity {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int r = Integer.parseInt(st.nextToken());
		long total = 0;
		long sum = 0;
		int[] nums = new int[n];
		int low = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			total += i + 1;
			nums[i] = Integer.parseInt(st.nextToken());
			while(nums[i] - nums[low] > r) {	//if the double-date is possible, then we need to move our boundaries up
				low ++;
			}
			sum += i - low + 1;
			//System.out.println(sum);
		}
		//System.out.println(total);
		System.out.println(total - sum);
	}
}
