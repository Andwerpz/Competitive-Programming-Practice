//package gaspipeline;

import java.util.*;
import java.io.*;

public class gaspipeline {
	public static void main(String[] args) throws IOException {
		
		//not dumb solution
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long n = Integer.parseInt(st.nextToken());
			long a = Integer.parseInt(st.nextToken());
			long b = Integer.parseInt(st.nextToken());
			char[] s = fin.readLine().toCharArray();
			long sum = b;	//first pillar.
			boolean intersectionExists = false;
			for(int i = 0; i < n; i++) {
				if(s[i] == '1') {
					intersectionExists = true;
					break;
				}
			}
			if(intersectionExists) {
				int pointer = 0;
				while(true) {	//before the first intersection
					if(s[pointer] == '1') {
						break;
					}
					sum += a + b;
					pointer ++;
				}
				sum += 2 * a + 2 * b;
				boolean high = false;
				while(true) {
					if(s[pointer] == '1') {
						sum += (2 * b + a);
						pointer ++;
					}
					else {
						int scout = pointer;
						boolean done = false;
						while(s[scout] == '0') {
							if(scout == n - 1) {
								done = true;
								break;
							}
							scout ++;
						}
						if(done) {
							break;
						}
						long highSum = (2 * b + a) * (scout - pointer);
						long lowSum = (b + a) * (scout - pointer - 2) + 3 * b + 4 * a;
						sum += Math.min(highSum, lowSum);
						pointer = scout;
					}
				}
				sum += b + 2 * a;
				pointer ++;
				sum += (a + b) * (n - 1 - pointer);
			}
			else {
				sum = (a + b) * n + b;
			}
			
			fout.append(sum).append("\n");
		}
		System.out.print(fout);
	}
}
