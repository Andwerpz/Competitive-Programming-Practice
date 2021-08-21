//package excitingbets;

import java.util.*;
import java.io.*;

public class excitingbets {
	public static void main(String[] args) throws IOException {
		
		//1543C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long a = Long.parseLong(st.nextToken());
			long b = Long.parseLong(st.nextToken());
			long diff = Math.abs(a - b);
			if(diff == 0) {
				fout.append("0 0\n");
			}
			else {
				long mod = Math.max(a, b) % diff;
				long minMoves = Math.min(mod, diff - mod);
				fout.append(diff).append(" ").append(minMoves).append("\n");
			}
		}
		System.out.print(fout);
	}
}	
