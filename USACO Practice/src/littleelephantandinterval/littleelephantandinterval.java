//package littleelephantandinterval;

import java.util.*;
import java.io.*;

public class littleelephantandinterval {
	
	public static long solve(long a) {
		if(a < 10) {
			return a;
		}
		else if(a < 100) {
			//System.out.println(a / 11 + 9);
			return a / 11 + 9;
		}
		else {
			String num = a + "";
			long pow = num.length() - 1;
			long div = (long) Math.pow(10, pow) + 1;
			long count = (a % div) / 10 + 1;
			long howMany = (long) (a / div) - 1;
			count += howMany == -1? -1 : 0;
			long increment = 10;
			for(int i = 0; i < pow - 2; i++) {
				increment *= 10;

			}
			count += increment * howMany;
			//System.out.println(div + " " + count + " " + a + " " + howMany + " " + pow);
			String next = "";
			for(int i = 0; i < pow; i++) {
				next += "9";
			}
			//System.out.println(next);
			return count + solve(Long.parseLong(next));
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		long a = Long.parseLong(st.nextToken()) - 1;
		long b = Long.parseLong(st.nextToken());
		System.out.println(solve(b) - solve(a));
	}
}
