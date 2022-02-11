//package okea;

import java.util.*;
import java.io.*;

public class okea {
	public static void main(String[] args) throws IOException {
		
		//1634C
		
		//A number by itself on a row is always good. 
		
		//two numbers on a row both have to be odd, or even. This will extend to n numbers, since all adjacent numbers have to be odd or even. 
		//so, when setting up the shelves, all numbers sharing a row must also share the same parity. 
		
		//notice that if numbers increase by a constant even rate from left to right within a shelf,
		//they are always good.
		
		//so the solution is to iterate from the top to bottom row, left to right. 
		//put in even numbers first, and when you run out, put in odd numbers, always in increments of 2. 
		
		//if there ever comes a time when you must put an odd and an even number in a row, then the situation is invalid. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			if(k == 1) {
				fout.append("YES\n");
				for(int i = 0; i < n; i++) {
					fout.append(i + 1).append("\n");
				}
				continue;
			}
			else if(n % 2 == 1 || (n * k) % 2 == 1) {
				fout.append("NO\n");
				continue;
			}
			fout.append("YES\n");
			int e = 2;
			int o = 1;
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < k; j++) {
					if(i % 2 == 0) {
						fout.append(e).append(" ");
						e += 2;
					}
					else {
						fout.append(o).append(" ");
						o += 2;
					}
				}
				fout.append("\n");
			}
		}
		System.out.print(fout);
	}
}
