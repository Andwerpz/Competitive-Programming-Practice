//package ihate1111;

import java.util.*;
import java.io.*;

public class ihate1111 {
	public static void main(String[] args) throws IOException {
		
		//1526B
		
		//first find the minimum amount of numbers needed to sum up to make a value greater than x. Then see if by reducing the numbers, you can make that value
		//equal to x. 111 = 10 * 11 + 1. You can remove 1s in this way.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int x = Integer.parseInt(fin.readLine());
			int pointer = 11;
			int diff = 0;
			while(x > 0) {
				while(pointer * 10 + 1 <= x) {
					pointer = pointer * 10 + 1;
				}
				while(pointer > 11 && pointer > x) {
					pointer /= 10;
				}
				//System.out.println("POINTER : " + pointer + " X: " + x);
				x -= pointer;
				diff += pointer / 100;
			}
			if(Math.abs(x) <= diff) {
				fout.append("YES\n");
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
