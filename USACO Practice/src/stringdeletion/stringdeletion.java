//package stringdeletion;

import java.util.*;
import java.io.*;

public class stringdeletion {
	public static void main(String[] args) throws IOException {
		
		//1430D
		
		//first notice that you can simplify the problem from a string of 1s and 0s to a bunch of segments containing a number of 1s and 0s. 
		//Then notice that it is better when doing the first step of the operation, to remove the digit from a segment containing more than 1 
		//1 or 0. This is because in order to do the most operations, we need to have as many segments as possible, because the second part of the operation 
		//removes one segment from the beginning. The final observation is that we have to remove the digits from the segments that are closest
		//to the beginning of the string. This is because they will be the first to get deleted, so we want to use them while we can.
		//the solution is to just simulate it, and return the answer.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			ArrayList<Integer> segments = new ArrayList<Integer>();
			char prev = 'x';
			for(int i = 0; i < n; i++) {
				if(s[i] != prev) {
					prev = s[i];
					segments.add(0);
				}
				segments.set(segments.size() - 1, segments.get(segments.size() - 1) + 1);
			}
			int pointer = 0;
			int ans = 0;
			for(int i = 0; i < segments.size(); i++) {
				while(pointer < segments.size() && (pointer < i || segments.get(pointer) <= 1)) {
					pointer ++;
				}
				//System.out.println("POINTER : " + pointer + " ITERATION: " + i);
				if(pointer == segments.size()) {
					//System.out.println("BREAK : " + (segments.size() - i));
					ans += (segments.size() - i) / 2 + ((segments.size() - i) % 2 == 1? 1 : 0);
					break;
				}
				else {
					segments.set(pointer, segments.get(pointer) - 1);
					ans ++;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
