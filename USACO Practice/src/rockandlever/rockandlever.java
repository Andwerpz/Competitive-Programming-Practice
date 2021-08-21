//package rockandlever;

import java.util.*;
import java.io.*;

public class rockandlever {
	public static void main(String[] args) throws IOException {
		
		//1420B
		
		//all numbers with the same maximum bit satisfy the condition.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
			long ans = 0;
			for(int i = 0; i < n; i++) {
				int maxBit = 0;
				int next = Integer.parseInt(st.nextToken());
				for(int j = 30; j >= 0; j--) {
					if(((1 << j) | next) == next) {
						//System.out.println((1 << j));
						maxBit = j;
						break;
					}
				}
				ans += dict.getOrDefault(maxBit, 0);
				dict.put(maxBit, dict.getOrDefault(maxBit, 0) + 1);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
