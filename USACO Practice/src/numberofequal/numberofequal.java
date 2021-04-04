//package numberofequal;

import java.util.*;
import java.io.*;

public class numberofequal {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			dict.put(next, dict.getOrDefault(next, 0) + 1);
		}
		st = new StringTokenizer(fin.readLine());
		long ans = 0;
		for(int i = 0; i < m; i++) {
			ans += dict.getOrDefault(Integer.parseInt(st.nextToken()), 0);
		}
		System.out.println(ans);
	}
}
