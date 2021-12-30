//package bastring;

import java.util.*;
import java.io.*;

public class bastring {
	public static void main(String[] args) throws IOException {
		
		//1620C
		
		//simple base conversion problem. You just need to represent x in the base given by the ab string. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			long k = Integer.parseInt(st.nextToken());
			long x = Long.parseLong(st.nextToken()) - 1;
			String s = fin.readLine();
			boolean hasA = false;
			ArrayList<Long> sequence = new ArrayList<Long>();
			char prev = 'a';
			for(int i = 0; i < s.length(); i++) {
				char c = s.charAt(i);
				if(c == '*') {
					if(prev == 'a') {
						sequence.add(k);
					}
					else {
						sequence.set(sequence.size() - 1, sequence.get(sequence.size() - 1) + k);
					}
				}
				prev = c;
				if(c == 'a') {
					hasA = true;
				}
			}
			if(!hasA) {
				x ++;
			}
			//System.out.println(sequence);
			ArrayList<Long> ans = new ArrayList<Long>();
			for(int i = 0; i < sequence.size(); i++) {
				ans.add((long) 0);
			}
			long mult = 1;
			int index = 0;
			outer:
			for(int i = sequence.size() - 1; i >= 0; i--) {
				//System.out.println(mult);
				long count = 1;
				while(count <= sequence.get(i) + 1) {
					if(mult * count > x) {
						index = i;
						break outer;
					}
					count ++;
				}
				mult *= sequence.get(i) + 1;
			}
			//System.out.println("IN:" + index + " " + x);
			for(int i = index; i < sequence.size(); i++) {
				//System.out.println(i + " " + (x / mult));
				ans.set(i, x / mult);
				x %= mult;
				if(i != sequence.size() - 1) {
					mult /= sequence.get(i + 1) + 1;
				}
			}
			//System.out.println(ans);
			int counter = 0;
			outer:
			for(int i = 0; i < s.length(); i++) {
				char c = s.charAt(i);
				if(c == '*') {
					while(s.charAt(i) == '*') {
						i ++;
						if(i == s.length()) {
							break;
						}
					}
					i--;
					for(long j = 0; j < ans.get(counter); j++) {
						fout.append("b");
					}
					counter ++;
				}
				else {
					fout.append("a");
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
