package vanyaandlanterns;

import java.util.*;
import java.io.*;

public class vanyaandlanternsver1 {
	
	static double[] lamps;
	
	public static boolean isValid(double range, double l) {
		if(lamps[0] - range > 0) {
			return false;
		}
		if(lamps[lamps.length - 1] + range < l) {
			return false;
		}
		for(int i = 0; i < lamps.length - 1; i++) {
			if(lamps[i + 1] - lamps[i] > range * 2) {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int l = Integer.parseInt(st.nextToken());
		lamps = new double[(int) n];
		//st = new StringTokenizer(fin.readLine());
		for(int i = 0; i  < n; i++) {
			lamps[i] = Integer.parseInt(fin.readLine());
		}
		Arrays.sort(lamps);
		double high = l;
		double low = 0;
		double mid = low + (high - low) / 2;
		while(high - low > Math.pow(10, -9)) {
			System.out.println(low + " " + high + " " + mid);
			if(isValid(mid, l)) {
				high = mid;
			}
			else {
				low = mid;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(high);
	}
}
