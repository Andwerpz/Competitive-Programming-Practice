//package minorsum;

import java.util.*;
import java.io.*;

public class minorsum {
	public static void main(String[] args) throws IOException {
		
		//1635A
		
		//notice that if you have one number equal to the or sum of all the numbers, 
		//you can make all the rest of the numbers equal to 0.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int ans = 0;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				ans |= Integer.parseInt(st.nextToken());
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
