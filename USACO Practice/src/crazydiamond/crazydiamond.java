//package crazydiamond;

import java.util.*;
import java.io.*;

public class crazydiamond {
	
	static int[] nums;
	static HashMap<Integer, Integer> dict;
	static StringBuilder fout;
	
	public static void switchNums(int a, int b) {
		fout.append(a + 1).append(" ").append(b + 1).append("\n");
		int aVal = nums[a];
		int bVal = nums[b];
		nums[a] = bVal;
		nums[b] = aVal;
		dict.put(aVal, b);
		dict.put(bVal, a);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1148C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		nums = new int[n];
		dict = new HashMap<Integer, Integer>();
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken()) - 1;
			nums[i] = next;
			dict.put(next, i);
		}
		fout = new StringBuilder();
		int ans = 0;
		for(int i = 0; i < n / 2; i++) {
			int cur = (n / 2) - 1 - i;
			int curIndex = dict.get(cur);
			if(curIndex != cur) {
				if(curIndex >= n / 2) {
					ans += 2;
					switchNums(curIndex, 0);
					switchNums(0, n - 1);
				}
				else {
					ans ++;
					switchNums(curIndex, n - 1);
				}
				ans ++;
				switchNums(n - 1, cur);
			}
			cur = (n / 2) + i;
			curIndex = dict.get(cur);
			if(curIndex != cur) {
				if(curIndex < n / 2) {
					ans += 2;
					switchNums(curIndex, n - 1);
					switchNums(n - 1, 0);
				}
				else {
					ans ++;
					switchNums(curIndex, 0);
				}
				ans ++;
				switchNums(0, cur);
			}
		}
		System.out.print(ans + "\n" + fout);
	}
}
