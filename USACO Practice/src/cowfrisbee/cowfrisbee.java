//package cowfrisbee;

import java.util.*;
import java.io.*;

public class cowfrisbee {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long ans = 0;
		StringTokenizer st = new StringTokenizer(fin.readLine());
		Stack<int[]> s = new Stack<int[]>();
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			while(s.size() != 0 && s.peek()[0] < next) {
				ans += Math.abs(i - s.peek()[1]) + 1;
				s.pop();
			}
			if(s.size() != 0) {
				ans += Math.abs(i - s.peek()[1]) + 1;
			}
			s.add(new int[] {next, i});
		}
		System.out.println(ans);
	}
}
