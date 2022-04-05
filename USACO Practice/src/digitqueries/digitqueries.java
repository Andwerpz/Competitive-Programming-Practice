//package digitqueries;

import java.util.*;
import java.io.*;

public class digitqueries {
	public static void main(String[] args) throws IOException {
		
		//CSES 2431
		
		//first find which order of magnitude the number falls in
		
		//then find the specific number, you can do this since you have the length of the number
		
		//finally find which digit it is 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			long n = Long.parseLong(fin.readLine()) - 1l;
			long magnitude = 0;
			long magSum = 9;
			while(n >= magSum * (magnitude + 1)) {
				n -= magSum * (magnitude + 1);
				//System.out.println(n + " " + magSum);
				magSum *= 10l;
				magnitude ++;
			}
			//System.out.println(n);
			long numLength = magnitude + 1;
			long whichNum = n / numLength + (long) (Math.pow(10, magnitude));
			long whichDigit = n % numLength;
			//System.out.println(whichNum + " " + magnitude + " " + String.valueOf(whichNum).length() + " " + whichDigit);
			fout.append(String.valueOf(whichNum).charAt((int) whichDigit)).append("\n");
		}
		System.out.print(fout);
	}
}
