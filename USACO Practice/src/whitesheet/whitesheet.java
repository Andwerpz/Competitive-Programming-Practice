//package whitesheet;

import java.util.*;
import java.awt.Point;
import java.awt.Rectangle;
import java.io.*;

public class whitesheet {
	
	public static boolean contains(double x, double y, double[] rect) {
		if(x >= rect[0] && x <= rect[2] && y >= rect[1] && y <= rect[3]) {
			return true;
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1216C
		
		//just check the edges of the white sheet to see if it's poking out
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int[] sheet = new int[4];
		for(int i = 0; i < 4; i++) {
			sheet[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		double[] r1 = new double[4];
		double[] r2 = new double[4];
		for(int i = 0; i < 4; i++) {
			r1[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < 4; i++) {
			r2[i] = Integer.parseInt(st.nextToken());
		}
		boolean isValid = false;
		for(double i = sheet[0]; i <= sheet[2]; i += 0.5d) {
			//System.out.println(i + " " + sheet[1] + ", " + i + " " + sheet[3]);
			if((!contains(i, sheet[1], r1) && !contains(i, sheet[1], r2)) || (!contains(i, sheet[3], r1) && !contains(i, sheet[3], r2))) {
				isValid = true;
				break;
			}
		}
		for(double i = sheet[1]; i <= sheet[3]; i += 0.5d) {
			//System.out.println(sheet[0] + " " + i + ", " + sheet[2] + " " + i);
			if((!contains(sheet[0], i, r1) && !contains(sheet[0], i, r2)) || (!contains(sheet[2], i, r1) && !contains(sheet[2], i, r2))) {
				isValid = true;
				break;
			}
		}
		System.out.println(isValid? "YES" : "NO");
	}
}
