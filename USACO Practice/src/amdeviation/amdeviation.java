//package amdeviation;

import java.util.*;
import java.io.*;

public class amdeviation {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			int diff = Math.abs((a + c) - b * 2);
			//System.out.println(a + " " + b + " " + c);
			diff %= 3;
			fout.append(diff == 0? 0 : 1).append("\n");
		}
		System.out.print(fout);
	}
}
