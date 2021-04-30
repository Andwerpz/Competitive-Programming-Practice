//package diamondminer;

import java.util.*;
import java.io.*;

public class diamondminer {
	public static void main(String[] args) throws IOException {
		
		//sort the miners and the diamonds by distance from the origin. 
		//pair the miners that are closest to the origin with diamonds that are the closest to the origin, and so on
		
		//if you take the absolute value of all the coordinates, the answer becomes clear
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] miners = new int[n];
			int[] diamonds = new int[n];
			int mineCount = 0;
			int diamondCount = 0;
			for(int i = 0; i < n * 2; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				int next = Integer.parseInt(st.nextToken());
				if(next == 0) {
					miners[mineCount] = Math.abs(Integer.parseInt(st.nextToken()));
					mineCount ++;
				}
				else {
					diamonds[diamondCount] = Math.abs(next);
					diamondCount ++;
				}
			}
			double sum = 0;
			Arrays.sort(miners);
			Arrays.sort(diamonds);
			for(int i = 0; i < n; i++) {
				sum += Math.sqrt(Math.pow(miners[i], 2) + Math.pow(diamonds[i], 2));
			}
			fout.append(sum).append("\n");
		}
		System.out.print(fout);
	}
}
