//package oddswapsort;

import java.util.*;
import java.io.*;

public class oddswapsort {
	public static void main(String[] args) throws IOException {
		
		//1638B
		
		//notice that although you cannot swap two odd or two even numbers in the array, you can swap one even and one odd
		//number. 
		
		//this means that the relative order of all odd numbers, and all even numbers are fixed, but between odd and even numbers
		//you can order them however you like
		
		//so you can split the array into odds and evens, and just check if those seperate ones are sorted.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int prevEven = 0;
			int prevOdd = 0;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			boolean isValid = true;
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(next % 2 == 0) {
					if(next < prevEven) {
						isValid = false;
						break;
					}
					prevEven = next;
				}
				else {
					if(next < prevOdd) {
						isValid = false;
						break;
					}
					prevOdd = next;
				}
			}
			fout.append(isValid? "Yes\n" : "No\n");
		}
		System.out.print(fout);
	}
}
