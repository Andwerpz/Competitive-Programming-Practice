//package taymyriscallingyou;

import java.util.*;
import java.io.*;

public class taymyriscallingyou {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int z = Integer.parseInt(st.nextToken());
		boolean[] v = new boolean[z + 1];
		int pointer = 1;
		while(pointer * n <= z) {
			v[pointer * n] = true;
			pointer ++;
		}
		int ans = 0;
		pointer = 1;
		while(pointer * m <= z) {
			if(v[pointer * m]) {
				ans ++;
			}
			pointer ++;
		}
		System.out.println(ans);
	}
}
