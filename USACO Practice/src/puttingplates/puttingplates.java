//package puttingplates;

import java.util.*;
import java.io.*;

public class puttingplates {
	
	public static int getAns(int h, int w) {
		int curAns = 0;
		if(h % 2 == 1) {
			curAns += ((h / 2) + 1) * 2;
			curAns += (((w - 4) / 2) + ((w - 4) % 2 == 1? 1 : 0)) * 2;
		}
		else {
			curAns += (h / 2) * 2;
			curAns += ((w - 4) / 2) + ((w - 4) % 2 == 1? 1 : 0);
			if(w % 2 == 0) {
				curAns += w / 2 - 1;
			}
			else {
				curAns += w / 2;
			}
		}
		return curAns;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1530B
		
		//just fill up the top and bottom. Then put as many plates as you can in the left and right.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int h = Integer.parseInt(st.nextToken());
			int w = Integer.parseInt(st.nextToken());
			int[][] table = new int[h][w];
			for(int i = 0; i < w; i += 2) {
				table[0][i] = 1;
				table[h - 1][i] = 1;
			}
			for(int i = 2; i < h - 2; i += 2) {
				table[i][0] = 1;
				table[i][w - 1] = 1;
			}
			for(int[] i : table) {
				for(int j : i) {
					fout.append(j).append("");
				}
				fout.append("\n");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
