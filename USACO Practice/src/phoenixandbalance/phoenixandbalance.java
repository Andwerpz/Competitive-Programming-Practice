//package phoenixandbalance;

import java.util.*;
import java.io.*;

public class phoenixandbalance {
	public static void main(String[] args) throws IOException {
		
		//1348A
		
		//what is the number that you can get a to that will minimize |a - b|? it is 1/2 of (2^1 + 2^2 + 2^3 ... + 2^n). 
		//to get close you can set a equal to 2^n + (2^1 + 2^2 ... + 2^(n / 2 - 1)). 
		
		//set b equal to the sum of the remaining bits, and get the answer from there.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int a = 0;
			int b = 0;
			for(int i = 1; i <= n; i++) {
				a |= (1 << i);
			}
			for(int i = n - 1; i > (n - 1) - (n / 2); i--) {
				b |= (1 << i);
			}
			a -= b;
			//System.out.println(a + " " + b);
			fout.append(Math.abs(a - b)).append("\n");
		}
		System.out.print(fout);
	}
}
