//package imboredwithlife;

import java.util.*;
import java.io.*;

public class imboredwithlife {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		int which = Math.min(a, b);
		int ans = 1;
		for(int i = 1; i <= which; i++) {
			ans *= i;
		}
		System.out.println(ans);
	}
}
