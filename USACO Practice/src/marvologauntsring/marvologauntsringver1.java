//package marvologauntsring;

import java.util.*;
import java.io.*;

public class marvologauntsringver1 {
	public static void main(String[] args) throws IOException {
		
		//lol, the question can't be that easy
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long[] nums = new long[3];
		nums[0] = Integer.parseInt(st.nextToken());
		nums[1] = Integer.parseInt(st.nextToken());
		nums[2] = Integer.parseInt(st.nextToken());
		
		st = new StringTokenizer(fin.readLine());
		long ans = 0;
		int min = Integer.MAX_VALUE;
		int max = Integer.MIN_VALUE;
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			min = Math.min(min, next);
			max = Math.max(max, next);
		}
		for(int i = 0; i < 3; i++) {
			if(nums[i] >= 0) {
				ans += nums[i] * max;
			}
			else {
				ans += nums[i] * min;
			}
		}
		System.out.println(ans);
	}
}
