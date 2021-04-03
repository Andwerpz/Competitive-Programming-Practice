//package snacktower;

import java.util.*;
import java.io.*;

public class snacktower {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		boolean[] nums = new boolean[n];
		int pointer = n - 1;
		StringTokenizer st = new StringTokenizer(fin.readLine());
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken()) - 1;
			nums[next] = true;
			while(pointer >= 0 && nums[pointer]) {
				fout.append((pointer + 1) + " ");
				pointer --;
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
