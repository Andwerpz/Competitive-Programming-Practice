//package funwithevensubarrays;

import java.util.*;
import java.io.*;

public class funwithevensubarrays {
	public static void main(String[] args) throws IOException {
		
		//1631B
		
		//notice that the operation that you can perform on the array doesn't let you change the last number in the array.
		//this is because when choosing the 2k numbers to change, you must change the first k numbers to equal the last
		//k numbers, and the last number in the array can never be in the first k. 
		
		//this means that you must make the entire array to equal the last number in the array.
		//from here, you can just simulate it.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int last = nums[n - 1];
			int ans = 0;
			int p = n - 1;
			int amt = 0;
			outer:
			while(true) {
				if(p == -1) {
					break;
				}
				while(nums[p] == last) {
					p --;
					amt ++;
					if(p == -1) {
						break outer;
					}
				}
				ans ++;
				for(int i = 0; i < amt; i++) {
					if(p == -1) {
						break outer;
					}
					nums[p] = last;
					p --;
				}
				amt *= 2;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
