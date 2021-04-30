package agagaxooorrr;

import java.util.*;
import java.io.*;

public class agagaxooorrrver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int a = nums[0];
			for(int i = 1; i < n; i++) {
				System.out.println(a);
				a ^= nums[i];
			}
			fout.append(a == 0? "YES" : "NO").append("\n");
		}
		System.out.print(fout);
	}
}
