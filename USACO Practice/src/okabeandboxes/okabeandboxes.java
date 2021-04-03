//package okabeandboxes;

import java.util.*;
import java.io.*;

public class okabeandboxes {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int removeNext = 1;
		int ans = 0;
		Stack<Integer> s = new Stack<Integer>();
		for(int i = 0; i < n * 2; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			String type = st.nextToken();
			if(type.equals("add")) {
				int next = Integer.parseInt(st.nextToken());
				s.add(next);
			}
			else {
				if(s.size() != 0 && removeNext != s.peek()) {
					s = new Stack<Integer>();
					ans++;
				}
				if(s.size() != 0) {
					s.pop();
				}
				removeNext++;
			}
		}
		System.out.println(ans);
	}
}
