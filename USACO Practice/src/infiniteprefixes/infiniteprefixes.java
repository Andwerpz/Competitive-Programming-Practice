//package infiniteprefixes;

import java.util.*;
import java.io.*;

public class infiniteprefixes {
	public static void main(String[] args) throws IOException {
		
		//1295B
		
		//some advanced level heuristics right here
		//too many cheese
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		//int counter = 0;
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			int pointer = 0;
			char[] s = fin.readLine().toCharArray();
			TreeMap<Integer, Integer> dict = new TreeMap<Integer, Integer>();
			dict.put(0, 1);
			int diff = 0;
			for(int i = 0; i < n; i++) {
				pointer += s[i] == '1'? -1 : 1;
				dict.put(pointer, dict.getOrDefault(pointer, 0) + 1);
				if(i == n - 1) {
					diff = pointer;
				}
			}
			int min = dict.firstKey();
			int max = dict.lastKey();
			if(diff == 0) {
				//System.out.println("X: " + x);
				if(min <= x && max >= x) {
					fout.append("-1\n");
				}
				else {
					fout.append("0\n");
				}
			}
			else if(diff > 0) {
				//System.out.println("X: " + x);
				if(x > max) {
					//System.out.println(((Math.abs(x - max) / Math.abs(diff)) * Math.abs(diff)) + " Subtract");
					x -= ((Math.abs(x - max) / Math.abs(diff)) * Math.abs(diff));
					//System.out.println((Math.abs(x - max)) + " " + diff);
				}
				//System.out.println(x + " " + min + " " + max);
				int ans = 0;
				while(x >= min) {
					//System.out.println(x);
					if(x == diff) {
						ans --;
					}
					ans += dict.getOrDefault(x, 0);
					x -= diff;
				}
				fout.append(ans).append("\n");
			}
			else {
				//System.out.println("X: " + x);
				if(x < min) {
					x += (((min - x) / Math.abs(diff)) * Math.abs(diff));
					//System.out.println(-(((min - x) / diff) * diff));
				}
				//System.out.println(x + " " + min + " " + max);
				int ans = 0;
				while(x <= max) {
					if(x == diff) {
						ans --;
					}
					ans += dict.getOrDefault(x, 0);
					x -= diff;
				}
				fout.append(ans).append("\n");
			}
		}
		System.out.print(fout);
	}
}
