package cookingconundrums3;

import java.util.*;
import java.io.*;

public class cookingconundrums3 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int sum = 0;
		int min = 0;
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			sum = Math.min(next + sum, next);
			min = Math.min(min, sum);
		}
		System.out.println(min);
	}
}
