//package johnnyandhishobbies;

import java.util.*;
import java.io.*;

public class johnnyandhishobbies {
	public static void main(String[] args) throws IOException {
		
		//1362B
		
		//you just have to try every value of k from 1 - 1023. If a value of k is valid, then for each number, s, there must be another number that is equal to s xor k
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			HashSet<Integer> dict = new HashSet<Integer>();
			for(int i = 0; i < n; i++) {
				dict.add(Integer.parseInt(st.nextToken()));
			}
			boolean isValid = false;
			int ans = 0;
			for(int i = 1; i < 1024; i++) {
				boolean curValid = true;
				for(int j : dict) {
					if(!dict.contains(j ^ i)) {
						curValid = false;
						break;
					}
				}
				if(curValid) {
					isValid = true;
					ans = i;
					break;
				}
			}
			fout.append(isValid? ans : -1).append("\n");
		}
		System.out.print(fout);
	}
}
