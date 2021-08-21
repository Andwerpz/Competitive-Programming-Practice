//package maximizetheremainingstring;

import java.util.*;
import java.io.*;

public class maximizetheremainingstring {
	public static void main(String[] args) throws IOException {
		
		//1506G
		
		//very greedy problem
		
		//the solution is to first maximize the first letter, then the second, then third, and so on. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			ArrayList<Character> ans = new ArrayList<Character>();
			int[] num = new int[26];
			for(int i = 0; i < s.length; i++) {
				num[s[i] - 'a'] ++;
			}
			HashSet<Character> v = new HashSet<Character>();
			int pointer = 0;
			char prevMax = 0;
			int maxIndex = -1;
			while(pointer != s.length) {
				char next = s[pointer];
				if(v.contains(next)) {
					pointer ++;
					continue;
				}
				if(prevMax < next) {
					prevMax = next;
					maxIndex = pointer;
				}
				num[next - 'a'] --;
				if(num[next - 'a'] == 0) {
					ans.add(prevMax);
					v.add(prevMax);
					prevMax = 0;
					for(int j = pointer; j > maxIndex; j--) {
						num[s[j] - 'a'] ++;
					}
					pointer = maxIndex;
				}
				pointer ++;
			}
			for(char i : ans) {
				fout.append(i);
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
