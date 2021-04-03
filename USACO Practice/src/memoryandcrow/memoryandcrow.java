//package memoryandcrow;

import java.util.*;
import java.io.*;

public class memoryandcrow {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine() + " 0");
		StringBuilder fout = new StringBuilder();
		int a = Integer.parseInt(st.nextToken());
		int b = 0;
		for(int i = 0; i < n; i++) {
			b = a;
			a = Integer.parseInt(st.nextToken());
			fout.append((b + a) + " ");
		}
		fout.deleteCharAt(fout.length() - 1);
		System.out.println(fout);
	}
}
