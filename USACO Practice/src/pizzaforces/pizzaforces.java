//package pizzaforces;

import java.util.*;
import java.io.*;

public class pizzaforces {
	public static void main(String[] args) throws IOException {
		
		//1555A
		
		//you can make any even number greater than 6.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			long n = Long.parseLong(fin.readLine());
			long ans = 0;
			if(n <= 6) {
				ans = 15;
			}
			else {
				if(n % 2 == 1) {
					n ++;
				}
				ans = (n / 2) * 5;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
