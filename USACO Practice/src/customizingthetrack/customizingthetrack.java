//package customizingthetrack;

import java.util.*;
import java.io.*;

public class customizingthetrack {
	public static void main(String[] args) throws IOException {
		
		//1543C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long sum = 0;
			for(int i = 0; i < n; i++) {
				sum += Long.parseLong(st.nextToken());
			}
			sum %= n;
			long ans = sum * (n - sum);
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
