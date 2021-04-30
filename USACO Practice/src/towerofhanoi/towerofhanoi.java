package towerofhanoi;

import java.util.*;
import java.io.*;

public class towerofhanoi {
	
	public void solve()
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int[][] cost = new int[3][3];
		for(int i = 0; i < 3; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < 3; j++) {
				cost[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		int n = Integer.parseInt(fin.readLine());
		
	}
}
