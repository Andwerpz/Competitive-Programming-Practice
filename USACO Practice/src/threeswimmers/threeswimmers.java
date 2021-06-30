//package threeswimmers;

import java.util.*;
import java.io.*;

public class threeswimmers {
	public static void main(String[] args) throws IOException {
		
		//1492A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long p = Long.parseLong(st.nextToken());
			long a = Long.parseLong(st.nextToken());
			long b = Long.parseLong(st.nextToken());
			long c = Long.parseLong(st.nextToken());
			long ans = Math.min((a - (p % a)) % a, Math.min((b - (p % b)) % b, (c - (p % c)) % c));
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
