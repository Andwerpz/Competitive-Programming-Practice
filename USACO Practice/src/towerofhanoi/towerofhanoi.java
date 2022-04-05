//package towerofhanoi;

import java.util.*;
import java.io.*;

public class towerofhanoi {
	
	static StringBuilder fout = new StringBuilder();
	static HashMap<Integer, Integer> loc;
	
	public static void move(int which, int dest) {
		int from = loc.get(which);
		if(which == 1) {
			fout.append(from).append(" ").append(dest).append("\n");
			loc.put(which, dest);
			return;
		}
		int mid = 0;
		for(int i = 1; i <= 3; i++) {
			if(i != from && i != dest) {
				mid = i;
				break;
			}
		}
		move(which - 1, mid);
		fout.append(from).append(" ").append(dest).append("\n");
		loc.put(which, dest);
		move(which - 1, dest);
	}
	
	public static void main(String[] args) throws IOException {
		
		//CSES 2615
		
		//simple recursion problem; the optimal solution will always get 2^n - 1 moves.
		
		//label the disks by size; 1 being the smallest and n being the largest.
		
		//the function move(which, dest) will attempt to move the disk labeled which and all disks above it to the pole dest. 
		
		//if which == 1, then we can go ahead and move it
		
		//else, we must move which - 1 to the pole that is not dest or the initial location of which. Once we do so, move which to 
		//dest, and then move back the pile initially above which to dest. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		loc = new HashMap<Integer, Integer>();
		for(int i = 1; i <= n; i++) {
			loc.put(i, 1);
		}
		move(n, 3);
		System.out.println((int) Math.pow(2, n) - 1);
		System.out.print(fout);
	}
}
