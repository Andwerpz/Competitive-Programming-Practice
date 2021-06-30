//package evenpath;

import java.util.*;
import java.io.*;

public class evenpath {
	public static void main(String[] args) throws IOException {
		
		//1252C
		
		//if you graph out where the even numbers are for any given two sides, you'll find that it forms a gridlike pattern. This is because the sum of two numbers is either even or odd,
		//and when you add different numbers to the set of numbers, the evenness of the product will just alternate between two presets. Now the solution becomes trivial, 
		//just go down the line of both row and col and group them up into adjacent even and odd groups. If both the starting and destination row and starting and destination column are in the same group,
		//then there is an even path between them.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());
		int[] row = new int[n];
		int[] col = new int[n];
		boolean isEven = false;
		st = new StringTokenizer(fin.readLine());
		int pointer = 0;
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			if(next % 2 == 0 != isEven) {
				pointer ++;
				isEven = next % 2 == 0;
			}
			row[i] = pointer;
		}
		st = new StringTokenizer(fin.readLine());
		pointer = 0;
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			if(next % 2 == 0 != isEven) {
				pointer ++;
				isEven = next % 2 == 0;
			}
			col[i] = pointer;
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < q; i++) {
			st = new StringTokenizer(fin.readLine());
			int r1 = Integer.parseInt(st.nextToken()) - 1;
			int c1 = Integer.parseInt(st.nextToken()) - 1;
			int r2 = Integer.parseInt(st.nextToken()) - 1;
			int c2 = Integer.parseInt(st.nextToken()) - 1;
			if(row[r1] == row[r2] && col[c1] == col[c2]) {
				fout.append("YES\n");
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
