//package banquetpreparations1;

import java.util.*;
import java.io.*;

public class banquetpreparations1 {
	public static void main(String[] args) throws IOException {
		
		//1607G
		
		//find the difference between a and b when you eat as much meat as possible, then find the difference when you only eat fish. 
		//notice that you can make nearly every value in between them. Nearly, since every time you switch a piece of meat for a 
		//piece of fish, you actually change the distance from a to b by 2. So you can only make every other one. 
		
		//To solve, start with only eating meat or fish, and then for each meal, change it to eating the other type of food, until the
		//difference is minimized. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			fin.readLine();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			long m = Integer.parseInt(st.nextToken());
			long[][] meals = new long[n][2];
			for(int i = 0; i < n; i++) {
				st = new StringTokenizer(fin.readLine());
				meals[i][0] = Integer.parseInt(st.nextToken());
				meals[i][1] = Integer.parseInt(st.nextToken());
			}
			long[][] eaten = new long[n][2];
			long a = 0;
			long b = 0;
			//first eat as much a as possible
			for(int i = 0; i < n; i++) {
				long aEaten = Math.min(meals[i][0], m);
				eaten[i][0] = aEaten;
				eaten[i][1] = m - aEaten;
				a += meals[i][0] - eaten[i][0];
				b += meals[i][1] - eaten[i][1];
				//System.out.println(eaten[i][0] + " " + eaten[i][1]);
			}
			//now, switch to eating b, until you get a and b equal
			long diff = b - a;
			//System.out.println(diff);
			for(int i = 0; i < n; i++) {
				if(diff <= 1) {
					break;
				}
				long maxChange = Math.min((long) Math.min(m, diff / 2), Math.min(meals[i][1] - eaten[i][1], eaten[i][0]));
				diff -= maxChange * 2;
				eaten[i][0] -= maxChange;
				eaten[i][1] += maxChange;
			}
			fout.append(Math.abs(diff)).append("\n");
			for(int i = 0; i < n; i++) {
				fout.append(eaten[i][0]).append(" ").append(eaten[i][1]).append("\n");
			}
		}
		System.out.print(fout);
	}
}
