//package mochaandhiking;

import java.util.*;
import java.io.*;

public class mochaandhiking {
	public static void main(String[] args) throws IOException {
		
		//1559C
		
		//there always is a solution. 
		
		//if all paths from village n + 1 are outgoing, then start at village n + 1, then go to village 1 - n. 
		
		//else, then there is a path from villages 1 - n to vilage n + 1. 
		
		//if there is a path from village n to n + 1, then just go in order from 1 - n + 1. 
		
		//else, then there must exist a situation where at village i, 1 <= i <= n, where there is a path from i to n + 1, and from n + 1 to i + 1. Just start from village 1 and go to village i. Then go to n + 1
		//and back to i + 1, where you continue all the way to village n.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] c = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			boolean isValid = false;
			for(int i = 0; i < n; i++) {
				c[i] = Integer.parseInt(st.nextToken());
				c[i] = c[i] == 1? 0 : 1;
				if(c[i] == 1) {
					isValid = true;
				}
			}
			if(isValid) {
				boolean visited = false;
				for(int i = 0; i < n; i++) {
					fout.append(i + 1).append(" ");
					if(!visited) {
						if(i == n - 1 && c[i] == 1) {
							visited = true;
							fout.append(n + 1).append(" ");
						}
						else if(i != n - 1 && c[i] == 1 && c[i + 1] == 0) {
							visited = true;
							fout.append(n + 1).append(" ");
						}
					}
				}
				fout.append("\n");
			}
			else {
				fout.append(n + 1).append(" ");
				for(int i = 0; i < n; i++) {
					fout.append(i + 1).append(" ");
				}
				fout.append("\n");
			}
		}
		System.out.print(fout);
	}
}
