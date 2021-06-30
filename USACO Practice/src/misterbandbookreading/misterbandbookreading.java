//package misterbandbookreading;

import java.util.*;
import java.io.*;

public class misterbandbookreading {
	public static void main(String[] args) throws IOException {
		
		//820A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int c = Integer.parseInt(st.nextToken());
		int v0 = Integer.parseInt(st.nextToken());
		int v1 = Integer.parseInt(st.nextToken());
		int a = Integer.parseInt(st.nextToken());
		int l = Integer.parseInt(st.nextToken());
		boolean done = false;
		int prev = 0;
		int diff = v0;
		int ans = 0;
		//System.out.println("L: " + l);
		boolean reviewed = false;
		while(!done) {
			
			ans ++;
			int curDiff = diff;
			if(reviewed) {
				//System.out.println("REVIEWED: " + l);
				curDiff -= l;
			}
			c -= curDiff;
			//System.out.println("C: " + c + " DIFF: " + diff);
			diff += a;
			diff = Math.min(diff, v1);
			reviewed = true;
			if(c <= 0) {
				break;
			}
		}
		System.out.println(ans);
	}
}
