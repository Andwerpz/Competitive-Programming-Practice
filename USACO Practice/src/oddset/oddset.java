//package oddset;

import java.util.*;
import java.io.*;

public class oddset {
	public static void main(String[] args) throws IOException {
		
		//1542A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int odd = 0;
			int even = 0;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n * 2; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(next % 2 == 0) {
					even ++;
				}
				else {
					odd ++;
				}
			}
			if(odd == even) {
				fout.append("Yes\n");
			}
			else {
				fout.append("No\n");
			}
		}
		System.out.print(fout);
	}
}
