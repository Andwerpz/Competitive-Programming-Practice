//package gcdarrays;

import java.util.*;
import java.io.*;

public class gcdarrays {
	public static void main(String[] args) throws IOException {
		
		//1629B
		
		//notice that if gcd(a) == x, then all members of a must be multiples of x. 
		
		//if we were to make gcd(a) == 2, then we would need to remove all odd numbers. Making gcd(a) == 2 as our
		//goal makes it so that we have to remove the least amount of numbers from the array. 
		
		//an operation effectively removes numbers because the product inserted into the array has the other desired number as a factor
		//of it.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int l = Integer.parseInt(st.nextToken());
			int r = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			if(l == r) {
				fout.append(l == 1? "NO\n" : "YES\n");
				continue;
			}
			int numOdd = 0;
			int diff = r - l + 1;
			if(l % 2 == 1) {
				numOdd ++;
				diff --;
			}
			numOdd += diff / 2;
			fout.append(k >= numOdd? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
