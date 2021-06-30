//package maximumsumofproducts;

import java.util.*;
import java.io.*;

public class maximumsumofproducts {
	public static void main(String[] args) throws IOException {
		
		//Educational 108 D
		
		//reverse subsegment of array a to generate the maximum sum. Only allowed to reverse one subsegment.
		//The naive approach is to try all possible subsegments, and reverse them. Going through all possible subsegments is an n^2 operation, and 
		//if you were to recalculate every time, the complexity would go up to n^3. Not fast enough.
		//you don't need to recalculate. Instead of keeping track of the beginning of the subsegment, keep track of the middle of the subsegment. 
		//if you want to expand the subsegment, then all you have to do is compute the two numbers at the edges. 
		//in this solution, i also use a pfx sum array to keep track of the rest of the numbers in O(1) time.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long[] a = new long[n];
		long[] b = new long[n];
		long[] pfx = new long[n + 1];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			a[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			b[i] = Integer.parseInt(st.nextToken());
			pfx[i + 1] = pfx[i] + (b[i] * a[i]);
		}
		long ans = pfx[n];
		for(int i = 0; i < n; i++) {	//1 center
			long sum = 0;
			sum += a[i] * b[i];
			for(int j = 1; j < n; j++) {
				//System.out.println(i - j + " " + (i + j));
				if(i - j < 0 || i + j >= n) {
					break;
				}
				else {
					sum += a[i - j] * b[i + j] + a[i + j] * b[i - j];
					long test = pfx[i - j] + sum + (pfx[n] - pfx[i + j + 1]);
					//System.out.println("TEST: " + test);
					ans = Math.max(ans, test);
				}
			}
		}
		for(int i = 0; i < n - 1; i++) {	//2 centers
			long sum = 0;
			sum += a[i] * b[i + 1];
			sum += a[i + 1] * b[i];
			for(int j = 0; j < n; j++) {
				//System.out.println(i - j + " " + (i + j));
				if(j == 0) {
					long test = pfx[i - j] + sum + (pfx[n] - pfx[i + j + 2]);
					ans = Math.max(ans, test);
				}
				else if(i - j < 0 || i + j + 1 >= n) {
					break;
				}
				else {
					sum += a[i - j] * b[i + j + 1] + a[i + j + 1] * b[i - j];
					long test = pfx[i - j] + sum + (pfx[n] - pfx[i + j + 2]);
					ans = Math.max(ans, test);
				}
			}
		}
		System.out.println(ans);
	}
}
