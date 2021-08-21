//package arena;

import java.util.*;
import java.io.*;

public class arena {
	public static void main(String[] args) throws IOException {
		
		//1487A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int min = Integer.MAX_VALUE;
			int numMin = 0;
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(next < min) {
					min = next;
					numMin = 1;
				}
				else if(min == next) {
					numMin ++;
				}
			}
			fout.append(n - numMin).append("\n");
		}
		System.out.print(fout);
	}
}
