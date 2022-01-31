//package searchingforsoulmates;

import java.util.*;
import java.io.*;

public class searchingforsoulmates {
	public static void main(String[] args) throws IOException {
		
		//USACO Silver 2022 Feb
		
		//first notice that the more you divide, the more +1 is worth, since you multiply it back up. 
		
		//the answer is to try every level of division, and construct the answer from there
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long a = Long.parseLong(st.nextToken());
			long b = Long.parseLong(st.nextToken());
			long ans = 0;
			while(a > b) {
				if(a % 2 == 1) {
					a ++;
					ans ++;
				}
				a /= 2;
				ans ++;
			}
			while(a * 2 <= b) {
				a *= 2;
				ans --;
			}
			//System.out.println(a + " " + b + " " + ans);
			long min = Long.MAX_VALUE;
			long depth = 0;
			outer:
			while(true) {
				long curAns = 0;
				long cur = a;
				for(int i = 0; i < depth; i++) {
					if(cur == 1) {
						break outer;
					}
					if(cur % 2 == 1) {
						cur ++;
						curAns ++;
					}
					cur /= 2;
					curAns ++;
				}
				long projected = cur;
				long amt = 0;
				while(projected * 2 <= b) {
					projected *= 2;
					amt ++;
				}	
				long pow = (long) Math.pow(2, amt);
				//System.out.println(projected + " " + pow + " " + cur);
				for(int i = 0; i <= amt; i++) {
					long diff = b - projected;
					curAns += diff / pow;
					projected += diff - (diff % pow);
					pow /= 2;
				}
				//System.out.println(cur + " " + amt + " " + curAns);
				curAns += amt;
				depth ++;
				min = Math.min(min, curAns);
			}
			//System.out.println(min);
			fout.append(ans + min).append("\n");
		}
		System.out.print(fout);
	}
}
