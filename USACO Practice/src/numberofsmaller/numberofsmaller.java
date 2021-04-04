//package numberofsmaller;

import java.util.*;
import java.io.*;

public class numberofsmaller {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] nArr = new int[n];
		int[] mArr = new int[m];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nArr[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < m; i++) {
			mArr[i] = Integer.parseInt(st.nextToken());
		}
		int a = 0;
		int b = 0;
		StringBuilder fout = new StringBuilder();
		while(b != m) {
			while(a < n && nArr[a] < mArr[b]) {
				a++;
			}
			fout.append(a).append(" ");
			b++;
		}
		System.out.println(fout.substring(0, fout.length() - 1));
	}
}
