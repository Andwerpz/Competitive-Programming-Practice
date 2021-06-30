package ticketgame;

import java.util.*;
import java.io.*;

public class ticketgame {
	
	public boolean minimize(int[] a, int[] b) {
		
	}
	
	public boolean maximize(int[] a, int[] b) {
		
	}
	
	public static void main(String[] args) throws IOException {
		
		//1215D
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		int[] first = new int[2];
		int[] last = new int[2];
		for(int i = 0; i < n; i++) {
			if(i < n / 2) {
				if(s[i] == '?') {
					first[1] ++;
				}
				else {
					first[0] += s[i] - '0';
				}
			}
			else {
				if(s[i] == '?') {
					last[1] ++;
				}
				else {
					last[0] += s[i] - '0';
				}
			}
		}
		
	}
}
