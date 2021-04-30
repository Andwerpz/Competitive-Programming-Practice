//package dimaandtodolist;

import java.util.*;
import java.io.*;

public class dimaandtodolist {
	public static void main(String[] args) throws IOException {
		
		//we just go through all starting points from 0 -> k - 1. The values just cycle from there. 
		//even though we have nested loop, we only visit each index one time, so the complexity is O(n)
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int ans = 0;
		int min = Integer.MAX_VALUE;
		for(int i = 0; i < k; i++) {
			int sum = 0;
			for(int j = i; j < i + nums.length; j += k) {
				sum += nums[j % nums.length];
			}
			if(min > sum) {
				min = sum;
				ans = i;
			}
		}
		System.out.println(ans + 1);
	}
}
