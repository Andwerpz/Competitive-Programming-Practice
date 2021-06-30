//package serejaandcontests;

import java.util.*;
import java.io.*;

public class serejaandcontests {
	public static void main(String[] args) throws IOException {
		
		//401B
		
		//for each segment of missed contests, sereja can either assume that they were all div2 to get the maximum missed, or he can assume that they were
		//all combined contests, for the minimum. To get the minimum, you also need to keep in mind that combined contests are in groups of two, so if you have an odd
		//number, you must add one, since a div 1 contest can't be hosted without a div 2 contest.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int x = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		boolean[] attended = new boolean[x];
		attended[x - 1] = true;
		for(int i = 0; i < k; i++) {
			st = new StringTokenizer(fin.readLine());
			int which = Integer.parseInt(st.nextToken());
			if(which == 1) {
				int a = Integer.parseInt(st.nextToken()) - 1;
				int b = Integer.parseInt(st.nextToken()) - 1;
				attended[a] = true;
				attended[b] = true;
			}
			else {
				int a = Integer.parseInt(st.nextToken()) - 1;
				attended[a] = true;
			}
		}
		int max = 0;
		int min = 0;
		int count = 0;
		for(int i = 0; i < x; i++) {
			if(attended[i] && count != 0) {
				max += count;
				min += (count / 2) + count % 2;
				count = 0;
			}
			if(!attended[i]) {
				count ++;
			}
		}
		System.out.println(min + " " + max);
	}
}
