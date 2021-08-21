//package kthlargestvalue;

import java.util.*;
import java.io.*;

public class kthlargestvalue {
	public static void main(String[] args) throws IOException {
		
		//1491A
		
		//notice that the values are only 0 and 1
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		int[] nums = new int[n];
		int num1 = 0;
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			if(nums[i] == 1) {
				num1 ++;
			}
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < q; i++) {
			st = new StringTokenizer(fin.readLine());
			int t = Integer.parseInt(st.nextToken());
			int a = Integer.parseInt(st.nextToken());
			if(t == 1) {
				a --;
				if(nums[a] == 0) {
					num1 ++;
					nums[a] = 1;
				}
				else {
					num1 --;
					nums[a] = 0;
				}
			}
			else {
				fout.append(num1 >= a? 1 : 0).append("\n");
			}
		}
		System.out.print(fout);
	}
}
