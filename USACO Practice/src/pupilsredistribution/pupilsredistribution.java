//package pupilsredistribution;

import java.util.*;
import java.io.*;

public class pupilsredistribution {
	public static void main(String[] args) throws IOException {
		
		//779A
		
		//bingo sheet done lol
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] total = new int[5];
		int[] a = new int[5];
		int[] b = new int[5];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken()) - 1;
			total[next] ++;
			a[next] ++;
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken()) - 1;
			total[next] ++;
			b[next] ++;
		}
		boolean isValid = true;
		for(int i = 0; i < total.length; i++) {
			if(total[i] % 2 != 0) {
				isValid = false;
				break;
			}
		}
		if(isValid) {
			int ans = 0;
			for(int i = 0; i < total.length; i++) {
				ans += Math.abs(a[i] - (total[i] / 2));
			}
			System.out.println(ans / 2);
		}
		else {
			System.out.println("-1");
		}
	}
}
