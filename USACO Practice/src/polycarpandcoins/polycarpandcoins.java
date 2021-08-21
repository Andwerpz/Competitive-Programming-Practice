//package polycarpandcoins;

import java.util.*;
import java.io.*;

public class polycarpandcoins {
	public static void main(String[] args) throws IOException {
		
		//1551A
		
		//find the number of 3 groups. The remaining amount can be either a 1 or 2.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int ans1 = 0;
			int ans2 = 0;
			int multiple = n / 3;
			int remainder = n % 3;
			ans1 = multiple + (remainder == 1? 1 : 0);
			ans2 = multiple + (remainder == 2? 1 : 0);
			fout.append(ans1).append(" ").append(ans2).append("\n");
		}
		System.out.print(fout);
	}
}
