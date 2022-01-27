//package ancientcivilization;

import java.util.*;
import java.io.*;

public class ancientcivilization {
	public static void main(String[] args) throws IOException {
		
		//1625A
		
		//each bit is independent from all other bits. This means that for each bit of the original word, you can minimize the difference
		//from that bit to all other observed words. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int l = Integer.parseInt(st.nextToken());
			char[][] s = new char[n][];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				String nextS = Integer.toBinaryString(next);
				while(nextS.length() < l) {
					nextS = "0" + nextS;
				}
				s[i] = nextS.toCharArray();
				//System.out.println(nextS);
			}
			int ans = 0;
			int pow = 1;
			for(int i = l - 1; i >= 0; i--) {
				int one = 0;
				int zero = 0;
				for(int j = 0; j < n; j++) {
					if(s[j][i] == '0') {
						zero ++;
					}
					else {
						one ++;
					}
				}
				if(one >= zero) {
					ans += pow;
				}
				pow *= 2;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
