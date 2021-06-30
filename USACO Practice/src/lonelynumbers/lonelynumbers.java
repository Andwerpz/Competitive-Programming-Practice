//package lonelynumbers;

import java.util.*;
import java.io.*;

public class lonelynumbers {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		boolean[] sieve = new boolean[1000001];
		int[] pfx = new int[1000001];
		for(int i = 2; i < sieve.length; i++) {
			if(!sieve[i]) {
				pfx[i] ++;
				int index = i * 2;
				while(index < sieve.length) {
					sieve[index] = true;
					index += i;
				}
			}
			pfx[i] += pfx[i - 1];
		}
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < t; i++) {
			int next = Integer.parseInt(st.nextToken());
			int low = (int) Math.floor(Math.sqrt(next));
			//System.out.println(low + " " + next);
			fout.append((pfx[next] - pfx[low]) + 1).append(" ");
		}
		System.out.println(fout);
	}
}
