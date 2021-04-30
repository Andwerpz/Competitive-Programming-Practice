//package sumof2050;

import java.util.*;
import java.io.*;

public class sumof2050 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		long base = 2050;
		while(t-- > 0) {
			long num = Long.parseLong(fin.readLine());
			long power = 0;
			while(base * (long)Math.pow(10, power) <= num) {
				power ++;
			}
			//System.out.println(base * (long)Math.pow(10, 0) + " " + power);
			power --;
			boolean isValid = true;
			if(power == -1) {
				//System.out.println("not valid");
				isValid = false;
			}
			int ans = 0;
			for(long i = power; i >= 0; i--) {
				long next = (long) (base * Math.pow(10, i));
				while(num >= next) {
					//System.out.println("loop");
					num -= next;
					ans ++;
				}
				if(num < 2050 && num != 0) {
					isValid = false;
				}
			}
			if(isValid) {
				fout.append(ans).append("\n");
			}
			else {
				fout.append("-1\n");
			}
		}
		System.out.print(fout);
	}
}
