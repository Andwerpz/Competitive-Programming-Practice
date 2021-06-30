//package routineproblem;

import java.util.*;
import java.io.*;

public class routineproblem {
	
	public static int gcd(int a, int b) {
		int gcd = 1;
		for(int i = 2; i <= Math.min(a, b); i++) {
			while(a % i == 0 && b % i == 0) {
				gcd *= i;
				a /= i;
				b /= i;
			}
		}
		return gcd;
	}
	
	public static void main(String[] args) throws IOException {
		
		//337B
		
		//too lazy to write up an explanation for this problem, just refer to the editorial
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		if(b > a) {
			int temp = a;
			a = b;
			b = temp;
			temp = c;
			c = d;
			d = temp;
		}
		a *= c * d;
		b *= c * d;
		//System.out.println(a + " " + b);
		if(d * (a / c) <= b) {	//scaling horizontal side up; sides a and c
			int numerator = b - (d * (a / c));
			int denominator = b;
			int gcd = gcd(numerator, denominator);
			numerator /= gcd;
			denominator /= gcd;
			if(numerator == 0) {
				denominator = 1;
			}
			System.out.println(numerator + "/" + denominator);
		}
		else if(c * (b / d) <= a) {	//scaling up vertical side; sides b and d
			int numerator = a - (c * (b / d));
			int denominator = a;
			int gcd = gcd(numerator, denominator);
			numerator /= gcd;
			denominator /= gcd;
			if(numerator == 0) {
				denominator = 1;
			}
			System.out.println(numerator + "/" + denominator);
		}
	}
}
