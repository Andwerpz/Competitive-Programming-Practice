package trailinglovesorloeufs;

import java.util.*;
import java.io.*;

public class trailinglovesorloeufs {
	public static void main(String[] args) throws IOException {
		
		//1114C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		long n = Integer.parseInt(st.nextToken());
		long b = Integer.parseInt(st.nextToken());
		long remainder = n % b;
		long multiple = n / b;
		long ans = 0;
		for(int i = 1; i <= (int) Math.sqrt(b); i++) {
			if(b % i == 0) {
				long add = multiple;
				long a = b / i;
				System.out.println(i + " " + a);
				if(a <= remainder) {
					multiple ++;
				}
				long amt = 
				ans += (multiple * (multiple + 1)) / 2;
			}
		}
		System.out.println(ans);
	}
}
