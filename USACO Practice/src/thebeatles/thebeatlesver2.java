package thebeatles;

import java.util.*;
import java.io.*;

public class thebeatlesver2 {
	
	public static long gcd(long a, long b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1142A
		
		//you have to find the maximum and minimum possible stops that you could take given a, b, k and n. You first notice that all that you need are the distances
		//between the steps. If you know all the distances between steps, then for a given distance, the number of steps is equal to totalDist / gcd(totalDist, stepDist). 
		//The steps start with 1 of 4 possibilities; a + b, a - b, - a + b, - a - b. Then just increment using k from that point on.
		
		//note: first solution got tle because gcd function was too expensive. Use this new gcd function in the future.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		long n = Integer.parseInt(st.nextToken());
		long k = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		long min = Long.MAX_VALUE;
		long max = 0;
		long totalDist = n * k;
		for(int i = 0; i <= n; i++) {
			long d1 = (long) i * k + b - a;
			long d2 = (long) (i + 1) * k - b - a;
			if(d1 > 0) {
				long cur = totalDist / gcd(totalDist, d1);
				min = Math.min(cur, min);
				max = Math.max(cur, max);
			}
			if(d2 > 0) {
				long cur = totalDist / gcd(totalDist, d2);
				min = Math.min(cur, min);
				max = Math.max(cur, max);
			}
		}
		System.out.println(min + " " + max);
	}
}
