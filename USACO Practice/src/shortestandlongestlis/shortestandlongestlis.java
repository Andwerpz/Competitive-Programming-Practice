//package shortestandlongestlis;

import java.util.*;
import java.io.*;

public class shortestandlongestlis {
	public static void main(String[] args) throws IOException {
		
		//1304D
		
		//when making the largest lis, you want to start at the bottom, and make sure that all of your increasing segments can "link up". Do the reverse when making the shortest lis, by starting at the top
		//and separating all of your increasing segments.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			char[] s = st.nextToken().toCharArray();
			char prev = s[0];
			int counter = 0;
			boolean increasingFirst = s[0] == '<';
			boolean inc = false;
			ArrayList<Integer> groups = new ArrayList<Integer>();
			for(int i = 0; i < n - 1; i++) {
				if(s[i] != prev) {
					groups.add(counter);
					counter = 0;
					prev = s[i];
				}
				counter ++;
			}
			groups.add(counter);
			inc = increasingFirst;
			int pointer = n;
			//System.out.println(groups);
			for(int i = 0; i < groups.size(); i++) {
				if(!inc && i != groups.size() - 1) {
					int cur = groups.get(i);
					int next = groups.get(i + 1);
					if(i == 0) {
						cur ++;
					}
					for(int j = 0; j < cur - 1; j++) {
						fout.append(pointer).append(" ");
						pointer --;
					}
					pointer -= (next);
					fout.append(pointer).append(" ");
				}
				else if(!inc && i == groups.size() - 1) {
					int cur = groups.get(i);
					if(i == 0) {
						cur ++;
					}
					for(int j = 0; j < cur; j++) {
						fout.append(pointer).append(" ");
						pointer --;
					}
				}
				else {
					//System.out.println(pointer);
					int cur = groups.get(i);
					int lowPointer = pointer;
					if(i == 0) {
						cur ++;
						lowPointer = n - cur;
					}
					pointer = lowPointer + 1;
					for(int j = 0; j < cur; j++) {
						fout.append(pointer).append(" ");
						pointer ++;
					}
					pointer = lowPointer;
					if(i != 0) {
						pointer --;
					}
				}
				inc = !inc;
			}
			fout.append("\n");
			inc = increasingFirst;
			pointer = 1;
			for(int i = 0; i < groups.size(); i++) {
				if(inc && i != groups.size() - 1) {
					int cur = groups.get(i);
					int next = groups.get(i + 1);
					if(i == 0) {
						cur ++;
					}
					for(int j = 0; j < cur - 1; j++) {
						fout.append(pointer).append(" ");
						pointer ++;
					}
					pointer += (next);
					fout.append(pointer).append(" ");
				}
				else if(inc && i == groups.size() - 1) {
					int cur = groups.get(i);
					if(i == 0) {
						cur ++;
					}
					for(int j = 0; j < cur; j++) {
						fout.append(pointer).append(" ");
						pointer ++;
					}
				}
				else {
					//System.out.println(pointer);
					int cur = groups.get(i);
					int lowPointer = pointer;
					if(i == 0) {
						cur ++;
						lowPointer = cur + 1;
					}
					pointer = lowPointer - 1;
					for(int j = 0; j < cur; j++) {
						fout.append(pointer).append(" ");
						pointer --;
					}
					pointer = lowPointer;
					if(i != 0) {
						pointer ++;
					}
				}
				inc = !inc;
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
