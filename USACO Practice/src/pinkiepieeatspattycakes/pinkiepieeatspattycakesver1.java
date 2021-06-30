package pinkiepieeatspattycakes;

import java.util.*;
import java.io.*;

public class pinkiepieeatspattycakesver1 {
	
	public static boolean isValid(int val) {
		
	}
	
	public static void main(String[] args) throws IOException {
		
		//1393C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			
		}
	}
}
