//package animpassionedcirculationofaffection;

import java.util.*;
import java.io.*;

public class animpassionedcirculationofaffectionver3 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		String s = fin.readLine();
		int q = Integer.parseInt(fin.readLine());
		int[][] key = new int[26][s.length() + 1];
		for(char c = 'a'; c <= 'z'; c++) {
			//System.out.println("doing character: " + c);
			int count = c - 97;
			for(int i = 0; i < n; i++) {
				//System.out.println("with " + i);
				int replaceCount = 0;
				for(int j = i; j < n; j++) {
					if(s.charAt(j) != c) {
						replaceCount ++;
					}
					key[count][replaceCount] = Math.max(key[count][replaceCount], j - i + 1);
					//System.out.print("(" + key[count][replaceCount] + " " + (replaceCount) + ")");
				}
				//System.out.println();
			}
			for(int i = 1; i < n; i++) {
				key[count][i] = Math.max(key[count][i], key[count][i - 1]);
			}
		}
		
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < q; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int amt = Integer.parseInt(st.nextToken());
			char c = st.nextToken().charAt(0);
			if(amt >= n) {
				fout.append(n).append("\n");
			}
			else {
				fout.append(key[c - 97][amt]).append("\n");
			}
		}
		System.out.print(fout);
	}
}
