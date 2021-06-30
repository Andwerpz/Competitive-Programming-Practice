//package rowgcd;

import java.util.*;
import java.io.*;

public class rowgcd {
	
	public static long gcd(long a, long b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1458A
		
		//the differences between the numbers is key. Lets say that i have an array a, and all the numbers, if added some x, can be divided by y. Then it must hold true that for any two numbers in a, 
		//the difference must also be divisible by y. This is true since if all of a can be divisible by y, then they must be multiples of y, and their differences must be divisible by y. 
		//So what you do is get the gcd of all the differences in array a, then for each number in array b, the answer is gcd(diffgcd, a[0] + b[i]). Pick any number in a
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		long[] a = new long[n];
		long[] b = new long[m];
		for(int i = 0; i < n; i++) {
			a[i] = Long.parseLong(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < m; i++) {
			b[i] = Long.parseLong(st.nextToken());
		}
		Arrays.sort(a);
		long diffgcd = 0;
		for(int i = 0; i < n; i++) {
			if(i != 0 && a[i] != a[i - 1]) {
				if(diffgcd == 0) {
					diffgcd = a[i] - a[i - 1];
				}
				else {
					diffgcd = gcd(diffgcd, a[i] - a[i - 1]);
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0 ; i < m; i++) {
			fout.append(diffgcd == 0? (a[0] + b[i]) : gcd(diffgcd, a[0] + b[i])).append(" ");
		}
		System.out.println(fout);
	}
}
