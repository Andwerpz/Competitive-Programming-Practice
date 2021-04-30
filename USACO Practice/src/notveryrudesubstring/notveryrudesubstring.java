//package notveryrudesubstring;

import java.util.*;
import java.io.*;

public class notveryrudesubstring {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long c = Long.parseLong(st.nextToken());
		char[] s = fin.readLine().toCharArray();
		long numA = 0;
		long numB = 0;
		long totB = 0;
		int low = 0;
		int max = 1;
		long totalRudeness = 0;
		for(int i = 0; i < n; i++) {
			if(s[i] == 'a') {
				numA ++;
			}
			else if(s[i] == 'b') {
				totB ++;
				totalRudeness += numA;
			}
			while(low < n && totalRudeness > c) {
				if(s[low] == 'a') {
					numA --;
					totalRudeness -= totB;
				}
				else if(s[low] == 'b') {
					totB --;
				}
				low++;
			}
			if(i - low + 1 > max) {
				max = i - low + 1;
			}
		}
		System.out.println(max);
	}
}
