//package gamewithchips;

import java.util.*;
import java.io.*;

public class gamewithchips {
	public static void main(String[] args) throws IOException {
		
		//1327C
		
		//sweep up all of the chips into one corner, and then sweep them all around the board, visiting every cell.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int m = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		StringBuilder fout = new StringBuilder();
		int ans = 0;
		for(int i = 0; i < n - 1; i++) {
			ans ++;
			fout.append("R");
		}
		for(int i = 0; i < m - 1; i++) {
			ans ++;
			fout.append("U");
		}
		boolean down = true;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m - 1; j++) {
				ans ++;
				fout.append(down? "D" : "U");
			}
			ans ++;
			fout.append("L");
			down = !down;
		}
		System.out.println(ans);
		System.out.println(fout);
	}
}
