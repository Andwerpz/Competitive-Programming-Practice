//package minorreduction;

import java.util.*;
import java.io.*;

public class minorreduction {
	public static void main(String[] args) throws IOException {
		
		//1626B
		
		//first, look for a situation where you can sum two numbers to over 10. This will preserve the digit count.
		//prioritize combining the lowest place value numbers.
		
		//if no such situation exists, combine the two leading digits. This will make so that the new number has the highest possible
		//leading digit.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			String x = fin.readLine();
			boolean found = false;
			//back to front. Check for sums greater than 9
			for(int i = x.length() - 1; i > 0; i--) {
				int cur = Integer.parseInt(x.substring(i, i + 1));
				int next = Integer.parseInt(x.substring(i - 1, i));
				if(cur + next >= 10) {
					found = true;
					fout.append(x.substring(0, i - 1)).append(cur + next).append(x.substring(i + 1, x.length())).append("\n");
					break;
				}
			}
			if(found) {
				continue;
			}
			int a = Integer.parseInt(x.substring(0, 1));
			int b = Integer.parseInt(x.substring(1, 2));
			fout.append(a + b).append(x.substring(2, x.length())).append("\n");
		}
		System.out.print(fout);
	}
}
