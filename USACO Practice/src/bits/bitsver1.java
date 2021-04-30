//package bits;

import java.util.*;
import java.io.*;

public class bitsver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		//System.out.println();
		while(n-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long l = Long.parseLong(st.nextToken());
			long r = Long.parseLong(st.nextToken());
			long temp = l;
			//int ans = 0;
			boolean[] bin = new boolean[60];	//log2(10 ^ 18) + 1; enough to represent a long in binary
			while(l != 0) {
				int next = (int) Math.floor(Math.log(l) / Math.log(2));
				bin[next] = true;
				l -= (long) Math.pow(2, next);
				//System.out.print((long) Math.pow(2, next) + " ");
				//ans ++;
			}
			
			l = temp;
			for(int i = 0; i < bin.length; i++) {	//first finding out the greatest amount of bits possible, and the smallest of them
				if(!bin[i]) {
					l += (long) Math.pow(2, i);	//cant forget to use longs
					if(l > r) {
						l -= (long) Math.pow(2, i);
						break;
					}
				}
			}
			
			fout.append(l).append("\n");
		}
		System.out.print(fout);
	}
}
