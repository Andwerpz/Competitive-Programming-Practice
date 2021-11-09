package cookingconundrums1;

import java.util.*;
import java.io.*;

public class cookingconundrums1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int first = Integer.parseInt(st.nextToken());
		int sum = first;
		int max = first;
		for(int i = 1; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			sum = Math.max(next + sum, next);
			max = Math.max(max, sum);
		}
		System.out.println(max);
	}
}
