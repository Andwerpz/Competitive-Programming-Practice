//package azamonwebservices;

import java.util.*;
import java.io.*;

public class azamonwebservices {
	public static void main(String[] args) throws IOException {
		
		//1281B
		
		//first figure out what the minimum string you can make s into by just moving around the characters. Then go down the line, and find the first character in s
		//that isn't sorted in accordance to the minimum. Replace that character with the last appropriate value in the string s, and check whether the new s is
		//less than c.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			char[] s = st.nextToken().toCharArray();
			char[] c = st.nextToken().toCharArray();
			char[] sSorted = String.valueOf(s).toCharArray();
			Arrays.sort(sSorted);
			char lowest = 'Z';
			for(int i = 0; i < s.length; i++) {
				if(s[i] < lowest) {
					lowest = s[i];
				}
			}
			char notLowest = 'a';
			int notLowestIndex = 0;
			for(int i = 0; i < s.length; i++) {
				if(s[i] != sSorted[i]) {
					notLowest = s[i];
					notLowestIndex = i;
					break;
				}
			}
			if(notLowest != 'a') {
				char min = s[notLowestIndex];
				int minIndex = notLowestIndex;
				for(int i = notLowestIndex; i < s.length; i++) {
					if(s[i] <= min) {
						min = s[i];
						minIndex = i;
					}
				}
				s[minIndex] = notLowest;
				s[notLowestIndex] = min;
			}
			
			//System.out.println(String.valueOf(s) + " " + String.valueOf(c));
			boolean lexographicallyGreater = true;
			for(int i = 0; i < s.length; i++) {
				if(i == c.length) {
					lexographicallyGreater = false;
					break;
				}
				if(s[i] < c[i]) {
					break;
				}
				else if(s[i] > c[i]) {
					lexographicallyGreater = false;
					break;
				}
			}
			if(String.valueOf(s).equals(String.valueOf(c))) {
				lexographicallyGreater = false;
			}
			if(lexographicallyGreater) {
				fout.append(String.valueOf(s)).append("\n");
			}
			else {
				fout.append("---\n");
			}
		}
		System.out.print(fout);
	}
}
