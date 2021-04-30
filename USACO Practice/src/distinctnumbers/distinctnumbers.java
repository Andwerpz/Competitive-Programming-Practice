//package distinctnumbers;

import java.util.*;
import java.io.*;

public class distinctnumbers {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		HashSet<Integer> dict = new HashSet<Integer>();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int ans = 0;
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			if(!dict.contains(next)) {
				dict.add(next);
				ans ++;
			}
		}
		System.out.println(ans);
	}
}
