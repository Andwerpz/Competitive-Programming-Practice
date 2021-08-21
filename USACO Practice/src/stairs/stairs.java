//package stairs;

import java.util.*;
import java.io.*;

public class stairs {
	public static void main(String[] args) throws IOException {
		
		//1419B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			long x = Long.parseLong(fin.readLine());
			long pointer = 1;
			long sum = 1;
			int ans = 0;
			while(x >= sum) {
				x -= sum;
				ans ++;
				pointer *= 2;
				pointer ++;
				sum = (pointer * (pointer + 1)) / 2;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
