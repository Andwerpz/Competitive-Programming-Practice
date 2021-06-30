//package platformsjumping;

import java.util.*;
import java.io.*;

public class platformsjumping {
	public static void main(String[] args) throws IOException {
		
		//1256C
		
		//just move the platforms wherever you need them
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		d--;
		int numWater = 0;
		int numPlank = 0;
		int[] planks = new int[m];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < m; i++) {
			planks[i] = Integer.parseInt(st.nextToken());
			numPlank += planks[i];
		}
		numWater = n - numPlank;
		int pointer = 1;
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < m; i++) {
			int jump = d;
			for(int j = Math.min(jump, numWater); j > 0; j--) {
				fout.append("0 ");
				numWater --;
			}
			int next = planks[i];
			for(int j = 0; j < next; j++) {
				fout.append(pointer).append(" ");
			}
			pointer ++;
		}
		if(numWater <= d) {
			for(int i = 0; i < numWater; i++) {
				fout.append("0 ");
			}
			System.out.println("YES\n" + fout);
		}
		else {
			System.out.println("NO");
		}
	}
}
