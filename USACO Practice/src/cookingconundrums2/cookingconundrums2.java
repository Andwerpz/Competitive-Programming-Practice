package cookingconundrums2;

import java.util.*;
import java.io.*;

public class cookingconundrums2 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int sum = 0;
		int max = 0;
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			sum = Math.max(next + sum, next);
			max = Math.max(max, sum);
		}
		System.out.println(max);
	}
}
