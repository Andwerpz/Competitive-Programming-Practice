//package game;

import java.util.*;
import java.io.*;

public class game {
	public static void main(String[] args) throws IOException {
		
		//1649A
		
		//notice that if there exists a tile with a '0', then you have to use the one jump operation
		//you have to jump over it. 
		
		//so the optimal solution is:
		//if no 0 exists, then you can spend 0 coins. 
		//else, you must jump from the tile before the first 0 to the tile after the last 0. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			boolean hasZero = false;
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				if(nums[i] == 0) {
					hasZero = true;
				}
			}
			if(!hasZero) {
				fout.append("0\n");
				continue;
			}
			int l = 0;
			int r = n - 1;
			while(nums[l + 1] == 1) {
				l ++;
			}
			while(nums[r - 1] == 1) {
				r --;
			}
			fout.append(r - l).append("\n");
		}
		System.out.print(fout);
	}
}
