package sagesbirthdayhardversion;

import java.util.*;
import java.io.*;

public class sagesbirthdayhardversionver2 {
	public static void main(String[] args) throws IOException {
		
		//1419D2
		
				//basically what we do is put a pointer at the midpoint, and one at the end. Then we alternate between them, and this generates lots of cheap items. 
				//bandaid section at the bottom is to test whether if we put a pointer at the very bottom and the other at the very top, will it generate more cheap items.
		
		//doesn't work lol
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int[] ans = new int[n];
		int count = 0;
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(nums);
		int pointerLow = 0;
		int pointerHigh = n - 1;
		for(int i = 0; i < n; i += 0) {
			ans[i] = nums[pointerHigh];
			if(i + 1 != n) {
				ans[i + 1] = nums[pointerLow];
			}
			pointerHigh --;
			pointerLow ++;
			i += 2;
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 1; i < n - 1; i++) {
			if(ans[i] < ans[i + 1] && ans[i] < ans[i - 1]) {
				count ++;
			}
		}
		fout.append(count).append("\n");
		for(int i = 0; i < n; i++) {
			fout.append(ans[i]).append(" ");
		}
		int count2 = 0;
		int[] ans2 = new int[n];
		pointerLow = n / 2 - 1;
		pointerHigh = n - 1;
		for(int i = 0; i < n; i += 0) {
			ans2[i] = nums[pointerHigh];
			if(i + 1 != n) {
				ans2[i + 1] = nums[pointerLow];
			}
			pointerHigh --;
			pointerLow --;
			i += 2;
		}
		for(int i = 1; i < n - 1; i++) {
			if(ans2[i] < ans2[i + 1] && ans2[i] < ans2[i - 1]) {
				count2 ++;
			}
		}
		StringBuilder fout2 = new StringBuilder();
		fout2.append(count2).append("\n");
		for(int i = 0; i < n; i++) {
			fout2.append(ans2).append(" ");
		}
		if(count2 > count) {
			System.out.println(fout2);
		}
		else {
			System.out.println(fout);
		}
	
	}
}
