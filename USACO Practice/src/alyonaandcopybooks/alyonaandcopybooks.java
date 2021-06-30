//package alyonaandcopybooks;

import java.util.*;
import java.io.*;

public class alyonaandcopybooks {
	public static void main(String[] args) throws IOException {
		
		///740A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long a = Integer.parseInt(st.nextToken());
		long b = Integer.parseInt(st.nextToken());
		long c = Integer.parseInt(st.nextToken());
		long ans = 0;
		//System.out.println(n % 4);
		if(n % 4 == 1) {
			ans = Math.min(a * 3, c);
			ans = Math.min(ans, a + b);
		}
		else if(n % 4 == 2) {
			ans = Math.min(b, a * 2);
			ans = Math.min(ans, c * 2);
		}
		else if(n % 4 == 3){
			ans = a;
			ans = Math.min(ans, c + b);
			ans = Math.min(c * 3, ans);
		}
		else {
			ans = 0;
		}
		System.out.println(ans);
	}
}
