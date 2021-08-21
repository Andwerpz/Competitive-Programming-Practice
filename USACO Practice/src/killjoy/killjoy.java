//package killjoy;

import java.util.*;
import java.io.*;

public class killjoy {
	public static void main(String[] args) throws IOException {
		
		//1419C
		
		//you can make every number except for 1 equal to x on the first move, and then on the second move, just make the last number equal to x. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			boolean hasX = false;
			boolean allX = true;
			int avg = 0;
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				avg += next;
				if(next == x) {
					hasX = true;
				}
				else {
					allX = false;
				}
			}
			boolean avgX = (avg % n == 0 && avg / n == x);
			fout.append(allX? "0\n" : (hasX? "1\n" : (avgX? "1\n" : "2\n")));
		}
		System.out.print(fout);
	}
}
