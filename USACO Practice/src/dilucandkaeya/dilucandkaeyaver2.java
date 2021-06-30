package dilucandkaeya;

import java.util.*;
import java.awt.Point;
import java.io.*;

public class dilucandkaeyaver2 {
	
	public static int gcd(int a, int b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1536C
		
		//lets say you have d amount of 'D's and k amount of 'K's. if you want to split it into parts of equal ratio, then all of the ratios of the parts must adhere to the original
		//d : k ratio. So you can go along, and save every ratio you come across, then the answer to any given prefix is equal to the amount of times you have seen the prefix's
		//ratio before.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			HashMap<Point, Integer> ratios = new HashMap<Point, Integer>();
			int d = 0;
			int k = 0;
			for(int i = 0; i < n; i++) {
				if(s[i] == 'D') {
					d ++;
				}
				else {
					k ++;
				}
				Point p;
				if(d == 0) {
					p = new Point(0, 1);
				}
				else if(k == 0) {
					p = new Point(1, 0);
				}
				else {
					int gcd = gcd(d, k);
					//System.out.println(d + " " + k + " " + gcd);
					p = new Point(d / gcd, k / gcd);
				}
				//System.out.println(p);
				ratios.put(p, ratios.getOrDefault(p, 0) + 1);
				fout.append(ratios.get(p)).append(" ");
			}
			//System.out.println();
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
