//package findthearray;

import java.util.*;
import java.io.*;

public class findthearray {
	public static void main(String[] args) throws IOException {
		
		//1550A
		
		//solved using a greedy approach: start with 1, and then count up by 2. When the next count is greater than the remaining sum, then stop there.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int s = Integer.parseInt(fin.readLine());
			int ans = 0;
			int sum = 0;
			int pointer = 1;
			while(true) {
				sum += pointer;
				ans ++;
				pointer += 2;
				if(sum == s) {
					break;
				}
				if(s - sum <= pointer) {
					ans ++;
					break;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
