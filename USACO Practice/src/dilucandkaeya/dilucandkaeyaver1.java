package dilucandkaeya;

import java.util.*;
import java.io.*;

public class dilucandkaeyaver1 {
	public static void main(String[] args) throws IOException {
		
		//1536C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			char first = s[0];
			char second = s[0] == 'D'? 'K' : 'D';
			char prev = s[0];
			int a = 0;
			int b = 0;
			int c = 0;
			int d = 0;
			boolean firstRatio = true;
			boolean firstChar = true;
			int ratioCount = 0;
			for(int i = 0; i < n; i++) {
				if(firstChar) {
					if(s[i] == first) {
						a ++;
						fout.append(i + 1).append(" ");
					}
					else {
						firstChar = false;
						fout.append("1 ");
						b ++;
					}
				}
				else if(firstRatio) {
					if(s[i] == second){
						b ++;
					}
					else {
						c ++;
						firstRatio = false;
						ratioCount = 1;
					}
					fout.append("1 ");
				}
				else {
					if(s[i] == first) {
						if(a * d != b * c) {
							ratioCount = -1;
						}
						c = 1;
						d = 0;
						fout.append("1 ");
					}
					else {
						d ++;
						if(a * d == b * c && ratioCount != -1) {
							ratioCount ++;
							fout.append(ratioCount).append(" ");
						}
						else {
							fout.append("1 ");
						}
					}
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
