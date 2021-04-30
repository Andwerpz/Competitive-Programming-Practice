//package vanyaandlanterns;

import java.util.*;
import java.io.*;

public class vanyaandlanterns {
	
	static int n;
	
	public static void main(String[] args) throws IOException {
		
		//im dumb
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		double l = Integer.parseInt(st.nextToken());
		double[] lamps = new double[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i  < n; i++) {
			lamps[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(lamps);
		double ans = 0;
		ans = Math.max(lamps[0], (l - lamps[n - 1]));
		for(int i = 0; i < n - 1; i++) {
			double dist = lamps[i + 1] - lamps[i];
			//System.out.println(dist);
			ans = Math.max(ans, dist / 2);
		}
		System.out.println(ans);
	}
}
