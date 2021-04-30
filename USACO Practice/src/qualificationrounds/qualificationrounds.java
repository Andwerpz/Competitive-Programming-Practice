package qualificationrounds;

import java.util.*;
import java.io.*;

public class qualificationrounds {
	
	public static int simpleSolution(boolean[][] teams) {	//return 1 if YES, return 2 if NO, return 0 if INDECISIVE
		boolean[] check = new boolean[4];
		boolean[][] oneKnown = new boolean[4][5];	//first 4 for the state, and last for the true indication
		for(int i = 0; i < teams.length; i++) {
			boolean unknown = true;
			for(int j = 0; j < 4; j++) {
				check[j] = teams[j][i] && check[j];
				if(teams[j][i]) {
					unknown = false;
				}
			}
			if(unknown) {
				return 1;
			}
		}
		for(int i = 0; i < 4; i++) {
			if(check[i]) {
				return 2;
			}
		}
		return 0;
	}
	
	public static void main(String[] args) throws IOException {
		
		//probably a 1-0 dp question, nope
		//in the event that less than 4 teams are present, we just fill in the rest of the columns with 0's
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		boolean[][] teams = new boolean[k][n];	//does the kth team know the nth problem
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < 4; j++) {
				if(st.countTokens() != 0) {
					int next = Integer.parseInt(st.nextToken());
					if(next == 1) {
						teams[j][i] = true;
					}
					else {
						teams[j][i] = false;
					}
				}
				else {
					teams[j][i] = false;
				}
			}
		}
	}
}
