//package infinitefence;

import java.util.*;
import java.io.*;

public class infinitefence {
	
	public static long getMax(long a, long b) {
		b -= 1;
		long ans = b / a + 1;
		if(b % a == 0) {
			ans --;
		}
		return ans;
	}
	
	public static long gcd(long a, long b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1260C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long r = Integer.parseInt(st.nextToken());
			long b = Integer.parseInt(st.nextToken());
			long k = Integer.parseInt(st.nextToken());
			long gcd = gcd(r, b);
			r /= gcd;
			b /= gcd;
			long max = getMax(Math.min(r, b), Math.max(r, b));
			fout.append(max >= k? "REBEL\n" : "OBEY\n");
		}
		System.out.print(fout);
	}
}
