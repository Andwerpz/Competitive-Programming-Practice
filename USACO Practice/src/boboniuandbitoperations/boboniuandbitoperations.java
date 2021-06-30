//package boboniuandbitoperations;

import java.util.*;
import java.io.*;

public class boboniuandbitoperations {
	
	static int[] a;
	static int[] b;
	
	public static boolean isValid(int val) {
		for(int i = 0; i < a.length; i++) {
			boolean isValid = false;
			for(int j = 0; j < b.length; j++) {
				if(((a[i] & b[j]) | val) == val) {
					isValid = true;
					break;
				}
			}
			if(!isValid) {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1395C
		
		//since the range of values is so low, (0 - 2^9), we can just check for each value if it is valid, and take the smallest one. In order a value x to be valid, 
		//some combination of (a[i] & b[j]) | x must equal to x. So for each value in a, if this holds true for any value from b, then x is valid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		a = new int[n];
		b = new int[m];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			a[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < m; i++) {
			b[i] = Integer.parseInt(st.nextToken());
		}
		int ans = 0;
		for(int i = 0; i <= (int) Math.pow(2, 9); i++) {
			if(isValid(i)) {
				ans = i;
				break;
			}
		}
		System.out.println(ans);
	}
}
