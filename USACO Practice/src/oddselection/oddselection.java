//package oddselection;

import java.util.*;
import java.io.*;

public class oddselection {
	public static void main(String[] args) throws IOException {
		
		//1363A
		
		//this one was kinda annoying.
		
		//just pick as many numbers from the odd category as you can. Make sure the amount that you picked is odd. Then fill up the remaining spaces with even numbers.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			int numOdd = 0;
			int numEven = 0;
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(next % 2 == 1) {
					numOdd ++;
				}
				else {
					numEven ++;
				}
			}
			boolean isValid = false;
			if(numOdd != 0) {
				int selectedOdd = 0;
				selectedOdd ++;
				numOdd --;
				while(selectedOdd + 2 <= x && numOdd >= 2) {
					selectedOdd += 2;
					numOdd -= 2;
				}
				int diff = x - selectedOdd;
				if(numEven >= diff) {
					isValid = true;
				}
			}	
			fout.append(isValid? "Yes\n" : "No\n");
		}
		System.out.print(fout);
	}
}
