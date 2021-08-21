//package rockpaperscissors;

import java.util.*;
import java.io.*;

public class rockpaperscissors {
	
	public static int maxRounds(int[] a, int[] b) {	//make a win as many rounds as possible
		int ans = 0;
		for(int i = 0; i < 3; i++) {
			ans += Math.min(a[i], b[(i + 1) % 3]);
		}
		return ans;
	}
	
	public static int minRounds(int[] a, int[] b) {	//make a tie or lose as many rounds as possible
		for(int i = 3; i < 6; i++) {
			int next = a[i % 3];
			if(b[i % 3] + b[(i - 1) % 3] <= next) {
				next -= b[i % 3] + b[(i - 1) % 3];
				return next;
			}
		}
		return 0;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1426E
		
		//wins are easy, just win alot. For losing, try to lose or tie.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] bob = new int[3]; 	//rock, scissors, paper
		int[] alice = new int[3];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < 3; i++) {
			alice[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < 3; i++) {
			bob[i] = Integer.parseInt(st.nextToken());
		}
		System.out.println(minRounds(alice, bob) + " " + maxRounds(alice, bob));
	}
}
