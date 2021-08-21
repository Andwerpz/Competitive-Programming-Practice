//package cogrowingsequence;

import java.util.*;
import java.io.*;

public class cogrowingsequence {
	public static void main(String[] args) throws IOException {
		
		//1547D
		
		//since you want to find the lexographic minimum array that you can have as the second one, you need to minimize each value at every step, going from left to right.
		//for each number, look at the next number, and if the first number is missing any bits from the second number, then add them using the y array. only add bits, 
		//don't remove any, since we want to minimize the value of y at every step.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int prev = 0;
			for(int i = 0; i < n; i++) {
				int next = nums[i];
				int add = 0;
				for(int j = 0; j < 30; j ++) {
					if(((1 << j) | prev) == prev && ((1 << j) | next) != next) {
						add += (1 << j);
					}
				}
				fout.append(add).append(" ");
				prev = next + add;
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
