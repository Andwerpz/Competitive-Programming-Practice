//package paralleluniverseseasy;

import java.util.*;
import java.io.*;

public class paralleluniverseeasy {
	public static void main(String[] args) throws IOException {
		
		//1184D1
		
		//you just have to implement the situation described in the problem statement. You don't have to be smart about it, you can even simulate it
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int t = Integer.parseInt(st.nextToken());
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < t; i++) {
			st = new StringTokenizer(fin.readLine());
			int type = Integer.parseInt(st.nextToken());
			int next = Integer.parseInt(st.nextToken());
			if(type == 0) {
				if(next >= k) {
					n = next;
				}
				else {
					n -= next;
					k -= next;
				}
			}
			else {
				n ++;
				if(next - 1 < k) {
					k ++;
				}
			}
			fout.append(n + " " + k + "\n");
		}
		System.out.print(fout);
	}
}
