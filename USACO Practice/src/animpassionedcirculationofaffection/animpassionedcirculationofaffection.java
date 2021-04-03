//package animpassionedcirculationofaffection;

import java.util.*;
import java.io.*;

public class animpassionedcirculationofaffection {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		String g = fin.readLine();
		int q = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(q-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int m = Integer.parseInt(st.nextToken());
			char c = st.nextToken().charAt(0);
			int low = 0;
			int high = -1;
			int extra = 0;
			int max = m;
			while(high < n) {
				//System.out.println(low + " " + high + " " + extra);
				if(high - low + 1 > max) {
					max = high - low + 1;
					if(max == n) {
						break;
					}
				}
				if(high - low - extra + 1< m || (high + 1 < n && g.charAt(high + 1) == c)) {
					//System.out.println(high - low - extra + " " + m);
					high++;
					if(g.charAt(high % n) == c) {
						extra++;
					}
				}
				else if(high - low - extra + 1 >= m) {
					if(low != -1 && g.charAt(low % n) == c) {
						extra--;
					}
					low++;
				}
			}
			System.out.println();
			fout.append(max).append("\n");
		}
		System.out.print(fout);
	}
}
