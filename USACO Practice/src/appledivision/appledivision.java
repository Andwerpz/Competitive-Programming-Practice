//package appledivision;

import java.util.*;
import java.io.*;

public class appledivision {
	public static void main(String[] args) throws IOException {
		
		//CSES 1623
		
		
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long[] nums = new long[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		long sum = 0;
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			sum += nums[i];
		}
		//try all binary strings
		int amt = (int) Math.pow(2, n);
		long ans = Long.MAX_VALUE;
		for(int i = 0; i < amt; i++) {
			char[] s = Integer.toBinaryString(i).toCharArray();
			long curSum = 0;
			int diff = n - s.length;
			for(int j = 0; j < n; j++) {
				if(j - diff >= 0 && s[j - diff] == '1') {
					curSum += nums[j - diff];
				}
			}
			ans = Math.min(ans, Math.abs(curSum * 2 - sum));
		}
		System.out.println(ans);
	}
}
