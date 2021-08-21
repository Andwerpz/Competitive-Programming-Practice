//package digitssum;

import java.util.*;
import java.io.*;

public class digitssum {
	public static void main(String[] args) throws IOException {
		
		//1553A
		
		//you need to find out how many numbers start with 9, if you were to count from 1 -> n. if n >= 9, then subtract 9 from n, and add to that, how many times 10 goes into what's left.
		//else, the answer is 0.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int ans = 0;
			n -= 9;
			if(n >= 0) {
				ans ++;
				ans += n / 10;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
