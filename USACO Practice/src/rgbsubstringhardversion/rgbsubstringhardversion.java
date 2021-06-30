//package rgbsubstringhardversion;

import java.util.*;
import java.io.*;

public class rgbsubstringhardversion {
	public static void main(String[] args) throws IOException {
		
		//1196D2
		
		//you can just test the similarity of the string with each infinite string. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		char[][] base = new char[3][3];
		base[0] = new char[] {'R', 'G', 'B'};
		base[1] = new char[] {'G', 'B', 'R'};
		base[2] = new char[] {'B', 'R', 'G'};
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			char[] s = fin.readLine().toCharArray();
			int min = Integer.MAX_VALUE;
			for(int i = 0; i < 3; i++) {
				int[] pfx = new int[n];
				for(int j = 0; j < n; j++) {
					if(s[j] != base[i][j % 3]) {
						pfx[j] ++;
					}
					pfx[j] += j == 0? 0 : pfx[j - 1];
					//System.out.print(pfx[j] + " ");
				}
				//System.out.println();
				for(int j = 0; j < n; j++) {
					if(j + k - 1 == n) {
						break;
					}
					min = Math.min(min, pfx[j + k - 1] - (j == 0? 0 : pfx[j - 1]));
					//System.out.println(pfx[j + k - 1] - (j == 0? 0 : pfx[j - 1]));
				}
			}
			fout.append(min).append("\n");
		}
		System.out.print(fout);
	}
}
