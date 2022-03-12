//package squarecounting;

import java.util.*;
import java.io.*;

public class squarecounting {
	public static void main(String[] args) throws IOException {
		
		//1646A
		
		//notice that the value generated with no squares, n * (n + 1) / 2, is less than n * n.
		
		//thus, just see how many times n^2 fits into s, and that is the answer.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long n = Long.parseLong(st.nextToken());
			long s = Long.parseLong(st.nextToken());
			fout.append(s / (n * n)).append("\n");
		}
		System.out.print(fout);
	}
}
